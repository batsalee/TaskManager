/* JsonParser.h

1. Ŭ���� ����
JsonManager�� �ڽ�Ŭ����

2. �뵵
json ������ �Ľ��ؼ� ���α׷��� �ʿ��� ���·� ��ȯ

3. �������
rapidjson ���̺귯�� Ȱ��
*/

#pragma once

#include "JsonManager.h"

class JsonParser : public JsonManager
{
public:
    Document parse(const std::string& file_content);
    std::pair<bool, std::tuple<int, int, int>> jsonToProgramInfo(const std::string& file_content);
    QList<QList<Task>> jsonToTaskList(const std::string& file_content);
};
