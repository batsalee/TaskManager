/* JsonManager.h

1. Ŭ���� ����
JsonParser�� JsonSerializer�� �θ�Ŭ����
FileManagerŬ������ ���� ������ context�� json���� �Ľ�
Schedule Ŭ���� �Ҹ�� ���߸���Ʈ�� json���� �Ľ� �� FileManager�� ���� ����

2. �뵵
���� ������ ���ÿ� json���� �����ϱ� ����

3. �������
rapidjson ���̺귯���� ����ؼ� �Ľ� �� �ø������¡
*/

#pragma once

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"

class JsonManager
{
public:
    virtual ~JsonManager() {};
};
