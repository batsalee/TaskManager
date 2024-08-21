#include "FileWriter.h"

std::ofstream FileWriter::getOfstream()
{
    std::ofstream ofs(file_path);
    if(!ofs) throw std::runtime_error("Failed to open file.");

    return ofs;
}

/* writeFile()
용도 : File 스트림을 열고 내용을 로컬에 저장함
시퀀스 : 종료시점에 Schedule객체의 task_list내용을 jsonManager가 Serializing하고
        파싱된 내용을 FileWriter의 writeFile 객체를 통해 로컬에 저장
*/
void FileWriter::writeFile(const std::string& context)
{
    // 폴더 없으면 만들기
    if (!std::filesystem::exists(folder_path))
        std::filesystem::create_directories(folder_path);

    std::ofstream out(file_path, std::ios::trunc);
    out << context;
}
