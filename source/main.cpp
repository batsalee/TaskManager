// Qt 관련 header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QtPlugin/app_environment.h"
#include "QtPlugin/import_qml_components_plugins.h"
#include "QtPlugin/import_qml_plugins.h"

// 내가 추가한 헤더들
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



    // 내 코드 시작


    // 0) 사전준비
    FolderOpener folder_opener;

    // 1) Schedule객체 선언
    TodayScheduleFactory tsf;
    tsf.makeSchedule();
    Schedule& schedule = Schedule::instance();

    // -2) Date 객체 생성 및 오늘 날짜 획득
    Date& date = Date::instance();
    // date.setToCurrentDate(); // 원래는 사용했지만 실수방지를 위해 생성자에 넣어버리기로 했음

    // Date와 Schedule간의 signal - slot
    QObject::connect(&date, &Date::dateChanged, &schedule, &Schedule::makeTaskList);

    // -1) initializer
    Initializer initializer;
    //if(initializer.isTutorialNeeded()) tutorial(); // 만약 첫 실행이라면 튜토리얼, 추후 기능추가때 구현

    //if(initializer.isOpenedToday()) schedule.justParse;
    //else schedule.makeSchedule();


    // qml과 C++ integration
    qRegisterMetaType<Task>("Task"); // Task 구조체 QML에 등록
    engine.rootContext()->setContextProperty("schedule", &schedule); // unique_ptr의 주소를 복사할 수 없어서 get()으로 schedule의 주소 넘김
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
