#include "Initializer.h"

// -1) initializer
/*
        1) "./Data/init.json" ����
        2) �� ���� �Ľ�
        3)     "is_first_time": false, "last_managed_date_year": 2024,"last_managed_date_month": 8,"last_managed_date_day": 18
        �� ������ ���� ���
        4) ���� ��¥�� �ٸ��� makeSchedule, ��¥�� ���ٸ� �׳� �о�ͼ� �Ľ�
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
        schedule.makeTaskList(); // ��� �̰� ���� ����� �׳� �ص� �Ǵ°� �ƴѰ�? �� ������ �ȿ� ������?
                                // �׳� ����� �ϸ� ������¥ ������ ���⼭ �߰��ϸ� �Ǵµ� �ξ� �������� ��

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
