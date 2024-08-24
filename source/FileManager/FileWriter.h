/* FileWriter.h

1. Ŭ���� ����
FileManager.h�� �ڽ�Ŭ����

2. �뵵
���ÿ� ���������� ������ �ۼ��ϰ� ������

3. �������
FileManager ��ӹް� ���� ���õ� �κи� FileWriter���� Ȯ��
*/

#pragma once

#include "FileManager.h"

class FileWriter : public FileManager
{
public:
    std::ofstream getOfstream(); // ���� ������ ������ rapidjson�� �ٸ� ������� ���� ���ܵ�
    void writeFile(const std::string& context);
};
