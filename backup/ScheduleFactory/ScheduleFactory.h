/* ScheduleFactory.h

1. 클래스 관계
Schedule 클래스의 팩토리메서드 패턴 구현부의 팩토리 클래스
Date, FileReader, JsonParser 클래스를 이용해 일정 목록을 작성

2. 용도
Schedule 클래스의 팩토리

3. 구현방식
팩토리 메서드 패턴으로 구현
이유1) Schedule 객체 생성시 Schedule객체와 Date, FileManager, JsonManager간의 커플링 감소를 위해
이유2) Schedule 객체 생성과정에서 오늘날짜인지, 다른 날짜인지의 차이를 제외한 공통점에 초점
*/

#pragma once

#include <iostream>
#include <memory>
#include "../Schedule/Schedule.h"
#include "../Date/Date.h"
#include "../FileManager/FileReader.h"
#include "../JsonManager/JsonParser.h"

class ScheduleFactory
{
public:
    void makeSchedule(); // 팩토리 메서드 패턴의 생성함수
    virtual Date& getDate() = 0;

    virtual ~ScheduleFactory() {};
};
