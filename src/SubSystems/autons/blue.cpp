#include "main.h"
#include <iostream>
#include <sstream>
#include <string>
namespace autons
{
    double cTI(int tiles)
    {
        return 24 * tiles;
    }
    void setBlueHue()
    {
        int i = 1;
        if (hueRange[1][0] == 145769)
            i = 2;
        hueRange[i][0] = 215;
        hueRange[i][1] = 150;
    }

    void blueRightStart()
    {

        arms::odom::reset({0, 0}, 0); // Reset point
        arms::chassis::move({24,0},100,0.25);
        // arms::chassis::move({-44, 0}, 100, 0.250, arms::REVERSE);
        // pros::delay(500);
        // ClampOut = true;
        // setClampPiston(ClampOut);
        // pros::delay(500);
        // setIntake(127);
        // pros::delay(500);
        // setIntake(0);
        // arms::chassis::move({-38, -29, 0}, 100, 0.25, arms::REVERSE);

    }

    void blueLeftStart()
    {
        blueRightStart();
    }
}