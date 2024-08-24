/* Task.h

1. 클래스 관계
Task는 정확히는 클래스가 아니라 구조체
TaskListManager 클래스의 멤버변수인 task_list의 구성요소인 task구조를 담당
즉 TaskListManager는 Task에 의존적임

2. 용도
일정의 내용뿐 아니라 중요도 설정을 위해 json화 및 구조체화

3. 구현방식
일정의 내용인 title과 중요도인 importance로 구성
또한 해당 내용이 qml에서 활용되어야 하므로 Q_DECLARE_METATYPE로 메타타입으로 선언
*/

#pragma once

#include <QObject>
#include <QString>
#include <QMetaType>

using Task = struct task {
    Q_GADGET
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(int importance MEMBER importance)

public:
    QString title; // 일정의 내용
    int importance; // 일정의 중요도(1이 가장 높음, 3이 가장 낮음)
};

Q_DECLARE_METATYPE(Task)
