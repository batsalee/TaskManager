#include "Schedule.h"

/*
MakeScheduleList()
�뵵 : init, ó�� �ش� ��¥�� ���������� ���� ȣ��
������ : FileReader�� ������ �о��ָ� JsonParser�� �Ľ��ϰ� �ش� ������ MakeScheduleList()�� ���߸���Ʈ�� ����
*/
void Schedule::MakeScheduleList(Document& document)
{
    if (document.HasMember("Schedule") && document["Schedule"].IsArray()) {
        const Value& json_array = document["Schedule"];

        for (int i = 0; i < json_array.Size(); i++) {
            if (json_array[i].IsArray()) {
                const Value& inner_array = json_array[i];

                QList<QString> inner_list;
                for (int j = 0; j < inner_array.Size(); j++) {
                    inner_list.push_back(inner_array[j].GetString());
                    // ���� ���ڵ� ������ ����ٸ� UTF-8 to EUC-KR �ڵ� ���⿡ �ֱ�
                }
                schedule_list.push_back(inner_list);
            }
        }
    }
}

/*
GetScheduleList()
�뵵 : C++�� QML�� integration������ Q_PROPERTY�Ӽ��� READ�Լ�
������ : QML���� Window�� ��ﶧ ListView�� ������ ���� �ϹǷ� �ش� �Լ��� ���� ����
*/
QList<QList<QString>> Schedule::GetScheduleList()
{
    return schedule_list;
}

/*
insertTask()
�뵵 : ����ڰ� ����� ������ ���� ���ܼ� �߰��ϰ� ������ ȣ��
������ : QML���� Button ���� �� �ߴ� TextInputWindow�� ������ �Է��ϰ� ���͸� ġ�� �ش� ������ ListView�� �ֻ�ܿ� �߰���
��� ���� : version 1.0���� #���� ������ �Է½� �и��ϰ� �߾��µ� �̰Ŷ����� C#���� �ܾ ������ ���߾���
          �׷��� �ش� ����� �������� ���������� ���� ���� �� �ش� ����� ���Ŀ� GUI���� �߰� �����ϵ��� �����ϴ°� �´ٰ� �Ǵ��ؼ� �켱 ����
*/
Q_INVOKABLE void Schedule::insertTask(QString inserted_task)
{
    QList<QString> new_schedule_list = {inserted_task}; // ���� �߰��� QList
    schedule_list.push_front(new_schedule_list);
    emit ListChanged();
}

/*
updateTask()
�뵵 : ����ڰ� ������ ������ �����ϰ� ������ ȣ��
������ : QML���� ListView�� ��Ÿ���ִ� �������� Rectangle���� �ϳ��� ����(task)�� �������, �ش� task�� ������ �����ϰ� ������ ��Ŭ�� �� ���� �Է� �� ���ͽ� ����
*/
Q_INVOKABLE void Schedule::updateTask(qint32 y, qint32 x, QString updated_task)
{
    schedule_list[y][x] = updated_task;
    emit ListChanged();
}

/*
deleteTask()
�뵵 : ����ڰ� ������ ������ �Ϸ��ؼ� ��Ͽ��� ����� ������ ȣ��
������ : QML���� ListView�� ��Ÿ���ִ� �������� Rectangle �� ����ڰ� �Ϸ��� task�� ����Ŭ���ϸ� �� �Լ��� ȣ��Ǿ� �ش� ������ schedule_list���� ������
*/
Q_INVOKABLE void Schedule::deleteTask(int y, int x)
{
    schedule_list[y].removeAt(x);
    if(schedule_list[y].empty()) schedule_list.removeAt(y);

    emit ListChanged();
}