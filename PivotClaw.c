


bool killSwitch = false;
bool killSwitchDrive = false;

task clawTask () {
	while(1){

		//The Claw
		//claw controls
		if(vexRT[Btn6UXmtr2] == 1) {
			motor[rightClaw] = 127;

			}else if(vexRT[Btn6DXmtr2] == 1) {
			motor[rightClaw] = -127;

			}else if(vexRT[Btn5UXmtr2] == 1) {
			motor[rightClaw] = 20;
			}else {
			motor[rightClaw] = 0;
		}

		if(vexRT[Btn5DXmtr2] == 1) {
			killSwitch = true;
		}
		if(abs(vexRT[Ch1Xmtr2]) > 20) {
			motor[TrackMotor] = vexRT[Ch1Xmtr2];
		}else {
			motor[TrackMotor] = 0;
		}
		if(killSwitch) {
			allElStop();
			stopTask(  elevatorTask );
			startTask( elevatorTask );
			killSwitch =  false;
		}
		if(killSwitchDrive) {
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
