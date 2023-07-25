#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Date.h"
//
#include <QDebug>>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // for test
    QDate currentDate = QDate::currentDate();
    //year = currentDate.year();
    qDebug() << currentDate.month();

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
