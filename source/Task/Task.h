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

4. 특이사항
구조체이지만 이동생성자를 구현해뒀음
Task 구조체는 TaskListManager의 appendTaskList()에 의해 복사되는 경우가 아주 많이 생기는데
여기서 Qtring은 복사보다는 이동을 사용하는쪽이 더 이득일 수 있으니 이동생성자를 noexcept로 구현해서
appendTaskList()에서 push_back할때 우측값 레퍼런스를 넘기도록 구현

그리고 이동생성자를 구현했으니 default 생성자나 복사생성자도 명시적으로 선언해줘야 했으며
값을 설정하면서 바로 생성하도록 만드는 task(QString& t, int i)생성자도 insertTask()에서 사용되므로 선언해줘야 했음

또한 이 프로그램에서 사용하고 있지는 않지만 우선 대입연산자도 구현해뒀음
복사 대입연산자, 이동 대입연산자가 있으니 나중에 활용할 수 있을 듯 함
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

    // 생성자
    task() = default; // 기본 생성자
    task(QString& t, int i) // 값 설정하면서 바로 생성(insertTask()에서 사용)
        : title(t), importance(i) {}
    task(const task&) = default; // 복사 생성자
    task(task&& other) noexcept // 이동 생성자
        : title(std::move(other.title)), importance(other.importance) {}

    // 대입 연산자
    task& operator=(const task&) = default; // 복사 대입 연산자
    task& operator=(task&& other) noexcept { // 이동 대입 연산자
        if (this != &other) {
            title = std::move(other.title);
            importance = other.importance;
        }
        return *this;
    }
};

Q_DECLARE_METATYPE(Task)
