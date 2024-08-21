/* Schedule.h

1. Ŭ���� ����
ScheduleFactory�� ScheduleŬ������ ���丮�޼��� ������ ������ ���丮 Ŭ����
JsonManagerŬ������ ���� ���߸���Ʈ�� ���, �����
qml�� ���������� �����ϴ� �� ������Ʈ�� �ٽ� Ŭ����

2. �뵵
�ش� ��¥�� ������ ����ִ� ���߸���Ʈ�� ������

3. �������
���丮�޼��忡 ���� �����Ǹ� �� �� �Ҹ�ɶ����� ���߸���Ʈ�� �����ϴ� ���� ���
*/

#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "../Task/Task.h"

#include "../FileManager/FileReader.h"
#include "../FileManager/FileWriter.h"
#include "../JsonManager/JsonParser.h"
#include "../JsonManager/JsonSerializer.h"

class TaskListManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<Task>> task_list READ getTaskList NOTIFY ListChanged)

private:
    // ������
    TaskListManager() = default;
    ~TaskListManager() = default;

    // �̱��� ���� ���� ����, �̵�, ���� delete
    TaskListManager(const TaskListManager& d) = delete;
    TaskListManager(TaskListManager&& d) = delete;
    TaskListManager& operator=(const TaskListManager & d) = delete;

public:
    QList<QList<Task>> task_list; // �� Ŭ������ ���α׷��� �ٽ��� ���߸���Ʈ
    QList<QList<Task>> getTaskList(); // getter

    // setter
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(int, int, QString);
    Q_INVOKABLE void deleteTask(int, int);

    void makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day);
    void appendList(QList<QList<Task>> appended_list);
    Q_INVOKABLE void saveTaskList(); // invokable �ʿ����� ����غ���
    void adjustImportance(QList<QList<Task>> remaining_list);

    static TaskListManager& instance(); // �̱��� ��ü ȹ�� �Լ�

signals:
    void ListChanged();

public slots:
    void loadTaskList();
};
