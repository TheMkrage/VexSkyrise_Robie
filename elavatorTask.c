

#include "Basic Drive and Elavaotr Methods.c"


const int EL_2 = 601;
const int EL_3 = 1315;
const int EL_4 = 2125;
const int EL_5 = 194;

task elevatorTask () {
	bool resetMotor=false; //bottom
	bool level1=false;
	bool level2=false;
	bool level3=false;
	bool level4=false;
	while(1){

		while(resetMotor == true){
			if(SensorValue(bumperSwitch) == 0){
				allElOnMaxDown();
				}else{
				resetMotor=false;
			}
		}
		while(level1==true){

			if(nMotorEncoder[rightEl] <= EL_2){
				allElOnMax();
				}else{
				level1=false;
			}

		}
		while(level2==true){
			if(nMotorEncoder[rightEl] <= EL_3){
				allElOnMax();
				}else{
				level2=false;
			}
		}
		while(level3==true){
			if(nMotorEncoder[rightEl] <= EL_4){
				allElOnMax();
				}else{
				level3=false;
			}
		}
		while(level4==true) {
			if(nMotorEncoder[rightEl] <= EL_5) {
				allElOnMax();
				}else{
				level4 = false;
				}
			}
			//The Elavator

			//Up
			if(vexRT[Ch3Xmtr2] > 20) {//if joystick is pressed more than 20, 20 is threshold, move vator
				int ElRate = vexRT[Ch3Xmtr2];
				motor[rightEl] = ElRate;
				motor[leftEl]= ElRate;
				motor[bRightEl] = ElRate;
				motor[bLeftEl] = ElRate;

				//DOWN
			}else if(vexRT[Ch3Xmtr2]< -20) {
				if(SensorValue(bumperSwitch) == 0) {//if the switch is up
					//let it go down if the button is not pressed
					int ElRate = vexRT[Ch3Xmtr2];
					motor[rightEl] = ElRate;
					motor[leftEl]= ElRate;
					motor[bRightEl] = ElRate;
					motor[bLeftEl] = ElRate;
					}else {
					allElStop(); //if switch is pressed, stop
				}
				}else {//if not then set stop elavators (if no joystick is pressed
				allElStop();
			}

			//Automatic Elavator buttons
			if(vexRT[Btn8DXmtr2] == 1) {//2
				level1=true;
				}else if(vexRT[Btn8RXmtr2] == 1) {
				level2=true;
				}else if(vexRT[Btn8UXmtr2] == 1) {//4
				level3=true;
				}else if(vexRT[Btn8LXmtr2] == 1) {//3
				resetMotor=true;

				//to be used in future for other encoder spots
				}else if(vexRT[Btn7DXmtr2] == 1) { //1
				level4 = true;
				}else if(vexRT[Btn7RXmtr2] == 1) {//2

				}else if(vexRT[Btn7UXmtr2] == 1) {//3


		}
	}
}
