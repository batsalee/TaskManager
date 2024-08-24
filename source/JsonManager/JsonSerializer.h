/* JsonSerializer.h

1. Ŭ���� ����
JsonManager�� �ڽ�Ŭ����

2. �뵵
���α׷� ������ �����͸� json ���·� ����

3. �������
rapidjson ���̺귯�� Ȱ��
*/

#pragma once

#include "JsonManager.h"

class JsonSerializer : public JsonManager
{
public:
    std::string programInfoToJson(int y, int m, int d);
    std::string taskListToJson(const QList<QList<Task>>& task_list);
};
