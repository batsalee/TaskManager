/* Date 클래스

1. 클래스 관계
Schedule 클래스에 날짜정보 제공

2. 용도
프로그램이 현재 관리중인 스케쥴의 날짜정보를 저장하는 클래스
- 프로그램 최초 실행시 오늘의 날짜 획득
- 날짜 변경시 해당 날짜정보 기록

3. 구현방식
싱글턴 패턴으로 구현
이유 1) 하나만 있으면 된다는 점
이유 2) qml과 integration
이유 3) Schedule의 팩토리메서드 구현시 참조목적으로 전역접근
*/

#pragma once

#include <QDate>

class Date
{
private:
    int year;
    int month;
    int day;
    int day_of_week; // 요일별 할일 기능을 사용하기 위해 오늘이 무슨 요일인지 알아야 함

    Date() = default;
    virtual ~Date() = default;

    // 싱글턴 구현 위해 복사, 이동, 대입 delete
    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

public:
    static Date& instance(); // 싱글턴 객체 획득 함수
    void currentDate(); // 오늘 날짜 획득 함수

    // setter
    // Q_INVOKABLE void setDate(); // 나중에 qml측에서 날짜 변경기능 만들때 사용할 예정

    // getter
    int getYear();
    int getMonth();
    int getDay();
    int getDayOfWeek();
};
