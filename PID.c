#include "PID.h"
void PIDInit(struct PID controller, float kP, float kD) {
	controller.kP = kP;
	controller.kD = kD;
}

float PIDRun(struct PID controller, float error) {

	// calculate the derivative
	float pidDerivative = error - controller.previousError;
	// calculate drive
	return ((controller.kP * error)  + (controller.kD * pidDerivative));

	controller.previousError = error;
	wait1Msec(25);
}

int requestedGyroAngle;
struct PID gyroPID;
void 	PIDStartGyroTask(struct PID controller, int requested) {
	requestedGyroAngle = requested;
	startTask(gyro);
	gyroPID = controller;

}


task PIDGyroController() {
		int pidDrive = PIDRun(gyroPID, SensorValue[gyro] - requestedGyroAngle);
		motor[leftFront] = pidDrive;
		motor[leftBack] = pidDrive;
		motor[rightFront] = -pidDrive;
		motor[rightBack] = -pidDrive;
}

void 	PIDStopGyroTask(struct PID controller) {
	stopTask(gyro);
}
