/* ProgramInfo.h

1. Ŭ���� ����
FileReader Ŭ������ JsonParser�� ȣ���ؼ� Ȱ���ϴ� Ŭ����

2. �뵵
���α׷� ���� �� ���α׷� ���� ������ ����� program_info.json ������ �ؼ��ؼ� ���α׷� ������ ȹ����

3. �������
FileReader�� ���� program_info.json ������ �о����, JsonParser�� ���� �Ľ��� ������� �ʿ��� ������ ������
�ش� ������ �̿��ؼ� ���α׷� ������� ������ ������
�۾��� ������ ���� ������ �����ؼ� JsonSerializer�� FileWriter�� Ȱ���� �ٽ� program_info.json ���Ͽ� ���α׷� ������ ������
*/

#pragma once

#include "../FileManager/FileReader.h"
#include "../FileManager/FileWriter.h"
#include "../JsonManager/JsonParser.h"
#include "../JsonManager/JsonSerializer.h"
#include "../Tutorial/Tutorial.h"

class ProgramInfo
{
private:
    bool tutorial;
    int last_managed_date_year;
    int last_managed_date_month;
    int last_managed_date_day;

public:
    // ������, �Ҹ���
    ProgramInfo();
    ~ProgramInfo();

    // ���� Ȯ�ο� bool�Լ�
    bool isTutorialNeeded();
    bool isOpenedToday(Date& date);

    // getter
    int getLastManagedDateYear() const;
    int getLastManagedDateMonth() const;
    int getLastManagedDateDay() const;
};
