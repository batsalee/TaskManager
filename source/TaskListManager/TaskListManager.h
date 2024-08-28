/* TaskListManager.h

1. Ŭ���� ����
FileReader, FileWriter, JsonParser, JsonSerializer�� ȣ���ؼ� Ȱ���ϴ� Ŀ�ø��� �߽��� �Ǵ� Ŭ����
qml�� ���������� �����ϴ� �� ������Ʈ�� �ٽ� Ŭ����

2. �뵵
���߸���Ʈ ������
Ư�� ��¥�� ������ �����Ҷ��� �ش� ��¥�� ������, ���� ������ �����Ҷ����� �ش� ���Ͽ� ����� ������ ǥ�� �� �����ϴ� Ŭ����

3. �������
�ٸ� Ŭ�������� �ִ��� Ŀ�ø��� �߻����� �ʰ� �Ϸ��� ����߰�, �� Ŭ���� �ϳ��� �� ��� Ŭ�������� Ȱ���ؼ� Ŀ�ø��� �߽��� �ǰ� ���α׷��� �ٽ� Ŭ������ ������

4. ���
�� Ŭ������ �̱��� �������� �����Ǿ���
���� 1) �ϳ��� ������ �ȴٴ� ��
���� 2) qml�� integration
�׸��� ������ ���� 3�� �־��µ� ������ �� Ŭ������ Ŀ�ø��� �߽��� �ƴ϶� �� Ŭ�������� �� Ŭ������ �����ϴ� ������� ����߾���
������ �ٸ� Ŭ�������� ���뼺�̳� ���� å�� ��Ģ �ؼ��� ���� ������Ʈ�� ��ü���� ������ �����ϰ� ���� �� Ŭ������ �������� ������ ���� �������� �Ǿ���

�׷����� �� Ŭ������ �̱������� �����ȴٸ� �ϳ��� �����ؾ��Ѵٴ� ������ �ο� �ܿ��� �ǹ̰� ����.
������ ������ �ϳ��� �־�� �ϴ°� ����. �׷��� �̱����� �������� ���� ��� ��
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
    QList<QList<Task>> task_list; // �� Ŭ������ ���α׷��� �ٽ��� ���߸���Ʈ

    TaskListManager() = default;
    ~TaskListManager() = default;

    // �̱��� ���� ���� ����, �̵�, ���� delete
    TaskListManager(const TaskListManager& d) = delete;
    TaskListManager(TaskListManager&& d) = delete;
    TaskListManager& operator=(const TaskListManager& d) = delete;

    // load �Լ�
    void loadTaskList(FileReader& file_reader, JsonParser& json_parser); // loadFixedTaskList()�� loadSpecificTaskList()�� ����κ��� �ۼ��ǹǷ� private�� ����

public:
    static TaskListManager& instance(); // �̱��� ��ü ȹ�� �Լ�

    // Task List ���� �Լ�
    void makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day); // �������� ���� �Լ�
    void saveTaskList(); // �������� ���� �Լ�(�����ϴ� ��¥�� ����ǰų� ���α׷��� ����� �� ȣ���)
    void appendList(const QList<QList<Task>>& appended_list); // ���߸���Ʈ�� ���� �������� ������ �����̴� �Լ�
    void adjustImportance(QList<QList<Task>>& remaining_list); // ���߸���Ʈ ���� Task�� �߿䵵�� �����ϴ� �Լ�

    // load �Լ�
    Q_INVOKABLE void loadFixedTaskList(std::string file_path); // ���� ����(���� ����, �� ���Ϻ� ����)�� �����ϱ� ���� �ҷ����� �Լ�

    // Task ���� �Լ�
    Q_INVOKABLE void insertTask(QString inserted_task);
    Q_INVOKABLE void updateTask(int y, int x, QString updated_task);
    Q_INVOKABLE void deleteTask(int y, int x);

    // getter
    QList<QList<Task>> getTaskList() const;

signals:
    void ListChanged(); // qml ������ ���� insert, update, delete�� �ñ׳� emit

public slots:
    void loadSpecificTaskList(); // Ư�� ��¥�� ���������� �о���� �Լ�
};
