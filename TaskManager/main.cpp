#include <iostream>
#include "Scheduler.h"
#include "Calendar.h"
#include "Date.h"

int main()
{
	// Debug
	std::cout << "Scheduler �ۼ���...\n";

	Date da;
	Calendar c;
	c.makeCalendar(da);

	return 0;
}