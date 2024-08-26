#include "FileWriter.h"

/* getOfstream()
���� ������ ������ rapidjson�� �ٸ� ������� ���� ���ܵ�
*/
std::ofstream FileWriter::getOfstream()
{
    std::ofstream ofs(file_path);
    if(!ofs.is_open()) throw std::runtime_error("Failed to open file.");

    return ofs;
}

/* writeFile()
�뵵 : File ��Ʈ���� ���� ������ ���ÿ� ������
������ : ��¥ ���� Ȥ�� ���α׷� ���� �� TaskListManager�� task_list ������ jsonSerializer�� Serialize�ϰ� ���⼭ ������� ����� FileWriter�� ���ÿ� ����

��� : ���� ���� �������� ���� �߻� �� ��ó ���
*/
void FileWriter::writeFile(const std::string& context)
{
    // ������ ����� ��ο� �´� ������ ���ٸ� �����
    if (!std::filesystem::exists(folder_path)) std::filesystem::create_directories(folder_path);

    try {
        std::ofstream ofs(file_path, std::ios::trunc);
        if(!ofs.is_open()) throw std::runtime_error("Failed to open file.");

        ofs << context;
        if(ofs.fail()) throw std::runtime_error("Failed to write to file.");
    }
    catch(const std::runtime_error& re) {
        std::cerr << std::string(re.what()) << "(" + file_path << ")";
    }
}
