

void startRed12() {
	///sets initial angle
	int initialAngle = SensorValue(gyro);

	startPID(initialAngle, gyro);
	//initial strafe
	motor[Strafe] = -127;
	wait1Msec(330);
	motor[Strafe] = 0;

	//finish realigning
	wait1Msec(500);
	stopTask(PIDController);

	//move forward to mustard holder
	resetEn();
	while(SensorValue(leftDrive) < 60 && SensorValue(rightDrive) > -60) {
		moveForward(63);
	}
	stopDrive();

	wait1Msec(500);

	resetEn();
	//Move up little, grab, continue
	while(nMotorEncoder[rightEl] < 300) {
		allElOnMax();
	}
	allElStop();

	wait1Msec(1000);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(nMotorEncoder[rightEl] < 601) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(SensorValue(leftDrive) > -100 && SensorValue(rightDrive) < 100) {
		moveBackward(63);
	}
	stopDrive();

	//get gyro angle
	startPID(542, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow base
	while(SensorValue(leftDrive) < 70 && SensorValue(rightDrive) > -70) {
		moveForward(63);
	}
	stopDrive();

	//bring down el
	while(SensorValue(bumperSwitch) == 0) {
		allElOnMaxDown();
	}
	allElStop();

	wait1Msec(500);
	//open
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -20;

	//move Back to same space as before
	resetEn();
	while(SensorValue(leftDrive) > -65 && SensorValue(rightDrive) < 65) {
		moveBackward(63);
	}
	stopDrive();

	//move back to initial angle to go get yellow
	startPID(initialAngle, gyro);
	wait1Msec(1000);
	stopTask(PIDController);

	//move forward to mustard holder, again
	resetEn();
	while(SensorValue(leftDrive) < 60 && SensorValue(rightDrive) > -60) {
		moveForward(63);
	}

	//close claw, again
	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent, again
	while(nMotorEncoder[rightEl] < 1315) {
		allElOnMax();
	}
	allElStop();

	//moveback a little, again
	resetEn();
	while(SensorValue(leftDrive) > -100 && SensorValue(rightDrive) < 100) {
		moveBackward(63);
	}
	stopDrive();

	//get gyro angle, again
	startPID(542, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow, again
	while(SensorValue(leftDrive) < 70 && SensorValue(rightDrive) > -70) {
		moveForward(63);
	}
	stopDrive();

	//bring down el, again
	while(SensorValue(bumperSwitch) == 0) {
		allElOnMaxDown();
	}
	allElStop();

	wait1Msec(500);
	//open
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = 0;



	//move back
	resetEn();
	while(SensorValue(leftDrive) > -50 && SensorValue(rightDrive) < 50) {
		moveBackward(63);
	}
	stopDrive();
	/*

	while(SensorValue(lineFolRight) > 1000) {
		motor[leftBack] = -25;
		motor[leftFront] = -25;
		motor[rightFront] = 25;
		motor[rightBack] = 25;
	}
	while(SensorValue(lineFolLeft) > 1000) {
		motor[leftBack] = -40;
		motor[leftFront] = -40;
		motor[rightFront] = 0;
		motor[rightBack] = 0;
	}





	const float lineFromHolderCm = 24.7;



	int distanceFromWall = SensorValue[rightSon];
	float angleCorrection = ((atan((lineFromHolderCm / distanceFromWall)) * (180 / PI)) * 10);
	writeDebugStreamLine("%d",angleCorrection);

	angleCorrection = SensorValue[in1] - angleCorrection;
	startPID(angleCorrection + 48 , in1);
	wait1Msec(1500);
	stopTask(PIDController);
	*/


}
