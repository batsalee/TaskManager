#include "Date.h"

Date::Date()
{
    getTodaysDate();
}

Date::Date(QString y, QString m, QString d)
{
    setDate(y, m, d);
}

/////////////////////////////////////////////////////////////////////////

void Date::getTodaysDate()
{
    QDate currentDate = QDate::currentDate();
    year = QString::number(currentDate.year());
    month = QString::number(currentDate.month());
    day = QString::number(currentDate.day());
    dayOfWeek = QString::number(currentDate.dayOfWeek());
}

void Date::setDate(QString y, QString m, QString d)
{
    year = y;
    month = m;
    day = d;
}
