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
    Schedule() = default;

    void MakeScheduleList(Document& document);
    QList<QList<QString>> GetScheduleList();
    Q_INVOKABLE void EraseTask(int y, int x);

signals:
    void ListChanged();
};
