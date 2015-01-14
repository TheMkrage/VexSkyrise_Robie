
#include "AUTO_CONSTANTS.c"
//#include "AUTO_BLUE.c"
//#include "AUTO_RED.c"
//#include "AUTO_12POINT_RED.c"
#include "AUTO_RED_2..c"





const int RED_BASE_MAX = 3545;
const int RED_BASE_MIN = 3405;
const int BLUE_BASE_MAX = 2745;
const int BLUE_BASE_MIN = 2605;
const int BLUE_STRAFE_MAX = 515;
const int BLUE_STRAFE_MIN = 375;
const int RED_STRAFE_MAX = 80;
const int RED_STRAFE_MIN = 0;
const int NONE_MAX = 1295;
const int NONE_MIN = 1155;
void startauton() {
	startREDTWO();
	/*if(SensorValue(autoChoose) <= RED_BASE_MAX && SensorValue(autoChoose) >= RED_BASE_MIN){
		startRed();
	}else if(SensorValue(autoChoose) <= BLUE_BASE_MAX && SensorValue(autoChoose) >= BLUE_BASE_MIN) {
		startBlue();
	}else if(SensorValue(autoChoose) <= BLUE_STRAFE_MAX && SensorValue(autoChoose) >= BLUE_STRAFE_MIN) {
		motor[Strafe] = 127;
		wait1Msec(1000);
		motor[Strafe] = -127;
		wait1Msec(1000);
		motor[Strafe] = 0;
	}else if(SensorValue(autoChoose) <= RED_STRAFE_MAX && SensorValue(autoChoose) >= RED_STRAFE_MIN) {
		motor[Strafe] = -127;
		wait1Msec(1000);
		motor[Strafe] = 127;
		wait1Msec(1000);
		motor[Strafe] = 0;
	}else if(SensorValue(autoChoose) <= NONE_MAX && SensorValue(autoChoose) >= NONE_MIN) {

	}*/
}
