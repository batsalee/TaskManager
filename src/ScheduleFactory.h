#pragma once

#include <iostream>
#include <memory>
#include "Schedule.h"
#include "Date.h"
#include "FileReader.h"
#include "JsonManager.h"
using namespace rapidjson;

class ScheduleFactory
{
public:
    std::unique_ptr<Schedule> makeSchedule();
    virtual Date& getDate() = 0;

    virtual ~ScheduleFactory() {};
};
