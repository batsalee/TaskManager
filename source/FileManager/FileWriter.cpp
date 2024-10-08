#include "FileWriter.h"

/* getOfstream()
현재 사용되지 않지만 rapidjson의 다른 사용방식을 위해 남겨둠
*/
std::ofstream FileWriter::getOfstream()
{
    std::ofstream ofs(file_path);
    if(!ofs.is_open()) throw std::runtime_error("Failed to open file.");

    return ofs;
}

/* writeFile()
용도 : File 스트림을 열고 내용을 로컬에 저장함
시퀀스 : 날짜 변경 혹은 프로그램 종료 시 TaskListManager의 task_list 내용을 jsonSerializer가 Serialize하고 여기서 만들어진 결과를 FileWriter가 로컬에 저장

고민 : 파일 쓰기 과정에서 예외 발생 시 대처 방법
*/
void FileWriter::writeFile(const std::string& context)
{
    // 파일이 저장될 경로에 맞는 폴더가 없다면 만들기
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
