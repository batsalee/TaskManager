/* JsonManager.h

1. Ŭ���� ����
JsonParser�� JsonSerializer�� �θ�Ŭ����

2. �뵵
json ������ �Ľ��ϰ�, �����͸� json���� �ø������¡�ϴ� �뵵

3. �������
rapidjson ���̺귯���� ���
�ڽ�Ŭ������ JsonParser Ŭ������ json������ ���ڿ��� �Ľ��ϰ�, ���ϴ� ���·� ��ȯ�ϴ� ����� ����
�ڽ�Ŭ������ JsonSerializer Ŭ������ ���α׷� ���� �����͸� json���·� �Ľ��ϴ� ����� ����
*/

#pragma once



#include "../Task/Task.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"
using namespace rapidjson;

class JsonManager
{
public:
    virtual ~JsonManager() {};
};
