#include "ProgramInfo.h"

#include <tuple>

/* ProgramInfo()
�뵵 : ������, program_info.json���� ���� ȹ��
������ : ���α׷� ���� �� �����Ǿ� program_info.json ������ �а� �Ľ��ؼ� �ʿ��� ������ ȹ��
*/
ProgramInfo::ProgramInfo()
{
    FileReader file_reader;
    JsonParser json_parser;

    file_reader.setPath("./Data/program_info.json");
    try {
        std::string file_content = file_reader.readFile(); // RVO ����

        std::pair<bool, std::tuple<int, int, int>> program_info = json_parser.jsonToProgramInfo(file_content);
        tutorial = program_info.first;
        last_managed_date_year = std::get<0>(program_info.second);
        last_managed_date_month = std::get<1>(program_info.second);
        last_managed_date_day = std::get<2>(program_info.second);
    }
    catch(const std::runtime_error& re) {
        tutorial = true;
        last_managed_date_year = last_managed_date_month = last_managed_date_day = 0;

        std::cerr << std::string(re.what()) + "(" + file_reader.getFilePath() << ")\n";
    }
}

/* ~ProgramInfo()
�뵵 : �Ҹ���, ���α׷��� ������ program_info.json�� ����
������ : ���α׷� ���� ���� �۾��� ������ ���� �� �̻� �ʿ�����Ƿ� �Ҹ�Ǹ� ���� ���α׷��� �����͸� program_info.json�� ����
*/
ProgramInfo::~ProgramInfo()
{
    Date& date = Date::instance();

    JsonSerializer json_serializer;
    std::string context = json_serializer.programInfoToJson(date.getYear(), date.getMonth(), date.getDay());

    FileWriter file_writer;
    file_writer.setPath("./Data/program_info.json");
    file_writer.writeFile(context);
}

/* isTutorialNeeded()
�뵵 : ���α׷� ��ġ �� ���� ����� Ʃ�丮�� �ʿ� ���� Ȯ��
������ : ���α׷� ��ġ �� ���ʷ� �����Ѵٸ� program_info.json�� tutorial ���� true�̹Ƿ� Ʃ�丮���� ����
*/
bool ProgramInfo::isTutorialNeeded()
{
    return tutorial;
}

/* isOpenedToday()
�뵵 : ���� ���α׷��� �� ���� �ִٸ� �̹� ���� ������ ������� ������ load�� �ϸ� �ǰ�, ���� ó�� ���α׷��� �����ٸ� ���� ������ make�ؾ� ��. �̸� �Ǵ��ϱ� ���� �Լ�
������ : program_info.json ���Ͽ��� ���� �ֱٿ� ���α׷��� ����� ���ڰ� ��ϵǾ� ����.
        �ش� ���ڸ� Ȯ���� �� ������ ��¥�� ���ٸ� TaskListManager Ŭ������ loadTaskList() �Լ��� ���, �ٸ��ٸ� TaskListManager Ŭ������ makeTaskList() �Լ��� ���
*/
bool ProgramInfo::isOpenedToday(Date& date)
{
    return (date.getYear() == last_managed_date_year && date.getMonth() == last_managed_date_month && date.getDay() == last_managed_date_day);
}

/* getLastManagedDateYear(), getLastManagedDateMonth(), getLastManagedDateDay()
�뵵 : getter
������ : isOpendToday()���� false�� �����ϸ� TaskListManager Ŭ������ MakeTaskList() �Լ��� ȣ��Ǵµ� �̶� �Ʒ��� getter���� �̿��� ������ �Ű������� �ѱ�.
        �Ű������� �Ѿ ������ ���� ������ ���� �ֱٿ� ���α׷��� ����� ��¥�̹Ƿ� �ش� ��¥�� ���� ������ Ȯ���ؼ� ���� ������ �ִٸ� ������ ������ append��
*/
int ProgramInfo::getLastManagedDateYear() const { return last_managed_date_year; }
int ProgramInfo::getLastManagedDateMonth() const { return last_managed_date_month; }
int ProgramInfo::getLastManagedDateDay() const { return last_managed_date_day; }
