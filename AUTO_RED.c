
void startRed() {
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	startPID(initialAngle, gyro);
	//initial strafe
	motor[strafe] = -127;
	wait1Msec(RED_STRAFE_TIME);
	motor[strafe] = 0;

	//finish realigning
	wait1Msec(500);
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
	startPID(RED_MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(500);

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < RED_LITTLE_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < RED_FULL_HEIGHT_ELEVATOR) {
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
	resetEn();
	startPID(RED_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(RED_FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(1500);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(RED_SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(500);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < RED_TIME_TO_BRING_DOWN_EL) {
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
	while(abs(SensorValue(leftDrive)) < 200 && abs(SensorValue(rightDrive)) < 200) {
		moveBackward(127);
	}
	stopDrive();

	resetEn();
	startPID(900, gyro);
	wait1Msec(1000);
	stopTask(PIDController);
	stopDrive();
}
