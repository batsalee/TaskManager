/* TaskListManager.h

1. 클래스 관계
FileReader, FileWriter, JsonParser, JsonSerializer를 호출해서 활용하는 커플링의 중심이 되는 클래스
qml과 직접적으로 소통하는 이 프로젝트의 핵심 클래스

2. 용도
이중리스트 관리자
특정 날짜의 일정을 관리할때엔 해당 날짜의 일정을, 고정 일정을 관리할때에는 해당 파일에 저장된 일정을 표현 및 조작하는 클래스

3. 구현방식
다른 클래스들은 최대한 커플링이 발생하지 않게 하려고 노력했고, 이 클래스 하나가 그 모든 클래스들을 활용해서 커플링의 중심이 되고 프로그램의 핵심 클래스로 동작함

4. 고민
이 클래스는 싱글턴 패턴으로 구현되었음
이유 1) 하나만 있으면 된다는 점
이유 2) qml과 integration
그리고 기존엔 이유 3이 있었는데 기존엔 이 클래스가 커플링의 중심이 아니라 각 클래스에서 이 클래스를 참조하는 방식으로 사용했었음
하지만 다른 클래스들의 재사용성이나 단일 책임 원칙 준수를 위해 프로젝트의 전체적인 구조를 변경하고 보니 이 클래스가 전역적일 이유가 전혀 없어지게 되었음

그로인해 이 클래스가 싱글턴으로 유지된다면 하나만 존재해야한다는 강제성 부여 외에는 의미가 없음.
하지만 실제로 하나만 있어야 하는게 맞음. 그래서 싱글턴을 유지할지 말지 고민 중
*/

#pragma once

#include <QObject>
#include <QString>
#include <QList>

#include "../Task/Task.h"
#include "../FileManager/FileReader.h"
#include "../FileManager/FileWriter.h"
#include "../JsonManager/JsonParser.h"
#include "../JsonManager/JsonSerializer.h"

class TaskListManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<Task>> task_list READ getTaskList NOTIFY ListChanged)

private:
    QList<QList<Task>> task_list; // 이 클래스와 프로그램의 핵심인 이중리스트

    TaskListManager() = default;
    ~TaskListManager() = default;

    // 싱글턴 구현 위해 복사, 이동, 대입 delete
    TaskListManager(const TaskListManager& d) = delete;
    TaskListManager(TaskListManager&& d) = delete;
    TaskListManager& operator=(const TaskListManager& d) = delete;

    // load 함수
    void loadTaskList(FileReader& file_reader, JsonParser& json_parser); // loadFixedTaskList()와 loadSpecificTaskList()의 공통부분이 작성되므로 private로 선언

public:
    static TaskListManager& instance(); // 싱글턴 객체 획득 함수

    // Task List 관리 함수
    void makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day); // 일정파일 생성 함수
    void saveTaskList(); // 일정파일 저장 함수(관리하는 날짜가 변경되거나 프로그램이 종료될 때 호출됨)
    void appendList(const QList<QList<Task>>& appended_list); // 이중리스트를 현재 관리중인 일정에 덧붙이는 함수
    void adjustImportance(QList<QList<Task>>& remaining_list); // 이중리스트 내의 Task의 중요도를 조정하는 함수

    // load 함수
    Q_INVOKABLE void loadFixedTaskList(std::string file_path); // 고정 일정(매일 할일, 각 요일별 할일)을 관리하기 위해 불러오는 함수

    // Task 관리 함수
    Q_INVOKABLE void insertTask(QString inserted_task);
    Q_INVOKABLE void updateTask(int y, int x, QString updated_task);
    Q_INVOKABLE void deleteTask(int y, int x);

    // getter
    QList<QList<Task>> getTaskList() const;

signals:
    void ListChanged(); // qml 갱신을 위해 insert, update, delete시 시그널 emit

public slots:
    void loadSpecificTaskList(); // 특정 날짜의 일정파일을 읽어오는 함수
};
