#include "Date.h"

/* Date()
�뵵 : ������, �ʱⰪ ����
������ : ��ü ������ ���� ��¥ ������ ȹ���ؼ� ��� ���� �� ����

- �ʱⰪ ������ ����
ó�� Date::instance()�� ��ü ������ ���� �������� ������ int ��������鿡 �����Ⱚ�� ��������Ƿ� �����ϸ��� �� ������� �� �� ����
���� ���α׷� ���۰� ���ÿ� Date��ü ���� �� setToCurrentDate()�Լ��� ȣ���ϵ��� �����ϸ� ������ Ȥ�� �� �� �Ǽ��� �̿��� �����ϱ� ���� �׳� �ʱⰪ���� �����ع������ ��
*/
Date::Date()
{
    setToCurrentDate();
}

/* instance()
�뵵 : Date �̱��� ��ü ȹ��
������ : FileManager�� �������� ��¥�� ������� ������ ��θ� �����ϹǷ� ��¥ ���� ȹ�� �� ���
*/
Date& Date::instance()
{
    static Date instance;
    return instance;
}

/* setDate()
�뵵 : ������ ��¥ ���� �� ���� ���� ó��
������ : ������� ��¥ ���� -> dateChanged() �ñ׳� �߻� -> TaskListManager�� saveTaskList() slot ȣ�� -> ������ ���������� �����
        -> �ٽ� setDate()�� ���ƿͼ� ��¥ ���� ���� -> readyToLoad() �ñ׳� �߻� -> TaskListManager�� loadTaskList() slot ȣ�� -> ����� ��¥�� ���������� load��
*/
void Date::setDate(QDate& q_date)
{
    emit dateChanged(); // ����ڰ� ��¥�� �����ϸ� �߻� -> ���������� �����ϵ��� saveTaskList() ȣ��

    year = q_date.year();
    month = q_date.month();
    day = q_date.day();
    day_of_week = q_date.dayOfWeek();

    emit readyToLoad(); // ��¥ ���ŵ����� �� ��¥�� �ٽ� �ҷ������ �ñ׳� �߻���Ŵ -> loadTaskList() ȣ��
}

/* setToCurrentDate()
�뵵 : ������ ��¥(��, ��, ��, ����) ȹ�� �� ��� ���� �� ����
������ : ���α׷� ���� ����� ���� ��¥�� ������ �����ֱ� ���� ���� ��¥ ȹ��, �� �� FileManager�� ���� ���� ��� ������ ���� ��¥ ���� Ȯ�ν� ������
*/
void Date::setToCurrentDate()
{
    QDate current_date = QDate::currentDate();
    setDate(current_date);
}

/* setToSpecificDate()
- Q_INVOKABLE �Լ�
�뵵 : ����ڰ� �ٸ� ��¥�� ������ �����ϱ� ���� �� �ش� ��¥�� ����
������ : ����ڰ� qml���� ��¥ ����� ȣ��Ǿ� ��¥ ���� ����, ���� �������� setDate()�� ���� signal-slot �۾� ����
*/
void Date::setToSpecificDate(int y, int m, int d)
{
    QDate specific_date(y, m, d);
    setDate(specific_date);
}

/* getYear(), getMonth(), getDay(), getDayOfWeek()
�뵵 : ���� Date��ü�� �����ϰ� �ִ� ��¥���� ��ȯ
������ : FileManager�� �������� ��θ� ������ �� ȣ��Ǿ� ���� ��ȯ
*/
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getDayOfWeek() const { return day_of_week; }
