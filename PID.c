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
