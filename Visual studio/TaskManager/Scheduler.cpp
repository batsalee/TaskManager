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
	getTodaysDate();
	path = setPath();

	createTaskfile();
}

Scheduler::Scheduler(Date d) // �ٸ� Ư�� ��¥ �����Ҷ�
{
	year = d.year; month = d.month; day = d.day;
	path = setPath();

	createTaskfile();
}

Scheduler::~Scheduler() {};  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�


/////////////////////////////////////////////////////////////////////////


// ���� ��¥ ���
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

// ������ ���� ���� �� ���� ����
void Scheduler::createTaskfile()
{
	// ���� ������ �����
	if (!std::filesystem::exists("./Schedule/" + year + "/" + month))
		std::filesystem::create_directories("./Schedule/" + year + "/" + month);

	// ���� ������ �����
	if (!std::filesystem::exists(path)) {	
		std::filesystem::path from("./Schedule/const_data/everyday.txt");
		std::filesystem::path to(path);
		std::filesystem::copy(from, to);
	}
	else { // ������ �̹� �ִٸ�
		std::ifstream p(path);
		char c;
		p.seekg(-1, std::ios::end);
		p.read(&c, 1);
		p.close();

		if (c != '#') { // ���������� �ְ� && ���� ó�� �� �����̶��
			std::ifstream in("./Schedule/const_data/everyday.txt");
			std::string s;

			// ���������� �ִٴ� ���̹Ƿ� const.txt append���ֱ�
			in.seekg(0, std::ios::end);
			int size = in.tellg();
			s.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&s[0], size);

			std::ofstream out(path, std::ios::app);			
			out << '\n' << s << "\n#";
			// �̹� everday.txt�� �ٿ������� �� ���� �ʿ� �����Ƿ�
		}		
	}	
} 

void Scheduler::removeTaskfile() {} // ��������/���� ����
void Scheduler::changeTaskfile() {}	// �������� ���뺯��
