/* Task Schduler 자세한 구현
*
역할
1) 일정파일 생성 / 제거
2) 일정파일 내용변경(ui에서는 클릭하면 줄그어지게)
3) 프로그램 종료시 현재 일정대로 일정파일 갱신

주의사항
1) C++ 17이상 사용, 20이상 권장

*/
#include "Scheduler.h"

Scheduler::Scheduler() // 오늘 일정 관리할때
{
    getTodaysDate();
    setPath();

    createTaskfile();
    readTaskfile();
}

Scheduler::Scheduler(QString y, QString m, QString d) // 다른 특정 날짜 관리할때
{
    year = y; month = m; day = d;
    setPath();

    createTaskfile();
    readTaskfile();
}

Scheduler::~Scheduler() {};  // 현재 상태 파일에 새로 쓰는 내용 갱신하기


/////////////////////////////////////////////////////////////////////////

// 오늘 날짜 얻기
void Scheduler::getTodaysDate()
{
    Date d;
    d.getTodaysDate();

    this->year = d.year;
    if((d.month).toInt() < 10) this->month = '0' + d.month;
    else this->month = d.month;
    if((d.day).toInt() < 10) this->day = '0' + d.day;
    else this->day = d.day;
}

void Scheduler::setPath()
{
    path = "./Schedule/" + year + "/" + month + "/" + day + ".txt";
}

// 오늘의 일정 폴더 및 파일 생성
void Scheduler::createTaskfile()
{
    // 폴더 없으면 만들기
    if (!std::filesystem::exists("./Schedule/" + year.toStdString() + "/" + month.toStdString()))
        std::filesystem::create_directories("./Schedule/" + year.toStdString() + "/" + month.toStdString());

    // 파일 없으면 만들기
    if (!std::filesystem::exists(path.toStdString())) {
        std::filesystem::path from("./Schedule/const_data/everyday.txt");
        std::filesystem::path to(path.toStdString());
        std::filesystem::copy(from, to);
    }
    else { // 파일이 이미 있다면
        std::ifstream p(path.toStdString());
        char c;
        p.seekg(-1, std::ios::end);
        p.read(&c, 1);
        p.close();

        if (c != '#') { // 개별일정이 있고 && 오늘 처음 연 파일이라면
            std::ifstream in("./Schedule/const_data/everyday.txt");
            std::string s;

            // 개별일정이 있다는 뜻이므로 const.txt append해주기
            in.seekg(0, std::ios::end);
            int size = in.tellg();
            s.resize(size);
            in.seekg(0, std::ios::beg);
            in.read(&s[0], size);

            std::ofstream out(path.toStdString(), std::ios::app);
            out << '\n' << s << "\n#";
            // 이미 everday.txt를 붙여왓으니 또 붙일 필요 없으므로
        }
    }
}

void Scheduler::readTaskfile()
{
    std::ifstream file(path.toStdString());

    std::string line; // 한 줄단위로 읽기 위해
    std::string task; // 단어 하나
    while (std::getline(file, line)) {  // task 단위로 분리해서 QList로 넣어주기
        std::stringstream ss(line);// #단위로 분리
        QList<QString> temp;
        while(std::getline(ss, task, '#')) {
            task.erase(0, task.find_first_not_of(" "));
            task.erase(task.find_last_not_of(" ") + 1); // 제일 뒤나 앞에 공백 제거용

            temp.push_back(QString::fromStdString(task));
        }
        tasks.push_back(temp);
    }
}



//void Scheduler::removeTaskfile() {} // 일정파일/폴더 제거

