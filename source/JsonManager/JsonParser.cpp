#include "JsonParser.h"

/* parse()
용도 : json 문구를 파싱
시퀀스 : FileReader에 의해 읽혀진 파일의 내용을 jsonParser가 파싱
특이사항 : 예외 발생시 예외는 이 함수 내부가 아닌 호출한 측에서 처리하며,
          이유는 parse()를 호출한 대상이 ProgramInfo인지 TaskListManager인지에 따라 처리방법이 다르므로 호출한 쪽에서 처리
*/
Document JsonParser::parse(const std::string& file_content)
{
    Document document;
    if(file_content.empty()) { // 파일에 아무 내용도 없을 때
        throw std::runtime_error("file content is empty");
    }
    else if (document.Parse(file_content.c_str()).HasParseError()) { // 파싱 오류가 발생했을 때
        std::string error_log = GetParseError_En(document.GetParseError());
        int error_offset = document.GetErrorOffset();

        throw std::runtime_error(error_log + " (" + std::to_string(error_offset) + ")");
    }

    return document;
}

/* jsonToProgramInfo()
용도 : program_info.json 파일을 파싱해서 프로그램에 필요한 정보로 변환
시퀀스 : ProgramInfo 클래스에 의해 호출됨. json 파일을 파싱한 결과에서 필요한 정보를 담아서 반환하면 ProgramInfo에서 해당 정보를 활용
*/
std::pair<bool, std::tuple<int, int, int>> JsonParser::jsonToProgramInfo(const std::string& file_content)
{
    Document document = parse(file_content.c_str()); // 주의! 예외는 여기서 처리 안하고 ProgramInfo에서 FileReader와 함께 처리

    bool tutorial = document["tutorial"].GetBool();
    int last_managed_date_year = document["last_managed_date_year"].GetInt();
    int last_managed_date_month = document["last_managed_date_month"].GetInt();
    int last_managed_date_day = document["last_managed_date_day"].GetInt();

    return make_pair(tutorial, std::make_tuple(last_managed_date_year, last_managed_date_month, last_managed_date_day)); // RVO 유도
}


/* jsonToTaskList()
용도 : 일정이 담겨있는 json파일을 파싱해서 이중리스트로 변환
시퀀스 : TaskListManager 클래스에 의해 호출됨. json 파일을 파싱한 결과를 프로그램에서 사용하는 이중리스트 형태로 변환 후 반환
특이사항 : parse()함수에서 예외가 발생시 예외를 처리하고 다시 예외를 던짐, 이유는 TaskListManager 측에서 예외가 발생한 파일명과 예외의 내용을 모두 확인하기 위함
*/
QList<QList<Task>> JsonParser::jsonToTaskList(const std::string& file_content)
{
    Document document;
    try {
        document = parse(file_content.c_str());
    }
    catch (const std::runtime_error& re) {
        document.Parse("{}"); // 일정파일이 비어있거나 손상된 경우 오류발생 방지를 위해 {} 삽입
        throw re; // 주의! 어느 파일에서 예외가 발생했는지 표기하기 위해 호출한측에서 예외를 받아서 출력하게 구현
    }

    QList<QList<Task>> parsed_result;
    // parse함수에서 문제가 발생한 경우는 그냥 빈 이중리스트를 리턴하기 위해 형식상 문제가 없는지 철저히 검사
    if (document.HasMember("Schedule") && document["Schedule"].IsArray()) {
        const Value& json_array = document["Schedule"];

        for (int i = 0; i < json_array.Size(); i++) {
            if (json_array[i].IsArray()) {
                const Value& inner_array = json_array[i];

                QList<Task> inner_result;
                for (int j = 0; j < inner_array.Size(); j++) {
                    if (inner_array[j].IsObject()) {
                        Task task;
                        if (inner_array[j].HasMember("title") && inner_array[j]["title"].IsString()) {
                            task.title = inner_array[j]["title"].GetString();
                        }
                        if (inner_array[j].HasMember("importance") && inner_array[j]["importance"].IsInt()) {
                            task.importance = inner_array[j]["importance"].GetInt();
                        }
                        inner_result.push_back(task);
                    }
                    // 만약 인코딩 문제가 생긴다면 UTF-8 to EUC-KR 코드 여기에 넣기
                    // 우선 현재까진 인코딩 문제 없는걸로 확인
                }
                parsed_result.push_back(inner_result);
            }
        }
    }

    return parsed_result;
}
