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
//Don't worry, the LCD uses UART2 by default so there is no need to configure that. Thanks RobotC.

//Set To VEX Skyrise Competition
#pragma systemFile
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

//Used For Angle and Sonar PID Values
int rightPIDAngle;
int leftPIDAngle;
int rightPIDSonar;
int leftPIDSonar;

//Necessary File
#include "Vex_Competition_Includes.c"

//Tasks
#include "ElevatorTask.c"
#include "DriveTask.c"
#include "ClawTask.c"

//LCD And Auto
#include "LCDAuto.c"
#include "AUTO.c"

//Ran Before Auto
void pre_auton() {
	resetEn();
}



//Ran in Auto
task autonomous() {
	//Reset Encoders and then run the begin auto method found in AUTO.c
	resetEn();
	startauton();
	stopDrive();
}

//Ran in Teleop
task usercontrol(){
	//Clear LCD and Reset Sensors, then begin teleop
	clearLCDLine(0);
	resetEn();
	resetGyro();
	nMotorEncoder[rightEl] = 0;

	//Start the tasks that control each aspect of the robot
	startTask( driveTask );
	startTask( clawTask );
	startTask( elevatorTask );

	//LCD Screen Task
	startTask( runLCD);

	//The Debug Loop, not used for moving the robot, but for misc things that dont go in any other tasks
	while(true) {
		bool testingAuto = true;
		if(vexRT[Btn7D] == 1 && testingAuto) { //When Testing Auto, make the boolean true
			//Stop All and Begin Auto
			stopTask( driveTask);
			stopTask(elevatorTask);
			stopTask(clawTask);
			startTask(autonomous);
		}

		if(vexRT[Btn7R] == 1) {
			playSoundFile("4.wav");
		}
		if(SensorValue(gyroBumper) == 1) { //if the gyro reset button is pressed, reset the gyro
			 PlaySoundFile("1.wav");
			resetGyro();
			//PlaySoundFile("gyroReset.wav");
			//flash LED to show that it is done
			SensorValue[led1] = true;
			wait1Msec(750);
			SensorValue[led1] = false;
		}
	}
}
