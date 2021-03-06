/* Main class for drive train
In this class, there is:
- Normal Drive (driveHalo)
- Gyro Drive (gyroDrive)
This doesn't work, vex gyros do not update fast enough for this to be successful
*/

#include "PIDController.c"
#include "PID.c"

PID gyroDrivePID;
PID driveLeftDrivePID;
PID driveRightDrivePID;

float x = 0;
float y = 0;

float pastLeft = 0;
float pastRight =0;
float pastGyro = 0;

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

float cut(int x, int limit) {
	if(abs(x) < abs(limit)) {
		return 0;
	}
	return x;
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

float angVelocityPWM = 0; // How much do we want to change the motor PWM values to reach an angular velocity
float leftVelocityPWM = 0;
float rightVelocityPWM = 0;
float leftDriveVelocity = 0;
float rightDriveVelocity = 0;
float gyroAngularVelocity = 0;
float delayAmount = 50; // Delay 10ms

float MAX_ANG_VEL = 50;
float MAX_VEL = 10;
void gyroDrive2() {
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
	} else {

		writeDebugStreamLine("pastRight: %4.4f pastLeft: %4.4f pastGyro: %4.4f" , pastRight, pastLeft, pastGyro);

		leftDriveVelocity = (float)(((float)-SensorValue[leftDrive] - pastLeft) / delayAmount); // Divide by "delayAmount" so that if you change the update loop frequency, your velocities don't change
		rightDriveVelocity = (float)(((float)SensorValue[rightDrive] - pastRight) / delayAmount);
		gyroAngularVelocity = (float)(((float)-SensorValue[gyro] - pastGyro) / delayAmount);

		writeDebugStreamLine("LeftError: %4.4f rightError: %4.4f gyroError: %4.4f", ((float)SensorValue[leftDrive] - pastLeft), ((float)-SensorValue[rightDrive] - pastRight),  ((float)-SensorValue[gyro] - pastGyro));
		x += sin((SensorValue[gyro]/10) * (pi/180)) * ((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2);
		y += cos((SensorValue[gyro]/10) * (pi/180)) * ((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2);
		writeDebugStreamLine("anglerawcos:%4.4f cos: %4.4f sin: %4.4f h: %4.4f", cos((SensorValue[gyro]/10) * (pi/180)), cos(SensorValue[gyro]/10), sin(SensorValue[gyro]/10),((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2 ));
		writeDebugStreamLine("x: %i y: %i", x, y);

		pastRight = (float)SensorValue[rightDrive];
		pastLeft = (float)-SensorValue[leftDrive];
		pastGyro = (float)-SensorValue[gyro];




		// SensorValue[leftDrive] = SensorValue[rightDrive] = SensorValue[gyro] = 0;
		//writeDebugStreamLine("Left: %4.4f Right: %4.4f Ang: %4.4f", leftDriveVelocity, rightDriveVelocity, gyroAngularVelocity);

		//writeDebugStreamLine("j: %4.4f max: %4.4f", vexRT[Ch1]/127, MAX_ANG_VEL);
		float targetAngularVelocity = (float)((float) cut(vexRT[Ch1], 20) /127) * MAX_ANG_VEL;
		float targetDriveVelocity = (float)((float) cut(vexRT[Ch3], 20) /127) * MAX_VEL;
		///writeDebugStreamLine("forJoy: %4.4f, after: %4.4f", vexRT[Ch3], vexRT[Ch3]/127);
		//writeDebugStreamLine("target ang: %4.4f target drive: %4.4f", targetAngularVelocity, targetDriveVelocity);

		// During a velocity PID, you need to add the velocity error to the term modifying the speed/PWM
		angVelocityPWM = PIDRun(gyroDrivePID, targetAngularVelocity - gyroAngularVelocity);
		leftVelocityPWM = PIDRun(driveLeftDrivePID, targetDriveVelocity - leftDriveVelocity);
		rightVelocityPWM = PIDRun(driveRightDrivePID, targetDriveVelocity - rightDriveVelocity);

		float angVel = angVelocityPWM + skim(angVelocityPWM);
		float leftVel = leftVelocityPWM + skim(leftVelocityPWM);
		float rightVel = rightVelocityPWM + skim(rightVelocityPWM);

		//writeDebugStreamLine("leftVel PID: %4.4f",PIDRun(driveLeftDrivePID, targetDriveVelocity - leftDriveVelocity));
		//writeDebugStreamLine("VELTerm %4.4f", leftVelocityPWM);
		//writeDebugStreamLine("AngVelTerm %4.4f", angVelocityPWM);

		//set power to motors
		motor[leftFront]  = 127*(leftVel + angVel); // (y + x)/2
		motor[rightFront] = 127*(rightVel - angVel);
		motor[leftBack]  = 127*(leftVel + angVel);  // (y + x)/2
		motor[rightBack] = 127*(rightVel - angVel);
		//writeDebugStreamLine("left: %4.4f right: %4.4f", 127*(leftVelocityPWM + angVelocityPWM), 127*(rightVelocityPWM - angVelocityPWM));
		writeDebugStreamLine(" ");
	}

	if(vexRT[Ch4] > 40 || vexRT[Ch4] < -40) {	//Threshold for strafe joystick
		motor[strafe] = vexRT[Ch4];
		}else {
		motor[strafe] = 0;
	}
	// I don't know how fast the gyro updates on the cortex firmware, but try to match whatever frequency that is
	delay(delayAmount);

}

//don't even bother with this, it doesnt work because it can't update fast enough,
//left here in case a solution is found
void gyroDrive() {
	driveHalo(vexRT[Ch3],vexRT[Ch1]);
}




task driveTask (){
	PIDInit(straightStrafe, .01, .25);
	PIDInit(gyroDrivePID, .02, 00);
	PIDInit(driveRightDrivePID, .11, 0);
	PIDInit(driveLeftDrivePID, .11, 0);
	while(true){
		//Set Encoders to 0 on bumperswitch press
		if(SensorValue(bumperSwitch)==1){ //if the elevator is all the way down, set encoder to 0
			nMotorEncoder[rightEl]= 0;
			allElStop();
		}
		//Drive Multiplier
		driveMult = 1;

		//Switch between the two to switch drives


			gyroDrive2();

	}
}
