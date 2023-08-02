/* Date
 *
역할
1) 오늘 날짜 계산

*/

#pragma once
#include <QDate>

class Date {
private:
    friend class Scheduler;
    //friend class Calendar;
    QString year, month, day, dayOfWeek;

    void getTodaysDate();
    void setDate(QString, QString, QString);

public:
    Date();
    Date(QString, QString, QString);
};
