/* FileReader.h

1. Ŭ���� ����
FileManager.h�� �ڽ�Ŭ����

2. �뵵
���ÿ� ����� File�� �о��
�о�� ����� JsonParser�� ���� ���߸���Ʈ�� �Ľ̵�

3. �������
FileManager.h�� virtual readFrile()�� ������
*/

#pragma once

#include "FileManager.h"

class FileReader : public FileManager
{
public:
    FileReader() = default;
    FileReader(std::string path) { file_path = path; }

    std::string readFile();
};