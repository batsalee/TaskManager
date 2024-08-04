#include "FileManager.h"

void FileManager::setFolderPath(Date& date)
{
    std::string year, month;
    year = std::to_string(date.getYear());
    month = (date.getMonth() < 10) ? '0' + std::to_string(date.getMonth()) : std::to_string(date.getMonth());

    folder_path = "./Schedule/" + year + "/" + month;
}

void FileManager::setFilePath(Date& date)
{
    std::string file_name = (date.getDay() < 10) ? '0' + std::to_string(date.getDay()) : std::to_string(date.getDay());

    file_path = folder_path + "/" + file_name + ".json";
}

std::string FileManager::getFolderPath()
{
    return folder_path;
}

std::string FileManager::getFilePath()
{
    return file_path;
}

void FileManager::setPath(Date& date)
{
    setFolderPath(date);
    setFilePath(date);
}

void FileManager::setPath(std::string file_name)
{
    folder_path = "./Schedule/fixed_schedule";
    file_path = folder_path + "/" + file_name + ".json";
}
