#include "Schedule.h"

//
#include "FileWriter.h"

/*
MakeScheduleList()
용도 : init, 처음 해당 날짜의 일정파일을 열때 호출
시퀀스 : FileReader가 파일을 읽어주면 JsonParser가 파싱하고 해당 내용을 MakeScheduleList()가 이중리스트에 담음
*/
void Schedule::ConvertJsonToScheduleList(Document& document)
{
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
                    // 만약 인코딩 문제가 생긴다면 UTF-8 to EUC-KR 코드 여기에 넣기
                }
                task_list.push_back(inner_list);
            }
        }
    }
}

/* task_list -> json 테스트중
std::string Schedule::ConvertScheduleListToJson() const {
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    Value scheduleArray(kArrayType);

    for (const auto& innerList : task_list) {
        Value innerArray(kArrayType);
        for (const auto& task : innerList) {
            Value taskObject(kObjectType);
            taskObject.AddMember("title", StringRef(task.title.toUtf8().constData()), allocator);
            taskObject.AddMember("importance", task.importance, allocator);
            innerArray.PushBack(taskObject, allocator);
        }
        scheduleArray.PushBack(innerArray, allocator);
    }

    document.AddMember("Schedule", scheduleArray, allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);  // PrettyWriter를 사용
    document.Accept(writer);

    return buffer.GetString();
}
*/

// 소멸시점에 값을 저장하게 만든다면?
// 종료시점에 이중리스트 -> json변환 및 저장 테스트
Schedule::~Schedule()
{
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    Value scheduleArray(kArrayType);

    for (const auto& innerList : task_list) {
        Value innerArray(kArrayType);
        for (const auto& task : innerList) {
            Value taskObject(kObjectType);
            taskObject.AddMember("title", StringRef(task.title.toUtf8().constData()), allocator);
            taskObject.AddMember("importance", task.importance, allocator);
            innerArray.PushBack(taskObject, allocator);
        }
        scheduleArray.PushBack(innerArray, allocator);
    }

    document.AddMember("Schedule", scheduleArray, allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);  // PrettyWriter를 사용
    document.Accept(writer);


    std::string json_for_saving = buffer.GetString();
    FileWriter fw("./Schedule/test2.json");
    fw.writeFile(json_for_saving);
}




/*
GetScheduleList()
용도 : C++과 QML의 integration에서의 Q_PROPERTY속성의 READ함수
시퀀스 : QML에서 Window를 띄울때 ListView의 내용을 얻어야 하므로 해당 함수를 통해 얻음
*/
QList<QList<Task>> Schedule::GetScheduleList()
{
    return task_list;
}

/*
insertTask()
용도 : 사용자가 사용중 할일이 새로 생겨서 추가하고 싶을때 호출
시퀀스 : QML에서 Button 누른 후 뜨는 TextInputWindow에 내용을 입력하고 엔터를 치면 해당 내용이 ListView의 최상단에 추가됨
기능 고민 : version 1.0에서 #으로 여러개 입력시 분리하게 했었는데 이거때문에 C#같은 단어를 쓰지를 못했었음
          그래서 해당 기능을 유지할지 삭제할지에 대한 고민 후 해당 기능은 추후에 GUI에서 추가 가능하도록 구현하는게 맞다고 판단해서 우선 삭제
*/
Q_INVOKABLE void Schedule::insertTask(QString inserted_task)
{
    QList<Task> new_task_list = { Task{inserted_task, 1} }; // 새로 추가될 QList
    task_list.push_front(new_task_list);
    emit ListChanged();
}

/*
updateTask()
용도 : 사용자가 할일의 내용을 변경하고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle에는 하나의 할일(task)가 들어있음, 해당 task의 내용을 변경하고 싶을때 우클릭 후 내용 입력 후 엔터시 변경
*/
Q_INVOKABLE void Schedule::updateTask(qint32 y, qint32 x, QString updated_task)
{
    task_list[y][x].title = updated_task;
    emit ListChanged();
}

/*
deleteTask()
용도 : 사용자가 할일의 내용을 완료해서 목록에서 지우고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle 중 사용자가 완료한 task를 더블클릭하면 이 함수가 호출되어 해당 내용이 task_list에서 지워짐
*/
Q_INVOKABLE void Schedule::deleteTask(int y, int x)
{
    task_list[y].removeAt(x);
    if(task_list[y].empty()) task_list.removeAt(y);

    emit ListChanged();
}
