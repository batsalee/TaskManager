#include "TodayScheduleFactory.h"

Date& TodayScheduleFactory::getDate()
{
    Date& date = Date::instance();
    date.getTodayDate();
    return date;
}
