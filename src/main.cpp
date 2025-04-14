#include "main.h"
#include "ARMS/config.h"
#include "ui.h"
#include <map>
#include <cmath>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
std::chrono::_V2::steady_clock::time_point start_time = std::chrono::steady_clock::now();
std::chrono::_V2::steady_clock::time_point auton_time;
std::chrono::_V2::steady_clock::time_point drive_time;

bool debug = false;
void initialize()
{
    // pros::Task Flywheelcontrol(FlyWheelControlTask);

    // pros::Task CataController(cataControl);
    std::cout << "Pre Initialize" << std::endl;
    arms::init();
    arms::selector::destroy();
    //selector::init(-2); // auton
    selector::init(0); // auton

    // while ((*arms::odom::imu).is_calibrating())
    // {
    //     pros::delay(10);
    // }
    std::cout << "Post Initialize" << std::endl;
}

void runDebug()
{
    std::cout << "Running Debug" << std::endl;

    while (true)
    {
        if (controller.get_digital_new_press(controls::clampPiston))
        {
            std::cout << "x: " << arms::odom::getPosition().x << "\ny: " << arms::odom::getPosition().y << std::endl;
        }
    }
}
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void autonomous()
{
    std::cout << "Pre Autonomous" << std::endl;

    IntakeOut = true;

    selector::shutdown();
    selector::runauton();
    std::cout << "Post Autonomous" << std::endl;

    //  selector::runauton();

    // if (au)
    //   arms::odom::reset({0, 0}, 0);
    // au=false;
    // chassis::move({24, 0,0}, 100);
}
void task()
{
    // Get temperatures of motors
    double LFT = (*arms::chassis::leftMotors)[0].get_temperature();
    double LMT = (*arms::chassis::leftMotors)[1].get_temperature();
    double LBT = (*arms::chassis::leftMotors)[2].get_temperature();
    double RFT = (*arms::chassis::rightMotors)[0].get_temperature();
    double RMT = (*arms::chassis::rightMotors)[1].get_temperature();
    double RBT = (*arms::chassis::rightMotors)[2].get_temperature();

    // Calculate average temperature
    int temp = std::round((LFT + LMT + LBT + RFT + RMT + RBT) / 6);

    // End time: calculate it when you need to measure the elapsed time
    auto end_time = std::chrono::steady_clock::now();

    // Calculate the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - drive_time);

    // Convert to seconds and milliseconds
    int seconds = duration.count() / 1000;      // Total seconds
    int milliseconds = duration.count() % 1000; // Remaining milliseconds

    // Calculate elapsed minutes and seconds
    int elapsed_minutes = seconds / 60;
    seconds %= 60;

    // Print the total duration in milliseconds (for debugging purposes)

    // Print the Drive Direction
    controller.print(0, 0, "Drive Dir: %s", (DriveReverse ? "Reverse" : "Forward"));
    pros::delay(50);

    // Print the Mode
    controller.print(1, 0, "Mode: %s", (tankswitch ? "Tank" : "Arcade"));
    pros::delay(50);

    // Format the elapsed time in MM:SS format with leading zeros
    std::ostringstream time_stream;
    time_stream << std::setw(2) << std::setfill('0') << elapsed_minutes << ":"
                << std::setw(2) << std::setfill('0') << seconds;

    // Print the formatted temperature and elapsed time
    controller.print(2, 0, "Temp: %s, %s", std::to_string(temp).c_str(), time_stream.str().c_str());
}
void opcontrol()
{
    drive_time = std::chrono::steady_clock::now();
    std::cout << "Pre Driver Control" << std::endl;

    IntakeOut = true;

    if (debug)
    {
        runDebug();
    }
    arms::odom::reset({0, 0}, 0);
    // arms::chassis::move({0, 0, 0}, 100, 0.25);
    arms::chassis::setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    while (true)
    {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
        {
            std::cout << "x: " << arms::odom::getPosition().x << "\ny: " << arms::odom::getPosition().y << std::endl;
        }

        pros::Task DriveInfo(task);
        setDriveMotors();
        setIntakeMotor();
        setPistonStates();
        pros::delay(10);
    }
    std::cout << "Post Driver Control" << std::endl;
}
