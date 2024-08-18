/* Initializer.h

1. Ŭ���� ����

2. �뵵

3. �������
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
