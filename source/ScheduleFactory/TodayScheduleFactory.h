/* TodayScheduleFactory Ŭ����

1. Ŭ���� ����
ScheduleFactory�� ����Ŭ����
ScheduleFactory Ŭ������ Schedule Ŭ������ ���丮 �޼ҵ� ���� ���� �����̸�
TodayScheduleFactory Ŭ������ �� ������ concrete Ŭ����

2. �뵵
���α׷� ���� ����� ���� ��¥�� �����찴ü ����

3. �������
���� ��¥�� Schedule ��ü�� ����� ���丮�޼����� ������
*/

#pragma once

#include "ScheduleFactory.h"

class TodayScheduleFactory : public ScheduleFactory
{
public:
    Date& getDate() override;
};
