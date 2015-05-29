/* This class controls the claw and all its contents */

//Killswitches
bool killSwitch = false;
bool killSwitchDrive = false;

task clawTask () {
	while(true){

		//The Claw
		//Claw controls
		if(vexRT[Btn6UXmtr2] == 1) { //close
			if(!bSoundActive) {
				playSoundFile("2.wav");

			}

			motor[rightClaw] = 127;

			}else if(vexRT[Btn6DXmtr2] == 1) { //open
			if(!bSoundActive) {
				//playSoundFile("3.wav");
			}
			motor[rightClaw] = -127;

			}else if(vexRT[Btn5UXmtr2] == 1) { //autoclaw. hold to keep skyrise in place and not burn out motors
			motor[rightClaw] = 20;
			}else {
			motor[rightClaw] = 0;
		}

		if(vexRT[Btn5DXmtr2] == 1) {//kills elevator
			killSwitch = true;
		}

		if(killSwitch) { //kill elevator
			allElStop();
			stopTask(  elevatorTask );
			startTask( elevatorTask );
			killSwitch =  false;
		}
		if(killSwitchDrive) { //kill drive
			motor[rightBack] = 0;
			motor[rightFront] = 0;
			motor[leftBack] = 0;
			motor[leftFront] = 0;
			stopTask( driveTask );
			startTask( driveTask );
			killSwitchDrive = false;
		}

	}
}
