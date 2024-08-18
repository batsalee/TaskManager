/* JsonParser.h

1. Ŭ���� ����
JsonManager�� �ڽ�Ŭ����
FileReader�� ���� ������ ������ Json���� �Ľ� �� ScheduleFactory���� ���߸���Ʈ ����

2. �뵵
json������ �Ľ��ؼ� ���߸���Ʈ ������ ����

3. �������
rapidjson ���̺귯�� Ȱ��
*/

#pragma once

#include "JsonManager.h"
#include "../Schedule/Schedule.h"

class JsonParser : public JsonManager
{
public:
    Document parse(std::string file_content);
    bool isOpened(std::string file_content);
    void jsonToTaskList(std::string file_content, bool isRemaining = false);
};
