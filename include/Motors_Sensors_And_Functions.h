#include "main.h"

//This is our drive trian motors.
// 1=front left
// 2=back left
// 3=front right
// 4=back right
pros::Motor DT1(1, true);
pros::Motor DT2(2, true);
pros::Motor DT3(3);
pros::Motor DT4(4);
// These are the two intake motors
pros::Motor I1(5);
pros::Motor I2(6);
// These are our two fly-wheel motors
pros::Motor FW1(7);
pros::Motor FW2(8);
// These are the net releases on the four corners of our robot.They are in the same order as our drive train.
pros::ADIDigitalOut Net1(1);
pros::ADIDigitalOut Net2(2);
pros::ADIDigitalOut Net3(3);
pros::ADIDigitalOut Net4(4);
pros::Controller master(pros::E_CONTROLLER_MASTER);
