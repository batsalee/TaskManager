// Qt ���� header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QtPlugin/app_environment.h"
#include "QtPlugin/import_qml_components_plugins.h"
#include "QtPlugin/import_qml_plugins.h"

// ���� �ۼ��� header
#include "Alarm/Alarm.h"
#include "Date/Date.h"
#include "FolderOpener/FolderOpener.h"
#include "ProgramInfo/ProgramInfo.h"
#include "TaskListManager/TaskListManager.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    /* 1. �ֿ� ��ü ����
        1) date : ��¥ ������ �����ϴ� Date ��ü
            - date ��ü�� �����ڿ� ���� ���� ��¥�� ������ ������
            - date ��ü�� ����������� ���� �������� ������ ��¥ ������ �����
        2) tasklist_manager : ���� ������ �����ϴ� TaskListManager ��ü
            - tasklist_manager�� ��ü�� �����Ǿ� �ְ� ���� ���� ������ task_list�� ���� �������

        - Ư�̻��� : �̶��� ���� Date�� TaskListManager�� signal-slot�� �����Ǿ����� �����Ƿ� saveTaskList()�� loadTaskList()�� ȣ����� ����
    */
    Date& date = Date::instance();
    TaskListManager& tasklist_manager = TaskListManager::instance();

    /* 2. ���� ��ü ����
        1) folder_opener : ������ Ž����� ������ �����ִ� ��ü
            - �����θ� ������� ��ο� �ѱ��� �־ ���������� ���ڵ� �� Qt���� �����ϴ� �Լ��� �̿��� ������ ������
        2) alram : ����ڰ� ����� �˶��� �����ϴ� ��ü
            - json�� ����� �˶����� �˶� ��ü�� �о�ͼ� �����(**�˶� ����� ���� ��� �߰��� ���� ����**)
    */
    FolderOpener folder_opener;
    Alarm alarm;

    /* 3. ���α׷� ���� Ȯ���� ���� ��ü ����
        1) file_reader : ���ÿ� ����� ������ �о���� FileReader ��ü
            - �θ�Ŭ������ FileManager�� �����ڿ� ���� ���� ��¥�� ������� ������ ��ΰ� ������
        2) json_parser : file_reader�� ���� ������ json ������ �Ľ��ϴ� JsonParser ��ü
            - �Ľ� �� �Ľ̵� ����� Document�� ��Ƽ� �����ϵ��� �����Ǿ���
            - ProgramInfo ��ü�� TaskListManager ��ü�� �ش� Document�� �ؼ��ؼ� �ڽſ��� �ʿ��� ������ ȹ��
        3) program_info : ���α׷��� ������ Ȯ���ϴ� ProgramInfo ��ü
            - ���� ���� ����, �ֱ� ���� ��¥ ���� ������ Ȯ���ϴ� ����
            - �ش� ������ Ȱ���ؼ� ���α׷� ��������� Ʃ�丮���� ��������, ���� ������ �������� �������� ��

        - Ư�̻��� : �� 3���� ��ü ��� ���α׷� ����ÿ��� ���ǰ�, ���α׷� �����߿��� �޸𸮿� �ö� ���� �ʿ䰡 �����Ƿ� ��� �� �Ҵ����� �ϱ� ���� �����Ҵ����� ����
    */
    std::unique_ptr<FileReader> file_reader = std::make_unique<FileReader>();
    std::unique_ptr<JsonParser> json_parser = std::make_unique<JsonParser>();
    std::unique_ptr<ProgramInfo> program_info = std::make_unique<ProgramInfo>();

    /* 4. ���α׷� �ʱ� ����
        - 3���� ������ ��ü���� ����ؼ� ���α׷� ������ Ȯ���ϰ�, �����Ǵ� ������ ����
        - �˶� ���� Ȯ�� �� ���

        IF ���α׷� ��ġ �� ���� ���� THEN {
            Ʃ�丮�� ����(**���� �̱��������̸� ���� ��� �߰��� ���� ����**)
        }
        ELSE {
            IF ���� �̹� ���������� �ִٸ� THEN
                �̹� ���������� ������� �����Ƿ� loadTaskList()�� ȣ���ؼ� �׳� load�� ��
            ELSE IF ���� ó�� �����Ѵٸ� THEN
                ���� ��¥�� ���������� ������ �ϹǷ� makeTaskList()�� ȣ��
        }

        - Ư�̻��� : ���������� ���� �� ��� ���ÿ� ������
                    �� �κ��� ������ ���α׷� ���� �� �����ϸ鼭 �ݿ��ǹǷ� ���ʿ��� �� ������, ���α׷� ������ ���ῡ ���� ������ �ʿ��ϴٴ� ����� �ǵ�鿡 ���� �߰���
    */
    if(program_info->isTutorialNeeded()) { // Ʃ�丮�� ���� �ľ�
        Tutorial tutorial;
        tutorial.startTutorial();
    }

    if(program_info->isOpenedToday(date)) { // ���� �̹� ������ ���� �ִٸ�
        tasklist_manager.loadSpecificTaskList();
    }
    else { // ���� ó�� �����ϴ� ���̶��
        tasklist_manager.makeTaskList(program_info->getLastManagedDateYear(), program_info->getLastManagedDateMonth(), program_info->getLastManagedDateDay());
        tasklist_manager.saveTaskList();
    }

    alarm.registerAlarm(); // �˶� ���� Ȯ�� �� ���(**���� ��� �߰��� ���� ����**)

    /* 5. �Ҵ� ����
        - ���α׷� �ʱ� ������ ���� ��ü���� �� �̻� �ʿ� �����Ƿ� ���ҽ� ������ ���� �Ҵ� ����
    */
    file_reader.reset();
    json_parser.reset();
    program_info.reset();

    /* 6. Qt ���� ��ü ���� �� C++�� ����
        - Qt �⺻���� ��ü ����
    */
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /* 7. signal - slot ����
        1) Date::dateChanged signal -> TaskListManager::saveTaskList slot
            - ����ڰ� ������ ������ ��¥�� �����ؼ� date ��ü�� ��¥�� �ٲ�� dateChanged() �ñ׳��� �߻� -> ������ �������̴� ���� ������ �����ؾ� �ϹǷ� tasklist_manager ��ü�� saveTaskList() �Լ��� ����
        2) Date::readyToLoad signal -> TaskListManager::loadTaskList slot
            - ���� 1) �ñ׳� - ������ ���� saveTaskList()�� ��ġ���� date ���� �����ϰ� readyToLoad() �ñ׳� �߻� -> ����� ��¥�� ���������� �ҷ��;� �ϹǷ� tasklist_manager ��ü�� loadTaskList() �Լ��� ����
        3) QCoreApplication ::aboutToQuit signal -> TaskListManager::saveTaskList slot
            - Qt �����ӿ�ũ�� ���� ���α׷� ���� ���� �ñ׳��� �߻��ϸ�, tasklist_manager ��ü�� ���� ������ ���ÿ� ���Ϸ� �����ϱ� ���� saveTaskList() �Լ��� ����
    */
    QObject::connect(&date, &Date::dateChanged, &tasklist_manager, &TaskListManager::saveTaskList);
    QObject::connect(&date, &Date::readyToLoad, &tasklist_manager, &TaskListManager::loadSpecificTaskList);
    QObject::connect(qApp, &QCoreApplication ::aboutToQuit, &tasklist_manager, &TaskListManager::saveTaskList);

    /* 8. Ŭ���̾�Ʈ ����ü QML�� ���
            - ���� ���Ͽ� ������ string �Ӹ� �ƴ϶� �߿䵵���� �����ϱ� ���� Task ����ü�� ���������� �㵵�� �����߰�, �� ������ qml���� ǥ���ؾ� �ϹǷ� Task ����ü�� MetaType�� ���
    */
    qRegisterMetaType<Task>("Task");

    /* 9. Qml�� C++ integration
        - �ֿ� ��ü �� ���� ��ü���� qml�� integration
    */
    engine.rootContext()->setContextProperty("date", &date);
    engine.rootContext()->setContextProperty("tasklist_manager", &tasklist_manager);
    engine.rootContext()->setContextProperty("folder_opener", &folder_opener);

    /* 10. GUI �ҷ����� �̺�Ʈ ���� ON
        - �׳� Qt ������Ʈ �⺻ �ڵ�
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
