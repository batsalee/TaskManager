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
#include "ScheduleFactory/TodayScheduleFactory.h"
#include "Schedule/Schedule.h"
#include "FolderOpener/FolderOpener.h"


int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;



    // �� �ڵ� ����


    // 0) �����غ�
    FolderOpener folder_opener;

    // 1) Schedule��ü ����
    TodayScheduleFactory tsf;
    tsf.makeSchedule();
    Schedule& schedule = Schedule::instance();

    // -2) Date ��ü ���� �� ���� ��¥ ȹ��
    Date& date = Date::instance();
    // date.setToCurrentDate(); // ������ ��������� �Ǽ������� ���� �����ڿ� �־������� ����

    // Date�� Schedule���� signal - slot
    QObject::connect(&date, &Date::dateChanged, &schedule, &Schedule::makeTaskList);

    // -1) initializer
    Initializer initializer;
    //if(initializer.isTutorialNeeded()) tutorial(); // ���� ù �����̶�� Ʃ�丮��, ���� ����߰��� ����

    //if(initializer.isOpenedToday()) schedule.justParse;
    //else schedule.makeSchedule();


    // qml�� C++ integration
    qRegisterMetaType<Task>("Task"); // Task ����ü QML�� ���
    engine.rootContext()->setContextProperty("schedule", &schedule); // unique_ptr�� �ּҸ� ������ �� ��� get()���� schedule�� �ּ� �ѱ�
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
