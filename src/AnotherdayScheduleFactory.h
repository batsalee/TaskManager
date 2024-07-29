#pragma once

#include "ScheduleFactory.h"

class AnotherdayScheduleFactory : public ScheduleFactory
{
public:
    Date& getDate() override;
};
