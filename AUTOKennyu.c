


int gyroValueToAlign = 0;


//25cm from wall to align with the mustard holder
void moveToAnglingPosition(){

	//get gyro value to keep aligned with

}




//Knocks cube onto mustard catcher
void initalForwardAndBack() {

}

//starts here Kenny
void startauton()
{

motor[Strafe] = -60 ;
wait1Msec(1000);
motor[Strafe] = 0;

if (bumperSwitch == 1)
{
	clearTimer(T1);
	SensorType[in1] = sensorNone;
	wait1Msec(1101);
	SensorType[in1] = sensorGyro;
	wait1Msec(2000);
}
//needed for competition
	//pre_auton();
	//moves forward until encoders are 80
	while(SensorValue[rightDrive] > -80 && SensorValue[leftDrive] < 80) {
		moveForward(50);
		writeDebugStreamLine("Hello");
	}

	wait1Msec(250);

	stopDrive();

	wait1Msec(250);

	resetEn();

	//Moves back to the line (or about)
	while(SensorValue(leftDrive) > -90 && SensorValue(rightDrive) < 90) {
		moveBackward(50);
	}



	int distanceFromWall = SensorValue[rightSon];
	const float lineFromHolderCm = 24.7;

	motor[Strafe] = -60;
	//moveToAnglingPosition();
	startPID(0 , in1);
	while(SensorValue[rightSon] < 23) {

	}
	motor[Strafe] = 0;
	stopTask(PIDController);

	float angleCorrection = ((atan((lineFromHolderCm / distanceFromWall)) * (180 / PI)) * 10);
	writeDebugStreamLine("%d",angleCorrection);

	angleCorrection = SensorValue[in1] - angleCorrection;
	startPID(angleCorrection + 48, in1);
	wait1Msec(1500);
	stopTask(PIDController);
	//go to yellow holder
	resetEn();
	while(SensorValue[leftDrive] < 220  && SensorValue[rightDrive] > -220 ) {
		int driveRate = 70;

		motor[leftBack] = driveRate;
		motor[leftFront] = driveRate;
		motor[rightFront] = -driveRate;
		motor[rightBack] = -driveRate;
	}
	writeDebugStreamLine("hello");
	stopDrive();



	//Lifts Elevator
	resetEn();
	while(nMotorEncoder[rightEl] < 210) {
		motor[bRightEl] = 127;
		motor[rightEl] = 127;
		motor[bLeftEl] = 127;
		motor[leftEl] = 127;
	}

	motor[bRightEl] = 0;
	motor[rightEl] = 0;
	motor[bLeftEl] = 0;
	motor[leftEl] = 0;
	motor[leftBack] = 0;
	motor[leftFront] = 0;
	motor[rightFront] = 0;
	motor[rightBack] = 0;

	wait1Msec(500);

	//Grabs mustard
	motor[rightClaw] = 127;

	wait1Msec(400);
	resetEn();
	//Elevates Elevator
	while(nMotorEncoder[rightEl] < 450) {
		motor[bRightEl] = 63;
		motor[rightEl] = 63;
		motor[bLeftEl] = 63;
		motor[leftEl] = 63;
	}

	//autoclaw
	motor[rightClaw] = 20;
	motor[bRightEl] = 0;
	motor[rightEl] = 0;
	motor[bLeftEl] = 0;
	motor[leftEl] = 0;

	wait1Msec(500);

	//backup to line
	motor[leftBack] = -50;
	motor[leftFront] = -50;
	motor[rightFront] = 50;
	motor[rightBack] = 50;
	motor[Strafe] = 60;
	wait1Msec(100);
	motor[Strafe] = 0;
	wait1Msec(100);
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
	wait1Msec(100);
	startPID(0, in1);


	wait1Msec(1000);

	while(SensorValue[rightSon] < 39 ){

		motor[Strafe] = -60;
	}

	motor[Strafe] = 0;
	stopTask(PIDController);
	stopDrive();

	wait1Msec(200);

	resetEn();

	stopDrive();

	moveForward(50);

	wait1Msec(800);

	stopDrive();

	motor[rightClaw] = -60;
	wait1Msec(1000);

	motor[rightClaw] = 0;

}
