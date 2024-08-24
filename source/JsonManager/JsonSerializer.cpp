#include "JsonSerializer.h"

/* programInfoToJson()
�뵵 : ProgramInfo Ŭ������ ������ Serialize�ؼ� json���·� ��ȯ
������ : ���α׷� ���� ����� ProgramInfo Ŭ������ ���� ȣ���. ���α׷� �ʱ� ������ ������ ���õ� ������ ���� �� �ش� ������ json ���Ϸ� ����
*/
std::string JsonSerializer::programInfoToJson(int y, int m, int d)
{
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("tutorial", false, allocator);
    document.AddMember("last_managed_date_year", y, allocator);
    document.AddMember("last_managed_date_month", m, allocator);
    document.AddMember("last_managed_date_day", d, allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

/* taskListToJson()
�뵵 : TaskListManager Ŭ������ ��������� ���߸���Ʈ task_list�� json���·� ��ȯ
������ : ��¥ ���� Ȥ�� ���α׷� ����� ������̴� ���� ������ ���ÿ� ���Ϸ� �����ؾ� �ϹǷ� ȣ��
*/
std::string JsonSerializer::taskListToJson(const QList<QList<Task>>& task_list)
{
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    Value schedule(kArrayType);
    for (const auto& inner_list : task_list) {
        Value inner_array(kArrayType);
        for (const auto& task : inner_list) {
            Value task_object(kObjectType);

            task_object.AddMember("title", Value().SetString(task.title.toStdString().c_str(), allocator), allocator);
            task_object.AddMember("importance", task.importance, allocator);
            inner_array.PushBack(task_object, allocator);
        }
        schedule.PushBack(inner_array, allocator);
    }

    document.AddMember("Schedule", schedule, allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}
