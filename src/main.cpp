#include "main.h"
#include "Motors_Sensors_And_Functions.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
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
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {}

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
	DT1.set_brake_mode(MOTOR_BRAKE_HOLD);
	DT2.set_brake_mode(MOTOR_BRAKE_HOLD);
	DT3.set_brake_mode(MOTOR_BRAKE_HOLD);
	DT4.set_brake_mode(MOTOR_BRAKE_HOLD);
	while (true) {
		//JSL and JSR stand for joy-stick left and joy-stick right respectively. They act as a buffer to obtain the raw value of the joysticks of the controller which can go between 0 and 127
		JSL = master.get_analog(ANALOG_LEFT_Y);
		JSR = master.get_analog(ANALOG_RIGHT_Y);
		//Below is the actual drive code it reads JSL and JSR to determine if they are within cetain values and acts on them. If the values are between 15 and 100 positive or negative the motors are set to the variable*(100/127).
		//The reason for the alteration of the joy-stick is that the maximum value I can put into the motor is 100 so scaling the joy-stick to the motor allows for finer movement.
		//The reason for waiting until the joy-stick reads at least 15 is to avoid unintentional movement if the joy-stick doesn't return directly to center or if the joy-stick flicks back and imputs a negative value before returning to center.
		//Sometimes when we are driving the joy-stick drifts diagonally a little bit which can lower our total speed so if the joy-stick is above a certian hreshhold I now set it to max speed that way tiny fluctuations in our driving don't effect our proformance.
		if(15 < JSL && JSL < 100){
			DT1.move_velocity(JSL*(100/127));
			DT2.move_velocity(JSL*(100/127));
		}

		else if(JSL > 100){
			DT1.move_velocity(100);
			DT2.move_velocity(100);
		}

		else if(-15 > JSL && JSL > -100){
			DT1.move_velocity(JSL*(100/127));
			DT2.move_velocity(JSL*(100/127));
		}

		else if(JSL < -100){
			DT1.move_velocity(-100);
			DT2.move_velocity(-100);
		}

		else {
			DT1.brake();
			DT2.brake();
		}

		if(15 < JSR && JSR < 100){
			DT3.move_velocity(JSR*(100/127));
			DT4.move_velocity(JSR*(100/127));
		}

		else if(JSR > 100){
			DT3.move_velocity(100);
			DT4.move_velocity(100);
		}

		else if(-15 > JSR && JSR > -100){
			DT3.move_velocity(JSR*(100/127));
			DT4.move_velocity(JSR*(100/127));
		}

		else if(JSR < -100){
			DT3.move_velocity(-100);
			DT4.move_velocity(-100);
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

		if (FWM == 1) {
			FW1.move_velocity(100);
			FW2.move_velocity(100);
			master.print(0, 0, "Fly-Wheel Mode: %s", "Close");
			FWAS = (FW1.get_actual_velocity() + FW2.get_actual_velocity())/2;
			FWP = 100*(FWAS/FW1.get_target_velocity());
			master.print(1,0, "Fly-Wheel Percentage: %%i", FWP);
			pros::delay(100);
		}

		if (FWM == 2) {
			FW1.move_velocity(200);
			FW2.move_velocity(200);
			master.print(0, 0, "Fly-Wheel Mode: %s", "Medium");
			FWAS = (FW1.get_actual_velocity() + FW2.get_actual_velocity())/2;
			FWP = 100*(FWAS/FW1.get_target_velocity());
			master.print(1,0, "Fly-Wheel Percentage: %%i", FWP);
			pros::delay(100);
		}


		if (FWM == 3) {
			FW1.move_velocity(300);
			FW2.move_velocity(300);
			master.print(0, 0, "Fly-Wheel Mode: %s", "Far");
			FWAS = (FW1.get_actual_velocity() + FW2.get_actual_velocity())/2;
			FWP = 100*(FWAS/FW1.get_target_velocity());
			master.print(1,0, "Fly-Wheel Percentage: %%i", FWP);
			pros::delay(100);
		}

		//This section is fairly simple, if the press the top right bumper the intake pulls in disks from the ground and loads them into the fly-wheel, if the bottom right bumper is pressed it sends disks out the frond of the intake.
		if (master.get_digital(DIGITAL_R1)) {
			I1.move_velocity(200);
			I2.move_velocity(200);
		}

		else if (master.get_digital(DIGITAL_R2)) {
			I1.move_velocity(-200);
			I2.move_velocity(-200);
		}

		else {
			I1.move_velocity(0);
			I2.move_velocity(0);
		}

		//This section is what I call "Net Mode". When we press the up button on the controller whcih changes the variable NM to 1. While NM equals 1 the drive base is set to hold and the rest of the motors on the drive base are set to 0 and each of the bumpers on the controller are set to activate one of the cylenders to fire the net mechanism. The up button is set to fire them all at once. The X button is set to turn NM to 0 and deactivate net mode.
		//I made this a seperate mode because if we accidentally slipped and activated the net durin g the match it could easily disqualify us.
		if (master.get_digital(DIGITAL_UP)) {
			NM = 1;
			pros::delay(100);
		}

		while (NM == 1) {
				DT1.brake();
				DT2.brake();
				DT3.brake();
				DT4.brake();
				FW1.move_velocity(0);
				FW2.move_velocity(0);
				I1.move_velocity(0);
				I2.move_velocity(0);

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
