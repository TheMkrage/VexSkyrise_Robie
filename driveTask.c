#include "PIDController.c"

int driveMult;
bool angleNotSet = true;

float getAngle() {
	if(SensorValue[gyro] < 0) {
		return 3600 + SensorValue[gyro];
	}else {
		return SensorValue[gyro];
	}
}

float getDesiredAngle(float turn) {
	float newOffset = (turn/127) * 3600;
	float aim = getAngle() + newOffset;
	//writeDebugStreamLine("aim: %f3.3",aim);
	if(aim < 0) {
		return aim + 3600;
	}else if(aim > 3600) {
		return aim - 3600;
	}else {
		return aim;
	}
}

float skimGain = .25;
float skim(float v) {
	// gain determines how much to skim off the top
	if (v > 1.0) {
		return -((v - 1.0) * skimGain);
		} else if (v < -1.0) {
		return -((v + 1.0) * skimGain);
	}
	return 0;
}


void driveHalo(float throttle, float turn) {
		float gyroKP = .1;
		if(throttle < 30 && throttle > -30) {
			throttle = 0;
		}

		float currentAngle = getAngle();
		float desiredAngle = getDesiredAngle(turn);
		writeDebugStreamLine("current: %3.3f desired: %3.3f", currentAngle, desiredAngle);
		float modifiedTurn = (currentAngle - desiredAngle) * gyroKP;
		writeDebugStreamLine("modified: %5.3f Throttle: %5.3f", modifiedTurn, throttle);

		float t_left = throttle + modifiedTurn;
		float t_right = throttle - modifiedTurn;
		writeDebugStreamLine("left: %4.3f, right %4.3f", t_left, t_right);

		int left = (int)t_left;
		int right = (int)t_right;

		//negative because Vinnie did it
		writeDebugStreamLine("left: %i, right %i", left, right);
		motor[leftBack] = left;
		motor[leftFront] = left;
		motor[rightFront] = right;
		motor[rightFront] = right;
		writeDebugStreamLine(" ");
	}

void normalDrive() {

	//sets speeds for dleft
	int leftSpeed;
	int rightSpeed;
	/*if(vexRT[Ch1] > -20 && vexRT[Ch1] < 20) {
		leftSpeed = 0;
		rightSpeed =0;
	}else if(vexRT[Ch3] > -20 &&  vexRT[Ch3] < 20) {
		leftSpeed = 0;
		rightSpeed =0;
	}else{
		leftSpeed = (vexRT[Ch1] + vexRT[Ch3])/driveMult; //speed for left motors
		rightSpeed =(vexRT[Ch3] - vexRT[Ch1])/driveMult; //speed for right motors
	}*/
	leftSpeed = (vexRT[Ch1] + vexRT[Ch3])/driveMult; //speed for left motors
	rightSpeed =(vexRT[Ch3] - vexRT[Ch1])/driveMult; //speed for right motors
		if(vexRT[Btn6U] == 1) {
		if(angleNotSet == true) {
			startPID(SensorValue[gyro], in1);
			angleNotSet = false;
		}
		}else{
		angleNotSet = true;
		stopTask(PIDController);

		if(leftSpeed < 20 && leftSpeed > -20) {
			leftSpeed = 0;
			rightSpeed = 0;
		}
		motor[leftFront]  = leftSpeed; // (y + x)/2
		motor[rightFront] = rightSpeed;
		motor[leftBack]  = leftSpeed;  // (y + x)/2
		motor[rightBack] = rightSpeed;
	}
	if(vexRT[Ch4] > 40 || vexRT[Ch4] < -40) {	//Threshold for strafe joystick
		motor[strafe] = vexRT[Ch4];
		}else {
		motor[strafe] = 0;
	}
}

void gyroDrive() {
	//overide, if not then do rest of things
	/*if(vexRT[Btn5U] == 1) {
		driveMult = 1;
		}else if(nMotorEncoder[rightEl] > 2500) {
		//driveMult = 1.5;
		}else {
		driveMult = 1;
	}*/
	driveHalo(vexRT[Ch3],vexRT[Ch1]);

	//Drive Fast
	//Drive
}

task driveTask (){
	while(1){
		//Set Encoders to 0 on bumperswitch press
		if(SensorValue(bumperSwitch)==1){
			nMotorEncoder[rightEl]= 0;
			allElStop();
		}
		//Drive Multiplier
		driveMult = 1;
		normalDrive();
		//gyroDrive();
	}
}
