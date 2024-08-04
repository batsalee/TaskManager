#include "FileWriter.h"

/* writeFile()
용도 : File 스트림을 열고 내용을 로컬에 저장함
시퀀스 : 종료시점에 Schedule객체의 task_list내용을 jsonManager가 Serializing하고
        파싱된 내용을 FileWriter의 writeFile 객체를 통해 로컬에 저장
*/

void FileWriter::writeFile(std::string& context)
{
    std::ofstream out(file_path);
    out << context;
}

