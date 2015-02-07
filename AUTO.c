
task autoClock() {
	clearTimer(T4);
	while(time1[T4] < 14700) {

	}
	stopTask(autonomous);
	allElStop();
	motor[rightClaw] = 0;
	moveBackward(127);
	wait1Msec(300);
	stopDrive();
}

#include "AUTO_CONSTANTS.c"
#include "AUTO_RED.c"
#include "AUTO_BLUE.c"

bool manualPickAuto = false;
void startauton() {
	if(manualPickAuto) {
		startRed();
		return;
	}


	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	switch(count){
	case 0:
		startRed8();
		break;
	case 1:
		startBlue8();
		break;
	case 2:
		startRed12();
		break;
	case 3:
		startBlue12();
		break;
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
	//------------- End of Robot Movement Code -----------------------
}
