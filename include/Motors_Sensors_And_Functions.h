#include "main.h"

//This is our drive trian motors.
// 1=front left
// 2=back left
// 3=front right
// 4=back right
pros::Motor DT1(6, true);
pros::Motor DT2(7, true);
pros::Motor DT3(5);
pros::Motor DT4(4);
// These are the two intake motors
pros::Motor I1(1);
pros::Motor R1(8);
// These are our two fly-wheel motors
pros::Motor FW1(3);
pros::Motor FW2(2);
// These are the net releases on the four corners of our robot.They are in the same order as our drive train.
pros::ADIDigitalOut Net1(1);
pros::ADIDigitalOut Net2(2);
pros::ADIDigitalOut Net3(3);
pros::ADIDigitalOut Net4(4);

pros::ADIDigitalOut Trigger(5);

pros::Controller master(pros::E_CONTROLLER_MASTER);

void Turn (int Direction, int dist){
  DT1.move_relative((Direction*dist*600)/12.56, 100);
  DT2.move_relative((Direction*dist*600)/12.56, 100);
  DT3.move_relative((-Direction*dist*600)/12.56, 100);
  DT4.move_relative((-Direction*dist*600)/12.56, 100);
}

void DriveFWD (float dist){
  DT1.move_relative((dist*600)/12.56, 100);
  DT2.move_relative((dist*600)/12.56, 100);
  DT3.move_relative((dist*600)/12.56, 100);
  DT4.move_relative((dist*600)/12.56, 100);
}

void DriveSET (int dir){
  DT1.move_velocity(dir*100);
  DT2.move_velocity(dir*100);
  DT3.move_velocity(dir*100);
  DT4.move_velocity(dir*100);
}

void IntakeOnOff (int Power){
  I1.move_velocity(200*Power);
}

void FlyWheelOnOff (int Power){
  FW1.move_velocity(135*Power);
  FW2.move_velocity(135*Power);
}

void RollerToggle(){
  R1.move_relative((7.47*900)/12.56, 100);
};

void RPivot (int Direction, int dist){
  DT3.move_relative((-Direction*dist*600)/12.56, 100);
  DT4.move_relative((-Direction*dist*600)/12.56, 100);
}

void LPivot (int Direction, int dist){
  DT1.move_relative((Direction*dist*600)/12.56, 100);
  DT2.move_relative((Direction*dist*600)/12.56, 100);
}
