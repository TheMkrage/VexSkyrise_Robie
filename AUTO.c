
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

//This is called at the beginning of auto
void startauton() {
	if(manualPickAuto) { //in case you want to manually select auto
		startRed8();
		return;
	}


	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	//this switch case chooses the auto to run based off of the LCD Screen's choice
	//to see how count is choosen, reference LCDAuto.c
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
		startBlue2Mustard();
		break;
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
	//------------- End of Robot Movement Code -----------------------
}
