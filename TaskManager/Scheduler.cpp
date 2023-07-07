/* Task Schduler 자세한 구현
* 
역할
1) 일정파일 생성 / 제거
2) 일정파일 내용변경(ui에서는 클릭하면 줄그어지게)
3) 프로그램 종료시 현재 일정대로 일정파일 갱신

주의사항
1) C++ 17이상 사용, 20이상 권장

*/
#include "Scheduler.h"

Scheduler::Scheduler() // 오늘 일정 관리할때
{
	get_todays_date();
	path = setPath();

	create_taskfile();
}

Scheduler::Scheduler(std::string y, std::string m, std::string d) // 다른 특정 날짜 관리할때
{
	year = y; month = m; day = d;
	path = setPath();

	create_taskfile();
}

Scheduler::~Scheduler() {};  // 현재 상태 파일에 새로 쓰는 내용 갱신하기


/////////////////////////////////////////////////////////////////////////


// 오늘 날짜 얻기
void Scheduler::get_todays_date()
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

std::string Scheduler::setPath()
{
	return "./Schedule/" + year + "/" + month + "/" + day + ".txt";
}

// 오늘의 일정 폴더 및 파일 생성
void Scheduler::create_taskfile()
{
	// 폴더 없으면 만들기
	if (!std::filesystem::exists("./Schedule/" + year + "/" + month))
		std::filesystem::create_directories("./Schedule/" + year + "/" + month);

	if (!std::filesystem::exists(path)) {	
		std::filesystem::path from("./Schedule/const_data/everyday.txt");
		std::filesystem::path to(path);
		std::filesystem::copy(from, to);
	}
		
} 

void Scheduler::remove_taskfile() {} // 일정파일/폴더 제거
void Scheduler::change_taskfile() {}	// 일정파일 내용변경
