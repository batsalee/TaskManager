#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "Task.h"

class Schedule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<Task>> task_list READ GetScheduleList NOTIFY ListChanged)

public:
    QList<QList<Task>> task_list;

    // »ý¼ºÀÚ
    Schedule() = default;
    ~Schedule() = default;

    // exit
 //   std::string ConvertScheduleListToJson() const;

    // getter
    QList<QList<Task>> GetScheduleList();

    // setter
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(int, int, QString);
    Q_INVOKABLE void deleteTask(int, int);

signals:
    void ListChanged();
};
