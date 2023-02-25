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
pros::ADIDigitalOut Net2(2, false);
pros::ADIDigitalOut Net3(3, false);
pros::ADIDigitalOut Net4(4);

pros::ADIDigitalOut Trigger(5);

pros::Controller master(pros::E_CONTROLLER_MASTER);

//Drive base is 17.5 inches 8.75 to center in both width and length
//GPS 6.25 from center length and 1.75 from center width
//from blue drive box positve x is toward me and positive y is right of me


pros::Gps GPS1(11);
pros::c::gps_status_s_t status;


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
  DT1.move_relative((Direction*dist*600)/12.56, 50);
  DT2.move_relative((Direction*dist*600)/12.56, 50);
  DT3.move_relative((-Direction*dist*600)/12.56, 50);
  DT4.move_relative((-Direction*dist*600)/12.56, 50);
}

void DriveFWD (float dist){
  DT1.move_relative((dist*600)/12.56, 200);
  DT2.move_relative((dist*600)/12.56, 200);
  DT3.move_relative((dist*600)/12.56, 200);
  DT4.move_relative((dist*600)/12.56, 200);
}

void DriveFWDM (float dist){
  DT1.move_relative((dist*600)/12.56, 50);
  DT2.move_relative((dist*600)/12.56, 50);
  DT3.move_relative((dist*600)/12.56, 50);
  DT4.move_relative((dist*600)/12.56, 50);
}

void DriveFWDSlow (float dist){
  DT1.move_relative((dist*600)/12.56, 25);
  DT2.move_relative((dist*600)/12.56, 25);
  DT3.move_relative((dist*600)/12.56, 25);
  DT4.move_relative((dist*600)/12.56, 25);
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
  pros::delay(100);
  R1.move_relative(-(7.47/12.56)*300, 100);
  R2.move_relative(-(7.47/12.56)*300, 100);
  pros::delay(180);
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
  WaitTillStopDriveBase();
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
  DT1.move_relative((Direction*dist*600)/12.56, 50);
  DT2.move_relative((Direction*dist*600)/12.56, 50);
}

