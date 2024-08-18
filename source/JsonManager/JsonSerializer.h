/* JsonSerializer.h

1. Ŭ���� ����
JsonManager�� �ڽ�Ŭ����
Schedule ��ü �Ҹ�� ���߸���Ʈ�� json���� serializing�� �� �ش� ������ FileWriter�� ���ÿ� ����

2. �뵵
���߸���Ʈ�� json���� ����

3. �������
rapidjson ���̺귯�� Ȱ��
*/

#pragma once

#include "JsonManager.h"
#include "../Schedule/Schedule.h"

class JsonSerializer : public JsonManager
{
public:
    std::string taskListToJson(QList<QList<Task>>& task_list);
};
