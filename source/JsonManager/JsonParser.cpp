#include "JsonParser.h"

bool JsonParser::isOpened(std::string file_content)
{
    Document document;
    if (document.Parse(file_content.c_str()).HasParseError()) { // 파싱 오류 발생시 예외 throw
        std::string error_log = GetParseError_En(document.GetParseError());
        int error_offset = document.GetErrorOffset();

        throw std::runtime_error(error_log + " (" + std::to_string(error_offset) + ")\n");
    }

    return (document.HasMember("opened") && document["opened"].IsBool() && document["opened"].GetBool() == true);
}

/* jsonToTaskList()
용도 : json파일을 파싱해서 이중리스트로 변환
시퀀스 : FileManager에 의해 읽혀진 파일의 내용을 jsonParser가 파싱하고, 그 결과를 Schedule객체의 task_list멤버변수에 보관
고민 : 파일 열때 opened : false거나 opened가 없다면 어제자 내용을 가져와야함, 있다면 그대로 읽으면 됨
*/
void JsonParser::jsonToTaskList(std::string file_content)
{
    Document document;
    if (document.Parse(file_content.c_str()).HasParseError()) { // 파싱 오류 발생시 예외 throw
        std::string error_log = GetParseError_En(document.GetParseError());
        int error_offset = document.GetErrorOffset();

        throw std::runtime_error(error_log + " (" + std::to_string(error_offset) + ")\n");
    }

    // json -> 이중리스트 변환 후 schedule객체의 task_list에 덧붙이기
    Schedule& schedule = Schedule::instance();
    if (document.HasMember("Schedule") && document["Schedule"].IsArray()) {
        const Value& json_array = document["Schedule"];

        for (int i = 0; i < json_array.Size(); i++) {
            if (json_array[i].IsArray()) {
                const Value& inner_array = json_array[i];

                QList<Task> inner_list;
                for (int j = 0; j < inner_array.Size(); j++) {
                    if (inner_array[j].IsObject()) {
                        Task task;
                        if (inner_array[j].HasMember("title") && inner_array[j]["title"].IsString()) {
                            task.title = inner_array[j]["title"].GetString();
                        }
                        if (inner_array[j].HasMember("importance") && inner_array[j]["importance"].IsInt()) {
                            task.importance = inner_array[j]["importance"].GetInt();
                        }
                        inner_list.push_back(task);
                    }
                    // 만약 인코딩 문제가 생긴다면 UTF-8 to EUC-KR 코드 여기에 넣기
                    // 우선 현재까진 인코딩 문제 없는걸로 확인
                }
                schedule.task_list.push_back(inner_list);
            }
        }
    }
}
