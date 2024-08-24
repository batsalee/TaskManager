/* Date Ŭ����

1. Ŭ���� ����
FileManager Ŭ������ ��¥���� ����
qml�� ���������� �����ϴ� Ŭ����

2. �뵵
���α׷��� ���� �������� �������� ��¥ ������ ���� �� �����ϴ� Ŭ����
- ���α׷� ���� ����� ������ ��¥ ȹ��
- ����ڿ� ���� ��¥ ����� �ش� ��¥ ���� ���

3. �������
�̱��� �������� ����
���� 1) �ϳ��� ������ �ȴٴ� ��
���� 2) qml�� integration
���� 3) FileManager���� ��¥��� ��� ���� �� ������������ ��������

4. ���
1) chrono ���̺귯���� ������� �� ���� ������ ���� ��, qml �ð����� ǥ�õ� �׷��� ���� �˶� ��� �����ÿ��� �� �����Ұ����� ���� ��
2) setDate()�� ����κ� �ۼ� �� �� �Լ����� ȣ���� �ƴ϶�, ���ø� �޼���ȭ �ϴ� ����� ����
   ������ ������ setToSpecificDate�� ��� �󵵰� setToCurrentDate�� ���� �ξ� �����ɷ� ����Ǹ�, ��κ��� ��� ���α׷� ���� ���� �ѹ��� ������ ���� ���ɼ��� ����
   ���� �̰� C++ �������� ó���Ѵٸ� ������ �ʱ�ȭ�� ����ϸ� �ǰ�����, qml�� integration�ؾ� �ϹǷ� ���α׷� ���� ���۰� ���ÿ� ��ü�� �����ؾ� �ϴ� ��ȿ���� �߻���
   �׷��Ƿ� Ŭ���� �и����ٴ� ���� �κ��� �Լ��� ���� ȣ���ϴ� ������ �����ϱ�� ��
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

    Date(); // ��ü ��� �Ǽ��� �����ϱ� ���� ���������� ������ ��¥�� ���� ����
    virtual ~Date() = default;

    // �̱��� ���� ���� ����, �̵�, ���� delete
    Date(const Date& d) = delete;
    Date(Date&& d) = delete;
    Date& operator=(const Date & d) = delete;

    // setter
    void setDate(QDate& q_date); // �Ʒ� public�� setToCurrentDate()�� setToSpecificDate()�� �ڵ� �ߺ��κ� �ۼ�

public:
    static Date& instance(); // �̱��� ��ü ȹ�� �Լ�

    // getter
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getDayOfWeek() const;

    // setter
    void setToCurrentDate(); // ��¥ ���� ���� ��¥�� ����
    Q_INVOKABLE void setToSpecificDate(int y, int m, int d); // ��¥ ���� ����ڿ� ���� Ư�� ��¥�� ����

signals:
    void dateChanged();
    void readyToLoad();
};
