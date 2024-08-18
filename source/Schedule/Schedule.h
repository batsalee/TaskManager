/* Schedule.h

1. 클래스 관계
ScheduleFactory가 Schedule클래스의 팩토리메서드 패턴을 구현한 팩토리 클래스
JsonManager클래스에 의해 이중리스트를 얻고, 기록함
qml과 직접적으로 소통하는 이 프로젝트의 핵심 클래스

2. 용도
해당 날짜의 일정이 들어있는 이중리스트의 관리자

3. 구현방식
팩토리메서드에 의해 생성되며 그 후 소멸될때까지 이중리스트를 관리하는 역할 담당
*/

#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "../Task/Task.h"

#include "../FileManager/FileReader.h"
#include "../JsonManager/JsonParser.h"

class Schedule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QList<Task>> task_list READ GetScheduleList NOTIFY ListChanged)

private:
    // 생성자
    Schedule() = default;
    ~Schedule();

    // 싱글턴 구현 위해 복사, 이동, 대입 delete
    Schedule(const Schedule& d) = delete;
    Schedule(Schedule&& d) = delete;
    Schedule& operator=(const Schedule & d) = delete;

public:
    QList<QList<Task>> task_list; // 이 클래스와 프로그램의 핵심인 이중리스트
    QList<QList<Task>> GetScheduleList(); // getter

    // setter
    Q_INVOKABLE void insertTask(QString);
    Q_INVOKABLE void updateTask(int, int, QString);
    Q_INVOKABLE void deleteTask(int, int);

    static Schedule& instance(); // 싱글턴 객체 획득 함수

signals:
    void ListChanged();

public slots:
    void showTaskList();
};
