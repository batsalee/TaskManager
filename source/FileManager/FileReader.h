/* FileReader.h

1. Ŭ���� ����
FileManager.h�� �ڽ�Ŭ����

2. �뵵
���ÿ� ����� File�� ������ �о��

3. �������
FileManager ��ӹް� �б� ���õ� �κи� FileReader���� Ȯ��
*/

#pragma once

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    std::ifstream getIfstream(); // ���� ������ ������ rapidjson�� �ٸ� ������� ���� ���ܵ�
    std::string readFile();
};
