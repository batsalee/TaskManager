#include "Date.h"

Date::Date()
{
    getTodaysDate();
}

Date::Date(std::string y, std::string m, std::string d)
{
    year = y;
    month = m;
    day = d;
}

/////////////////////////////////////////////////////////////////////////

void Date::getTodaysDate()
{
    QDate currentDate = QDate::currentDate();
    //year = currentDate.year();
    //std::cout << currentDate.year();
}

void Date::setDate(std::string y, std::string m, std::string d)
{
    year = y;
    month = m;
    day = d;
}
