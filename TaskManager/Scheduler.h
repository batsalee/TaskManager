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
#include <vector>
#include <list>
#include <stack>
#include "Date.h"

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

	void getTodaysDate(); // ���� ��¥ ���
	std::string setPath();

	void createTaskfile(); // ������ ���� ���� �� ���� ����
	void removeTaskfile(); // ��������/���� ����
	void changeTaskfile();	// �������� ���뺯��

public :
	Scheduler();
	Scheduler(Date);
	~Scheduler();  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�
};