/* TaskListManager.h

1. Ŭ���� ����
FileReader, FileWriter, JsonParser, JsonSerializer�� ȣ���ؼ� Ȱ���ϴ� Ŀ�ø��� �߽��� �Ǵ� Ŭ����
qml�� ���������� �����ϴ� �� ������Ʈ�� �ٽ� Ŭ����

2. �뵵
���߸���Ʈ ������
Ư�� ��¥�� ������ �����Ҷ��� �ش� ��¥�� ������, ���� ������ �����Ҷ����� �ش� ���Ͽ� ����� ������ ǥ�� �� �����ϴ� Ŭ����

3. �������
�ٸ� Ŭ�������� �ִ��� Ŀ�ø��� �߻����� �ʰ� �Ϸ��� ����߰�, �� Ŭ���� �ϳ��� �� ��� Ŭ�������� Ȱ���ؼ� Ŀ�ø��� �߽��� �ǰ� ���α׷��� �ٽ� Ŭ������ ������

�̱��� �������� ����
���� 1) �ϳ��� ������ �ȴٴ� ��
���� 2) qml�� integration

4. ���
Ŭ�������� �� �����ϰ� �� �� �� Ŭ������ Ŀ�ø��� �߽��� �� ���� �� Ŭ������ �̱����̾�� �� ������ ����.
�������� �ٸ� Ŭ�������� �� Ŭ������ ������ �Ἥ �������� �������̶�� ������ �־��µ� ����� �����ؾ��� ������ ��������. �ǵ����� ������ ������ ���
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
    TaskListManager() = default;
    ~TaskListManager() = default;

    // �̱��� ���� ���� ����, �̵�, ���� delete
    TaskListManager(const TaskListManager& d) = delete;
    TaskListManager(TaskListManager&& d) = delete;
    TaskListManager& operator=(const TaskListManager & d) = delete;

public:
    QList<QList<Task>> task_list; // �� Ŭ������ ���α׷��� �ٽ��� ���߸���Ʈ

    static TaskListManager& instance(); // �̱��� ��ü ȹ�� �Լ�

    // Task List ���� �Լ�
    void makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day); // �������� ���� �Լ�
    void saveTaskList(); // �����ϴ� ��¥ ���� Ȥ�� ���α׷� ����� �������� ���� �Լ�
    void appendList(const QList<QList<Task>>& appended_list); // ���߸���Ʈ�� ���� �������� ������ �����̴� �Լ�
    void adjustImportance(QList<QList<Task>>& remaining_list); // ���߸���Ʈ ���� Task�� �߿䵵�� �����ϴ� �Լ�

    // Task ���� �Լ�
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(int, int, QString);
    Q_INVOKABLE void deleteTask(int, int);

    // getter
    QList<QList<Task>> getTaskList() const;

signals:
    void ListChanged(); // qml ������ ���� insert, update, delete�� �ñ׳� emit

public slots:
    void loadTaskList(); // ���� �̹� ���������� ������� �ִٸ� �״�� �о���� �Լ�
};
