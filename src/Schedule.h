#pragma once

#include <QString>
#include <QList>
#include "JsonManager.h"
using namespace rapidjson;

class Schedule
{
private:
    QList<QList<QString>> schedule_list;

public:
    Schedule() = default;
    void MakeScheduleList(Document& document);
};
