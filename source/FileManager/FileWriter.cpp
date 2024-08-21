#include "FileWriter.h"

std::ofstream FileWriter::getOfstream()
{
    std::ofstream ofs(file_path);
    if(!ofs) throw std::runtime_error("Failed to open file.");

    return ofs;
}

/* writeFile()
�뵵 : File ��Ʈ���� ���� ������ ���ÿ� ������
������ : ��������� Schedule��ü�� task_list������ jsonManager�� Serializing�ϰ�
        �Ľ̵� ������ FileWriter�� writeFile ��ü�� ���� ���ÿ� ����
*/
void FileWriter::writeFile(const std::string& context)
{
    // ���� ������ �����
    if (!std::filesystem::exists(folder_path))
        std::filesystem::create_directories(folder_path);

    std::ofstream out(file_path, std::ios::trunc);
    out << context;
}
