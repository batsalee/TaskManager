// Qt ���� header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QtPlugin/app_environment.h"
#include "QtPlugin/import_qml_components_plugins.h"
#include "QtPlugin/import_qml_plugins.h"

// ���� �߰��� �����
#include "ProgramInfo/ProgramInfo.h"
#include "TaskListManager/TaskListManager.h"
#include "Date/Date.h"
#include "FolderOpener/FolderOpener.h"


int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // �� �ڵ� ����


    // 1. ��ü ����
    Date& date = Date::instance(); // �����ڿ� ���� ���� ��¥�� ���� ����

    // 3) ���� ������ �����ϴ� Schedule ��ü ����
    TaskListManager& tasklist_manager = TaskListManager::instance(); // ��ü�� �����Ǿ��ְ� task_list�� �������
    // �̶� ���� Date�� Schedule�� signal-slot�� �����Ǿ����� �����Ƿ� schedule�� make���� ����

    FileReader file_reader; // �θ�Ŭ������ FileManager�� �����ڿ� ���� ���� ��¥ ��� ��� ����
    JsonParser json_parser; // ���� ������ json�����̹Ƿ� �Ľ̴�� ��ü ����

    // 5) FolderOpener ��ü ����
    FolderOpener folder_opener;

    // 1) ���α׷� ���� Ȯ��
    std::unique_ptr<ProgramInfo> program_info = std::make_unique<ProgramInfo>();

    // ���� �� ���α׷��� ó�� ����غ��ٸ� Ʃ�丮�� ����, ���� ����߰��� ������ ����
    if(program_info->isTutorialNeeded()) {
        Tutorial tutorial;
        tutorial.startTutorial();
    }

    if(program_info->isOpenedToday(date)) { // ���� �̹� ������ ���� �־ ������ task_list�� ��������ִٸ� ���� ��¥�� ���������� �״�� ������
        tasklist_manager.loadTaskList();
    }
    else { // ���� ó�� �����ϴ� ���̶�� ������ task_list �����
        // ��������, ��������, �������� �߰�
        tasklist_manager.makeTaskList(program_info->last_managed_date_year, program_info->last_managed_date_month, program_info->last_managed_date_day);

        // 6) ������ �������� ��� �ݿ�
        // �� �κ��� ������ ���α׷� ����� �����ϸ鼭 �ݿ������� ���α׷� ������ ���ῡ ���� ������ �ʿ��ϴٴ� �ǵ�鿡 ���� �߰�
        tasklist_manager.saveTaskList();
    }

    program_info.reset(); // �ʱ� ������ �ܿ� �ʿ�����Ƿ� ���ҽ� ������ ���� �Ҵ�����


    // 4) Date�� Schedule���� signal - slot ����
    QObject::connect(&date, &Date::dateChanged, &tasklist_manager, &TaskListManager::loadTaskList); // �������� ��¥�� ����Ǹ� �� ��¥�� �������� �������
    // �� �ڵ尡 ������, ���� �� load�ϵ��� ��������, ��¥ ���� ��ư�� ������ ���� �����ϰ� ������ �ϳ�?
    QObject::connect(qApp, &QCoreApplication ::aboutToQuit, &tasklist_manager, &TaskListManager::saveTaskList); // ����ñ׳� �߻��� �����ϵ���




    // 6) qml�� C++ integration
    qRegisterMetaType<Task>("Task"); // Task ����ü QML�� ���
    engine.rootContext()->setContextProperty("date", &date);
    engine.rootContext()->setContextProperty("tasklist_manager", &tasklist_manager);
    engine.rootContext()->setContextProperty("folder_opener", &folder_opener);


    // �� �ڵ� ��


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
