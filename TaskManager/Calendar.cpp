/* Calendar 자세한 구현

*/

#include "Calendar.h"

Calendar::Calendar()
{
	getTodaysDate();
}

Calendar::Calendar(Date d)
{
	year = d.year;
	month = d.month;
	day = d.day;
}

/////////////////////////////////////////////////////////////////////////

void Calendar::getTodaysDate()
{
	Date d;
	d.getTodaysDate();

	this->year = d.year;
	this->month = d.month;
	this->day = d.day;
}

void Calendar::setDate(Date d)
{
	year = d.year;
	month = d.month;
	day = d.day;
}

void Calendar::makeCalendar(Date d)
{
	std::string ym = d.year + "-" + d.month + "-01";
	std::chrono::system_clock::time_point tp;
	std::istringstream ss(ym.c_str());
	std::chrono::from_stream(ss, "%F", tp);
	std::chrono::time_point<std::chrono::system_clock, std::chrono::days> dp = floor<std::chrono::days>(tp);

	std::chrono::year_month_weekday ymw{ dp };
	int firstWeekDay = ymw.weekday().c_encoding();

	std::chrono::year_month_day ymd{ dp };
	std::chrono::year_month_day_last last_day_of_month(ymd.year(), std::chrono::month_day_last(ymd.month()));
	int lastDay = (unsigned int)last_day_of_month.day();

	// 여기서부터 ui 작업해야할듯
	// firstWeekDay가 1일의 요일이고, lastDay가 해당 월의 마지막 일
}
