#pragma once

#include "ScheduleFactory.h"

class TodayScheduleFactory : public ScheduleFactory
{
public:
    Date& getDate() override;
};
