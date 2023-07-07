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
	// 할일들 목록
	std::vector<std::list<std::string>> tasks;
	std::stack<std::tuple<std::string, int, int>> completed;
	
	// 관리중인 날짜
	std::string year, month, day;
	
	// 해당 날짜의 일정 파일 경로
	std::string path; 

	void get_todays_date(); // 오늘 날짜 얻기
	std::string setPath();

	void create_taskfile(); // 오늘의 일정 폴더 및 파일 생성
	void remove_taskfile(); // 일정파일/폴더 제거
	void change_taskfile();	// 일정파일 내용변경

public :
	Scheduler();
	Scheduler(std::string, std::string, std::string);
	~Scheduler();  // 현재 상태 파일에 새로 쓰는 내용 갱신하기
};