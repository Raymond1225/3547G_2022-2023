#include "main.h"

//This is our drive trian motors.
// 1=front left
// 2=back left
// 3=front right
// 4=back right
pros::Motor DT1(6);
pros::Motor DT2(7);
pros::Motor DT3(10, true);
pros::Motor DT4(4, true);
// These are the two intake motors
pros::Motor R2(5, true);
pros::Motor R1(8);
// These are our two fly-wheel motors
pros::Motor FW1(3, true);
pros::Motor FW2(1, true);

pros::Motor C1(20);
// These are the net releases on the four corners of our robot.They are in the same order as our drive train.
pros::ADIDigitalOut Net1(1);
pros::ADIDigitalOut Net2(2);
pros::ADIDigitalOut Net3(3);
pros::ADIDigitalOut Net4(4);

pros::ADIDigitalOut Trigger(5);

pros::Controller master(pros::E_CONTROLLER_MASTER);

void WaitTillStopDriveBase() {
  int Volts;
  pros::delay(150);
  master.print(2, 0, "PlaceHolder: %i", 1);
  Volts = DT1.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(10);
    Volts = DT1.get_actual_velocity();
  }
}

void Turn (int Direction, float dist){
  DT1.move_relative((Direction*dist*600)/12.56, 100);
  DT2.move_relative((Direction*dist*600)/12.56, 100);
  DT3.move_relative((-Direction*dist*600)/12.56, 100);
  DT4.move_relative((-Direction*dist*600)/12.56, 100);
}

void DriveFWD (float dist){
  DT1.move_relative((dist*600)/12.56, 200);
  DT2.move_relative((dist*600)/12.56, 200);
  DT3.move_relative((dist*600)/12.56, 200);
  DT4.move_relative((dist*600)/12.56, 200);
}

void DriveFWDSlow (float dist){
  DT1.move_relative((dist*600)/12.56, 50);
  DT2.move_relative((dist*600)/12.56, 50);
  DT3.move_relative((dist*600)/12.56, 50);
  DT4.move_relative((dist*600)/12.56, 50);
}

void DriveSET (int dir){
  DT1.move_velocity(dir*100);
  DT2.move_velocity(dir*100);
  DT3.move_velocity(dir*100);
  DT4.move_velocity(dir*100);
}

void IntakeOnOff (int Power){
  R1.move_velocity(Power);
  R2.move_velocity(Power);
}

void FlyWheelOnOff (float Power){
  FW1.move_velocity(Power);
  FW2.move_velocity(Power);
  while(FW1.get_actual_velocity() < Power){
    FW1.move_velocity(Power);
    FW2.move_velocity(Power);
  }
  FW1.move_velocity(0);
  FW2.move_velocity(0);
  FW1.move_voltage((Power/154)*12000);
  FW2.move_voltage((Power/154)*12000);
}

void FlyWheelOnOffS (float Power){
  FW1.move_velocity(Power);
  FW2.move_velocity(Power);
}

void Unload (){
  Net1.set_value(true);
  pros::delay(100);
  Net1.set_value(false);
  pros::delay(850);
  Net1.set_value(true);
  pros::delay(100);
  Net1.set_value(false);
  pros::delay(850);
  Net1.set_value(true);
  pros::delay(100);
  Net1.set_value(false);
}

void RollerToggle(){
  DT1.move_velocity(-100);
  DT2.move_velocity(-100);
  DT3.move_velocity(-100);
  DT4.move_velocity(-100);
  pros::delay(1000);
  R1.move_relative(-(7.47/12.56)*300, 100);
  R2.move_relative(-(7.47/12.56)*300, 100);
  pros::delay(180);
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
}

void SkillsRollerToggle(){
  DT1.move_velocity(-100);
  DT2.move_velocity(-100);
  DT3.move_velocity(-100);
  DT4.move_velocity(-100);
  pros::delay(200);
  R1.move_relative((7.47/12.56)*600, 100);
  R2.move_relative((7.47/12.56)*600, 100);
  pros::delay(180);
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
};

void RPivot (int Direction, float dist){
  DT1.move_relative((-Direction*dist*600)/12.56, 100);
  DT2.move_relative((-Direction*dist*600)/12.56, 100);
}

void LPivot (int Direction, float dist){
  DT3.move_relative((Direction*dist*600)/12.56, 100);
  DT4.move_relative((Direction*dist*600)/12.56, 100);
}

void SkRT1 (){
  DT1.move_relative((2*600)/12.56, 100);
  DT2.move_relative((2*600)/12.56, 100);
  DT3.move_relative((2*600)/12.56, 100);
  DT4.move_relative((2*600)/12.56, 100);
  R1.move_relative(-(7.47/12.56)*600, 100);

}

void Expansion (){
  Net2.set_value(true);
  Net3.set_value(true);
}
