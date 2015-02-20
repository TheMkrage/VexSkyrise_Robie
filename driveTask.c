/* Main class for drive train
In this class, there is:
- Normal Drive (driveHalo)
- Gyro Drive (gyroDrive)
This doesn't work, vex gyros do not update fast enough for this to be successful
*/

#include "PIDController.c"
#include "PID.c"

int driveMult;
bool angleNotSet = true;

//modified angle, kind of worthless now, but still good to have
float getAngle() {
	if(SensorValue[gyro] < 0) {
		return 3600 + SensorValue[gyro];
		}else {
		return SensorValue[gyro];
	}
}

//also obsolete, but good to have still,
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

//another method used in gyro drive, doesn't work
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

//drives with gyro asssist
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

PID straightStrafe;
float requestedAngle;
//the drive used normally, it is a very simple working drive equation
void normalDrive() {

	//sets speeds for dleft
	int	leftSpeed = (vexRT[Ch1] + vexRT[Ch3])/driveMult; //speed for left motors
	int rightSpeed =(vexRT[Ch3] - vexRT[Ch1])/driveMult; //speed for right motors

	//straight strafing button, when pressed, the left and right drive will work to keep the same angle, strafe wheel still moves the robot however
	if(vexRT[Btn6U] == 1) {
		if(angleNotSet == true) {
			requestedAngle = SensorValue[gyro];
			//startPID(SensorValue[gyro], in1);
			angleNotSet = false;
		}
		int pidDrive = PIDRun(straightStrafe, SensorValue[gyro] - requestedAngle);
		motor[leftFront] = pidDrive;
		motor[leftBack] = pidDrive;
		motor[rightFront] = -pidDrive;
		motor[rightBack] = -pidDrive;

	}else{

		requestedAngle = NULL;

		angleNotSet = true;

		//thresholds
		if(leftSpeed < 20 && leftSpeed > -20) {
			leftSpeed = 0;
			rightSpeed = 0;
		}

		//set power to motors
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

//don't even bother with this, it doesnt work because it can't update fast enough,
//left here in case a solution is found
void gyroDrive() {
	driveHalo(vexRT[Ch3],vexRT[Ch1]);
}

task driveTask (){
	PIDInit(straightStrafe, .4, .25);
	while(true){
		//Set Encoders to 0 on bumperswitch press
		if(SensorValue(bumperSwitch)==1){ //if the elevator is all the way down, set encoder to 0
			nMotorEncoder[rightEl]= 0;
			allElStop();
		}
		//Drive Multiplier
		driveMult = 1;

		//Switch between the two to switch drives
		normalDrive();
		//gyroDrive();
	}
}
