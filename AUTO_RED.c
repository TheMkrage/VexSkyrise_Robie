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
	startTask(autoClock);
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	startPID(initialAngle, gyro);
	//initial strafe
	motor[strafe] = -127;
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

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < RED8_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(abs(SensorValue(leftDrive)) < 180 && abs(SensorValue(rightDrive)) < 180) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(RED8_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1300);
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
	//open
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -10;

	//move back
	resetEn();
	while(abs(SensorValue(leftDrive)) < 150 && abs(SensorValue(rightDrive)) < 150) {
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
	motor[strafe] = -62;
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
	while(abs(SensorValue(leftDrive)) < 180 && abs(SensorValue(rightDrive)) < 180) {
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
	while(abs(SensorValue(leftDrive)) < 150 && abs(SensorValue(rightDrive)) < 150) {
		moveBackward(127);
	}
	stopDrive();

	resetEn();
	startPID(930, gyro);
	wait1Msec(1000);
	stopTask(PIDController);
	stopDrive();

	resetEn();
	while(abs(SensorValue(leftDrive)) < 320 && abs(SensorValue(rightDrive)) < 320) {
		moveForward(127);
	}
	stopDrive();

	wait1Msec(300);
	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < RED12_FULL_HEIGHT_ELEVATOR + 370) {
		allElOnMax();
	}
	allElStop();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(-320, gyro);
	wait1Msec(1000);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(RED12_FORWARD_TO_BASE - 110, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

		//bring down el
	clearTimer(T1);
	while(time1[T1] < RED12_TIME_TO_BRING_DOWN_EL  && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();

	}
	allElStop();
}
