/* ScheduleFactory.h

1. Ŭ���� ����
Schedule Ŭ������ ���丮�޼��� ���� �������� ���丮 Ŭ����
Date, FileReader, JsonParser Ŭ������ �̿��� ���� ����� �ۼ�

2. �뵵
Schedule Ŭ������ ���丮

3. �������
���丮 �޼��� �������� ����
����1) Schedule ��ü ������ Schedule��ü�� Date, FileManager, JsonManager���� Ŀ�ø� ���Ҹ� ����
����2) Schedule ��ü ������������ ���ó�¥����, �ٸ� ��¥������ ���̸� ������ �������� ����
*/

#pragma once

#include <iostream>
#include <memory>
#include "../Schedule/Schedule.h"
#include "../Date/Date.h"
#include "../FileManager/FileReader.h"
#include "../JsonManager/JsonParser.h"

class ScheduleFactory
{
public:
    void makeSchedule(); // ���丮 �޼��� ������ �����Լ�
    virtual Date& getDate() = 0;

    virtual ~ScheduleFactory() {};
};
