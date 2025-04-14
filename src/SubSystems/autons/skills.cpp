#include "main.h"
#include <iostream>

namespace autons
{

    void autonSkills()
    {
        arms::chassis::move({-10,0},100,0.25, arms::REVERSE);
        ClampOut=true;
        setClampPiston(ClampOut);
        pros::delay(500);
        setIntake(127);
    }
}