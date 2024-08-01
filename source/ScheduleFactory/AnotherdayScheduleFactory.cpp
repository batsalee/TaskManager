#include "AnotherdayScheduleFactory.h"

Date& AnotherdayScheduleFactory::getDate()
{
    Date& date = Date::instance();
    return date;
}
