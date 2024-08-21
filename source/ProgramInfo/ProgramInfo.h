/* Initializer.h

1. Ŭ���� ����

2. �뵵

3. �������
*/

#pragma once

#include "../FileManager/FileReader.h"
#include "../FileManager/FileWriter.h"
#include "../JsonManager/JsonParser.h"
#include "../JsonManager/JsonSerializer.h"
#include "../Tutorial/Tutorial.h"

class ProgramInfo
{
public:
    bool tutorial;
    int last_managed_date_year;
    int last_managed_date_month;
    int last_managed_date_day; // �� ������ getter ����°� ��������

    // ������
    ProgramInfo();
    ~ProgramInfo();

    // ���� Ȯ�ο� bool�Լ�
    bool isTutorialNeeded();
    bool isOpenedToday(Date& date);
};
