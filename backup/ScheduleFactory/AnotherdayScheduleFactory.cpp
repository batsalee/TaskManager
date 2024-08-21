#include "AnotherdayScheduleFactory.h"

/* getDate()
용도 : ScheduleFactory에 의한 Schedule 객체 생성부분의 템플릿 메서드 구현부
시퀀스 : ScheduleFactory에서 Schedule객체를 만들때 Date객체가 이 함수를 통해 날짜 정보를 획득해서 반환
*/
Date& AnotherdayScheduleFactory::getDate()
{
    Date& date = Date::instance();
    return date;
}
