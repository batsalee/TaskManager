#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Scheduler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Scheduler s;
    QList<QList<QString>> taskList = s.tasks;

    QQmlApplicationEngine engine;        
    const QUrl url(u"qrc:/TaskManager/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);    
    engine.load(url);

    return app.exec();
}
