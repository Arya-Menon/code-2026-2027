/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// Brain
brain Brain;

// Controller
controller Controller1;

// Competition
competition Competition;

// Motors
motor leftMotorA(PORT2, ratio18_1, false);
motor rightMotorA(PORT1, ratio18_1, true);

motor liftMotor(PORT5, ratio18_1, false);
motor clawMotor(PORT6, ratio18_1, false);

// Drive Groups
motor_group LeftDriveGroup(leftMotorA);
motor_group RightDriveGroup(rightMotorA);



// -----------------------------------------------------------------------------
// Pre-Autonomous
// -----------------------------------------------------------------------------
void pre_auton(void) {

  LeftDriveGroup.resetPosition();
  RightDriveGroup.resetPosition();
  liftMotor.resetPosition();
  clawMotor.resetPosition();



}

// Claw control helper
void clawControl() {
  clawMotor.setVelocity(40, percent);
  clawMotor.spinFor(forward, 500, degrees);
}

// -----------------------------------------------------------------------------
// Autonomous
// -----------------------------------------------------------------------------
void autonomous(void) {
 // Drive forward 18 inches
 LeftDriveGroup.setVelocity(40, percent);
 RightDriveGroup.setVelocity(40, percent);

  LeftDriveGroup.spinFor(reverse, 530, degrees, false);
  RightDriveGroup.spinFor(reverse, 530, degrees);

//  Turn right 90°
  LeftDriveGroup.setVelocity(40, percent);
  RightDriveGroup.setVelocity(40, percent);



  LeftDriveGroup.spinFor(reverse, 300, degrees, false);
  RightDriveGroup.spinFor(forward, 300, degrees);

// Drive forward 15 inches
  LeftDriveGroup.setVelocity(40, percent);
  RightDriveGroup.setVelocity(40, percent);

  LeftDriveGroup.spinFor(reverse, 550, degrees, false);
  RightDriveGroup.spinFor(reverse, 550, degrees);

  // Lift up
 liftMotor.setVelocity(40, percent);
 liftMotor.spinFor(reverse,1200, degrees);
//Position
  LeftDriveGroup.spinFor(reverse, 140, degrees, false);
  RightDriveGroup.spinFor(reverse, 140, degrees, false);
  wait(1, sec);
   liftMotor.setVelocity(40, percent);
 liftMotor.spinFor(forward,800, degrees);
  // Open claw
 clawControl();
}

// -----------------------------------------------------------------------------
// Driver Control
// -----------------------------------------------------------------------------
void usercontrol(void) {

}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
int main() {

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}