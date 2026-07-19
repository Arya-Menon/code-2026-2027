#include "vex.h"

using namespace vex;


brain Brain;
controller Controller1;


motor leftMotorA(PORT2, ratio18_1, false);


motor rightMotorA(PORT1, ratio18_1, true);



motor liftMotor(PORT5, ratio18_1, false);   
motor clawMotor(PORT6, ratio18_1, false);   


motor_group LeftDriveGroup(leftMotorA );
motor_group RightDriveGroup(rightMotorA);

int main() {

    LeftDriveGroup.setStopping(brake);
    RightDriveGroup.setStopping(brake);

    liftMotor.setStopping(hold);
    clawMotor.setStopping(hold);
    liftMotor.setMaxTorque(100, percentUnits::pct);

    while (true) {

        
        int forward = Controller1.Axis3.position(percent);
        int turn = Controller1.Axis4.position(percent);

        int leftPower = forward + turn;
        int rightPower = forward - turn;

        LeftDriveGroup.spin(directionType::fwd, leftPower, pct);
        RightDriveGroup.spin(directionType::fwd, rightPower, pct);

      
        if (Controller1.ButtonL1.pressing()) {
            liftMotor.spin(directionType::fwd, 100, pct);
        }
        else if (Controller1.ButtonL2.pressing()) {
            liftMotor.spin(directionType::rev, 100, pct);
        }
        else {
            liftMotor.stop(hold);
        }

       
        if (Controller1.ButtonR1.pressing()) {
            liftMotor.spin(directionType::fwd, 100, pct);
        }
        else if (Controller1.ButtonR2.pressing()) {
            liftMotor.spin(directionType::rev, 100, pct);
        }
        else {
            // Claw motor stopped
        }

        wait(20, msec);
    }
}