#include "ScheduleFactory.h"

/* makeSchedule()
�뵵 : ScheduleFactory�� ���� Schedule ��ü �����Լ�
������ :
    1) Schedule ��ü ����(��������� task_list�� ���������� �Է��ϱ� ����)
    2) ��¥���� ȹ��(���丮 �޼���)
    3) ���� �б� �� json �Ľ� ��ü ����
    4) �ش� ��¥�� �������� Ȯ��, �ִٸ� task_list�� �߰�
    5) ���� ���� ���� Ȯ��, task_list�� �߰�
    6) �ش� ���Ͽ� ���� Ȯ��, task_list�� �߰�
    7) Schedule ��ü ��ȯ
*/
std::unique_ptr<Schedule> ScheduleFactory::makeSchedule()
{
    // 1) Schedule ��ü ����(��������� task_list�� ���������� �Է��ϱ� ����)
    std::unique_ptr<Schedule> schedule = std::make_unique<Schedule>();

    // 2) ��¥���� ȹ��
    Date& date = getDate(); // ���丮 �޼���

    // 3) ���� �б� �� json �Ľ� ��ü ����
    FileReader file_reader; // �ش� ��¥�� ���������� �о���� ���� FileReader ��ü ����
    JsonParser json_parser; // ���� ������ json�����̹Ƿ� �Ľ̴�� ��ü ����

    try {
        // �̹� ���� ������ ������ٸ� �״�� �о����
        // ���� ó�� �����ϴ°Ŷ�� task_list�� ������ ���� �߰�
        file_reader.setPath(date);
        if (std::filesystem::exists(file_reader.getFilePath()) && json_parser.isOpened(file_reader.readFile())) {
            json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());
        }
        else {
            // 4) �ش� ��¥�� �������� Ȯ��, �ִٸ� task_list�� �߰�
            if (std::filesystem::exists(file_reader.getFilePath())) {
                json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());
            }

            // 5) ���� ���� ���� Ȯ��, task_list�� �߰�
            file_reader.setPath("everyday");
            json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

            // 6) �ش� ���Ͽ� ���� Ȯ��, task_list�� �߰�
            std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
            file_reader.setPath(days[date.getDayOfWeek()]);
            json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());
        }
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
    }

    return schedule;
}
