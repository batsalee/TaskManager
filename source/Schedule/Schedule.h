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
#include "../JsonManager/JsonParser.h"

class Schedule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<Task>> task_list READ GetScheduleList NOTIFY ListChanged)

private:
    // ������
    Schedule() = default;
    ~Schedule();

    // �̱��� ���� ���� ����, �̵�, ���� delete
    Schedule(const Schedule& d) = delete;
    Schedule(Schedule&& d) = delete;
    Schedule& operator=(const Schedule & d) = delete;

public:
    QList<QList<Task>> task_list; // �� Ŭ������ ���α׷��� �ٽ��� ���߸���Ʈ
    QList<QList<Task>> GetScheduleList(); // getter

    // setter
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(int, int, QString);
    Q_INVOKABLE void deleteTask(int, int);

    static Schedule& instance(); // �̱��� ��ü ȹ�� �Լ�

signals:
    void ListChanged();

public slots:
    void showTaskList();
};
