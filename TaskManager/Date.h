/* Date

����
1) ���� ��¥ ���

*/

#pragma once
#include <chrono>

class Date {
private:
	friend class Scheduler;
	friend class Calendar;
	std::string year, month, day;	
	
	void getTodaysDate();
	void setDate(std::string, std::string, std::string);

public:
	Date();
	Date(std::string, std::string, std::string);
};