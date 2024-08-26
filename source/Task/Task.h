/* Task.h

1. Ŭ���� ����
Task�� ��Ȯ���� Ŭ������ �ƴ϶� ����ü
TaskListManager Ŭ������ ��������� task_list�� ��������� task������ ���
�� TaskListManager�� Task�� ��������

2. �뵵
������ ����� �ƴ϶� �߿䵵 ������ ���� jsonȭ �� ����üȭ

3. �������
������ ������ title�� �߿䵵�� importance�� ����
���� �ش� ������ qml���� Ȱ��Ǿ�� �ϹǷ� Q_DECLARE_METATYPE�� ��ŸŸ������ ����

4. Ư�̻���
����ü������ �̵������ڸ� �����ص���
Task ����ü�� TaskListManager�� appendTaskList()�� ���� ����Ǵ� ��찡 ���� ���� ����µ�
���⼭ Qtring�� ���纸�ٴ� �̵��� ����ϴ����� �� �̵��� �� ������ �̵������ڸ� noexcept�� �����ؼ�
appendTaskList()���� push_back�Ҷ� ������ ���۷����� �ѱ⵵�� ����

�׸��� �̵������ڸ� ���������� default �����ڳ� ��������ڵ� ��������� ��������� ������
���� �����ϸ鼭 �ٷ� �����ϵ��� ����� task(QString& t, int i)�����ڵ� insertTask()���� ���ǹǷ� ��������� ����

���� �� ���α׷����� ����ϰ� ������ ������ �켱 ���Կ����ڵ� �����ص���
���� ���Կ�����, �̵� ���Կ����ڰ� ������ ���߿� Ȱ���� �� ���� �� ��
*/

#pragma once

#include <QObject>
#include <QString>
#include <QMetaType>

using Task = struct task {
    Q_GADGET
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(int importance MEMBER importance)

public:
    QString title; // ������ ����
    int importance; // ������ �߿䵵(1�� ���� ����, 3�� ���� ����)

    // ������
    task() = default; // �⺻ ������
    task(QString& t, int i) // �� �����ϸ鼭 �ٷ� ����(insertTask()���� ���)
        : title(t), importance(i) {}
    task(const task&) = default; // ���� ������
    task(task&& other) noexcept // �̵� ������
        : title(std::move(other.title)), importance(other.importance) {}

    // ���� ������
    task& operator=(const task&) = default; // ���� ���� ������
    task& operator=(task&& other) noexcept { // �̵� ���� ������
        if (this != &other) {
            title = std::move(other.title);
            importance = other.importance;
        }
        return *this;
    }
};

Q_DECLARE_METATYPE(Task)
