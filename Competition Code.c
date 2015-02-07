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

#include "LCDAuto.c"
#include "AUTO.c"

void pre_auton() {
	resetEn();
}

task autonomous() {
	resetEn();
	startauton();
	stopDrive();
}

task usercontrol(){
	clearLCDLine(0);

	nMotorEncoder[rightEl] = 0;
	//driveStraightDistance(100, 63);
	resetEn();
	startTask( driveTask );
	startTask( clawTask );
	startTask( elevatorTask );

	startTask( runLCD);
	while(true) {
		//writeDebugStreamLine("Front Sonar: %i", SensorValue[frontSonar]);
		if(vexRT[Btn7D] == 1) {
			stopTask( driveTask);
			stopTask(elevatorTask);
			stopTask(clawTask);
			startTask(autonomous);
		}
		//displayLCDCenteredString(0, "HOWDY");
		if(vexRT[Btn7L] == 1) {
			//stopTask(autonomous);
		}

		if(SensorValue(gyroBumper) == 1) {
			resetGyro();
			SensorValue[led1] = true;
			wait1Msec(750);
			SensorValue[led1] = false;
		}//parmesan
	}
}
