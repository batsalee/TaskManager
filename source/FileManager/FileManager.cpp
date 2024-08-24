#include "FileManager.h"

/* FileManager()
�뵵 : ������, �ʱⰪ ����
������ : ��ü ������ Date�� �����ؼ� ���� ��¥ ������ ������� ��� ����

- �ʱⰪ ������ ����
��κ��� ��� ���� �������� ��¥�� ������ �а� ���⶧����, ��ü ���� ���� ��κ��� ��� setPath(Date&)�� ȣ���ϹǷ� �ڵ� �ߺ��� ���̰� ���Ǽ��� ���̱� ���� �����ڿ��� ȣ��
���� Date ��ü�� �����ڿ� �� �Ǽ��� ������ �� �ִ� ��ġ�� �����ױ⿡ �Ǽ� ������ ���弱
*/
FileManager::FileManager()
{
    setPath(Date::instance()); // ���� �������� ��¥�� ��� ����
}

/* setPath(Date& date)
�뵵 : �������� ��¥�� ������� ���������� ��� ����
������ : ��¥ ���� �� �Է� �Ű������� Date��ü(��¥����)�� ��� Date��ü�� ��/��/���� �����ϰ� �Ľ��ؼ� ������ ����� ���������� ���ϸ��� ����
*/
void FileManager::setPath(Date& date)
{
    std::string year = std::to_string(date.getYear());
    std::string month = (date.getMonth() < 10) ? '0' + std::to_string(date.getMonth()) : std::to_string(date.getMonth());
    folder_path = "./Data/" + year + "/" + month;

    std::string file_name = (date.getDay() < 10) ? '0' + std::to_string(date.getDay()) : std::to_string(date.getDay());
    file_path = folder_path + "/" + file_name + ".json";
}

/* setPath(std::string file_name)
�뵵 : �������� ���ϸ��� ������� ���������� ��� ����
      ProgramInfo ������ �аų�, fixed_schedule�� ��������, �ش� ���Ͽ� ���� ���� �����ص� ������ ��θ� ������ �� ���
������ : ��¥ ���� �� �Է� �Ű������� string(���ϸ�)�� ��� ���� ���� ������� ��� ����

- �� ��� �����ÿ� �̹� ���� ������ �����Ǿ� �����Ƿ� folder_path�� �ʿ����� ����
*/
void FileManager::setPath(std::string file_name)
{
    file_path = file_name;
}

/* getFolderPath(), getFilePath()
�뵵 : ���� �������� ���������� ��� ȹ��
������ : ���� ��¥�� ������ ����� ������ �ִ��� Ȯ���ϱ� ���� getFilePath() ȣ��
        ��¥ ���� Ȥ�� ���α׷� ���� �� ������ ���ÿ� �����ؾ� �ϹǷ� ���������� ��ġ�� ������ �����ϴ��� Ȯ���ϱ� ���� getFolderPath() ȣ��
*/
std::string FileManager::getFolderPath() const { return folder_path; }
std::string FileManager::getFilePath() const { return file_path; }

