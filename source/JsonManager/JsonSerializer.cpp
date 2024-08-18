#include "JsonSerializer.h"

std::string JsonSerializer::initializerToJson(int y, int m, int d)
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

std::string JsonSerializer::taskListToJson(QList<QList<Task>>& task_list)
{
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    Value schedule(kArrayType);
    for (const auto& inner_list : task_list) {
        Value inner_array(kArrayType);
        for (const auto& task : inner_list) {
            Value task_object(kObjectType);

            task_object.AddMember("title", Value().SetString(task.title.toStdString().c_str(), allocator), allocator); // 이 부분이 오류가 아주 많이 발생해서 고생하는 중인데 괜찮은지 계속 확인하기

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
