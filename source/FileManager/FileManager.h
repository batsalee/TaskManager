/* FileManager.h

1. Ŭ���� ����
FileReader, FileWriter Ŭ������ �θ�Ŭ����

2. �뵵
���� ������ ���ÿ� �����ؾ��ϹǷ� ��������� �� ���Ͻý��� ��� Ŭ����

3. �������
�����ϰ��� �ϴ� ������ �̹� �ִ���, Ȥ�� ���� ��ο� �´� ������ �̹� �ִ��� Ȯ���ϱ� ���� folder_path�� file_path�� ����
���� ���ϰ�ΰ� string���� ������ ��������� �ٷ� ������ ������
date�� ������ ��θ� �Ľ��ؾ� �ϹǷ� ���� �Լ� �����ε�
*/

#pragma once

#include <iostream> // ���� open close ���� ��¿뵵
#include <string>
#include <filesystem>
#include <fstream>
#include "../Date/Date.h"

class FileManager
{
protected:
    std::string folder_path; // ������ ���
    std::string file_path; // ������ ���
    // folder�� filesystem�� ���� �����ް�, file�� fstream�� ���� �����ް� �ϱ� ���� ���� ���

public:
    FileManager();

    virtual ~FileManager() {};

    // setter �����ε�
    void setPath(Date& date); // ��¥������ ��θ� �����ϴ� ��� ���
    void setPath(std::string path); // string���� ��ΰ� �����Ǵ� ��� ���

    // getter
    std::string getFolderPath(); // ���������� ��ġ�� ������ �������� �ľ��� ���� ���
    std::string getFilePath(); // ���������� �������� �ľ��� ���� ���
};
