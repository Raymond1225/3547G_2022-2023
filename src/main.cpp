#include "main.h"
#include "Motors_Sensors_And_Functions.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
int AutonSelect = 4;
void Center_Button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		AutonSelect = 0;
		pros::lcd::set_text(2, "No Auton Selected");
	}
}
void Left_Button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed && AutonSelect > 1) {
		AutonSelect --;
		if (AutonSelect == 0){
			pros::lcd::set_text(2, "No Auton Selected");
		}
		else if (AutonSelect == 1){
			pros::lcd::set_text(2, "Roller + Roller Shot");
		}
		else if (AutonSelect == 2){
			pros::lcd::set_text(2, "Roller + Center Shot");
		}
		else if (AutonSelect == 3){
			pros::lcd::set_text(2, "Skills");
		}
		else if (AutonSelect == 4){
			pros::lcd::set_text(2, "Skills 2");
		}
	}
	else if (pressed && AutonSelect == 1) {
		AutonSelect = 4;
		if (AutonSelect == 0){
			pros::lcd::set_text(2, "No Auton Selected");
		}
		else if (AutonSelect == 1){
			pros::lcd::set_text(2, "Roller + Roller Shot");
		}
		else if (AutonSelect == 2){
			pros::lcd::set_text(2, "Roller + Center Shot");
		}
		else if (AutonSelect == 3){
			pros::lcd::set_text(2, "Skills");
		}
		else if (AutonSelect == 4){
			pros::lcd::set_text(2, "Skills 2");
		}
	}

}
void Right_Button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed && AutonSelect < 4) {
		AutonSelect ++;
		if (AutonSelect == 0){
			pros::lcd::set_text(2, "No Auton Selected");
		}
		else if (AutonSelect == 1){
			pros::lcd::set_text(2, "Roller + Roller Shot");
		}
		else if (AutonSelect == 2){
			pros::lcd::set_text(2, "Roller + Center Shot");
		}
		else if (AutonSelect == 3){
			pros::lcd::set_text(2, "Skills");
		}
		else if (AutonSelect == 4){
			pros::lcd::set_text(2, "Skills 2");
		}
	}
	else if (pressed && AutonSelect == 4) {
		AutonSelect = 1;
		if (AutonSelect == 0){
			pros::lcd::set_text(2, "No Auton Selected");
		}
		else if (AutonSelect == 1){
			pros::lcd::set_text(2, "Roller + Roller Shot");
		}
		else if (AutonSelect == 2){
			pros::lcd::set_text(2, "Roller + Center Shot");
		}
		else if (AutonSelect == 3){
			pros::lcd::set_text(2, "Skills");
		}
		else if (AutonSelect == 4){
			pros::lcd::set_text(2, "Skills 2");
		}
	}

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Please Select Your Auton");

	pros::lcd::register_btn1_cb(Center_Button);
	pros::lcd::register_btn2_cb(Right_Button);
	pros::lcd::register_btn0_cb(Left_Button);
	if (AutonSelect == 0){
			pros::lcd::set_text(2, "No Auton Selected");
		}
		else if (AutonSelect == 1){
			pros::lcd::set_text(2, "Roller + Roller Shot");
		}
		else if (AutonSelect == 2){
			pros::lcd::set_text(2, "Roller + Center Shot");
		}
		else if (AutonSelect == 3){
			pros::lcd::set_text(2, "Skills");
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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

	if (AutonSelect == 1){
		//roller shot
		RollerToggle();
		WaitTillStopDriveBase();
		RPivot(-1, 5.30);
		WaitTillStopDriveBase();
		FlyWheelOnOff(117);
		Unload();
	}
	else if (AutonSelect == 2){
		//Center shot
		RollerToggle();
		Turn(-1, 45);
		DriveFWD(-84.85);
		Turn(1, 45);
		FlyWheelOnOff(1);
		pros::delay(1000);
		Unload();
		FlyWheelOnOff(0);
	}
	else if (AutonSelect == 3){
		DT1.set_brake_mode(MOTOR_BRAKE_HOLD);
		DT2.set_brake_mode(MOTOR_BRAKE_HOLD);
		DT3.set_brake_mode(MOTOR_BRAKE_HOLD);
		DT4.set_brake_mode(MOTOR_BRAKE_HOLD);
		R1.set_brake_mode(MOTOR_BRAKE_BRAKE);
		R2.set_brake_mode(MOTOR_BRAKE_BRAKE);
		FW1.set_brake_mode(MOTOR_BRAKE_COAST);
		FW2.set_brake_mode(MOTOR_BRAKE_COAST);
		C1.set_brake_mode(MOTOR_BRAKE_BRAKE);
		//skills
		//pickup one, shoot three
		Turn(1, 6.5);
		FlyWheelOnOffS(115);
		IntakeOnOff(200);
		WaitTillStopDriveBase();
		DriveFWDSlow(-12);
		WaitTillStopDriveBase();
		Turn(1, 5.5);
		WaitTillStopDriveBase();
		pros::delay(1000);
		Unload();
		//one rollers
		pros::delay(60000);
		Turn(-1, 2);
		WaitTillStopDriveBase();
		DriveFWD(-10);
		WaitTillStopDriveBase();
		SkillsRollerToggle();
		WaitTillStopDriveBase();
		//shoot triple stack
		pros::delay(60000);
		//shoot three in a row
		pros::delay(60000);
		//shoot triple stack
		pros::delay(60000);
		//shoot triple stack
		pros::delay(60000);
		//pick up disk three disks
		pros::delay(60000);
		//flip rollers and shoot three
		pros::delay(60000);
		//pick up three in a row and shoot
		pros::delay(60000);
		//pick up three in a row shoot
		pros::delay(60000);
		//pick up triple stack shoot
		pros::delay(60000);
	}
	else if (AutonSelect == 4){
		Net2.set_value(true);
		Net3.set_value(true);
		DT1.set_brake_mode(MOTOR_BRAKE_BRAKE);
		DT2.set_brake_mode(MOTOR_BRAKE_BRAKE);
		DT3.set_brake_mode(MOTOR_BRAKE_BRAKE);
		DT4.set_brake_mode(MOTOR_BRAKE_BRAKE);
		R1.set_brake_mode(MOTOR_BRAKE_BRAKE);
		R2.set_brake_mode(MOTOR_BRAKE_BRAKE);
		FW1.set_brake_mode(MOTOR_BRAKE_COAST);
		FW2.set_brake_mode(MOTOR_BRAKE_COAST);
		C1.set_brake_mode(MOTOR_BRAKE_BRAKE);
		DriveFWD(-3);
		WaitTillStopDriveBase();
		SkillsRollerToggle();
		WaitTillStopDriveBase();
		DriveFWDSlow(24);
		WaitTillStopDriveBase();
		Turn(-1, 12);
		WaitTillStopDriveBase();
		DriveFWDSlow(-28);
		WaitTillStopDriveBase();
		SkillsRollerToggle();
		WaitTillStopDriveBase();
		DriveFWDSlow(28);
		WaitTillStopDriveBase();
		Turn(1, 5.1);
		WaitTillStopDriveBase();
		DriveFWDSlow(200);
		WaitTillStopDriveBase();
		DriveFWDSlow(-32.25);
		WaitTillStopDriveBase();
		Turn(-1, 20);
		WaitTillStopDriveBase();
		DriveFWDSlow(-28);
	//	IntakeOnOff(200);
		WaitTillStopDriveBase();
		//IntakeOnOff(0);
		SkillsRollerToggle();
		WaitTillStopDriveBase();
		DriveFWDSlow(24);
		WaitTillStopDriveBase();
		Turn(-1, 12);
		WaitTillStopDriveBase();
		DriveFWDSlow(-24);
		//IntakeOnOff(200);
		WaitTillStopDriveBase();
	//	IntakeOnOff(0);
		SkillsRollerToggle();
		WaitTillStopDriveBase();
		DriveFWDSlow(14);
		WaitTillStopDriveBase();
		Turn(1, 12);
		WaitTillStopDriveBase();
		DriveFWDSlow(-10);
		WaitTillStopDriveBase();
		Turn(-1, 6);
		WaitTillStopDriveBase();
		Expansion();
	}
	else {

	}
	/**
	FlyWheelOnOff(1);
 	pros::delay(2000);
	IntakeOnOff(1);
	pros::delay(2000);
	IntakeOnOff(0);
	Turn(1,90);
	IntakeOnOff(1);
	DriveFWD(-24);
	IntakeOnOff(0);
	Turn(1,45);
	IntakeOnOff(1);
	DriveFWD(-12);
	IntakeOnOff(0);
	Turn(1,90);
	IntakeOnOff(1);
	pros::delay(2000);
	IntakeOnOff(0);
	Turn(-1,90);
	DriveFWD(40);
	RollerToggle();
	*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int JSL;
	int JSR;
	int NM = 0;
	int FWM;
	int FWP;
	int FWAS;
	int FWTS;
	int FW1S;
	int FW2S;
	int Roller1 = 0;
	DT1.set_brake_mode(MOTOR_BRAKE_HOLD);
	DT2.set_brake_mode(MOTOR_BRAKE_HOLD);
	DT3.set_brake_mode(MOTOR_BRAKE_HOLD);
	DT4.set_brake_mode(MOTOR_BRAKE_HOLD);
	R1.set_brake_mode(MOTOR_BRAKE_BRAKE);
	R2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	FW1.set_brake_mode(MOTOR_BRAKE_COAST);
	FW2.set_brake_mode(MOTOR_BRAKE_COAST);
	C1.set_brake_mode(MOTOR_BRAKE_BRAKE);
	master.clear();
	while (true) {
		//JSL and JSR stand for joy-stick left and joy-stick right respectively. They act as a buffer to obtain the raw value of the joysticks of the controller which can go between 0 and 127
		JSL = master.get_analog(ANALOG_RIGHT_Y);
		JSR = master.get_analog(ANALOG_LEFT_Y);
		//Below is the actual drive code it reads JSL and JSR to determine if they are within cetain values and acts on them. If the values are between 15 and 100 positive or negative the motors are set to the variable*(100/127).
		//The reason for the alteration of the joy-stick is that the maximum value I can put into the motor is 100 so scaling the joy-stick to the motor allows for finer movement.
		//The reason for waiting until the joy-stick reads at least 15 is to avoid unintentional movement if the joy-stick doesn't return directly to center or if the joy-stick flicks back and imputs a negative value before returning to center.
		//Sometimes when we are driving the joy-stick drifts diagonally a little bit which can lower our total speed so if the joy-stick is above a certian hreshhold I now set it to max speed that way tiny fluctuations in our driving don't effect our proformance.
		if(abs(JSL) > 5){
				DT1.move_velocity(JSL);
				DT2.move_velocity(JSL);
		}

		else {
			DT1.brake();
			DT2.brake();
		}

		if(abs(JSR) > 5){
				DT3.move_velocity(JSR);
				DT4.move_velocity(JSR);
		}
		//At the beginning I set the motors to the brake mode "hold" so that they would push back any time they were being forced to move. This way our stops are more precise and if we are stuck in a pushing match we cna let the robot do the work and not use more energy than we need.
		else {
			DT3.brake();
			DT4.brake();
		}

		//This is the code for the fly-wheel. The left, down, and right buttons are set to change the variable FWM or fly-wheel mode. Depending on this variable the fly-wheel motors are set to different speeds
		//This variable also changes the screen on the controller which updates with the fly-wheel mode (close, medium, and far) as well as taking the average of the actual velocities of both mototrs and dividing them by the target velocity. This is then multiplied by 100 to get a percentage of the target speed that the motors are going.
		//Not only does with help with troubleshooting (say, if one setting wasn't reaching the target velocity) it also can help us with consistency on the field by ensuring that we always are shooting at the desired speed.
		if (master.get_digital(DIGITAL_LEFT)) {
			FWM = 1;
		}

		if (master.get_digital(DIGITAL_DOWN)) {
			FWM = 2;
		}

		if (master.get_digital(DIGITAL_RIGHT)) {
			FWM = 3;
		}

		if (master.get_digital(DIGITAL_UP)) {
			FWM = 0;
		}

		if (FWM == 1) {
			FW1.move_voltage(7000);
			FW2.move_voltage(7000);
			master.print(0, 0, "Fly-Wheel Mode: %s", "Close");
			FWAS = (FW1.get_actual_velocity() + FW2.get_actual_velocity())/2;
			FWP = 100*(FWAS/FW1.get_target_velocity());
			master.print(1,0, "Fly-Wheel Percentage: %i", FWP);
			pros::delay(100);
		}

		if (FWM == 2) {
			FW1.move_velocity(150);
			FW2.move_velocity(150);
			master.print(0, 0, "Fly-Wheel Mode: %s", "Medium");
			FWAS = (FW1.get_actual_velocity() + FW2.get_actual_velocity())/2;
			FWP = 100*(FWAS/FW1.get_target_velocity());
			master.print(1,0, "Fly-Wheel Percentage: %i", FWP);
			pros::delay(100);
		}


		if (FWM == 0) {
			FW1.brake();
			FW2.brake();
			master.print(0, 0, "Fly-Wheel Mode: %s", "Off");
			pros::delay(100);
		}


		if (FWM == 3) {
			FW1.move_velocity(200);
			FW2.move_velocity(200);
			master.print(0, 0, "Fly-Wheel Mode: %s", "Far");
			FWAS = (FW1.get_actual_velocity() + FW2.get_actual_velocity())/2;
			FWP = 100*(FWAS/FW1.get_target_velocity());
			master.print(1,0, "Fly-Wheel Percentage: %i", FWP);
			pros::delay(100);
		}

		//This section is fairly simple, if the press the top right bumper the intake pulls in disks from the ground and loads them into the fly-wheel, if the bottom right bumper is pressed it sends disks out the frond of the intake.
		if (master.get_digital(DIGITAL_R1)) {
		  Roller1 = 1;
		}

		else if (master.get_digital(DIGITAL_R2)) {
		  Roller1 = -1;
		}

		else {
			Roller1 = 0;
		}

		while (abs(Roller1) > 0){
			R1.move_relative(Roller1*(7.47/12.56)*900, 100);
			Roller1 = 0;
		}

		//This section is what I call "Net Mode". When we press the up button on the controller whcih changes the variable NM to 1. While NM equals 1 the drive base is set to hold and the rest of the motors on the drive base are set to 0 and each of the bumpers on the controller are set to activate one of the cylenders to fire the net mechanism. The up button is set to fire them all at once. The X button is set to turn NM to 0 and deactivate net mode.
		//I made this a seperate mode because if we accidentally slipped and activated the net durin g the match it could easily disqualify us.
		if (master.get_digital(DIGITAL_X)) {
			NM = 1;
			pros::delay(100);
		}

		if (master.get_digital(DIGITAL_L2)){
			R1.move_velocity(200);
			R2.move_velocity(200);
		}

		else if (master.get_digital(DIGITAL_L1)){
			R1.move_velocity(-200);
			R2.move_velocity(-200);
		}

		else {
			R1.brake();
			R2.brake();
		}

		if (master.get_digital(DIGITAL_A)){
			Net1.set_value(true);
		}

		else {
			Net1.set_value(false);
		}

		if (master.get_digital(DIGITAL_B)){
			Net3.set_value(false);
			Net2.set_value(false);
		}

		else {
			Net3.set_value(true);
			Net2.set_value(true);
		}

		while (NM == 1) {
				DT1.brake();
				DT2.brake();
				DT3.brake();
				DT4.brake();
				FW1.move_velocity(0);
				FW2.move_velocity(0);
				R1.move_velocity(0);

				if (master.get_digital(DIGITAL_L1)){
					Net1.set_value(true);
				}

				if (master.get_digital(DIGITAL_L2)){
					Net2.set_value(true);
				}

				if (master.get_digital(DIGITAL_R1)){
					Net3.set_value(true);
				}

				if (master.get_digital(DIGITAL_R2)){
					Net4.set_value(true);
				}

				if (master.get_digital(DIGITAL_UP)){
					Net1.set_value(true);
					Net2.set_value(true);
					Net3.set_value(true);
					Net4.set_value(true);
				}
				if (master.get_digital(DIGITAL_X)){
					NM = 0;
				}
		}

		pros::delay(20);
	}
}
