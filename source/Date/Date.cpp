#include "Date.h"

Date& Date::instance()
{
    static Date instance;
    return instance;
}

void Date::getTodayDate()
{
    QDate current_date = QDate::currentDate();

    year = current_date.year();
    month = current_date.month();
    day = current_date.day();
}
