#include "Date.h"

/* instance()
용도 : Date 싱글턴 객체 획득
시퀀스 : ScheduleFactory가 Schedule 객체를 만들기 위해 날짜정보 획득시 사용
*/
Date& Date::instance()
{
    static Date instance;
    return instance;
}

/* getTodayDate()
용도 : 오늘의 날짜(년, 월, 일) 획득
시퀀스 : 프로그램 최초 실행시 오늘의 Schedule을 보여주기 위해 오늘 날짜 획득 후 ScheduleFactory에 제공
*/
void Date::getTodayDate()
{
    QDate current_date = QDate::currentDate();

    year = current_date.year();
    month = current_date.month();
    day = current_date.day();
}
