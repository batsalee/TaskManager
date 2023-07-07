/* Calendar

역할
1) 날짜/요일 계산
2) 해당 월의 마지막 일수
3) 음력계산까지

*/

#pragma once
#include "Date.h"

class Calendar
{
private:
	// 관리중인 날짜
	std::string year, month, day;

	void getTodaysDate();
	void setDate(Date);
	void makeCalendar(Date);

public:
	Calendar();
	Calendar(Date);

};