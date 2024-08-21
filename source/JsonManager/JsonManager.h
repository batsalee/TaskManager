/* JsonManager.h

1. Ŭ���� ����
JsonParser�� JsonSerializer�� �θ�Ŭ����
FileManagerŬ������ ���� ������ context�� json���� �Ľ�
Schedule Ŭ���� �Ҹ�� ���߸���Ʈ�� json���� �Ľ� �� FileManager�� ���� ����

2. �뵵
���� ������ ���ÿ� json���� �����ϰ�, ����� json�� �о�ͼ� �Ľ��ϴ� �뵵

3. �������
rapidjson ���̺귯���� ����ؼ� �Ľ� �� �ø������¡
*/

#pragma once

#include <iostream> // ���Ͽ������� cerr ��¿뵵

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
