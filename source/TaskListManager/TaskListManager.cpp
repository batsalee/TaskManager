#include "TaskListManager.h"

/* 고민
날짜 파일은 이 클래스로 정리가 된다.
근데 만약 고정일정을 편집한다면 경로면에서 문제가 생긴다.
그러니 일정 관리도 클래스 계층화해서 템플릿메서드화 해야할수도 있다.
*/



TaskListManager& TaskListManager::instance()
{
    static TaskListManager instance;
    return instance;
}

void TaskListManager::loadTaskList()
{
    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 현재 관리중인 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    try {
        if (std::filesystem::exists(file_reader.getFilePath())) { // 해당 날짜에 별도로 추가된 일정이 있다면 task_list에 추가
            std::string file_content = file_reader.readFile(); // RVO 유도
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
    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 현재 관리중인 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    std::string file_content;
    QList<QList<Task>> appended_list;


    /* 고민
    아래 예외처리는 파일 하나가 잘못돼도 다른 파일들은 정상이라면 반영할지, 그렇다면 try를 하나씩 묶어야 함
    반면 하나라도 잘못되면 일정파일 갱신하게 만들어야 하므로 try를 전체로 묶는게 맞게 됨
    */
    try {
        // 1) 오늘 날짜에 사전에 추가한 일정이 있다면 반영
        if (std::filesystem::exists(file_reader.getFilePath())) {
            file_content = file_reader.readFile(); // RVO 유도
            task_list = json_parser.jsonToTaskList(file_content);
        } // 이쪽은 없어도 이상한게 아니므로 else 없음

        // 2) 매일 할일로 설정된 내용이 있다면 반영
        file_reader.setPath("./Data/fixed_schedule/everyday.json");
        file_content = file_reader.readFile(); // RVO 유도
        appended_list = json_parser.jsonToTaskList(file_content);
        appendList(appended_list);

        // 3) 오늘 요일에 할일로 설정된 내용이 있다면 반영
        std::string days[8] = {"", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
        file_reader.setPath("./Data/fixed_schedule/" + days[Date::instance().getDayOfWeek()] + ".json");
        file_content = file_reader.readFile(); // RVO 유도
        appended_list = json_parser.jsonToTaskList(file_content);
        appendList(appended_list);

        // 4) 지난날 안하고 남겨둔 일이 있다면 반영
        std::string year_of_remaining_schedule = std::to_string(last_managed_date_year);
        std::string month_of_remaining_schedule = (last_managed_date_month < 10) ? '0' + std::to_string(last_managed_date_month) : std::to_string(last_managed_date_month);
        std::string day_of_remaining_schedule = (last_managed_date_day < 10) ? '0' + std::to_string(last_managed_date_day) : std::to_string(last_managed_date_day);
        std::string remaining_file_path = "./Data/" + year_of_remaining_schedule + "/" + month_of_remaining_schedule + "/" + day_of_remaining_schedule + ".json";
        if (std::filesystem::exists(remaining_file_path)) {
            file_reader.setPath(remaining_file_path);
            file_content = file_reader.readFile(); // RVO 유도
            appended_list = json_parser.jsonToTaskList(file_content);
            adjustImportance(appended_list);
            appendList(appended_list);
        }
    }
    catch(const std::runtime_error& re) {
        // 고장난 파일 재작성하게 만드는 로직을 추가한다면 여기에
        std::cerr << std::string(re.what()) + "(" + file_reader.getFilePath() << ")\n";
    }
}

// 안하고 남겨둔 일들 중요도 높이기
void TaskListManager::adjustImportance(QList<QList<Task>> remaining_list)
{
    for(auto& rl : remaining_list){
        for(auto& task : rl) {
            if(task.importance != 1) task.importance = 2;
        }
    }
}

/*
저장하는 로직
예외처리 필요한가 여기도?
*/
Q_INVOKABLE void TaskListManager::saveTaskList()
{
    JsonSerializer json_serializer;
    std::string json_content = json_serializer.taskListToJson(task_list);

    FileWriter file_writer;
    file_writer.writeFile(json_content);
}


/* GetScheduleList()
용도 : C++과 QML의 integration에서의 Q_PROPERTY속성의 READ함수
시퀀스 : QML에서 Window를 띄울때 ListView의 내용을 얻어야 하므로 해당 함수를 통해 얻음
*/
QList<QList<Task>> TaskListManager::getTaskList()
{
    return task_list;
}

/* insertTask()
용도 : 사용자가 사용중 할일이 새로 생겨서 추가하고 싶을때 호출
시퀀스 : QML에서 Button 누른 후 뜨는 TextInputWindow에 내용을 입력하고 엔터를 치면 해당 내용이 ListView의 최상단에 추가됨
고민 : version 1.0에서 #으로 여러개 입력시 분리하게 했었는데 이거때문에 C#같은 단어를 쓰지를 못했었음
      그래서 해당 기능을 유지할지 삭제할지에 대한 고민 후 해당 기능은 추후에 GUI에서 추가 가능하도록 구현하는게 맞다고 판단해서 우선 삭제
*/
Q_INVOKABLE void TaskListManager::insertTask(QString inserted_task)
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
Q_INVOKABLE void TaskListManager::updateTask(int y, int x, QString updated_task)
{
    task_list[y][x].title = updated_task;
    emit ListChanged();
}

/* deleteTask()
용도 : 사용자가 할일의 내용을 완료해서 목록에서 지우고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle 중
        사용자가 완료한 task를 더블클릭하면 이 함수가 호출되어 해당 내용이 task_list에서 지워짐
*/
Q_INVOKABLE void TaskListManager::deleteTask(int y, int x)
{
    task_list[y].removeAt(x);
    if(task_list[y].empty()) task_list.removeAt(y);

    emit ListChanged();
}
