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
                    // ���� ���ڵ� ������ ����ٸ� UTF-8 to EUC-KR �ڵ� ���⿡ �ֱ�
                }
                schedule_list.push_back(inner_list);
            }
        }
    }
}
