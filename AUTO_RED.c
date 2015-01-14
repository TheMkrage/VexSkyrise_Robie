#include "moreDrivePID.c"
void startRed() {
	///sets initial angle
	int initialAngle = SensorValue(gyro);


	//startPID(initialAngle, gyro);
	//initial strafe
	motor[Strafe] = -127;
	wait1Msec(STRAFE_TIME);
	motor[Strafe] = 0;

	//finish realigning
	wait1Msec(500);
	//stopTask(PIDController);



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
	startPID(MUSTARD_FORWARD, leftDrive, rightDrive, true);
	wait1Msec(700);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();
	wait1Msec(500);

	resetEn();
	//Move up little, grab, continue
	while(abs(nMotorEncoder[rightEl]) < LITTLE_ELEVATOR) {
		writeDebugStreamLine("right: %i", abs(nMotorEncoder[rightEl]));
		allElOnMax();
	}
	allElStop();

	wait1Msec(500);

	motor[rightClaw] = 127;
	wait1Msec(500);
	motor[rightClaw] = 20;

	//move up to full extent
	while(abs(nMotorEncoder[rightEl]) < FULL_HEIGHT_ELEVATOR) {
		allElOnMax();
	}
	allElStop();

	//moveback a little
	resetEn();
	while(SensorValue(leftDrive) > 180 && SensorValue(rightDrive) < -180) {
		moveBackward(40);
	}
	stopDrive();

	wait1Msec(9000);


	//get gyro angle
	resetEn();
	startPID(SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(1500);
	stopTask(PIDController);

	resetEn();
	//move to yellow
	startPID(FORWARD_TO_BASE, leftDrive, rightDrive, true);
	wait1Msec(1500);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
	stopDrive();

	resetEn();
	startPID(SKYRISE_BASE_ANGLE, gyro);
	wait1Msec(500);
	stopTask(PIDController);

	//bring down el
	clearTimer(T1);
	while(time1[T1] < TIME_TO_BRING_DOWN_EL) {
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
	while(SensorValue(leftDrive) > -125 && SensorValue(rightDrive) < 125) {
		moveBackward(40);
	}
	stopDrive();

	resetEn();
	startPID(initialAngle, gyro);
	wait1Msec(1000);
	stopTask(PIDController);
	stopDrive();

	wait1Msec(500);

	resetEn();
	startPID(SECOND_FORWARD_TO_MUSTARD, leftDrive, rightDrive, true);
	wait1Msec(2000);
	stopTask(PIDControllerEnFriend);
	stopTask(PIDControllerEn);
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
