/* Task Scheduler

����
1) �������� ���� / ����
2) �������� ���뺯��(ui������ Ŭ���ϸ� �ٱ׾�����)
3) ���α׷� ����� ���� ������� �������� ����

���ǻ���
1) C++ 17�̻� ���, 20�̻� ����

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
	// ���ϵ� ���
	std::vector<std::list<std::string>> tasks;
	std::stack<std::tuple<std::string, int, int>> completed;
	
	// �������� ��¥
	std::string year, month, day;
	
	// �ش� ��¥�� ���� ���� ���
	std::string path; 

	void get_todays_date(); // ���� ��¥ ���
	std::string setPath();

	void create_taskfile(); // ������ ���� ���� �� ���� ����
	void remove_taskfile(); // ��������/���� ����
	void change_taskfile();	// �������� ���뺯��

public :
	Scheduler();
	Scheduler(std::string, std::string, std::string);
	~Scheduler();  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�
};