#include "Initializer.h"

// -1) initializer
/*
        1) "./Data/init.json" ����
        2) �� ���� �Ľ�
        3)     "is_first_time": false, "last_managed_date_year": 2024,"last_managed_date_month": 8,"last_managed_date_day": 18
        �� ������ ���� ���
        4) ���� ��¥�� �ٸ��� makeSchedule, ��¥�� ���ٸ� �׳� �о�ͼ� �Ľ�
    */

void Initializer::init()
{
    FileReader file_reader;
    JsonParser json_parser;

    try {
        file_reader.setPath("./Data/init.json");

        json_parser.parse(file_reader.readFile());
        tutorial = json_parser.document["tutorial"].GetBool();
        last_managed_date_year = json_parser.document["last_managed_date_year"].GetInt();
        last_managed_date_month = json_parser.document["last_managed_date_month"].GetInt();
        last_managed_date_day = json_parser.document["last_managed_date_day"].GetInt();
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
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
