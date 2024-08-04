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
#include <fstream>

class FileManager
{
protected:
    std::string file_path; // ������ ���

public:
    virtual ~FileManager() {};
};
