#include "Schedule.h"

// ����� ������� �׽�Ʈ��
#include "../JsonManager/JsonSerializer.h"
#include "../FileManager/FileWriter.h"

Schedule& Schedule::instance()
{
    static Schedule instance;
    return instance;
}

void Schedule::makeTaskList()
{
    FileReader file_reader; // �θ�Ŭ������ FileManager�� �����ڿ� ���� ���� ��¥ ��� ��� ����
    JsonParser json_parser; // ���� ������ json�����̹Ƿ� �Ľ̴�� ��ü ����

    Date& date = Date::instance();

    if (std::filesystem::exists(file_reader.getFilePath())) { // ���� ������ �߰��� ������ �ִٸ� task_list�� �߰�
        json_parser.jsonToTaskList(file_reader.readFile());
    }

    file_reader.setPath("./Data/fixed_schedule/everyday.json"); // ���� ���� ������ �о�� �� task_list�� �߰�
    json_parser.jsonToTaskList(file_reader.readFile());

    std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    file_reader.setPath("./Data/fixed_schedule/" + days[date.getDayOfWeek()] + ".json"); // �ش� ���Ͽ� ���� ������ �о�� �� task_list�� �߰�
    json_parser.jsonToTaskList(file_reader.readFile());
}

/* GetScheduleList()
�뵵 : C++�� QML�� integration������ Q_PROPERTY�Ӽ��� READ�Լ�
������ : QML���� Window�� ��ﶧ ListView�� ������ ���� �ϹǷ� �ش� �Լ��� ���� ����
*/
QList<QList<Task>> Schedule::GetScheduleList()
{
    return task_list;
}

/* insertTask()
�뵵 : ����ڰ� ����� ������ ���� ���ܼ� �߰��ϰ� ������ ȣ��
������ : QML���� Button ���� �� �ߴ� TextInputWindow�� ������ �Է��ϰ� ���͸� ġ�� �ش� ������ ListView�� �ֻ�ܿ� �߰���
��� : version 1.0���� #���� ������ �Է½� �и��ϰ� �߾��µ� �̰Ŷ����� C#���� �ܾ ������ ���߾���
      �׷��� �ش� ����� �������� ���������� ���� ��� �� �ش� ����� ���Ŀ� GUI���� �߰� �����ϵ��� �����ϴ°� �´ٰ� �Ǵ��ؼ� �켱 ����
*/
Q_INVOKABLE void Schedule::insertTask(QString inserted_task)
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
Q_INVOKABLE void Schedule::updateTask(int y, int x, QString updated_task)
{
    task_list[y][x].title = updated_task;
    emit ListChanged();
}

/* deleteTask()
�뵵 : ����ڰ� ������ ������ �Ϸ��ؼ� ��Ͽ��� ����� ������ ȣ��
������ : QML���� ListView�� ��Ÿ���ִ� �������� Rectangle ��
        ����ڰ� �Ϸ��� task�� ����Ŭ���ϸ� �� �Լ��� ȣ��Ǿ� �ش� ������ task_list���� ������
*/
Q_INVOKABLE void Schedule::deleteTask(int y, int x)
{
    task_list[y].removeAt(x);
    if(task_list[y].empty()) task_list.removeAt(y);

    emit ListChanged();
}

/*
����� �����ϴ� ���� �׽�Ʈ��
*/
Schedule::~Schedule()
{
    JsonSerializer js;
    std::string _json = js.taskListToJson(task_list);

    FileWriter fw;
    fw.writeFile(_json);
}
