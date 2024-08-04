#include "FileReader.h"

/* readFile()
�뵵 : File ��Ʈ���� ���� ������ �о��
������ : ���ÿ� ����� ���������� �о�� �� JsonManager�� ���� �ش� ����(json����)�� �Ľ̵�
��� : rapidjson ���̺귯���� string���κ��� �Ľ��� �ƴ�, stream���κ����� �Ḻ̌���� ����
      �ش� ����� ����ϴ����� ������带 �ѹ� ���̴°��̹Ƿ� �����غ� �����ε�
      ������ �׷� readFile�Լ��� ���� ifstream�� return�ϴ� ��ɸ� ���� ��.
      ���� ���ǿ� ���� �����
*/
std::string FileReader::readFile()
{
    std::ifstream ifs(file_path);
    std::string file_content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    return file_content;
}

