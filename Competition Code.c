#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    autoChoose,     sensorPotentiometer)
#pragma config(Sensor, in5,    lineFolLeft,    sensorLineFollower)
#pragma config(Sensor, in6,    lineFolRight,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  gyroBumper,     sensorTouch)
#pragma config(Sensor, dgtl2,  bumperSwitch,   sensorTouch)
#pragma config(Sensor, dgtl3,  frontSonar,     sensorSONAR_raw)
#pragma config(Sensor, dgtl5,  rightDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftDrive,      sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  bigLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, litLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, led1,           sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  ElEn,           sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rightEl,       tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port2,           leftEl,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           bLeftEl,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightClaw,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           strafe,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightFront,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftFront,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          bRightEl,      tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma systemFile
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

//#pragma config(Motor,  port5,           Strafe,        tmotorVex393_MC29, openLoop)
int rightPIDAngle;
int leftPIDAngle;
int rightPIDSonar;
int leftPIDSonar;


#include "Vex_Competition_Includes.c"



#include "elavatorTask.c"
#include "driveTask.c"
#include "clawTask.c"

#include "AUTO.c"



void pre_auton() {
	resetEn();
}

#define abs(X) ((X < 0) ? -1 * X : X)
//vex Forum PID Attempt
void driveStraightDistance(int tenthsOfIn, int masterPower)
{
	//int tickGoal = (42 * tenthsOfIn) / 10;
	int tickGoal = tenthsOfIn;
	//This will count up the total encoder ticks despite the fact that the encoders are constantly reset.
	int totalTicks = 0;

	//Initialise slavePower as masterPower - 5 so we don't get huge error for the first few iterations. The
	//-5 value is based off a rough guess of how much the motors are different, which prevents the robot from
	//veering off course at the start of the function.
	int slavePower = masterPower - 5;

	int error = 0;

	int kp = 5;

	SensorValue[leftDrive] = 0;
	SensorValue[rightDrive] = 0;

	//Monitor 'totalTicks', instead of the values of the encoders which are constantly reset.
	while(abs(totalTicks) < tickGoal) {
		//Proportional algorithm to keep the robot going straight.

		writeDebugStreamLine("Left(MASTER): %i Right(SLAVE): %i",SensorValue[leftDrive], SensorValue[rightDrive]);
		writeDebugStreamLine("ERROR: %i", error);
		writeDebugStreamLine("master: %i slave: %i", masterPower, slavePower);
		writeDebugStreamLine(" ");
		motor[leftFront] = slavePower;
		motor[leftBack] = slavePower;
		motor[rightFront] = masterPower;
		motor[rightBack] = masterPower;

		error = abs(SensorValue[rightDrive]) - abs(SensorValue[leftDrive]);

		slavePower += error / kp;

		//SensorValue[leftDrive] = 0;
		//SensorValue[rightDrive] = 0;

		wait1Msec(100);

		//Add this iteration's encoder values to totalTicks.
		totalTicks  = abs(SensorValue[rightDrive]);
	}
	stopDrive();
}

task autonomous() {
	resetEn();
	startauton();
	wait1Msec(100000);
	driveStraightDistance(900,63);
	wait1Msec(1000);
	writeDebugStreamLine("----------------------");
	driveStraightDistance(900,-63);
	stopDrive();
}

const int dreamAngle = 525;

task usercontrol(){
	nMotorEncoder[rightEl] = 0;
	//driveStraightDistance(100, 63);
	resetEn();
	startTask( driveTask );
	startTask( clawTask );
	startTask( elevatorTask );
	while(true) {
		//writeDebugStreamLine("Front Sonar: %i", SensorValue[frontSonar]);
		if(vexRT[Btn7D] == 1) {
			startTask(autonomous);
		}
		if(vexRT[Btn7L] == 1) {
			//stopTask(autonomous);
		}
		if(SensorValue(gyroBumper) == 1) {
			resetGyro();
			SensorValue[led1] = true;
			wait1Msec(750);
			SensorValue[led1] = false;
		}
		if(SensorValue(gyro) > dreamAngle) {
			SensorValue[bigLED] = 1;
			SensorValue[litLED] = 0;
			}else if(SensorValue(gyro) < dreamAngle) {
			SensorValue[litLED] = 1;
			SensorValue[bigLED] = 0;
			}else if(SensorValue(gyro) == dreamAngle) {
			SensorValue[litLED] = 1;
			SensorValue[bigLED] = 1;
		}

	}
}
