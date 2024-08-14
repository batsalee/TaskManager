#include "FileWriter.h"

// ������
FileWriter::FileWriter()
{
    this->setPath(Date::instance());
}

/* writeFile()
�뵵 : File ��Ʈ���� ���� ������ ���ÿ� ������
������ : ��������� Schedule��ü�� task_list������ jsonManager�� Serializing�ϰ�
        �Ľ̵� ������ FileWriter�� writeFile ��ü�� ���� ���ÿ� ����
*/
void FileWriter::writeFile(std::string& context)
{
    // ���� ������ �����
    if (!std::filesystem::exists(folder_path))
        std::filesystem::create_directories(folder_path);

    std::ofstream out(file_path, std::ios::trunc);
    out << context;
}
