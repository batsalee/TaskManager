#include "JsonSerializer.h"

/* programInfoToJson()
용도 : ProgramInfo 클래스의 내용을 Serialize해서 json형태로 변환
시퀀스 : 프로그램 최초 실행시 ProgramInfo 클래스에 의해 호출됨. 프로그램 초기 설정이 끝나면 관련된 정보를 갱신 후 해당 내용을 json 파일로 저장
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
용도 : TaskListManager 클래스의 멤버변수인 이중리스트 task_list를 json형태로 변환
시퀀스 : 날짜 변경 혹은 프로그램 종료시 사용중이던 일정 정보를 로컬에 파일로 저장해야 하므로 호출
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
