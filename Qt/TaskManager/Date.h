/* Date

역할
1) 오늘 날짜 계산

*/

#pragma once
#include <QDate>

class Date {
private:
    friend class Scheduler;
    friend class Calendar;
    std::string year, month, day;

    void getTodaysDate();
    void setDate(std::string, std::string, std::string);

public:
    Date();
    Date(std::string, std::string, std::string);
};
