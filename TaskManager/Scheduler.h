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
	std::vector<std::list<std::string>> tasks;
	std::stack<std::tuple<std::string, int, int>> completed;
	std::string todays_date;
	
	// test
public:
	std::filesystem::path p;

public :
	Scheduler();
	Scheduler(std::filesystem::path p);
	~Scheduler();  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�

	std::string get_todays_date(); // ���� ��¥ ���

	void create_taskfile(); // ������ ���� ���� �� ���� ����
	void remove_taskfile(); // ��������/���� ����
	void change_taskfile();	// �������� ���뺯��

	// �Ű������� �Լ� �����ϸ鼭 ��üȭ�ϱ�
};