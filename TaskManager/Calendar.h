/* Calendar

����
1) ��¥/���� ���
2) �ش� ���� ������ �ϼ�
3) ���°�����

*/

#pragma once
#include "Date.h"

class Calendar
{
private:
	// �������� ��¥
	std::string year, month, day;

	void getTodaysDate();
	void setDate(Date);

public:
	Calendar();
	Calendar(Date);

	void makeCalendar(Date);
};