#include "TodayScheduleFactory.h"

/* getDate()
용도 : ScheduleFactory에 의한 Schedule 객체 생성부분의 템플릿 메서드 구현부
시퀀스 : 프로그램 최초 실행시 ScheduleFactory에서 Schedule객체를 만들때
        Date객체가 이 함수를 통해 오늘의 날짜정보를 얻어 반환
*/
Date& TodayScheduleFactory::getDate()
{
    Date& date = Date::instance();
    date.getTodayDate();
    return date;
}
