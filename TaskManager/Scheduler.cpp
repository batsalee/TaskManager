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

Scheduler::Scheduler() {};
Scheduler::Scheduler(std::filesystem::path p) {};
Scheduler::~Scheduler() {};  // ���� ���� ���Ͽ� ���� ���� ���� �����ϱ�


// �Ű������� �Լ� �����ϸ鼭 ��üȭ�ϱ�
void Scheduler::create_taskfile() {}; // ������ ���� ���� �� ���� ����
void Scheduler::remove_taskfile() {}; // ��������/���� ����
void Scheduler::change_taskfile() {};	// �������� ���뺯��
