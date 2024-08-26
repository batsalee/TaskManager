/* FileManager.h

1. Ŭ���� ����
FileReader, FileWriter Ŭ������ �θ�Ŭ����
Date Ŭ������ �����ؼ� ��� ���� �� ���

2. �뵵
���� ������ ���ÿ� �����ϰ� �о�;��ϹǷ� ��������� �� ���Ͻý��� ��� Ŭ����

3. �������
- Ŭ������ ���� �д� �� Ȯ��
�θ�Ŭ������ FileManager Ŭ������ ������ ��� ���� ��ɸ� ����
�ڽ�Ŭ������ FileReader Ŭ������ ������ ������ �о���� ����� Ȯ��
�ڽ�Ŭ������ FileWriter Ŭ������ ���Ͽ� ������ ���� ����� Ȯ��

- ������ο� ���ϰ�θ� ���� ����
���� �� ������ ���� ���� �ľ��� ���� filesystem ���̺귯�� Ȱ�� �� �̸� ���� ������ο� ���ϰ�θ� ���� ����
FileWriter Ŭ�������� �����ϴ� ������ ���� ��ο� �´� ������ ���� ���� �ľ��� ���� folder_path�� Ȱ��
���� ������ �̹� �����ϴ��� ���� �ľ��� ���� file_path�� Ȱ��

- �Լ� �����ε�
��¥�� ������� ���� ��θ� �����ϱ� ���� date�� �޴� setPath(Date&)��,
���� ������ ��� ���ϸ��� ������� ���� ��θ� �����ϱ� ���� std::string�� �޴� setPath(std::string&)�� ����
*/

#pragma once

#include <iostream> // ���Ͽ������� cerr ��¿뵵
#include <string>
#include <filesystem>
#include <fstream>

#include "../Date/Date.h"

class FileManager
{
protected:
    std::string folder_path; // ������ ���
    std::string file_path; // ������ ���

public:
    FileManager(); // ��ü ���� �� ���� �������� ��¥�� ������� ��� ����
    virtual ~FileManager() {};

    // getter
    std::string getFolderPath() const; // ���������� ��ġ�� ������ �������� �ľ��� ���� ���
    std::string getFilePath() const; // ���������� �������� �ľ��� ���� ���

    // setter �����ε�
    void setPath(Date& date); // ��¥������ ��θ� �����ϴ� ��� ���
    void setPath(std::string path); // string���� ��ΰ� �����Ǵ� ��� ���
};
