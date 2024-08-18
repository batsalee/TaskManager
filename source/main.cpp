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
//#include "ScheduleFactory/TodayScheduleFactory.h"
#include "Schedule/Schedule.h"
#include "Date/Date.h"
#include "FolderOpener/FolderOpener.h"


int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // 내 코드 시작


    // 1) 프로그램 초기 설정
    std::unique_ptr<Initializer> initializer = std::make_unique<Initializer>();
    initializer->Init();
    initializer.reset(); // 초기 설정시 외에 필요없으므로 리소스 관리를 위해 할당해제

    Date& date = Date::instance(); // 생성자에 의해 오늘 날짜로 정보 설정
    // 이땐 아직 Date와 Schedule의 signal-slot이 설정되어있지 않으므로 schedule은 make되지 않음

    // 3) 일정 정보를 관리하는 Schedule 객체 생성
    Schedule& schedule = Schedule::instance(); // 객체만 생성되어있고 task_list는 비어있음

    // 4) Date와 Schedule간의 signal - slot 연결
    QObject::connect(&date, &Date::dateChanged, &schedule, &Schedule::makeTaskList);
    // 이제부턴 날짜가 변경되면 그 날짜의 스케쥴이 만들어짐

    // 5) FolderOpener 객체 생성
    FolderOpener folder_opener;

    // 6) qml과 C++ integration
    qRegisterMetaType<Task>("Task"); // Task 구조체 QML에 등록
    engine.rootContext()->setContextProperty("date", &date);
    engine.rootContext()->setContextProperty("schedule", &schedule);
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
