#include "ScheduleFactory.h"

std::unique_ptr<Schedule> ScheduleFactory::makeSchedule()
{
    // 1) ��¥ ȹ��
    Date& date = getDate(); // ���丮 �޼���

    // 2) ���� ����
    // �� �κ� �����ϱ�(date�� ������� ���ϰ�� �����ϵ��� ����)
    FileReader fr("./Schedule/test.json"); // FileReader ��ü ����
    std::string file_content = fr.readFile(); // �� ���⼭ ����ó�� ���߿� ���� ������ ����� ��� �߰��ϱ�
    // ���� fr.readFile()���Ϻκп��� RVO �����Ϸ� ����ȭ �ϰ� move�Ⱦ��°ɷ� ����

    // 3) ���� ���� -> json �Ľ�
    Document document;
    try {
        if (document.Parse(file_content.c_str()).HasParseError())
            throw std::runtime_error("�ջ�� ���� �����Դϴ�.");
    }
    catch(const std::runtime_error& re) {
        std::cerr << re.what() << '\n';
        std::cerr << GetParseError_En(document.GetParseError()) << " (" << document.GetErrorOffset() << ")\n";
    }

    // 4) schedule ��ü ����
    std::unique_ptr<Schedule> schedule = std::make_unique<Schedule>();

    // 5) json -> ���߸���Ʈ ��ȯ �� schedule��ü�� task_list��������� �ֱ�
    // �� �κ� �����ϱ�(jsonParser ��ü ����� �� ���� �ϵ��� �����)
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
                    // ���� ���ڵ� ������ ����ٸ� UTF-8 to EUC-KR �ڵ� ���⿡ �ֱ�
                    // �켱 ������� ���ڵ� ���� ���°ɷ� Ȯ��
                }
                schedule->task_list.push_back(inner_list);
            }
        }
    }

    return schedule;
}
