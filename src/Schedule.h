#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "JsonManager.h"
#include "Task.h"
using namespace rapidjson;

class Schedule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<Task>> schedule_list READ GetScheduleList NOTIFY ListChanged)

private:
    QList<QList<Task>> schedule_list;

public:
    // »ý¼ºÀÚ
    Schedule() = default;
    ~Schedule();

    // init
    void ConvertJsonToScheduleList(Document&);

    // exit
    std::string ConvertScheduleListToJson() const;

    // getter
    QList<QList<Task>> GetScheduleList();

    // setter
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(qint32, qint32, QString);
    Q_INVOKABLE void deleteTask(qint32, qint32);

signals:
    void ListChanged();
};
