/* Task Scheduler

역할
1) 일정파일 생성 / 제거
2) 일정파일 내용변경(ui에서는 클릭하면 줄그어지게)
3) 프로그램 종료시 현재 일정대로 일정파일 갱신

주의사항
1) C++ 17이상 사용, 20이상 권장

*/
#pragma once

#include <filesystem>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <stack>

class Scheduler
{
private:
	std::vector<std::list<std::string>> tasks;
	std::stack<std::tuple<std::string, int, int>> completed;
	std::string todays_date;
	
	// test
public:
	std::filesystem::path p;

public :
	Scheduler();
	Scheduler(std::filesystem::path p);
	~Scheduler();  // 현재 상태 파일에 새로 쓰는 내용 갱신하기

	std::string get_todays_date(); // 오늘 날짜 얻기

	void create_taskfile(); // 오늘의 일정 폴더 및 파일 생성
	void remove_taskfile(); // 일정파일/폴더 제거
	void change_taskfile();	// 일정파일 내용변경

	// 매개변수들 함수 구현하면서 구체화하기
};