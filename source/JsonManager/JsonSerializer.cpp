#include "JsonSerializer.h"

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

            task_object.AddMember("title", Value().SetString(task.title.toStdString().c_str(), allocator), allocator); // �� �κ��� ������ ���� ���� �߻��ؼ� ����ϴ� ���ε� �������� ��� Ȯ���ϱ�

            task_object.AddMember("importance", task.importance, allocator);
            inner_array.PushBack(task_object, allocator);
        }
        schedule.PushBack(inner_array, allocator);
    }

    document.AddMember("Schedule", schedule, allocator);
    document.AddMember("opened", true, allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}
