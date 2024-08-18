#include "Initializer.h"

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
        // 1) 오늘 날짜에 사전에 추가한 일정이 있다면 반영
        if (std::filesystem::exists(file_reader.getFilePath())) json_parser.jsonToTaskList(file_reader.readFile());

        // 2) 매일 할일로 설정된 내용이 있다면 반영
        file_reader.setPath("./Data/fixed_schedule/everyday.json");
        json_parser.jsonToTaskList(file_reader.readFile());

        // 3) 오늘 요일에 할일로 설정된 내용이 있다면 반영
        std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
        file_reader.setPath("./Data/fixed_schedule/" + days[date.getDayOfWeek()] + ".json");
        json_parser.jsonToTaskList(file_reader.readFile());

        // 4) 지난날 안하고 남겨둔 일이 있다면 반영
        std::string year_of_remaining_schedule = std::to_string(last_managed_date_year);
        std::string month_of_remaining_schedule = (last_managed_date_month < 10) ? '0' + std::to_string(last_managed_date_month) : std::to_string(last_managed_date_month);
        std::string day_of_remaining_schedule = (last_managed_date_day < 10) ? '0' + std::to_string(last_managed_date_day) : std::to_string(last_managed_date_day);
        std::string remaining_file_path = "./Data/" + year_of_remaining_schedule + "/" + month_of_remaining_schedule + "/" + day_of_remaining_schedule + ".json";
        if (std::filesystem::exists(remaining_file_path)) {
            file_reader.setPath(remaining_file_path);
            json_parser.jsonToTaskList(file_reader.readFile(), true);
        }

        // 5) init.json에 최근 관리일자 오늘로 변경
        JsonSerializer json_serializer;
        std::string context = json_serializer.initializerToJson(date.getYear(), date.getMonth(), date.getDay());

        FileWriter file_writer;
        file_writer.setPath("./Data/init.json");
        file_writer.writeFile(context);

        // 6) 오늘의 일정파일 즉시 반영
        // 이 부분은 어차피 프로그램 종료시 저장하면서 반영되지만 프로그램 비정상 종료에 대한 대응이 필요하다는 피드백에 따라 추가
        // 또한 추후 추가될 날짜 변경 기능에 대해 다른 날짜에서 오늘 날짜로 돌아올때 고정일정에 대한 추가 로직을 반영할 필요가 없어지는 효과도 있음
        context = json_serializer.taskListToJson(schedule.task_list);
        file_writer.setPath(date);
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
