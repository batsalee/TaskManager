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
	getTodaysDate();
	path = setPath();

	createTaskfile();
}

Scheduler::Scheduler(Date d) // 다른 특정 날짜 관리할때
{
	year = d.year; month = d.month; day = d.day;
	path = setPath();

	createTaskfile();
}

Scheduler::~Scheduler() {};  // 현재 상태 파일에 새로 쓰는 내용 갱신하기


/////////////////////////////////////////////////////////////////////////


// 오늘 날짜 얻기
void Scheduler::getTodaysDate()
{
	Date d;
	d.getTodaysDate();

	this->year = d.year;
	this->month = d.month;
	this->day = d.day;
}

std::string Scheduler::setPath()
{
	return "./Schedule/" + year + "/" + month + "/" + day + ".txt";
}

// 오늘의 일정 폴더 및 파일 생성
void Scheduler::createTaskfile()
{
	// 폴더 없으면 만들기
	if (!std::filesystem::exists("./Schedule/" + year + "/" + month))
		std::filesystem::create_directories("./Schedule/" + year + "/" + month);

	// 파일 없으면 만들기
	if (!std::filesystem::exists(path)) {	
		std::filesystem::path from("./Schedule/const_data/everyday.txt");
		std::filesystem::path to(path);
		std::filesystem::copy(from, to);
	}
	else { // 파일이 이미 있다면
		std::ifstream p(path);
		char c;
		p.seekg(-1, std::ios::end);
		p.read(&c, 1);
		p.close();

		if (c != '#') { // 개별일정이 있고 && 오늘 처음 연 파일이라면
			std::ifstream in("./Schedule/const_data/everyday.txt");
			std::string s;

			// 개별일정이 있다는 뜻이므로 const.txt append해주기
			in.seekg(0, std::ios::end);
			int size = in.tellg();
			s.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&s[0], size);

			std::ofstream out(path, std::ios::app);			
			out << '\n' << s << "\n#";
			// 이미 everday.txt를 붙여왓으니 또 붙일 필요 없으므로
		}		
	}	
} 

void Scheduler::removeTaskfile() {} // 일정파일/폴더 제거
void Scheduler::changeTaskfile() {}	// 일정파일 내용변경
