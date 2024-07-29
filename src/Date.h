/* Date 클래스
관리중인 스케쥴의 날짜정보를 저장하는 클래스
싱글턴으로 구현
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

    Date() = default;
    ~Date() = default;

    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

public:
    static Date& instance();
    void getTodayDate();
};
