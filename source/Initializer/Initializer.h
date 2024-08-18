/* Initializer.h

1. 클래스 관계

2. 용도

3. 구현방식
*/

#pragma once

#include "../FileManager/FileReader.h"
#include "../JsonManager/JsonParser.h"

class Initializer
{
public:
    bool tutorial;
    int last_managed_date_year;
    int last_managed_date_month;
    int last_managed_date_day;

    void init();
    bool isTutorialNeeded();
    bool isOpenedToday(Date& date);
};
