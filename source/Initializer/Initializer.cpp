#include "Initializer.h"

// -1) initializer
/*
        1) "./Data/init.json" 열기
        2) 위 내용 파싱
        3)     "is_first_time": false, "last_managed_date_year": 2024,"last_managed_date_month": 8,"last_managed_date_day": 18
        위 변수들 정보 얻기
        4) 만약 날짜가 다르면 makeSchedule, 날짜가 같다면 그냥 읽어와서 파싱
    */

Initializer::Initializer()
{
    FileReader file_reader;
    JsonParser json_parser;

    try {
        file_reader.setPath("./Data/init.json");
        Document document = json_parser.parse(file_reader.readFile());

        tutorial = document["tutorial"].GetBool();
        last_managed_date_year = document["last_managed_date_year"].GetInt();
        last_managed_date_month = document["last_managed_date_month"].GetInt();
        last_managed_date_day = document["last_managed_date_day"].GetInt();
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
    }
}

void Initializer::Init()
{
    Date& date = Date::instance(); // 생성자에 의해 오늘 날짜로 정보 설정
    Schedule& schedule = Schedule::instance(); // 객체만 생성되어있고 task_list는 비어있음

    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 오늘 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    if(isTutorialNeeded()) { // 만약 이 프로그램을 처음 사용해본다면 튜토리얼 시작, 추후 기능추가때 구현할 예정
        Tutorial tutorial;
        tutorial.startTutorial();
    }

    if(isOpenedToday(date) && std::filesystem::exists(file_reader.getFilePath())) { // 오늘 이미 실행한 적이 있어서 오늘의 task_list가 만들어져있다면 오늘 날짜의 일정파일을 그대로 가져옴
        json_parser.jsonToTaskList(file_reader.readFile());
    }
    else { // 오늘 처음 실행하는 것이라면 오늘의 task_list 만들기
        schedule.makeTaskList(); // 고민 이거 내용 여기다 그냥 해도 되는거 아닌가? 왜 스케쥴 안에 적엇지?
                                // 그냥 여기다 하면 이전날짜 정보도 여기서 추가하면 되는데 훨씬 쉬워질듯 함

        JsonSerializer json_serializer;
        std::string context = json_serializer.initializerToJson(date.getYear(), date.getMonth(), date.getDay());

        FileWriter file_writer;
        file_writer.setPath("./Data/init.json");
        file_writer.writeFile(context);
    }
}

bool Initializer::isTutorialNeeded()
{
    return tutorial;
}

bool Initializer::isOpenedToday(Date& date)
{
    return (date.getYear() == last_managed_date_year && date.getMonth() == last_managed_date_month && date.getDay() == last_managed_date_day);
}
