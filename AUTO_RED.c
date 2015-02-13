void startRedStrafe() {
	motor[strafe] = -127;
	wait1Msec(RED8_STRAFE_TIME);
	motor[strafe] = 0;
	wait1Msec(RED8_STRAFE_TIME);
	motor[strafe] = 127;
	wait1Msec(RED8_STRAFE_TIME * 2);
	motor[strafe] = 0;
}

void startRed8() {
	writeDebugStreamLine("STARTING Red 12");
	//startTask(autoClock);
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	startPID(initialAngle, gyro);
	//initial strafe
	motor[strafe] = -80;
	wait1Msec(RED8_STRAFE_TIME);
	motor[strafe] = 0;

	//finish realigning
	wait1Msec(300);
	stopTask(PIDController);



	/*startPID(500, leftDrive, rightDrive, true);
	wait1Msec(3000);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(200);
	startPID(initialAngle, gyro);
	wait1Msec(400);
	stopDrive();*/


	//move forward to mustard holder
	startPID(RED8_MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(300);

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < RED8_LITTLE_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	//close
	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < RED8_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little, by encoders
	resetEn();
	while(abs(SensorValue(leftDrive)) < RED8_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER && abs(SensorValue(rightDrive)) <  RED8_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(RED8_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1800);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(RED8_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(RED8_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(400);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < RED8_TIME_TO_BRING_DOWN_EL && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();
	}
	allElStop();

	wait1Msec(500);

	//open claw
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -10;

	//final move back
	resetEn();
	while(abs(SensorValue(leftDrive)) < RED8_FINAL_BACKWARDS && abs(SensorValue(rightDrive)) < RED8_FINAL_BACKWARDS) {
		moveBackward(127);
	}
	stopDrive();
}




void startRed12() {
	writeDebugStreamLine("STARTING Red 12");
	startTask(autoClock);

	///sets initial angle
	int initialAngle = SensorValue(gyro);

	startPID(initialAngle, gyro);
	//initial strafe
	motor[strafe] = -80;
	wait1Msec(RED12_STRAFE_TIME);
	motor[strafe] = 0;

	//finish realigning
	wait1Msec(300);
	stopTask(PIDController);



	/*startPID(500, leftDrive, rightDrive, true);
	wait1Msec(3000);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(200);
	startPID(initialAngle, gyro);
	wait1Msec(400);
	stopDrive();*/


	//move forward to mustard holder
	startPID(RED12_MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(300);

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < RED12_LITTLE_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	//close claw
	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < RED12_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(abs(SensorValue(leftDrive)) < RED12_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER && abs(SensorValue(rightDrive)) < RED12_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(RED12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1300);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(RED12_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(RED12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(400);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < RED12_TIME_TO_BRING_DOWN_EL && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();
	}
	allElStop();

	wait1Msec(500);
	//open
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -10;

	//move back
	resetEn();
	while(abs(SensorValue(leftDrive)) < RED12_BACKWARDS_FROM_BASE && abs(SensorValue(rightDrive)) < RED12_BACKWARDS_FROM_BASE) {
		moveBackward(127);
	}
	stopDrive();

	resetEn();
	startPID(RED12_ANGLE_TO_GET_CUBE, gyro);
	wait1Msec(1000);
	stopTask(PIDController);
	stopDrive();

	resetEn();
	while(abs(SensorValue(leftDrive)) < RED12_FORWARD_TO_CUBE && abs(SensorValue(rightDrive)) < RED12_FORWARD_TO_CUBE) {
		moveForward(127);
	}
	stopDrive();

	wait1Msec(300);

	resetEn();
	nMotorEncoder[rightEl] = 0;
	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < RED12_ELEVATOR_CUBE_HEIGHT) {
		allElOnMax();
	}
	allElStop();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(RED12_ANGLE_TO_GET_TO_BASE_WITH_CUBE, gyro);
	wait1Msec(1000);
	stopTask(PIDController);

		resetEn();
	//move to yellow
	while(abs(SensorValue[rightDrive]) < RED12_FORWARD_TO_BASE_WITH_CUBE) {
		moveForward(62);
	}
stopDrive();

	//bring down el
	clearTimer(T1);
	while(time1[T1] < RED12_TIME_TO_BRING_DOWN_EL  && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();

	}
	allElStop();


	//it will move backwards with 300 ms left regardless what it is doing.
}
