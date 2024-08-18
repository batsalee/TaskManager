// Qt ���� header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QtPlugin/app_environment.h"
#include "QtPlugin/import_qml_components_plugins.h"
#include "QtPlugin/import_qml_plugins.h"

// ���� �߰��� �����
#include <iostream>
#include "Initializer/Initializer.h"
//#include "ScheduleFactory/TodayScheduleFactory.h"
#include "Schedule/Schedule.h"
#include "Date/Date.h"
#include "FolderOpener/FolderOpener.h"


int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // �� �ڵ� ����


    // 1) ���α׷� �ʱ� ����
    std::unique_ptr<Initializer> initializer = std::make_unique<Initializer>();
    initializer->Init();
    initializer.reset(); // �ʱ� ������ �ܿ� �ʿ�����Ƿ� ���ҽ� ������ ���� �Ҵ�����

    Date& date = Date::instance(); // �����ڿ� ���� ���� ��¥�� ���� ����
    // �̶� ���� Date�� Schedule�� signal-slot�� �����Ǿ����� �����Ƿ� schedule�� make���� ����

    // 3) ���� ������ �����ϴ� Schedule ��ü ����
    Schedule& schedule = Schedule::instance(); // ��ü�� �����Ǿ��ְ� task_list�� �������

    // 4) Date�� Schedule���� signal - slot ����
    QObject::connect(&date, &Date::dateChanged, &schedule, &Schedule::makeTaskList);
    // �������� ��¥�� ����Ǹ� �� ��¥�� �������� �������

    // 5) FolderOpener ��ü ����
    FolderOpener folder_opener;

    // 6) qml�� C++ integration
    qRegisterMetaType<Task>("Task"); // Task ����ü QML�� ���
    engine.rootContext()->setContextProperty("date", &date);
    engine.rootContext()->setContextProperty("schedule", &schedule);
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
