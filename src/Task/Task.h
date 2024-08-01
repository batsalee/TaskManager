/* Task.h

1. Ŭ���� ����
Task�� ��Ȯ���� Ŭ������ �ƴ϶� ����ü
Schedule Ŭ������ ��������� task_list�� ��������� task������ ���
ScheduleFactory���� JsonManager�� json�� �Ľ��Ҷ� ����ȭ��

2. �뵵
������ ����� �ƴ϶� �߿䵵 ������ ���� jsonȭ �� ����üȭ

3. �������
������ ������ title�� �߿䵵�� importance�� ����
���� �ش� ������ qml���� Ȱ��Ǿ�� �ϹǷ� Q_DECLARE_METATYPE�� ��ŸŸ������ ����
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
    QString title;
    int importance;
};

Q_DECLARE_METATYPE(Task)
