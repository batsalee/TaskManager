#include "AnotherdayScheduleFactory.h"

/* getDate()
�뵵 : ScheduleFactory�� ���� Schedule ��ü �����κ��� ���ø� �޼��� ������
������ : ScheduleFactory���� Schedule��ü�� ���鶧 Date��ü�� �� �Լ��� ���� ��¥ ������ ȹ���ؼ� ��ȯ
*/
Date& AnotherdayScheduleFactory::getDate()
{
    Date& date = Date::instance();
    return date;
}
