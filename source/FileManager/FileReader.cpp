#include "FileReader.h"

/* readFile()
�뵵 : File ��Ʈ���� ���� ������ �о��
������ : ���ÿ� ����� ���������� �о�� �� JsonManager�� ���� �ش� ����(json����)�� �Ľ̵�
*/
std::string FileReader::readFile()
{
    std::ifstream ifs(file_path);
    if(!ifs) {
        throw std::runtime_error("Failed to open file.");
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string file_content = buffer.str();

    return file_content;
}
