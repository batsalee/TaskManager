#include "TodayScheduleFactory.h"

/* getDate()
�뵵 : ScheduleFactory�� ���� Schedule ��ü �����κ��� ���ø� �޼��� ������
������ : ���α׷� ���� ����� ScheduleFactory���� Schedule��ü�� ���鶧
        Date��ü�� �� �Լ��� ���� ������ ��¥������ ��� ��ȯ
*/
Date& TodayScheduleFactory::getDate()
{
    Date& date = Date::instance();
    date.getTodayDate();
    return date;
}
