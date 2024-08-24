/* TaskListManager.h

1. 클래스 관계
FileReader, FileWriter, JsonParser, JsonSerializer를 호출해서 활용하는 커플링의 중심이 되는 클래스
qml과 직접적으로 소통하는 이 프로젝트의 핵심 클래스

2. 용도
이중리스트 관리자
특정 날짜의 일정을 관리할때엔 해당 날짜의 일정을, 고정 일정을 관리할때에는 해당 파일에 저장된 일정을 표현 및 조작하는 클래스

3. 구현방식
다른 클래스들은 최대한 커플링이 발생하지 않게 하려고 노력했고, 이 클래스 하나가 그 모든 클래스들을 활용해서 커플링의 중심이 되고 프로그램의 핵심 클래스로 동작함

싱글턴 패턴으로 구현
이유 1) 하나만 있으면 된다는 점
이유 2) qml과 integration

4. 고민
클래스들을 다 정리하고 난 후 이 클래스가 커플링이 중심이 된 지금 이 클래스가 싱글턴이어야 할 이유가 없다.
기존에는 다른 클래스에서 이 클래스를 가져다 써서 전역적인 접근점이라는 이유가 있었는데 현재는 유지해야할 이유가 없어졌다. 되돌려도 문제가 없을지 고민
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
    TaskListManager() = default;
    ~TaskListManager() = default;

    // 싱글턴 구현 위해 복사, 이동, 대입 delete
    TaskListManager(const TaskListManager& d) = delete;
    TaskListManager(TaskListManager&& d) = delete;
    TaskListManager& operator=(const TaskListManager & d) = delete;

public:
    QList<QList<Task>> task_list; // 이 클래스와 프로그램의 핵심인 이중리스트

    static TaskListManager& instance(); // 싱글턴 객체 획득 함수

    // Task List 관리 함수
    void makeTaskList(int last_managed_date_year, int last_managed_date_month, int last_managed_date_day); // 일정파일 생성 함수
    void saveTaskList(); // 관리하는 날짜 변경 혹은 프로그램 종료시 일정파일 저장 함수
    void appendList(const QList<QList<Task>>& appended_list); // 이중리스트를 현재 관리중인 일정에 덧붙이는 함수
    void adjustImportance(QList<QList<Task>>& remaining_list); // 이중리스트 내의 Task의 중요도를 조정하는 함수

    // Task 관리 함수
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(int, int, QString);
    Q_INVOKABLE void deleteTask(int, int);

    // getter
    QList<QList<Task>> getTaskList() const;

signals:
    void ListChanged(); // qml 갱신을 위해 insert, update, delete시 시그널 emit

public slots:
    void loadTaskList(); // 만약 이미 일정파일이 만들어져 있다면 그대로 읽어오는 함수
};
