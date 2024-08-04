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

/* getTodayDate()
�뵵 : ������ ��¥(��, ��, ��) ȹ��
������ : ���α׷� ���� ����� ������ Schedule�� �����ֱ� ���� ���� ��¥ ȹ�� �� ScheduleFactory�� ����
*/
void Date::getTodayDate()
{
    QDate current_date = QDate::currentDate();

    year = current_date.year();
    month = current_date.month();
    day = current_date.day();
}
