#include "ScheduleFactory.h"

/* makeSchedule()
�뵵 : ScheduleFactory�� ���� Schedule ��ü �����Լ�
������ :
    1) Schedule ��ü ����(��������� task_list�� ���������� �Է��ϱ� ����)
    2) ��¥���� ȹ��
    3) ���� �б� �� json �Ľ� ��ü ����
    4) �ش� ��¥�� �������� Ȯ��, �ִٸ� task_list�� �߰�
    5) ���� ���� ���� Ȯ��, task_list�� �߰�
    6) �ش� ���Ͽ� ���� Ȯ��, task_list�� �߰�
    7) Schedule ��ü ��ȯ
*/
/* ���
    ������ ������ �����ϴ� ������ ���� �ȴ�.
    ������������ ������ �ʿ��� �������� task_list�� �ֱ⸸ �ϸ� �ȴ�.
    �׷��� ���߿� ���� ���� ���鶧 ���� �� ���� ����� ���� �ۼ��ϱ�

     // ���� ������ �����
    if (!std::filesystem::exists(fr.getFolderPath()))
        std::filesystem::create_directories(fr.getFolderPath());

    // ���� ������ �����
    if (!std::filesystem::exists(fr.getFilePath())) {
        // json���ؼ� ���ϳ��� �����
        // ������� ���� ���ÿ� �����ϱ�
    }
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

    // 4) �ش� ��¥�� �������� Ȯ��, �ִٸ� task_list�� �߰�
    file_reader.setPath(date);
    if (std::filesystem::exists(file_reader.getFilePath()))
        json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

    // 5) ���� ���� ���� Ȯ��, task_list�� �߰�
    file_reader.setPath("everyday");
    json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

    // 6) �ش� ���Ͽ� ���� Ȯ��, task_list�� �߰�
    std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    file_reader.setPath(days[date.getDayOfWeek()]);
    json_parser.jsonToTaskList(schedule.get(), file_reader.readFile());

    return schedule;
}
