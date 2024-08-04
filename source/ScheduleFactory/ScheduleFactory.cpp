#include "ScheduleFactory.h"

/* makeSchedule()
용도 : ScheduleFactory에 의한 Schedule 객체 생성함수
시퀀스 :
    1) Schedule 객체 생성(멤버변수인 task_list에 일정내용을 입력하기 위해)
    2) 날짜정보 획득
    3) 파일 읽기 및 json 파싱 객체 생성
    4) 해당 날짜의 일정파일 확인, 있다면 task_list에 추가
    5) 매일 할일 파일 확인, task_list에 추가
    6) 해당 요일에 할일 확인, task_list에 추가
    7) Schedule 객체 반환
*/
/* 고민
    폴더나 파일은 저장하는 시점에 만들어도 된다.
    생성시점에는 오히려 필요한 일정들을 task_list에 넣기만 하면 된다.
    그러니 나중에 종료 로직 만들때 폴더 및 파일 만드는 로직 작성하기

     // 폴더 없으면 만들기
    if (!std::filesystem::exists(fr.getFolderPath()))
        std::filesystem::create_directories(fr.getFolderPath());

    // 파일 없으면 만들기
    if (!std::filesystem::exists(fr.getFilePath())) {
        // json통해서 파일내용 만들기
        // 만들어진 내용 로컬에 저장하기
    }
    */

std::unique_ptr<Schedule> ScheduleFactory::makeSchedule()
{
    // 1) Schedule 객체 생성(멤버변수인 task_list에 일정내용을 입력하기 위해)
    std::unique_ptr<Schedule> schedule = std::make_unique<Schedule>();

    // 2) 날짜정보 획득
    Date& date = getDate(); // 팩토리 메서드

    // 3) 파일 읽기 및 json 파싱 객체 생성
    FileReader file_reader; // 해당 날짜의 일정파일을 읽어오기 위해 FileReader 객체 생성
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    // 4) 해당 날짜의 일정파일 확인, 있다면 task_list에 추가
    file_reader.setPath(date);
    if (std::filesystem::exists(file_reader.getFilePath()))
        json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

    // 5) 매일 할일 파일 확인, task_list에 추가
    file_reader.setPath("everyday");
    json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

    // 6) 해당 요일에 할일 확인, task_list에 추가
    std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    file_reader.setPath(days[date.getDayOfWeek()]);
    json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

    return schedule;
}
