#include "Date.h"

/* instance()
�뵵 : Date �̱��� ��ü ȹ��
������ : ScheduleFactory�� Schedule ��ü�� ����� ���� ��¥���� ȹ��� ���
*/
Date& Date::instance()
{
    static Date instance;
    return instance;
}

/* currentDate()
�뵵 : ������ ��¥(��, ��, ��, ����) ȹ��
������ : ���α׷� ���� ����� ������ Schedule�� �����ֱ� ���� ���� ��¥ ȹ�� �� ScheduleFactory�� ����
*/
void Date::currentDate()
{
    QDate current_date = QDate::currentDate();

    year = current_date.year();
    month = current_date.month();
    day = current_date.day();
    day_of_week = current_date.dayOfWeek();
}

/* getYear(), getMonth(), getDay(), getDayOfWeek()
�뵵 : ���� Date��ü�� �����ϰ� �ִ� ��¥���� ��ȯ
������ : ScheduleFactory�� ���� Schedule ��ü�� ����ų� �������� ��θ� �����Ҷ� ��¥������ �ʿ��ϹǷ� ��ȯ
*/
int Date::getYear() { return year; }
int Date::getMonth() { return month; }
int Date::getDay() { return day; }
int Date::getDayOfWeek() { return day_of_week; }
