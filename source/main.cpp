// Qt 관련 header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QtPlugin/app_environment.h"
#include "QtPlugin/import_qml_components_plugins.h"
#include "QtPlugin/import_qml_plugins.h"

// 내가 작성한 header
#include "Alarm/Alarm.h"
#include "Date/Date.h"
#include "FolderOpener/FolderOpener.h"
#include "ProgramInfo/ProgramInfo.h"
#include "TaskListManager/TaskListManager.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    /* 1. 주요 객체 생성
        1) date : 날짜 정보를 관리하는 Date 객체
            - date 객체는 생성자에 의해 오늘 날짜로 정보가 설정됨
            - date 객체의 멤버변수에는 현재 관리중인 일정의 날짜 정보가 저장됨
        2) tasklist_manager : 일정 정보를 관리하는 TaskListManager 객체
            - tasklist_manager는 객체만 생성되어 있고 일정 정보 변수인 task_list는 아직 비어있음

        - 특이사항 : 이때는 아직 Date와 TaskListManager의 signal-slot이 설정되어있지 않으므로 saveTaskList()와 loadTaskList()는 호출되지 않음
    */
    Date& date = Date::instance();
    TaskListManager& tasklist_manager = TaskListManager::instance();

    /* 2. 보조 객체 생성
        1) folder_opener : 윈도우 탐색기로 폴더를 열어주는 객체
            - 절대경로를 기반으로 경로에 한글이 있어도 문제없도록 인코딩 후 Qt에서 제공하는 함수를 이용해 폴더를 열어줌
        2) alram : 사용자가 등록한 알람을 관리하는 객체
            - json에 저장된 알람들을 알람 객체가 읽어와서 등록함(**알람 기능은 추후 기능 추가때 구현 예정**)
    */
    FolderOpener folder_opener;
    Alarm alarm;

    /* 3. 프로그램 정보 확인을 위한 객체 생성
        1) file_reader : 로컬에 저장된 파일을 읽어오는 FileReader 객체
            - 부모클래스인 FileManager의 생성자에 의해 오늘 날짜를 기반으로 파일의 경로가 설정됨
        2) json_parser : file_reader에 의해 읽혀진 json 문서를 파싱하는 JsonParser 객체
            - 파싱 후 파싱된 결과를 Document에 담아서 리턴하도록 구현되었음
            - ProgramInfo 객체와 TaskListManager 객체가 해당 Document를 해석해서 자신에게 필요한 정보를 획득
        3) program_info : 프로그램의 정보를 확인하는 ProgramInfo 객체
            - 최초 실행 유무, 최근 실행 날짜 등의 정보를 확인하는 역할
            - 해당 정보를 활용해서 프로그램 실행시점에 튜토리얼을 실행할지, 일정 파일을 생성할지 정해지게 됨

        - 특이사항 : 이 3개의 객체 모두 프로그램 실행시에만 사용되고, 프로그램 동작중에는 메모리에 올라가 있을 필요가 없으므로 사용 후 할당해제 하기 위해 동적할당으로 생성
    */
    std::unique_ptr<FileReader> file_reader = std::make_unique<FileReader>();
    std::unique_ptr<JsonParser> json_parser = std::make_unique<JsonParser>();
    std::unique_ptr<ProgramInfo> program_info = std::make_unique<ProgramInfo>();

    /* 4. 프로그램 초기 설정
        - 3에서 생성한 객체들을 사용해서 프로그램 정보를 확인하고, 대응되는 동작을 수행
        - 알람 정보 확인 및 등록

        IF 프로그램 설치 후 최초 실행 THEN {
            튜토리얼 시작(**현재 미구현상태이며 추후 기능 추가때 구현 예정**)
        }
        ELSE {
            IF 오늘 이미 실행한적이 있다면 THEN
                이미 일정파일이 만들어져 있으므로 loadTaskList()를 호출해서 그냥 load만 함
            ELSE IF 오늘 처음 실행한다면 THEN
                오늘 날짜의 일정파일을 만들어야 하므로 makeTaskList()를 호출
        }

        - 특이사항 : 일정파일을 만든 후 즉시 로컬에 저장함
                    이 부분은 어차피 프로그램 종료 시 저장하면서 반영되므로 불필요할 수 있지만, 프로그램 비정상 종료에 대한 대응이 필요하다는 사용자 피드백에 따라 추가함
    */
    if(program_info->isTutorialNeeded()) { // 튜토리얼 여부 파악
        Tutorial tutorial;
        tutorial.startTutorial();
    }

    if(program_info->isOpenedToday(date)) { // 오늘 이미 실행한 적이 있다면
        tasklist_manager.loadSpecificTaskList();
    }
    else { // 오늘 처음 실행하는 것이라면
        tasklist_manager.makeTaskList(program_info->getLastManagedDateYear(), program_info->getLastManagedDateMonth(), program_info->getLastManagedDateDay());
        tasklist_manager.saveTaskList();
    }

    alarm.registerAlarm(); // 알람 정보 확인 및 등록(**추후 기능 추가때 구현 예정**)

    /* 5. 할당 해제
        - 프로그램 초기 설정에 사용된 객체들은 더 이상 필요 없으므로 리소스 관리를 위해 할당 해제
    */
    file_reader.reset();
    json_parser.reset();
    program_info.reset();

    /* 6. Qt 관련 객체 생성 및 C++과 연결
        - Qt 기본적인 객체 생성
    */
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /* 7. signal - slot 설정
        1) Date::dateChanged signal -> TaskListManager::saveTaskList slot
            - 사용자가 일정을 관리할 날짜를 변경해서 date 객체의 날짜가 바뀌면 dateChanged() 시그널이 발생 -> 기존에 관리중이던 일정 내용을 저장해야 하므로 tasklist_manager 객체가 saveTaskList() 함수를 수행
        2) Date::readyToLoad signal -> TaskListManager::loadTaskList slot
            - 위의 1) 시그널 - 슬롯을 통해 saveTaskList()를 마치고나면 date 값을 갱신하고 readyToLoad() 시그널 발생 -> 변경된 날짜의 일정파일을 불러와야 하므로 tasklist_manager 객체가 loadTaskList() 함수를 수행
        3) QCoreApplication ::aboutToQuit signal -> TaskListManager::saveTaskList slot
            - Qt 프레임워크에 의해 프로그램 종료 관련 시그널이 발생하면, tasklist_manager 객체가 일정 정보를 로컬에 파일로 저장하기 위해 saveTaskList() 함수를 수행
    */
    QObject::connect(&date, &Date::dateChanged, &tasklist_manager, &TaskListManager::saveTaskList);
    QObject::connect(&date, &Date::readyToLoad, &tasklist_manager, &TaskListManager::loadSpecificTaskList);
    QObject::connect(qApp, &QCoreApplication ::aboutToQuit, &tasklist_manager, &TaskListManager::saveTaskList);

    /* 8. 클라이언트 구조체 QML에 등록
            - 일정 파일에 내용의 string 뿐만 아니라 중요도까지 저장하기 위해 Task 구조체에 일정정보를 담도록 구현했고, 이 내용을 qml에서 표현해야 하므로 Task 구조체를 MetaType에 등록
    */
    qRegisterMetaType<Task>("Task");

    /* 9. Qml과 C++ integration
        - 주요 객체 및 보조 객체들을 qml과 integration
    */
    engine.rootContext()->setContextProperty("date", &date);
    engine.rootContext()->setContextProperty("tasklist_manager", &tasklist_manager);
    engine.rootContext()->setContextProperty("folder_opener", &folder_opener);

    /* 10. GUI 불러오고 이벤트 루프 ON
        - 그냥 Qt 프로젝트 기본 코드
    */
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
