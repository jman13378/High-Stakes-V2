#include "main.h"
#include <iostream>
#include <sstream>
#include <string>
namespace autons
{

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
        setBlueHue();
        setIntake(127);
        pros::delay(500);
        setIntake(0);
        arms::odom::reset({0, 0}, 0); // Reset point

        arms::chassis::move({24, 0}, 100, 0.250);

    }

    void blueLeftStart()
    {
        blueRightStart();
    }
}