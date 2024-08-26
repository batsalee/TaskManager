#include "TaskListManager.h"

/* instance()
용도 : TaskListManager 싱글턴 객체 획득
시퀀스 : 프로그램 실행 시 프로그램의 핵심이 되는 TaskListManager 객체를 생성 및 획득해야 하므로 호출
*/
TaskListManager& TaskListManager::instance()
{
    static TaskListManager instance;
    return instance;
}

/* makeTaskList()
용도 : 오늘의 일정파일의 내용을 구성함
시퀀스 : 프로그램 실행 시 ProgramInfo를 참조해서 프로그램이 오늘 처음 실행되는 것이라면 오늘의 일정파일을 구성해야 하므로 이 함수가 사용됨

고민 : 파일 구성에 대한 정책에 따라 예외처리의 범위가 달라짐
- 하나의 파일이라도 잘못되었다면 일정파일을 만들지 않는다 : 현재 구현처럼 전체를 try로 묶음
- 하나의 특정 파일이 잘못되었더라도 다른 파일은 정상적이라면 정상적인 파일만 일정에 반영한다 : 각 readFile()과 JsonToTaskList() 단위로 try를 묶어야 함
이 중 파일 중 하나라도 잘못되었다면 사용자에 의해 파일이 직접적으로 조작되었을 가능성이 높으므로 무결성 검사를 하는게 맞다고 판단해서 전체를 묶는 방법을 선택했음
*/
void TaskListManager::makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day)
{
    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 현재 관리중인 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    std::string file_content; // file_reader에 의해 읽혀진 내용이 저장될 변수
    QList<QList<Task>> appended_list; // json_parser에 의해 file_content가 파싱된 이후 결과가 담겨질 이중리스트

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

/* loadTaskList()
용도 : loadSpecificTaskList()와 loadFixedTaskList()의 공통부분 작성
시퀀스 : loadSpecificTaskList()에 의해 특정 날짜의 파일을 읽어와야 하거나, loadFixedTaskList()에 의해 고정 일정 파일을 읽어와야 할 때 두 함수에 의해 호출
*/
void TaskListManager::loadTaskList(FileReader& file_reader, JsonParser& json_parser)
{
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

/* loadSpecificTaskList()
용도 : 관리중인 날짜의 일정 파일의 내용을 불러와야 할 때 사용
시퀀스 :
case 1) 프로그램 실행 시 오늘 처음 실행하는 것이 아니라면, 처음 실행할때 일정파일을 이미 만들었을테니 그대로 읽기만 하면 되므로 호출됨
case 2) 관리할 날짜를 변경해서 해당 날짜의 일정을 불러와야 하는 경우 호출됨
*/
void TaskListManager::loadSpecificTaskList()
{
    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 현재 관리중인 날짜 기반 경로 설정
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    // loadFixedTaskList()와의 차이점은 이 함수는 Date 객체 기반으로 동작하므로 경로를 설정하지 않음
    loadTaskList(file_reader, json_parser);
}

/* loadFixedTaskList()
용도 : 고정 일정(매일 할일, 각 요일별 할일)을 관리하기 위해 불러와야 할 때 사용
시퀀스 : qml에서 사용자에 의해 고정일정관리가 선택되었을때 어느 파일인지 경로를 넘겨주면 해당 파일을 읽어와서 화면에 표시함
*/
Q_INVOKABLE void TaskListManager::loadFixedTaskList(std::string file_path)
{
    FileReader file_reader; // 부모클랙스인 FileManager의 생성자에 의해 현재 관리중인 날짜 기반 경로 설정되지만 다른 파일을 관리할 예정이므로 아래에서 setPath로 갱신됨
    JsonParser json_parser; // 파일 내용은 json형태이므로 파싱담당 객체 생성

    file_reader.setPath(file_path); // qml에서 선택한 일정파일로 경로 설정
    loadTaskList(file_reader, json_parser);
}

/* saveTaskList()
용도 : 관리중이던 일정 정보를 로컬에 파일로 저장함
시퀀스 :
case 1) 사용자에 의해 관리할 날짜가 변경되면 기존에 관리중이던 날짜의 일정 내용을 로컬에 저장해야 하므로 호출됨
case 2) 프로그램 종료시 일정 내용을 로컬에 저장해야 하므로 호출됨
*/
void TaskListManager::saveTaskList()
{
    JsonSerializer json_serializer;
    std::string json_content = json_serializer.taskListToJson(task_list);

    FileWriter file_writer;
    file_writer.writeFile(json_content);
}

/* appendList()
용도 : 멤버 변수인 task_list에 매개변수로 주어진 이중리스트를 이어붙임
시퀀스 : file_reader가 일정 파일을 읽고, json_parser가 일정 파일을 이중리스트로 변환해서 반환하면 해당 내용을 task_list에 이어붙임
*/
void TaskListManager::appendList(const QList<QList<Task>>& appended_list)
{
    for (const auto& inner_list : appended_list) {
        task_list.push_back(inner_list);
    }
}

/* adjustImportance()
용도 : 이중리스트에 담겨있는 Task들의 중요도를 높임, 지난 날 안하고 남겨둔 일을 표시하기 위해 사용
시퀀스 : ProgramInfo에 의해 마지막으로 이 프로그램을 사용한 날짜를 확인하고, 해당 날짜에 남겨둔 일이 있는지 확인한 후 있다면 읽어와서 중요도를 높인 후 task_list에 이어붙임
*/
void TaskListManager::adjustImportance(QList<QList<Task>>& remaining_list)
{
    for(auto& rl : remaining_list){
        for(auto& task : rl) {
            if(task.importance != 1) task.importance = 2;
        }
    }
}

/* insertTask()
용도 : 사용자가 사용중 할일이 새로 생겨서 추가하고 싶을때 호출
시퀀스 : QML에서 Button 누른 후 뜨는 TextInputWindow에 내용을 입력하고 엔터를 치면 해당 내용이 ListView의 최상단에 추가됨
고민 : version 1.0에서 새로운 할 일을 추가할때 한줄에 여러개 입력하고 싶다면 #으로 구분해서 작성시 분리해서 입력이 가능했었는데 이것때문에 C#같은 단어를 쓰지를 못했었음
      그래서 해당 기능은 이번에 삭제하고 추후에 기능 추가시에 GUI에서 구현하기로 함
*/
Q_INVOKABLE void TaskListManager::insertTask(QString inserted_task)
{
    QList<Task> new_task_list = { Task{inserted_task, 1} }; // 새로 추가될 QList, 추후에 기능 추가 개선때 중요도도 설정 가능하도록 만들기
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

/* GetScheduleList()
용도 : C++과 QML의 integration에서의 Q_PROPERTY속성의 READ함수
시퀀스 : QML에서 Window를 띄울때 ListView의 내용을 얻어야 하므로 해당 함수를 통해 얻음
*/
QList<QList<Task>> TaskListManager::getTaskList() const { return task_list; }
