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
    Date& date = Date::instance(); // �����ڿ� ���� ���� ��¥�� ���� ����
    Schedule& schedule = Schedule::instance(); // ��ü�� �����Ǿ��ְ� task_list�� �������

    FileReader file_reader; // �θ�Ŭ������ FileManager�� �����ڿ� ���� ���� ��¥ ��� ��� ����
    JsonParser json_parser; // ���� ������ json�����̹Ƿ� �Ľ̴�� ��ü ����

    if(isTutorialNeeded()) { // ���� �� ���α׷��� ó�� ����غ��ٸ� Ʃ�丮�� ����, ���� ����߰��� ������ ����
        Tutorial tutorial;
        tutorial.startTutorial();
    }

    if(isOpenedToday(date) && std::filesystem::exists(file_reader.getFilePath())) { // ���� �̹� ������ ���� �־ ������ task_list�� ��������ִٸ� ���� ��¥�� ���������� �״�� ������
        json_parser.jsonToTaskList(file_reader.readFile());
    }
    else { // ���� ó�� �����ϴ� ���̶�� ������ task_list �����
        // 1) ���� ��¥�� ������ �߰��� ������ �ִٸ� �ݿ�
        if (std::filesystem::exists(file_reader.getFilePath())) json_parser.jsonToTaskList(file_reader.readFile());

        // 2) ���� ���Ϸ� ������ ������ �ִٸ� �ݿ�
        file_reader.setPath("./Data/fixed_schedule/everyday.json");
        json_parser.jsonToTaskList(file_reader.readFile());

        // 3) ���� ���Ͽ� ���Ϸ� ������ ������ �ִٸ� �ݿ�
        std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
        file_reader.setPath("./Data/fixed_schedule/" + days[date.getDayOfWeek()] + ".json");
        json_parser.jsonToTaskList(file_reader.readFile());

        // 4) ������ ���ϰ� ���ܵ� ���� �ִٸ� �ݿ�
        std::string year_of_remaining_schedule = std::to_string(last_managed_date_year);
        std::string month_of_remaining_schedule = (last_managed_date_month < 10) ? '0' + std::to_string(last_managed_date_month) : std::to_string(last_managed_date_month);
        std::string day_of_remaining_schedule = (last_managed_date_day < 10) ? '0' + std::to_string(last_managed_date_day) : std::to_string(last_managed_date_day);
        std::string remaining_file_path = "./Data/" + year_of_remaining_schedule + "/" + month_of_remaining_schedule + "/" + day_of_remaining_schedule + ".json";
        if (std::filesystem::exists(remaining_file_path)) {
            file_reader.setPath(remaining_file_path);
            json_parser.jsonToTaskList(file_reader.readFile(), true);
        }

        // 5) init.json�� �ֱ� �������� ���÷� ����
        JsonSerializer json_serializer;
        std::string context = json_serializer.initializerToJson(date.getYear(), date.getMonth(), date.getDay());

        FileWriter file_writer;
        file_writer.setPath("./Data/init.json");
        file_writer.writeFile(context);

        // 6) ������ �������� ��� �ݿ�
        // �� �κ��� ������ ���α׷� ����� �����ϸ鼭 �ݿ������� ���α׷� ������ ���ῡ ���� ������ �ʿ��ϴٴ� �ǵ�鿡 ���� �߰�
        // ���� ���� �߰��� ��¥ ���� ��ɿ� ���� �ٸ� ��¥���� ���� ��¥�� ���ƿö� ���������� ���� �߰� ������ �ݿ��� �ʿ䰡 �������� ȿ���� ����
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
