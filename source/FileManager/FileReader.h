/* FileReader.h

1. Ŭ���� ����
FileManager.h�� �ڽ�Ŭ����

2. �뵵
���ÿ� ����� File�� �о��
�о�� ����� JsonParser�� ���� ���߸���Ʈ�� �Ľ̵�

3. �������
FileManager ��ӹް� �б� ���õ� �κи� FileReader�� ����
*/

#pragma once

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    std::string readFile();
};
