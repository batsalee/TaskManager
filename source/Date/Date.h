/* Date Ŭ����

1. Ŭ���� ����
Schedule Ŭ������ ��¥���� ����

2. �뵵
���α׷��� ���� �������� �������� ��¥������ �����ϴ� Ŭ����
- ���α׷� ���� ����� ������ ��¥ ȹ��
- ��¥ ����� �ش� ��¥���� ���

3. �������
�̱��� �������� ����
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
    int day_of_week; // ���Ϻ� ���� ����� ����ϱ� ���� ������ ���� �������� �˾ƾ� ��

    Date() = default;
    virtual ~Date() = default;

    // �̱��� ���� ���� ����, �̵�, ���� delete
    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

public:
    static Date& instance(); // �̱��� ��ü ȹ�� �Լ�
    void currentDate(); // ���� ��¥ ȹ�� �Լ�

    // setter
    // Q_INVOKABLE void setDate(); // ���߿� qml������ ��¥ ������ ���鶧 ����� ����

    // getter
    int getYear();
    int getMonth();
    int getDay();
    int getDayOfWeek();
};
