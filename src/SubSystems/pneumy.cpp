#include "main.h"
#include "pros/misc.h"
#include <iostream>
#include <sstream>
#include <string>

void setClampPiston(bool trigger)
{
    ClampPiston.set_value(trigger);
}
void setIntakePiston(bool trigger)
{
    IntakePiston.set_value(trigger);
    IntakePiston2.set_value(trigger);

}
void setPistonStates()
{
    if (controller.get_digital_new_press(controls::clampPiston))
    {
        ClampOut = ClampOut ? false : true;
    }




    setClampPiston(ClampOut);
    setIntakePiston(IntakeOut)
}