#include "Schedule.h"

// 종료시 저장로직 테스트중
#include "../JsonManager/JsonSerializer.h"
#include "../FileManager/FileWriter.h"

Schedule& Schedule::instance()
{
    static Schedule instance;
    return instance;
}

void Schedule::makeTaskList()
{
    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 오늘 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    Date& date = Date::instance();

    if (std::filesystem::exists(file_reader.getFilePath())) { // 오늘 별도로 추가된 일정이 있다면 task_list에 추가
        json_parser.jsonToTaskList(file_reader.readFile());
    }

    file_reader.setPath("./Data/fixed_schedule/everyday.json"); // 매일 할일 파일을 읽어온 후 task_list에 추가
    json_parser.jsonToTaskList(file_reader.readFile());

    std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    file_reader.setPath("./Data/fixed_schedule/" + days[date.getDayOfWeek()] + ".json"); // 해당 요일에 할일 파일을 읽어온 후 task_list에 추가
    json_parser.jsonToTaskList(file_reader.readFile());
}

/* GetScheduleList()
용도 : C++과 QML의 integration에서의 Q_PROPERTY속성의 READ함수
시퀀스 : QML에서 Window를 띄울때 ListView의 내용을 얻어야 하므로 해당 함수를 통해 얻음
*/
QList<QList<Task>> Schedule::GetScheduleList()
{
    return task_list;
}

/* insertTask()
용도 : 사용자가 사용중 할일이 새로 생겨서 추가하고 싶을때 호출
시퀀스 : QML에서 Button 누른 후 뜨는 TextInputWindow에 내용을 입력하고 엔터를 치면 해당 내용이 ListView의 최상단에 추가됨
고민 : version 1.0에서 #으로 여러개 입력시 분리하게 했었는데 이거때문에 C#같은 단어를 쓰지를 못했었음
      그래서 해당 기능을 유지할지 삭제할지에 대한 고민 후 해당 기능은 추후에 GUI에서 추가 가능하도록 구현하는게 맞다고 판단해서 우선 삭제
*/
Q_INVOKABLE void Schedule::insertTask(QString inserted_task)
{
    QList<Task> new_task_list = { Task{inserted_task, 1} }; // 새로 추가될 QList
    task_list.push_front(new_task_list);
    emit ListChanged();
}

/* updateTask()
용도 : 사용자가 할일의 내용을 변경하고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle에는 하나의 할일(task)가 들어있음
        해당 task의 내용을 변경하고 싶을때 우클릭 후 내용 입력 후 엔터시 변경
*/
Q_INVOKABLE void Schedule::updateTask(int y, int x, QString updated_task)
{
    task_list[y][x].title = updated_task;
    emit ListChanged();
}

/* deleteTask()
용도 : 사용자가 할일의 내용을 완료해서 목록에서 지우고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle 중
        사용자가 완료한 task를 더블클릭하면 이 함수가 호출되어 해당 내용이 task_list에서 지워짐
*/
Q_INVOKABLE void Schedule::deleteTask(int y, int x)
{
    task_list[y].removeAt(x);
    if(task_list[y].empty()) task_list.removeAt(y);

    emit ListChanged();
}

/*
종료시 저장하는 로직 테스트중
*/
Schedule::~Schedule()
{
    JsonSerializer js;
    std::string _json = js.taskListToJson(task_list);

    FileWriter fw;
    fw.writeFile(_json);
}
