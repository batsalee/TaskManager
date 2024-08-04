/* FileManager.h

1. Ŭ���� ����
FileReader, FileWriter Ŭ������ �θ�Ŭ����

2. �뵵
���� ������ ���ÿ� �����ؾ��ϹǷ� ��������� �� ���Ͻý��� ��� Ŭ����

3. �������
FileReader Ŭ������ ScheduleFactory Ŭ������ Ŀ�ø��� ���� �� �ۿ� ����
�׷��Ƿ� �������� ��ȭ��Ű�� ���� ��Ӱ���� ���� �� virtual �Լ��� ȣ���ϵ��� ���� ȣ���ϰ� ����

FileWriterŬ���� ���� Schedule ��ü�� �Ҹ��ϴ� ������ Schedule ��ü�� ���� ȣ��ǰų�
Visitor ������ �����ؼ� ȣ��Ǿ�� �ϹǷ� ���������� virtual�� ���� �� ȣ��
*/

#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include "../Date/Date.h"

class FileManager
{
protected:
    std::string folder_path; // ������ ���
    std::string file_path; // ������ ���
    // ���� �� ����ϴ� ������ ������ filesystem�� ���� �����ް�, ������ fstream�� ���� �����ް� �ϱ� ����

public:
    // �������� ��¥(Date)�� �ش��ϴ� ���������� ��� ����
    void setFolderPath(Date& date);
    void setFilePath(Date& date);

    // ���� �� ������ �������� �ľ��� ���� getter
    std::string getFolderPath();
    std::string getFilePath();

    void setPath(Date& date);
    void setPath(std::string path);

    FileManager() = default;
    virtual ~FileManager() {};
};
