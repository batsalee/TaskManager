/* Date Ŭ����
�������� �������� ��¥������ �����ϴ� Ŭ����
�̱������� ����
���� 1) �ϳ��� ������ �ȴٴ� ��
���� 2) qml�� integration
���� 3) Schedule�� ���丮�޼��� ������ ������������ ��������
*/

#pragma once

#include <QDate>

class Date
{
private:
    int year;
    int month;
    int day;

    Date() = default;
    ~Date() = default;

    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

public:
    static Date& instance();
    void getTodayDate();
};
