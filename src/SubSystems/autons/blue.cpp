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

    }

    void blueLeftStart()
    {
        blueRightStart();
    }
}