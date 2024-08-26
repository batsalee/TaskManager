#include "FileReader.h"

/* getIfstream()
���� ������ ������ rapidjson�� �ٸ� ������� ���� ���ܵ�
*/
std::ifstream FileReader::getIfstream()
{
    std::ifstream ifs(file_path);
    if(!ifs.is_open()) throw std::runtime_error("Failed to open file");

    return ifs;
}

/* readFile()
�뵵 : File ��Ʈ���� ���� ������ �о��
������ : ���ÿ� ����� ���������� �о�� �� ��ȯ
Ư�̻��� : ���� �߻��� ���ܴ� �� �Լ� ���ΰ� �ƴ� ȣ���� ������ ó���ϸ�,
          ������ ���ܰ� �߻��� ������ �̸��� Ȯ���ϱ� ���԰� read ���� �������� parse ���� �������� �����ϱ� ����
*/
std::string FileReader::readFile()
{
    std::ifstream ifs(file_path);
    if(!ifs.is_open()) throw std::runtime_error("Failed to open file");

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    if(ifs.fail()) throw std::runtime_error("Failed to read file");

    return buffer.str(); // RVO ����
}
