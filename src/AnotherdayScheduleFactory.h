/* AnotherdayScheduleFactory Ŭ����

1. Ŭ���� ����
ScheduleFactory�� ����Ŭ����
ScheduleFactory Ŭ������ Schedule Ŭ������ ���丮 �޼ҵ� ���� ���� �����̸�
AnotherdayScheduleFactory Ŭ������ �� ������ concrete Ŭ����

2. �뵵
������ �ƴ� �ٸ� ��¥ ���ý� �ش� ��¥�� �����찴ü ����

3. �������
�ش� ��¥�� Schedule ��ü�� ����� ���丮�޼����� ������
*/

#pragma once

#include "ScheduleFactory.h"

class AnotherdayScheduleFactory : public ScheduleFactory
{
public:
    Date& getDate() override;
};
