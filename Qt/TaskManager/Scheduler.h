/* Task Schduler 자세한 구현
 *
역할
1) 일정파일 생성 / 제거
2) 일정파일 내용변경(ui에서는 클릭하면 줄그어지게)
3) 프로그램 종료시 현재 일정대로 일정파일 갱신

주의사항
1) C++ 17이상 사용, 20이상 권장

구현방식
1) 오늘 할 일정들은 # 단위로 구성
  ex) #오늘할일1-1 #오늘할일1-2
      #오늘할일2-1
2) 어제 다 마무리 못하고 남겨둔 일은 #@로 구분
  ex) #@어제 남은일1-1

*/
#pragma once

#include "Date.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <QList>
#include <QString>
#include <QObject>

//
#include <QDebug>

class Scheduler : public QObject
{
    Q_OBJECT

private:
    QString year, month, day, dayOfWeek; // 관리중인 날짜
    QString path; // 해당 날짜의 일정 파일 경로
    QList<QList<QString>> tasks; // 할일들 목록

    void getTodaysDate(); // 오늘 날짜 얻기
    void setPath(); // 파일 경로 설정

    // 파일 관리 함수들
    void createTaskfile(); // 오늘의 일정 폴더 및 파일 생성
    void appendDayOfWeekTaskfile();
    void appendYesterDayTaskfile();
    void readTaskfile();
    void updateTaskfile();
    //void removeTaskfile(); // 일정파일/폴더 제거

public:
    Scheduler();
    Scheduler(QString, QString, QString);
    ~Scheduler();  // 현재 상태 파일에 새로 쓰는 내용 갱신하기

    Q_INVOKABLE void addTask(QString);
    Q_INVOKABLE void removeTask(qint32, qint32);
    Q_INVOKABLE QList<QList<QString>> getTaskList();

signals:
    void tasksChanged();
};
