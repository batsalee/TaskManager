/* JsonParser.h

1. Ŭ���� ����
JsonManager�� �ڽ�Ŭ����

2. �뵵
json ������ �Ľ��ؼ� ���α׷��� �ʿ��� ���·� ��ȯ

3. �������
rapidjson ���̺귯�� Ȱ��

4. ���
parse() �Լ��� private�� ���� �ϴ� ���� ���� ����� ����
parse() �Լ��� ����� ���ڿ��� �־��� json ������ �Ľ��ؼ� Document�� �����ϴ� �Լ��̹Ƿ� ��𼭵� �����ϰ� ���� �� ����
������ ���� �� ������Ʈ������ �Ľ̰� ���õ� ��� �۾��� JsonParser���� �����ϵ��� ������Ű�� �����Ƿ� jsonToProgramInfo()�� jsonToTaskList()���� �Լ��� ȣ���ϵ��� �������
��������� parse()�� ���ο����� ���ǹǷ� private�� ��������.
������ Ŭ������ ���뼺�� �����Ѵٸ� �ٸ� ��𿡼��� parse�� �����ϰ� ��� �����ϹǷ� public���� �����ϴ°��� ���� ���� ����.
*/

#pragma once

#include "JsonManager.h"

class JsonParser : public JsonManager
{
private:
    Document parse(const std::string& file_content);

public:
    std::pair<bool, std::tuple<int, int, int>> jsonToProgramInfo(const std::string& file_content);
    QList<QList<Task>> jsonToTaskList(const std::string& file_content);
};
