#include "main.h"
#include <iostream>

namespace autons
{

    void autonSkills()
    {
        arms::odom::reset({0, 0}, 180);
        arms::chassis::move({10, 0}, 100, 0.25, arms::REVERSE);
        ClampOut = true;
        setClampPiston(ClampOut);
        pros::delay(500);
        setIntake(127);
        pros::delay(200);
        arms::chassis::turn(-90);
        pros::delay(200);
        arms::chassis::move({11, -36});
        pros::delay(200);
        arms::chassis::turn(-45);
        pros::delay(200);
        arms::chassis::move({0, -48}, arms::REVERSE);
        ClampOut = false;
        setClampPiston(ClampOut);
        arms::chassis::move({0, 0, 0},100, .25);

    }
}