#include "TaskListManager.h"

/* ���
��¥ ������ �� Ŭ������ ������ �ȴ�.
�ٵ� ���� ���������� �����Ѵٸ� ��θ鿡�� ������ �����.
�׷��� ���� ������ Ŭ���� ����ȭ�ؼ� ���ø��޼���ȭ �ؾ��Ҽ��� �ִ�.
*/



TaskListManager& TaskListManager::instance()
{
    static TaskListManager instance;
    return instance;
}

void TaskListManager::loadTaskList()
{
    FileReader file_reader; // �θ�Ŭ������ FileManager�� �����ڿ� ���� ���� �������� ��¥ ��� ��� ����
    JsonParser json_parser; // ���� ������ json�����̹Ƿ� �Ľ̴�� ��ü ����

    try {
        if (std::filesystem::exists(file_reader.getFilePath())) { // �ش� ��¥�� ������ �߰��� ������ �ִٸ� task_list�� �߰�
            std::string file_content = file_reader.readFile(); // RVO ����
            task_list = json_parser.jsonToTaskList(file_content);
        }
        else {
            throw std::runtime_error("file does not exist");
        }
    }
    catch(const std::runtime_error& re) {
        task_list.clear();
        std::cerr << std::string(re.what()) + "(" + file_reader.getFilePath() << ")\n";
    }
}

void TaskListManager::appendList(QList<QList<Task>> appended_list)
{
    for (const auto& inner_list : appended_list) {
        task_list.append(inner_list);
    }
}

void TaskListManager::makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day)
{
    FileReader file_reader; // �θ�Ŭ������ FileManager�� �����ڿ� ���� ���� �������� ��¥ ��� ��� ����
    JsonParser json_parser; // ���� ������ json�����̹Ƿ� �Ľ̴�� ��ü ����

    std::string file_content;
    QList<QList<Task>> appended_list;


    /* ���
    �Ʒ� ����ó���� ���� �ϳ��� �߸��ŵ� �ٸ� ���ϵ��� �����̶�� �ݿ�����, �׷��ٸ� try�� �ϳ��� ����� ��
    �ݸ� �ϳ��� �߸��Ǹ� �������� �����ϰ� ������ �ϹǷ� try�� ��ü�� ���°� �°� ��
    */
    try {
        // 1) ���� ��¥�� ������ �߰��� ������ �ִٸ� �ݿ�
        if (std::filesystem::exists(file_reader.getFilePath())) {
            file_content = file_reader.readFile(); // RVO ����
            task_list = json_parser.jsonToTaskList(file_content);
        } // ������ ��� �̻��Ѱ� �ƴϹǷ� else ����

        // 2) ���� ���Ϸ� ������ ������ �ִٸ� �ݿ�
        file_reader.setPath("./Data/fixed_schedule/everyday.json");
        file_content = file_reader.readFile(); // RVO ����
        appended_list = json_parser.jsonToTaskList(file_content);
        appendList(appended_list);

        // 3) ���� ���Ͽ� ���Ϸ� ������ ������ �ִٸ� �ݿ�
        std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
        file_reader.setPath("./Data/fixed_schedule/" + days[Date::instance().getDayOfWeek()] + ".json");
        file_content = file_reader.readFile(); // RVO ����
        appended_list = json_parser.jsonToTaskList(file_content);
        appendList(appended_list);

        // 4) ������ ���ϰ� ���ܵ� ���� �ִٸ� �ݿ�
        std::string year_of_remaining_schedule = std::to_string(last_managed_date_year);
        std::string month_of_remaining_schedule = (last_managed_date_month < 10) ? '0' + std::to_string(last_managed_date_month) : std::to_string(last_managed_date_month);
        std::string day_of_remaining_schedule = (last_managed_date_day < 10) ? '0' + std::to_string(last_managed_date_day) : std::to_string(last_managed_date_day);
        std::string remaining_file_path = "./Data/" + year_of_remaining_schedule + "/" + month_of_remaining_schedule + "/" + day_of_remaining_schedule + ".json";
        if (std::filesystem::exists(remaining_file_path)) {
            file_reader.setPath(remaining_file_path);
            file_content = file_reader.readFile(); // RVO ����
            appended_list = json_parser.jsonToTaskList(file_content);
            adjustImportance(appended_list);
            appendList(appended_list);
        }
    }
    catch(const std::runtime_error& re) {
        // ���峭 ���� ���ۼ��ϰ� ����� ������ �߰��Ѵٸ� ���⿡
        std::cerr << std::string(re.what()) + "(" + file_reader.getFilePath() << ")\n";
    }
}

