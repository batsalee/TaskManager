#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "JsonManager.h"
using namespace rapidjson;

class Schedule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<QString>> schedule_list READ GetScheduleList NOTIFY ListChanged)

private:
    QList<QList<QString>> schedule_list;

public:
    // »ý¼ºÀÚ
    Schedule() = default;

    // init
    void MakeScheduleList(Document& document);

    // getter
    QList<QList<QString>> GetScheduleList();

    // setter
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(qint32, qint32, QString);
    Q_INVOKABLE void deleteTask(qint32, qint32);

signals:
    void ListChanged();
};
