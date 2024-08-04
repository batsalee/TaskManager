#include "FileManager.h"

/* setPath(Date& date)
�뵵 : �������� ���������� ��� ����, �Է� �Ű������� date(��¥����)�� ��� �Ľ� �� ����
������ : Date��ü�� ��/��/���� ������� ������ ����� ���������� ���ϸ��� ����
*/
void FileManager::setPath(Date& date)
{
    std::string year = std::to_string(date.getYear());
    std::string month = (date.getMonth() < 10) ? '0' + std::to_string(date.getMonth()) : std::to_string(date.getMonth());
    folder_path = "./Schedule/" + year + "/" + month;

    std::string file_name = (date.getDay() < 10) ? '0' + std::to_string(date.getDay()) : std::to_string(date.getDay());
    file_path = folder_path + "/" + file_name + ".json";
}

/* setPath(std::string file_name)
�뵵 : �������� ���������� ��� ����, �Է� �Ű������� string�ΰ�� �ش� ������ ����
������ : everyday.json�� ��� ��ΰ� �������̹Ƿ� �״�� ����
        �� ���Ϻ�.json�� ��� ������ ���Ͽ� �´� ���Ϸ� ����
*/
void FileManager::setPath(std::string file_name)
{
    folder_path = "./Schedule/fixed_schedule";
    file_path = folder_path + "/" + file_name + ".json";
}

/* getFolderPath(), getFilePath()
�뵵 : ���� �������� ���������� ��� ȹ��
������ : Schedule ��ü �Ҹ�� ������ ���ÿ� �����ؾ� �ϹǷ� ���������� ��ġ�� ������ �����ϴ���, ������ �����ϴ��� Ȯ���Ҷ� ȣ��
*/
std::string FileManager::getFolderPath() { return folder_path; }
std::string FileManager::getFilePath() { return file_path; }
