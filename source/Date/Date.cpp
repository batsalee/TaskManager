#include "Date.h"

Date::Date()
{
    /* �ʱⰪ ������ ����
    ó�� Date::instance()�� ��ü ������ ���� �������� ������
    int ��������鿡 �����Ⱚ�� ��������Ƿ� �����ϸ��� �� ������� �� �� ����
    ���� ���α׷� ���۰� ���ÿ� Date��ü ������ currentDate()�Լ��� ȣ���ϰ�����
    Ȥ�� �� �� �Ǽ��� �̿��� �����ϱ� ���� �׳� �ʱⰪ���� �����ع������ ��
    */
    setToCurrentDate();
}

/* instance()
�뵵 : Date �̱��� ��ü ȹ��
������ : ScheduleFactory�� Schedule ��ü�� ����� ���� ��¥���� ȹ��� ���
*/
Date& Date::instance()
{
    static Date instance;
    return instance;
}


void Date::setDate(QDate q_date)
{
    year = q_date.year();
    month = q_date.month();
    day = q_date.day();
    day_of_week = q_date.dayOfWeek();

    emit dateChanged(); // ��¥ ����� signal�����Ѽ� slot�� Schedule ��ü�� �ش� ��¥�� ������ �ҷ����� ����
}

/* currentDate()
�뵵 : ������ ��¥(��, ��, ��, ����) ȹ��
������ : ���α׷� ���� ����� ������ Schedule�� �����ֱ� ���� ���� ��¥ ȹ�� �� ScheduleFactory�� ����
*/
void Date::setToCurrentDate()
{
    QDate current_date = QDate::currentDate();
    setDate(current_date);
}

void Date::setToSpecificDate(int y, int m, int d)
{
    QDate specific_date(y, m, d);
    setDate(specific_date);
}

/* getYear(), getMonth(), getDay(), getDayOfWeek()
�뵵 : ���� Date��ü�� �����ϰ� �ִ� ��¥���� ��ȯ
������ : ScheduleFactory�� ���� Schedule ��ü�� ����ų� �������� ��θ� �����Ҷ� ��¥������ �ʿ��ϹǷ� ��ȯ
*/
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getDayOfWeek() const { return day_of_week; }

