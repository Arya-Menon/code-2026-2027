/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       arya-home                                                 */
/*    Created:      7/7/2026, 1:38:16 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define controller
vex::controller  Controller1 = vex::controller(vex::controllerType::primary);

// define your global instances of motors and other devices here
vex::motor leftMotorA = vex::motor(PORT2, ratio18_1, false);
vex::motor leftMotorB = vex::motor(PORT4, ratio18_1, false);
vex::motor leftMotorC = vex::motor(PORT5, ratio18_1, false);

vex::motor rightMotorA = vex::motor(PORT1, ratio18_1, true);
vex::motor rightMotorB = vex::motor(PORT3, ratio18_1, true);
vex::motor rightMotorC = vex::motor(PORT6, ratio18_1, true);

vex::motor liftMotorA = vex::motor(PORT9, ratio18_1, false);
// Reverse the second lift motor if the two motors are mounted in opposite directions
vex::motor liftMotorB = vex::motor(PORT8, ratio18_1, true);

vex::motor_group LeftDriveGroup = vex::motor_group(leftMotorA, leftMotorB, leftMotorC);
vex::motor_group RightDriveGroup = vex::motor_group(rightMotorA, rightMotorB, rightMotorC);
vex::motor_group LiftGroup = vex::motor_group(liftMotorA, liftMotorB);

int main() {
    LeftDriveGroup.setStopping(brake);
    RightDriveGroup.setStopping(brake);
    LiftGroup.setStopping(brake);

    while (1) {
        int forward_power = Controller1.Axis3.position(percent);
        int turn_power = Controller1.Axis4.position(percent);
        int leftPower = forward_power + turn_power;
        int rightPower = forward_power - turn_power;

        LeftDriveGroup.spin(forward, leftPower, percent);
        RightDriveGroup.spin(forward, rightPower, percent);

        if (Controller1.ButtonR1.pressing()) {
            LiftGroup.spin(forward, 100, percent);
        } else if (Controller1.ButtonR2.pressing()) {
            LiftGroup.spin(reverse, 100, percent);
        } else {
            LiftGroup.stop(brake);
        }

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
