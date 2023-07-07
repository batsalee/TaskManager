#include "Scheduler.h"

/* Task Schduler �ڼ��� ����
* 
����
1) �������� ���� / ����
2) �������� ���뺯��(ui������ Ŭ���ϸ� �ٱ׾�����)
3) ���α׷� ����� ���� ������� �������� ����

���ǻ���
1) C++ 17�̻� ���, 20�̻� ����

*/

Scheduler::Scheduler() // ���� ���� �����Ҷ�
{
	date = get_todays_date();
	path = "./Schedule/" + this->date;
}

Scheduler::Scheduler(std::string s) // �ٸ� Ư�� ��¥ �����Ҷ�
{
	date = get_todays_date();
	path = "./Schedule/" + s;
}

Scheduler::~Scheduler() {};  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�

// ���� ��¥ ���
std::string Scheduler::get_todays_date()
{
	using namespace std::chrono;

	// ���� local time ���ϱ�
	const local_time<system_clock::duration> now = 
		zoned_time{ current_zone(), system_clock::now() }.get_local_time();

	// year_month_day������ �ڸ���
	const time_point<std::chrono::local_t, std::chrono::days> tp = floor<std::chrono::days>(now);

	std::string todays_date = std::format("{:%Y-%m-%d}", tp);;
	// ex) 2023-07-07

	return todays_date;
}

// ������ ���� ���� �� ���� ����
void Scheduler::create_taskfile()
{	
	/*if (std::filesystem::exists())*/
} 

void Scheduler::remove_taskfile() {} // ��������/���� ����
void Scheduler::change_taskfile() {}	// �������� ���뺯��
