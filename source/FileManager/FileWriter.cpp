#include "FileWriter.h"

/* writeFile()
�뵵 : File ��Ʈ���� ���� ������ ���ÿ� ������
������ : ��������� Schedule��ü�� task_list������ jsonManager�� Serializing�ϰ�
        �Ľ̵� ������ FileWriter�� writeFile ��ü�� ���� ���ÿ� ����
*/

void FileWriter::writeFile(std::string& context)
{
    std::ofstream out(file_path);
    out << context;
}

