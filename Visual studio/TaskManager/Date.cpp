#include "Date.h"

Date::Date()
{
	getTodaysDate();
}

Date::Date(std::string y, std::string m, std::string d)
{
	year = y;
	month = m;
	day = d;
}

/////////////////////////////////////////////////////////////////////////

void Date::getTodaysDate()
{
	using namespace std::chrono;

	// 현재 local time 구하기
	const local_time<system_clock::duration> now =
		zoned_time{ current_zone(), system_clock::now() }.get_local_time();

	// year_month_day까지만 자르기
	const time_point<std::chrono::local_t, std::chrono::days> tp = floor<std::chrono::days>(now);

	year = std::format("{:%Y}", tp);
	month = std::format("{:%m}", tp);
	day = std::format("{:%d}", tp);
}

void Date::setDate(std::string y, std::string m, std::string d)
{
	year = y;
	month = m;
	day = d;
}