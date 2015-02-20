void startBlueStrafe() {
	motor[strafe] = 127;
	wait1Msec(RED8_STRAFE_TIME);
	motor[strafe] = 0;
	wait1Msec(RED8_STRAFE_TIME);
	motor[strafe] = -127;
	wait1Msec(RED8_STRAFE_TIME * 2);
	motor[strafe] = 0;
}

void startBlue8() {
		writeDebugStreamLine("STARTING BLUE 12");
	//startTask(autoClock);
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	PID encoderPID;
	PIDInit(encoderPID, .3, 1);
	clearTimer(T1);
	while(time1[T1] < 10000) {
		int throttle = -PIDRun(encoderPID, ((SensorValue[rightDrive] - SensorValue[leftDrive])/2) - 1000);
		int turn = PIDRun(gyroPID, (SensorValue[gyro]) - initialAngle);
		//int turn = 0;
		motor[leftFront] = throttle + turn;
		motor[leftBack] = throttle + turn;
		motor[rightFront] = throttle - turn;
		motor[rightBack] = throttle - turn;
	}

	wait1Msec(40000);

	startPID(initialAngle, gyro);
	//initial strafe
	motor[strafe] = 127;
	wait1Msec(BLUE8_STRAFE_TIME);
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
	startPID(BLUE8_MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(300);

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < BLUE8_LITTLE_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < BLUE8_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(abs(SensorValue(leftDrive)) < BLUE8_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER && abs(SensorValue(rightDrive)) < BLUE8_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(BLUE8_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1300);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(BLUE8_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(BLUE8_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(400);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < BLUE8_TIME_TO_BRING_DOWN_EL && SensorValue[bumperSwitch] == 0) {
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
	while(abs(SensorValue(leftDrive)) < BLUE8_FINAL_BACKWARDS && abs(SensorValue(rightDrive)) < BLUE8_FINAL_BACKWARDS) {
		moveBackward(127);
	}
	stopDrive();
}







void startBlue12() {
		writeDebugStreamLine("STARTING BLUE 12");
	startTask(autoClock);
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	PID gyroPID;
	PIDInit(gyroPID, .4, .25);
	PIDStartGyroTask(gyroPID, SensorValue[gyro]);

	//initial strafe
	motor[strafe] = 80;
	wait1Msec(BLUE12_STRAFE_TIME);
	motor[strafe] = 0;

	PIDStopGyroTask(gyroPID);


	//move Forward
	PID encoderPID;
	PIDInit(encoderPID, .3, .1);
	clearTimer(T1);
	while(time1[T1] < 700) {
		int throttle = PIDRun(encoderPID, ((SensorValue[rightDrive] + SensorValue[leftDrive])/2) - BLUE12_MUSTARD_FORWARD);
		int turn = PIDRun(gyroPID, (SensorValue[gyro]) - initialAngle);
		motor[leftFront] = throttle + turn;
		motor[leftBack] = throttle + turn;
		motor[rightFront] = throttle - turn;
		motor[rightBack] = throttle - turn;
	}

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < BLUE12_LITTLE_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < BLUE12_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(abs(SensorValue(leftDrive)) < BLUE12_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER && abs(SensorValue(rightDrive)) < BLUE12_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(BLUE12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(BLUE12_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(BLUE12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(400);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < BLUE12_TIME_TO_BRING_DOWN_EL && SensorValue[bumperSwitch] == 0) {
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
	while(abs(SensorValue(leftDrive)) < BLUE12_BACKWARDS_FROM_BASE  && abs(SensorValue(rightDrive)) < BLUE12_BACKWARDS_FROM_BASE ) {
		moveBackward(127);
	}
	stopDrive();

	resetEn();
	startPID(BLUE12_ANGLE_TO_GET_CUBE, gyro);
	wait1Msec(1000);
	stopTask(PIDController);
	stopDrive();

	resetEn();
	while(abs(SensorValue(leftDrive)) < BLUE12_FORWARD_TO_CUBE && abs(SensorValue(rightDrive)) < BLUE12_FORWARD_TO_CUBE) {
		moveForward(127);
	}
	stopDrive();

	wait1Msec(300);

	nMotorEncoder[rightEl] = 0;
	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < BLUE12_ELEVATOR_CUBE_HEIGHT) {
		allElOnMax();
	}
	allElStop();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(BLUE12_ANGLE_TO_GET_TO_BASE_WITH_CUBE, gyro);
	wait1Msec(1000);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	while(abs(SensorValue[rightDrive]) < BLUE12_FORWARD_TO_BASE_WITH_CUBE) {
		moveForward(62);
	}
stopDrive();
		//bring down el
	clearTimer(T1);
	while(time1[T1] < BLUE12_TIME_TO_BRING_DOWN_EL  && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();

	}
	allElStop();
}






//UNTIL LATER...
void startBlue2Mustard() {
		writeDebugStreamLine("STARTING BLUE 12");
	startTask(autoClock);
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	PID gyroPID;
	PIDInit(gyroPID, .4, .25);
	PIDStartGyroTask(gyroPID, SensorValue[gyro]);

	//initial strafe
	motor[strafe] = 80;
	wait1Msec(BLUE12_STRAFE_TIME);
	motor[strafe] = 0;

	PIDStopGyroTask(gyroPID);

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
	startPID(BLUE12_MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(300);

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < BLUE12_LITTLE_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < BLUE12_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(abs(SensorValue(leftDrive)) < 190 && abs(SensorValue(rightDrive)) < 190) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(BLUE12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(BLUE12_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(BLUE12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(400);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < BLUE12_TIME_TO_BRING_DOWN_EL && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();
	}
	allElStop();

	wait1Msec(500);
	//open
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -10;

	resetEn();
	while(abs(SensorValue[rightDrive]) < abs(BLUE12_FORWARD_TO_BASE)) {
		moveBackward(62);


		//TWO
	}
	stopDrive();

	stopTask(PIDController);

	startPID(initialAngle, gyro);
	wait1Msec(2000);
	stopTask(PIDController);

	resetEn();
	stopDrive();
	startPID(BLUE12_MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(300);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < BLUE12_FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(abs(SensorValue(leftDrive)) < 190 && abs(SensorValue(rightDrive)) < 190) {
		moveBackward(40);
	}
	stopDrive();

	//get gyro angle
	stopTask(PIDController);
	resetEn();
	startPID(BLUE12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(BLUE12_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(800);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(BLUE12_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(400);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < BLUE12_TIME_TO_BRING_DOWN_EL && SensorValue[bumperSwitch] == 0) {
		allElOnMaxDown();
	}
	allElStop();

	wait1Msec(500);
	//open
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -10;
}
