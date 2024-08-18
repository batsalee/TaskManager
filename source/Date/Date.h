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

#include <QObject>
#include <QDate>

class Date : public QObject
{
    Q_OBJECT

private:
    int year;
    int month;
    int day;
    int day_of_week; // ���Ϻ� ���� ����� ����ϱ� ���� ������ ���� �������� �˾ƾ� ��

    Date();
    virtual ~Date() = default;

    // �̱��� ���� ���� ����, �̵�, ���� delete
    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

public:
    static Date& instance(); // �̱��� ��ü ȹ�� �Լ�

    // setter
    void setDate(QDate q_date); // �Ʒ��� �� setTo~~Date �Լ��� �ڵ� �ߺ��κ� �ۼ�
    void setToCurrentDate(); // ���� ��¥�� �����ϴ� �Լ�
    Q_INVOKABLE void setToSpecificDate(int y, int m, int d); // Ư�� ��¥�� �����ϴ� �Լ� // ���߿� qml������ ��¥ ������ ���鶧 ����� ����

    // getter
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getDayOfWeek() const;

signals:
    void dateChanged();
};