void LPivot (int Direction, float dist){
  DT3.move_relative((Direction*dist*600)/12.56, 50);
  DT4.move_relative((Direction*dist*600)/12.56, 50);
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

void DriveToX(float TrgX, float TrgY){
  DT1.move_velocity(100);
  DT2.move_velocity(100);
  DT3.move_velocity(100);
  DT4.move_velocity(100);
  pros::delay(100);
  status = GPS1.get_status();
  while (status.x > TrgX+0.1 || status.x < TrgX-0.1){
    DT1.move_velocity(100);
    DT2.move_velocity(100);
    DT3.move_velocity(100);
    DT4.move_velocity(100);
    status = GPS1.get_status();
    if (status.y > TrgY){
      DT1.move_velocity(100);
      DT2.move_velocity(100);
      DT3.move_velocity(50);
      DT4.move_velocity(50);
      status = GPS1.get_status();
    }
    else if (status.y < TrgY){
      DT1.move_velocity(50);
      DT2.move_velocity(50);
      DT3.move_velocity(100);
      DT4.move_velocity(100);
      status = GPS1.get_status();
    }
    else {
      DT1.move_velocity(100);
      DT2.move_velocity(100);
      DT3.move_velocity(100);
      DT4.move_velocity(100);
      status = GPS1.get_status();
    }
  }
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
}

void DriveToQ1(float TrgX, float TrgY){
  float DisToX;
  float DisToY;
  float TrgHeading;
  float Heading;
  int Timer;
  status = GPS1.get_status();
  DisToX = status.x - TrgX;
  DisToY = status.y - TrgY;
  TrgHeading = 35 + (atan(DisToX/DisToY)*(180/M_PI));
  if (TrgHeading < 0){
    TrgHeading = TrgHeading + 360;
  }
  master.print(1, 1, "TrgHeading: %f", TrgHeading);
  Heading = GPS1.get_heading();
  while (Heading > TrgHeading+.25 || Heading < TrgHeading-.25){
    DT1.move_velocity(25);
    DT2.move_velocity(25);
    DT3.move_velocity(-25);
    DT4.move_velocity(-25);
    Heading = GPS1.get_heading();
    master.print(2, 1, "CrntHeading: %f", Heading);
  }
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
  status = GPS1.get_status();
  while (status.x > TrgX+0.1 || status.x < TrgX-0.1 || status.y > TrgY+0.1 || status.y < TrgY-0.1){
    DT1.move_velocity(25);
    DT2.move_velocity(25);
    DT3.move_velocity(25);
    DT4.move_velocity(25);
    status = GPS1.get_status();
  }
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
}

void DriveBackToQ1(float TrgX, float TrgY){
  float DisToX;
  float DisToY;
  float TrgHeading;
  float Heading;
  int Timer;
  status = GPS1.get_status();
  DisToX = status.x - TrgX;
  DisToY = status.y - TrgY;
  TrgHeading = 35 + (atan(DisToX/DisToY)*(180/M_PI));
  if (TrgHeading < 0){
    TrgHeading = TrgHeading + 360;
  }
  master.print(1, 1, "TrgHeading: %f", TrgHeading);
  Heading = GPS1.get_heading();
  while (Heading > TrgHeading+.25 || Heading < TrgHeading-.25){
    DT1.move_velocity(25);
    DT2.move_velocity(25);
    DT3.move_velocity(-25);
    DT4.move_velocity(-25);
    Heading = GPS1.get_heading();
    master.print(2, 1, "CrntHeading: %f", Heading);
  }
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
  status = GPS1.get_status();
  while (status.x > TrgX+0.1 || status.x < TrgX-0.1 || status.y > TrgY+0.1 || status.y < TrgY-0.1){
    R1.move_velocity(200);
    R1.move_velocity(200);
    DT1.move_velocity(-25);
    DT2.move_velocity(-25);
    DT3.move_velocity(-25);
    DT4.move_velocity(-25);
    status = GPS1.get_status();
  }
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
}


void DriveTo(bool Dir, float TrgX, float TrgY){
  //What do these variables do?
  float Heading;
  float LegX;
  float LegY;
  float CrntHeading;
  bool TDir;
  float TempHeading;
  float TrgError = .01;
  master.clear();
  status = GPS1.get_status();
  CrntHeading = GPS1.get_heading();
  LegX = (TrgX-status.x);
  LegY = (TrgY-status.y);
  if (TrgX > status.x && TrgY > status.y){
    //What does this return?
    //___________________________
    //|            |_|   /      |
    //|            |   /        |
    //|            | /          |
    //|------------+------------|
    //|            |            |
    //|            |            |
    //|____________|____________|

    Heading = (atan(LegX/LegY))*(180/M_PI);
    if (Dir == false){
      Heading = Heading + 180;
    }
  }
  else if (TrgX < status.x && TrgY > status.y){
    //What does this return?
    Heading = 270+((atan(LegY/LegX))*(180/M_PI));
    if (Dir == false){
      Heading = Heading - 180;
    }
  }
  else if (TrgX < status.x && TrgY < status.y){
    //What does this return?
    Heading = 180+((atan(LegX/LegY))*(180/M_PI));
    if (Dir == false){
      Heading = Heading - 180;
    }
  }
  else if (TrgX > status.x && TrgY < status.y){
    //What does this return?
    Heading = 90+((atan(LegY/LegX))*(180/M_PI));
    if (Dir == false){
      Heading = Heading + 180;
    }
  }
  TempHeading = Heading-CrntHeading;
  //What is the while loop checking for?
master.print(2, 1, "Cheading: %f", Heading);
  while (CrntHeading > Heading+2 || CrntHeading < Heading-2){
    if (fabsf(TempHeading)<180){
      if (CrntHeading > Heading+60 || CrntHeading < Heading-60){
        DT1.move_velocity(100);
        DT2.move_velocity(100);
        DT3.move_velocity(-100);
        DT4.move_velocity(-100);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
      else if (CrntHeading > Heading+30 || CrntHeading < Heading-30){
        DT1.move_velocity(75);
        DT2.move_velocity(75);
        DT3.move_velocity(-75);
        DT4.move_velocity(-75);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
      else if (CrntHeading > Heading+10 || CrntHeading < Heading-10){
        DT1.move_velocity(50);
        DT2.move_velocity(50);
        DT3.move_velocity(-50);
        DT4.move_velocity(-50);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
      else {
        DT1.move_velocity(25);
        DT2.move_velocity(25);
        DT3.move_velocity(-25);
        DT4.move_velocity(-25);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
    }
    else if (fabsf(TempHeading)>180) {
      if (CrntHeading > Heading+60 || CrntHeading < Heading-60){
        DT1.move_velocity(-100);
        DT2.move_velocity(-100);
        DT3.move_velocity(100);
        DT4.move_velocity(100);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
      else if (CrntHeading > Heading+30 || CrntHeading < Heading-30){
        DT1.move_velocity(-75);
        DT2.move_velocity(-75);
        DT3.move_velocity(75);
        DT4.move_velocity(75);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
      else if (CrntHeading > Heading+10 || CrntHeading < Heading-10){
        DT1.move_velocity(-50);
        DT2.move_velocity(-50);
        DT3.move_velocity(50);
        DT4.move_velocity(50);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
      else {
        DT1.move_velocity(-25);
        DT2.move_velocity(-25);
        DT3.move_velocity(25);
        DT4.move_velocity(25);
        //master.print(2, 1, "heading: %f", CrntHeading);
        CrntHeading = GPS1.get_heading();
      }
    }
    pros::delay(20);
  }
  while ((status.x > TrgX+TrgError || status.x < TrgX-TrgError) && (status.y > TrgY+TrgError || status.y < TrgY-TrgError)){
    //What is this if statement doing? What is this layer of if statement's conditional?
    //what is the else statement and the if statements inside of it doing?
      if (Dir == true){
        if (CrntHeading > Heading+.5){
          DT1.move_velocity(75);
          DT2.move_velocity(75);
          DT3.move_velocity(100);
          DT4.move_velocity(100);
        }
        else if (CrntHeading < Heading-.5){
          DT1.move_velocity(100);
          DT2.move_velocity(100);
          DT3.move_velocity(75);
          DT4.move_velocity(75);
        }
        else {
          DT1.move_velocity(100);
          DT2.move_velocity(100);
          DT3.move_velocity(100);
          DT4.move_velocity(100);
        }
      }
      else if (Dir == false){
        if (CrntHeading > Heading+.5){
          DT1.move_velocity(-75);
          DT2.move_velocity(-75);
          DT3.move_velocity(-100);
          DT4.move_velocity(-100);
        }
        else if (CrntHeading < Heading-.5){
          DT1.move_velocity(-100);
          DT2.move_velocity(-100);
          DT3.move_velocity(-75);
          DT4.move_velocity(-75);
        }
        else {
          DT1.move_velocity(-100);
          DT2.move_velocity(-100);
          DT3.move_velocity(-100);
          DT4.move_velocity(-100);
        }
      }
    CrntHeading = GPS1.get_heading();
    status = GPS1.get_status();
    pros::delay(20);
  }
  DT1.move_velocity(0);
  DT2.move_velocity(0);
  DT3.move_velocity(0);
  DT4.move_velocity(0);
}
