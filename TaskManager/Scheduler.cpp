/* Task Schduler �ڼ��� ����
* 
����
1) �������� ���� / ����
2) �������� ���뺯��(ui������ Ŭ���ϸ� �ٱ׾�����)
3) ���α׷� ����� ���� ������� �������� ����

���ǻ���
1) C++ 17�̻� ���, 20�̻� ����

*/
#include "Scheduler.h"

Scheduler::Scheduler() // ���� ���� �����Ҷ�
{
	get_todays_date();
	path = setPath();

	create_taskfile();
}

Scheduler::Scheduler(std::string y, std::string m, std::string d) // �ٸ� Ư�� ��¥ �����Ҷ�
{
	year = y; month = m; day = d;
	path = setPath();

	create_taskfile();
}

Scheduler::~Scheduler() {};  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�


/////////////////////////////////////////////////////////////////////////


// ���� ��¥ ���
void Scheduler::get_todays_date()
{
	using namespace std::chrono;

	// ���� local time ���ϱ�
	const local_time<system_clock::duration> now = 
		zoned_time{ current_zone(), system_clock::now() }.get_local_time();

	// year_month_day������ �ڸ���
	const time_point<std::chrono::local_t, std::chrono::days> tp = floor<std::chrono::days>(now);

	year = std::format("{:%Y}", tp);
	month = std::format("{:%m}", tp);
	day = std::format("{:%d}", tp);
}

std::string Scheduler::setPath()
{
	return "./Schedule/" + year + "/" + month + "/" + day + ".txt";
}

// ������ ���� ���� �� ���� ����
void Scheduler::create_taskfile()
{
	// ���� ������ �����
	if (!std::filesystem::exists("./Schedule/" + year + "/" + month))
		std::filesystem::create_directories("./Schedule/" + year + "/" + month);

	if (!std::filesystem::exists(path)) {	
		std::filesystem::path from("./Schedule/const_data/everyday.txt");
		std::filesystem::path to(path);
		std::filesystem::copy(from, to);
	}
		
} 

void Scheduler::remove_taskfile() {} // ��������/���� ����
void Scheduler::change_taskfile() {}	// �������� ���뺯��
