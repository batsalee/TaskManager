// Qt 관련 header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

// 내가 추가한 헤더들
#include <iostream>
#include "TodayScheduleFactory.h"
#include "Schedule.h"
#include "FolderOpener.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;



    // 내 코드 시작

    // 0) 사전준비
    FolderOpener folder_opener;

    // 1) Schedule객체 팩토리메서드 통해서 생성
    TodayScheduleFactory tsf;
    std::unique_ptr<Schedule> schedule = tsf.makeSchedule();

    // qml과 C++ integration
    qRegisterMetaType<Task>("Task"); // Task 구조체 QML에 등록
    engine.rootContext()->setContextProperty("schedule", schedule.get()); // unique_ptr의 주소를 복사할 수 없어서 get()으로 schedule의 주소 넘김
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
