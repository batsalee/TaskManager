#include "Schedule.h"

/*
MakeScheduleList()
용도 : init, 처음 해당 날짜의 일정파일을 열때 호출
시퀀스 : FileReader가 파일을 읽어주면 JsonParser가 파싱하고 해당 내용을 MakeScheduleList()가 이중리스트에 담음
*/
void Schedule::MakeScheduleList(Document& document)
{
    if (document.HasMember("Schedule") && document["Schedule"].IsArray()) {
        const Value& json_array = document["Schedule"];

        for (int i = 0; i < json_array.Size(); i++) {
            if (json_array[i].IsArray()) {
                const Value& inner_array = json_array[i];

                QList<QString> inner_list;
                for (int j = 0; j < inner_array.Size(); j++) {
                    inner_list.push_back(inner_array[j].GetString());
                    // 만약 인코딩 문제가 생긴다면 UTF-8 to EUC-KR 코드 여기에 넣기
                }
                schedule_list.push_back(inner_list);
            }
        }
    }
}

/*
GetScheduleList()
용도 : C++과 QML의 integration에서의 Q_PROPERTY속성의 READ함수
시퀀스 : QML에서 Window를 띄울때 ListView의 내용을 얻어야 하므로 해당 함수를 통해 얻음
*/
QList<QList<QString>> Schedule::GetScheduleList()
{
    return schedule_list;
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
    QList<QString> new_schedule_list = {inserted_task}; // 새로 추가될 QList
    schedule_list.push_front(new_schedule_list);
    emit ListChanged();
}

/*
updateTask()
용도 : 사용자가 할일의 내용을 변경하고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle에는 하나의 할일(task)가 들어있음, 해당 task의 내용을 변경하고 싶을때 우클릭 후 내용 입력 후 엔터시 변경
*/
Q_INVOKABLE void Schedule::updateTask(qint32 y, qint32 x, QString updated_task)
{
    schedule_list[y][x] = updated_task;
    emit ListChanged();
}

/*
deleteTask()
용도 : 사용자가 할일의 내용을 완료해서 목록에서 지우고 싶을때 호출
시퀀스 : QML에서 ListView에 나타나있는 여러개의 Rectangle 중 사용자가 완료한 task를 더블클릭하면 이 함수가 호출되어 해당 내용이 schedule_list에서 지워짐
*/
Q_INVOKABLE void Schedule::deleteTask(int y, int x)
{
    schedule_list[y].removeAt(x);
    if(schedule_list[y].empty()) schedule_list.removeAt(y);

    emit ListChanged();
}