// ���ϰ� ���ܵ� �ϵ� �߿䵵 ���̱�
void TaskListManager::adjustImportance(QList<QList<Task>> remaining_list)
{
    for(auto& rl : remaining_list){
        for(auto& task : rl) {
            if(task.importance != 1) task.importance = 2;
        }
    }
}

/*
�����ϴ� ����
����ó�� �ʿ��Ѱ� ���⵵?
*/
Q_INVOKABLE void TaskListManager::saveTaskList()
{
    JsonSerializer json_serializer;
    std::string json_content = json_serializer.taskListToJson(task_list);

    FileWriter file_writer;
    file_writer.writeFile(json_content);
}


/* GetScheduleList()
�뵵 : C++�� QML�� integration������ Q_PROPERTY�Ӽ��� READ�Լ�
������ : QML���� Window�� ��ﶧ ListView�� ������ ���� �ϹǷ� �ش� �Լ��� ���� ����
*/
QList<QList<Task>> TaskListManager::getTaskList()
{
    return task_list;
}

/* insertTask()
�뵵 : ����ڰ� ����� ������ ���� ���ܼ� �߰��ϰ� ������ ȣ��
������ : QML���� Button ���� �� �ߴ� TextInputWindow�� ������ �Է��ϰ� ���͸� ġ�� �ش� ������ ListView�� �ֻ�ܿ� �߰���
��� : version 1.0���� #���� ������ �Է½� �и��ϰ� �߾��µ� �̰Ŷ����� C#���� �ܾ ������ ���߾���
      �׷��� �ش� ����� �������� ���������� ���� ��� �� �ش� ����� ���Ŀ� GUI���� �߰� �����ϵ��� �����ϴ°� �´ٰ� �Ǵ��ؼ� �켱 ����
*/
Q_INVOKABLE void TaskListManager::insertTask(QString inserted_task)
{
    QList<Task> new_task_list = { Task{inserted_task, 1} }; // ���� �߰��� QList
    task_list.push_front(new_task_list);
    emit ListChanged();
}

/* updateTask()
�뵵 : ����ڰ� ������ ������ �����ϰ� ������ ȣ��
������ : QML���� ListView�� ��Ÿ���ִ� �������� Rectangle���� �ϳ��� ����(task)�� �������
        �ش� task�� ������ �����ϰ� ������ ��Ŭ�� �� ���� �Է� �� ���ͽ� ����
*/
Q_INVOKABLE void TaskListManager::updateTask(int y, int x, QString updated_task)
{
    task_list[y][x].title = updated_task;
    emit ListChanged();
}

/* deleteTask()
�뵵 : ����ڰ� ������ ������ �Ϸ��ؼ� ��Ͽ��� ����� ������ ȣ��
������ : QML���� ListView�� ��Ÿ���ִ� �������� Rectangle ��
        ����ڰ� �Ϸ��� task�� ����Ŭ���ϸ� �� �Լ��� ȣ��Ǿ� �ش� ������ task_list���� ������
*/
Q_INVOKABLE void TaskListManager::deleteTask(int y, int x)
{
    task_list[y].removeAt(x);
    if(task_list[y].empty()) task_list.removeAt(y);

    emit ListChanged();
}
