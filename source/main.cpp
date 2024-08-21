// Qt 관련 header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QtPlugin/app_environment.h"
#include "QtPlugin/import_qml_components_plugins.h"
#include "QtPlugin/import_qml_plugins.h"

// 내가 추가한 헤더들
#include "ProgramInfo/ProgramInfo.h"
#include "TaskListManager/TaskListManager.h"
#include "Date/Date.h"
#include "FolderOpener/FolderOpener.h"


int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // 내 코드 시작


    // 1. 객체 생성
    Date& date = Date::instance(); // 생성자에 의해 오늘 날짜로 정보 설정

    // 3) 일정 정보를 관리하는 Schedule 객체 생성
    TaskListManager& tasklist_manager = TaskListManager::instance(); // 객체만 생성되어있고 task_list는 비어있음
    // 이땐 아직 Date와 Schedule의 signal-slot이 설정되어있지 않으므로 schedule은 make되지 않음

    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 오늘 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    // 5) FolderOpener 객체 생성
    FolderOpener folder_opener;

    // 1) 프로그램 정보 확인
    std::unique_ptr<ProgramInfo> program_info = std::make_unique<ProgramInfo>();

    // 만약 이 프로그램을 처음 사용해본다면 튜토리얼 시작, 추후 기능추가때 구현할 예정
    if(program_info->isTutorialNeeded()) {
        Tutorial tutorial;
        tutorial.startTutorial();
    }

    if(program_info->isOpenedToday(date)) { // 오늘 이미 실행한 적이 있어서 오늘의 task_list가 만들어져있다면 오늘 날짜의 일정파일을 그대로 가져옴
        tasklist_manager.loadTaskList();
    }
    else { // 오늘 처음 실행하는 것이라면 오늘의 task_list 만들기
        // 오늘일정, 매일일정, 요일일정 추가
        tasklist_manager.makeTaskList(program_info->last_managed_date_year, program_info->last_managed_date_month, program_info->last_managed_date_day);

        // 6) 오늘의 일정파일 즉시 반영
        // 이 부분은 어차피 프로그램 종료시 저장하면서 반영되지만 프로그램 비정상 종료에 대한 대응이 필요하다는 피드백에 따라 추가
        tasklist_manager.saveTaskList();
    }

    program_info.reset(); // 초기 설정시 외에 필요없으므로 리소스 관리를 위해 할당해제


    // 4) Date와 Schedule간의 signal - slot 연결
    QObject::connect(&date, &Date::dateChanged, &tasklist_manager, &TaskListManager::loadTaskList); // 이제부턴 날짜가 변경되면 그 날짜의 스케쥴이 만들어짐
    // 위 코드가 문젠데, 저장 후 load하도록 만들어야함, 날짜 변경 버튼을 누르는 순간 저장하게 만들어야 하나?
    QObject::connect(qApp, &QCoreApplication ::aboutToQuit, &tasklist_manager, &TaskListManager::saveTaskList); // 종료시그널 발생시 저장하도록




    // 6) qml과 C++ integration
    qRegisterMetaType<Task>("Task"); // Task 구조체 QML에 등록
    engine.rootContext()->setContextProperty("date", &date);
    engine.rootContext()->setContextProperty("tasklist_manager", &tasklist_manager);
    engine.rootContext()->setContextProperty("folder_opener", &folder_opener);


    // 내 코드 끝


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
