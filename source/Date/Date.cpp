#include "Date.h"

Date::Date()
{
    /* 초기값 설정의 이유
    처음 Date::instance()로 객체 생성시 값을 설정하지 않으면
    int 멤버변수들에 쓰레기값이 들어있으므로 예상하못지 한 결과나가 올 수 있음
    물론 프로그램 시작과 동시에 Date객체 생성후 currentDate()함수를 호출하겠지만
    혹시 모를 내 실수를 미연에 방지하기 위해 그냥 초기값으로 설정해버리기로 함
    */
    setToCurrentDate();
}

/* instance()
용도 : Date 싱글턴 객체 획득
시퀀스 : ScheduleFactory가 Schedule 객체를 만들기 위해 날짜정보 획득시 사용
*/
Date& Date::instance()
{
    static Date instance;
    return instance;
}


void Date::setDate(QDate q_date)
{
    year = q_date.year();
    month = q_date.month();
    day = q_date.day();
    day_of_week = q_date.dayOfWeek();

    emit dateChanged(); // 날짜 변경시 signal일으켜서 slot인 Schedule 객체가 해당 날짜의 스케쥴 불러오게 변경
}

/* currentDate()
용도 : 오늘의 날짜(년, 월, 일, 요일) 획득
시퀀스 : 프로그램 최초 실행시 오늘의 Schedule을 보여주기 위해 오늘 날짜 획득 후 ScheduleFactory에 제공
*/
void Date::setToCurrentDate()
{
    QDate current_date = QDate::currentDate();
    setDate(current_date);
}

void Date::setToSpecificDate(int y, int m, int d)
{
    QDate specific_date(y, m, d);
    setDate(specific_date);
}

/* getYear(), getMonth(), getDay(), getDayOfWeek()
용도 : 현재 Date객체가 저장하고 있는 날짜정보 반환
시퀀스 : ScheduleFactory에 의해 Schedule 객체를 만들거나 일정파일 경로를 참조할때 날짜정보가 필요하므로 반환
*/
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getDayOfWeek() const { return day_of_week; }

