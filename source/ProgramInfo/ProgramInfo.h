/* Initializer.h

1. 클래스 관계

2. 용도

3. 구현방식
*/

#pragma once

#include "../FileManager/FileReader.h"
#include "../FileManager/FileWriter.h"
#include "../JsonManager/JsonParser.h"
#include "../JsonManager/JsonSerializer.h"
#include "../Tutorial/Tutorial.h"

class ProgramInfo
{
public:
    bool tutorial;
    int last_managed_date_year;
    int last_managed_date_month;
    int last_managed_date_day; // 이 변수들 getter 만드는게 나을수도

    // 생성자
    ProgramInfo();
    ~ProgramInfo();

    // 정보 확인용 bool함수
    bool isTutorialNeeded();
    bool isOpenedToday(Date& date);
};
