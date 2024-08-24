#include "JsonParser.h"

/* parse()
�뵵 : json ������ �Ľ�
������ : FileReader�� ���� ������ ������ ������ jsonParser�� �Ľ�
Ư�̻��� : ���� �߻��� ���ܴ� �� �Լ� ���ΰ� �ƴ� ȣ���� ������ ó���ϸ�,
          ������ parse()�� ȣ���� ����� ProgramInfo���� TaskListManager������ ���� ó������� �ٸ��Ƿ� ȣ���� �ʿ��� ó��
*/
Document JsonParser::parse(const std::string& file_content)
{
    Document document;
    if(file_content.empty()) { // ���Ͽ� �ƹ� ���뵵 ���� ��
        throw std::runtime_error("file content is empty");
    }
    else if (document.Parse(file_content.c_str()).HasParseError()) { // �Ľ� ������ �߻����� ��
        std::string error_log = GetParseError_En(document.GetParseError());
        int error_offset = document.GetErrorOffset();

        throw std::runtime_error(error_log + " (" + std::to_string(error_offset) + ")");
    }

    return document;
}

/* jsonToProgramInfo()
�뵵 : program_info.json ������ �Ľ��ؼ� ���α׷��� �ʿ��� ������ ��ȯ
������ : ProgramInfo Ŭ������ ���� ȣ���. json ������ �Ľ��� ������� �ʿ��� ������ ��Ƽ� ��ȯ�ϸ� ProgramInfo���� �ش� ������ Ȱ��
*/
std::pair<bool, std::tuple<int, int, int>> JsonParser::jsonToProgramInfo(const std::string& file_content)
{
    Document document = parse(file_content.c_str()); // ����! ���ܴ� ���⼭ ó�� ���ϰ� ProgramInfo���� FileReader�� �Բ� ó��

    bool tutorial = document["tutorial"].GetBool();
    int last_managed_date_year = document["last_managed_date_year"].GetInt();
    int last_managed_date_month = document["last_managed_date_month"].GetInt();
    int last_managed_date_day = document["last_managed_date_day"].GetInt();

    return make_pair(tutorial, std::make_tuple(last_managed_date_year, last_managed_date_month, last_managed_date_day)); // RVO ����
}


/* jsonToTaskList()
�뵵 : ������ ����ִ� json������ �Ľ��ؼ� ���߸���Ʈ�� ��ȯ
������ : TaskListManager Ŭ������ ���� ȣ���. json ������ �Ľ��� ����� ���α׷����� ����ϴ� ���߸���Ʈ ���·� ��ȯ �� ��ȯ
Ư�̻��� : parse()�Լ����� ���ܰ� �߻��� ���ܸ� ó���ϰ� �ٽ� ���ܸ� ����, ������ TaskListManager ������ ���ܰ� �߻��� ���ϸ�� ������ ������ ��� Ȯ���ϱ� ����
*/
QList<QList<Task>> JsonParser::jsonToTaskList(const std::string& file_content)
{
    Document document;
    try {
        document = parse(file_content.c_str());
    }
    catch (const std::runtime_error& re) {
        document.Parse("{}"); // ���������� ����ְų� �ջ�� ��� �����߻� ������ ���� {} ����
        throw re; // ����! ��� ���Ͽ��� ���ܰ� �߻��ߴ��� ǥ���ϱ� ���� ȣ���������� ���ܸ� �޾Ƽ� ����ϰ� ����
    }

    QList<QList<Task>> parsed_result;
    // parse�Լ����� ������ �߻��� ���� �׳� �� ���߸���Ʈ�� �����ϱ� ���� ���Ļ� ������ ������ ö���� �˻�
    if (document.HasMember("Schedule") && document["Schedule"].IsArray()) {
        const Value& json_array = document["Schedule"];

        for (int i = 0; i < json_array.Size(); i++) {
            if (json_array[i].IsArray()) {
                const Value& inner_array = json_array[i];

                QList<Task> inner_result;
                for (int j = 0; j < inner_array.Size(); j++) {
                    if (inner_array[j].IsObject()) {
                        Task task;
                        if (inner_array[j].HasMember("title") && inner_array[j]["title"].IsString()) {
                            task.title = inner_array[j]["title"].GetString();
                        }
                        if (inner_array[j].HasMember("importance") && inner_array[j]["importance"].IsInt()) {
                            task.importance = inner_array[j]["importance"].GetInt();
                        }
                        inner_result.push_back(task);
                    }
                    // ���� ���ڵ� ������ ����ٸ� UTF-8 to EUC-KR �ڵ� ���⿡ �ֱ�
                    // �켱 ������� ���ڵ� ���� ���°ɷ� Ȯ��
                }
                parsed_result.push_back(inner_result);
            }
        }
    }

    return parsed_result;
}
