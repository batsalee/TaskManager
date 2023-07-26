#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Scheduler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Scheduler s;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("lineCount", s.tasks.size() - 1);
    engine.rootContext()->setContextProperty("taskList", QVariant::fromValue(s.tasks));

    const QUrl url(u"qrc:/TaskManager/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);    
    engine.load(url);

    return app.exec();
}
