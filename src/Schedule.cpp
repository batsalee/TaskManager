#include "Schedule.h"

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
                    // 만약 인코딩 문제가 생긴다면 UTF-8 to EUC-KR 코드 여기에 넣기
                }
                schedule_list.push_back(inner_list);
            }
        }
    }
}

QList<QList<QString>> Schedule::GetScheduleList()
{
    return schedule_list;
}

Q_INVOKABLE void Schedule::EraseTask(int y, int x)
{
    schedule_list[y].removeAt(x);
    if(schedule_list[y].empty()) schedule_list.removeAt(y);

    emit ListChanged();
}
