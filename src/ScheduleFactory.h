/* ScheduleFactory.h

1. Ŭ���� ����
Schedule Ŭ������ ���丮�޼��� ���� �������� ���丮 Ŭ����
Date Ŭ�����κ��� ��¥������ �޾� �ش� ��¥�� ������ ����

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
#include "Schedule.h"
#include "Date.h"
#include "FileReader.h"
#include "JsonManager.h"
using namespace rapidjson;

class ScheduleFactory
{
public:
    std::unique_ptr<Schedule> makeSchedule();
    virtual Date& getDate() = 0;

    virtual ~ScheduleFactory() {};
};
