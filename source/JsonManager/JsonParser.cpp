#include "JsonParser.h"

bool JsonParser::isOpened(std::string file_content)
{
    Document document;
    if (document.Parse(file_content.c_str()).HasParseError()) { // �Ľ� ���� �߻��� ���� throw
        std::string error_log = GetParseError_En(document.GetParseError());
        int error_offset = document.GetErrorOffset();

        throw std::runtime_error(error_log + " (" + std::to_string(error_offset) + ")\n");
    }

    return (document.HasMember("opened") && document["opened"].IsBool() && document["opened"].GetBool() == true);
}

/* jsonToTaskList()
�뵵 : json������ �Ľ��ؼ� ���߸���Ʈ�� ��ȯ
������ : FileManager�� ���� ������ ������ ������ jsonParser�� �Ľ��ϰ�, �� ����� Schedule��ü�� task_list��������� ����
��� : ���� ���� opened : false�ų� opened�� ���ٸ� ������ ������ �����;���, �ִٸ� �״�� ������ ��
*/
void JsonParser::jsonToTaskList(std::string file_content)
{
    Document document;
    if (document.Parse(file_content.c_str()).HasParseError()) { // �Ľ� ���� �߻��� ���� throw
        std::string error_log = GetParseError_En(document.GetParseError());
        int error_offset = document.GetErrorOffset();

        throw std::runtime_error(error_log + " (" + std::to_string(error_offset) + ")\n");
    }

    // json -> ���߸���Ʈ ��ȯ �� schedule��ü�� task_list�� �����̱�
    Schedule& schedule = Schedule::instance();
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
                schedule.task_list.push_back(inner_list);
            }
        }
    }
}
