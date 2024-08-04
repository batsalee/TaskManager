#include "ScheduleFactory.h"

std::unique_ptr<Schedule> ScheduleFactory::makeSchedule()
{
    // 1) 날짜 획득
    Date& date = getDate(); // 팩토리 메서드

    // 2) 파일 열기
    // 이 부분 변경하기(date값 기반으로 파일경로 구성하도록 변경)
    FileReader fr("./Schedule/test.json"); // FileReader 객체 생성
    std::string file_content = fr.readFile(); // ★ 여기서 예외처리 나중에 파일 없으면 만드는 기능 추가하기
    // 위의 fr.readFile()리턴부분에서 RVO 컴파일러 최적화 믿고 move안쓰는걸로 변경

    // 3) 파일 내용 -> json 파싱
    Document document;
    try {
        if (document.Parse(file_content.c_str()).HasParseError())
            throw std::runtime_error("손상된 일정 파일입니다.");
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
        std::cerr << GetParseError_En(document.GetParseError()) << " (" << document.GetErrorOffset() << ")\n";
    }

    // 4) schedule 객체 생성
    std::unique_ptr<Schedule> schedule = std::make_unique<Schedule>();

    // 5) json -> 이중리스트 변환 후 schedule객체의 task_list멤버변수에 넣기
    // 이 부분 변경하기(jsonParser 객체 만들고 이 역할 하도록 만들기)
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
                schedule->task_list.push_back(inner_list);
            }
        }
    }

    return schedule;
}
