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

/* currentDate()
용도 : 오늘의 날짜(년, 월, 일, 요일) 획득
시퀀스 : 프로그램 최초 실행시 오늘의 Schedule을 보여주기 위해 오늘 날짜 획득 후 ScheduleFactory에 제공
*/
void Date::currentDate()
{
    QDate current_date = QDate::currentDate();

    year = current_date.year();
    month = current_date.month();
    day = current_date.day();
    day_of_week = current_date.dayOfWeek();
}

/* getYear(), getMonth(), getDay(), getDayOfWeek()
용도 : 현재 Date객체가 저장하고 있는 날짜정보 반환
시퀀스 : ScheduleFactory에 의해 Schedule 객체를 만들거나 일정파일 경로를 참조할때 날짜정보가 필요하므로 반환
*/
int Date::getYear() { return year; }
int Date::getMonth() { return month; }
int Date::getDay() { return day; }
int Date::getDayOfWeek() { return day_of_week; }
