/* FileWriter.h

1. Ŭ���� ����
FileManager.h�� �ڽ�Ŭ����

2. �뵵
���ÿ� ���������� ������ �ۼ��ϰ� ������
Schedule��ü�� �Ҹ��Ҷ� ���߸���Ʈ�� ������ JsonSerializer�� json���� �����ϰ�
FileWriter�� �ش� json ������ ���ÿ� File�� ����

3. �������
FileManager.h�� virtual writeFile()�� ������
*/

#pragma once

#include "FileManager.h"

class FileWriter : public FileManager
{
public:
    FileWriter() = default;
    FileWriter(std::string path) { file_path = path; }

    void writeFile(std::string&);
};