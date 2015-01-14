int offset = 0; //for gyro
void moveToSonarSensorForward(int sonar) {
	resetEn();

	startPIDAngle(0 + offset, gyro);
	startPIDSonar(sonar, frontSonar);
	writeDebugStreamLine("Sonar: %i sonar: %i",abs(SensorValue(frontSonar)), sonar );
	while(abs(SensorValue(frontSonar)) > sonar ) {
		int rightSpeed = rightPIDSonar - rightPIDAngle;
		int leftSpeed = leftPIDSonar  + leftPIDAngle;
		writeDebugStreamLine("right: %i, left: %i", rightSpeed, leftSpeed);
		writeDebugStreamLine("----");
		motor[leftFront]  = leftSpeed - 20; // (y + x)/2
		motor[rightFront] = rightSpeed - 20;//ross
		motor[leftBack]  = leftSpeed - 20;  // (y + x)/2
		motor[rightBack] = rightSpeed - 20;
		wait1Msec(25);
	}
	stopTask(PIDControllerAngleDrive);
	stopTask(PIDSonar);
	stopDrive();
}

void moveToSonarSensorBackward(int sonar) {
	resetEn();
	clearTimer(T4);

	startPIDAngle(0 + offset, gyro);
	startPIDSonar(sonar, frontSonar);
	writeDebugStreamLine("Sonar: %i sonar: %i",abs(SensorValue(frontSonar)), sonar );
	while(abs(SensorValue(frontSonar)) < sonar && time1[T4] < 2000) {
		int rightSpeed = rightPIDSonar - rightPIDAngle;
		int leftSpeed = leftPIDSonar  + leftPIDAngle;
		writeDebugStreamLine("right: %i, left: %i", rightSpeed, leftSpeed);
		writeDebugStreamLine("----");
		motor[leftFront]  = leftSpeed + 20; // (y + x)/2
		motor[rightFront] = rightSpeed + 20;//ross
		motor[leftBack]  = leftSpeed + 20;  // (y + x)/2
		motor[rightBack] = rightSpeed + 20;
		wait1Msec(25);
	}
	stopTask(PIDControllerAngleDrive);
	stopTask(PIDSonar);
	stopDrive();
}

void moveElTo(int en) {
	stopTask(PIDControllerEl);
	if(en == 0) {
		bool temp = true;
		clearTimer(T2);
		while(SensorValue[bumperSwitch] == 0 && temp) {
			allElOnMaxDown();
			if(time1[T2] > 1500) {
				temp = false;
			}
		}
		allElStop();
	}else {
		startPIDEl(en, rightEl);
	}
}
void startREDTWO() {
	clearTimer(T1);


	//move up a little
	moveElTo(EL_LITTLE_ELEVATOR_TWO);

	wait1Msec(600);

	//close then autoclaw
	motor[rightClaw] = 127;


	wait1Msec(800);

	//move up a little more
	moveElTo(EL_SLIGHTLY_ABOVE_HOLDER_TWO);

	motor[rightClaw] = 30;

	wait1Msec(600);

	//go to 2800 away
	moveToSonarSensorBackward(TO_DROP_MUSTARD_TWO);
	wait1Msec(500);

	writeDebugStreamLine(" ");
	writeDebugStreamLine("------------------------------STOP-----------------------------------------------------------------------------------------------------------------");
	writeDebugStreamLine(" ");

	//bring el Down
	moveElTo(0);

	wait1Msec(500);
	//open claw
	motor[rightClaw] = -127;
	wait1Msec(500);
	motor[rightClaw] = -50;

	wait1Msec(300);
	moveElTo(450);

	wait1Msec(800);

	moveToSonarSensorForward(TO_MUSTARD_HOLDER_TWO);
	wait1Msec(300);

	moveElTo(0);
	writeDebugStreamLine("--________________________________--");

	//move back to in front of mustard
	moveToSonarSensorForward(TO_MUSTARD_HOLDER_TWO);

	//close on mustard again
	motor[rightClaw] = 127;
	wait1Msec(600);
	motor[rightClaw] = 30;

	moveElTo(EL_SECOND_HEIGHT_TWO);

	wait1Msec(800);

	//go to 2800 away again
	moveToSonarSensorBackward(TO_DROP_SECOND_MUSTARD_TWO);
	wait1Msec(600);

	stopTask(PIDControllerEl);
	//bring el Down again
	clearTimer(T3);
	while(time1[T3] <300) {
		motor[rightEl] = -63;
		motor[leftEl] = -63;
		motor[bRightEl] = -63;
		motor[bLeftEl] = -63;
	}
	allElStop();
	wait1Msec(600);

	//open claw again
	motor[rightClaw] = -127;
	wait1Msec(600);
	motor[rightClaw] = -20;

	wait1Msec(700);

	moveBackward(63);
	wait1Msec(1300);
	stopDrive();
	//if(time1[T1] > 15000) break;

}
