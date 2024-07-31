/* AnotherdayScheduleFactory 클래스

1. 클래스 관계
ScheduleFactory의 하위클래스
ScheduleFactory 클래스는 Schedule 클래스의 팩토리 메소드 패턴 구현 목적이며
AnotherdayScheduleFactory 클래스는 그 하위의 concrete 클래스

2. 용도
오늘이 아닌 다른 날짜 선택시 해당 날짜의 스케쥴객체 생성

3. 구현방식
해당 날짜의 Schedule 객체를 만드는 팩토리메서드의 구현부
*/

#pragma once

#include "ScheduleFactory.h"

class AnotherdayScheduleFactory : public ScheduleFactory
{
public:
    Date& getDate() override;
};
