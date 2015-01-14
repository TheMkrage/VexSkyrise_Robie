

void allElOnMax() {
	motor[rightEl] = 127;
	motor[leftEl] = 127;
	motor[bRightEl] = 127;
	motor[bLeftEl] = 127;
}

void allElOnMaxDown() {
	motor[rightEl] = -127;
	motor[leftEl] = -127;
	motor[bRightEl] = -127;
	motor[bLeftEl] = -127;
}

void allElStop() {
	motor[rightEl] = 0;
	motor[leftEl] = 0;
	motor[bRightEl] = 0;
	motor[bLeftEl] = 0;
}

void resetEn() {
	SensorValue(leftDrive) = 0;
	SensorValue(rightDrive) = 0;
	//nMotorEncoder[rightEl] = 0;
}

void turnLeft(int throttle){
	motor[leftFront] = -throttle;
	motor[leftBack] = -throttle;
	motor[rightFront] = -throttle;
	motor[rightBack] = -throttle;
}

void turnRight(int throttle){
	motor[leftFront] = throttle;
	motor[leftBack] = throttle;
	motor[rightFront] = throttle;
	motor[rightBack] = throttle;
}

void moveForward(int throttle){
	motor[leftFront] = throttle;
	motor[leftBack] = throttle;
	motor[rightFront] = -throttle;
	motor[rightBack] = -throttle;
}

void moveBackward(int throttle){
	motor[leftFront] = -throttle;
	motor[leftBack] = -throttle;
	motor[rightFront] = -throttle;
	motor[rightBack] = -throttle;
}

void stopDrive() {
	motor[leftFront] = 0;
	motor[leftBack] = 0;
	motor[rightFront] = 0;
	motor[rightBack] = 0;
}

void resetGyro() {
	SensorType[in1] = sensorNone;
	wait1Msec(1101);
	SensorType[in1] = sensorGyro;
	wait1Msec(2000);

	//reset encoders before start
	resetEn();
}
