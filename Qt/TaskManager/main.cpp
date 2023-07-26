#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FolderOpener.h"
#include "Scheduler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Scheduler scheduler;
    FolderOpener folder_opener;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("scheduler", &scheduler);
    engine.rootContext()->setContextProperty("lineCount", scheduler.tasks.size() - 1);
    engine.rootContext()->setContextProperty("taskList", QVariant::fromValue(scheduler.tasks));
    engine.rootContext()->setContextProperty("folder_opener", &folder_opener);

    const QUrl url(u"qrc:/TaskManager/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);    
    engine.load(url);

    return app.exec();
}
