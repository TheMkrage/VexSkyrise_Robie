
#define PID_SENSOR_INDEX    myEncoder

const int PID_DRIVE_MAX = 127;
const int PID_DRIVE_MIN = -127;
const int PID_INTEGRAL_LIMIT = 50;

bool enIsRunning = false;
bool foreward;

const int RIGHTFRONT = -1;
const int RIGHTBACK = -1;
const int LEFTFRONT = 1;
const int LEFTBACK = 1;


float pidRequestedValue;
tSensors master;
tSensors slave;
task PIDControllerEnFriend(){
	float pid_Kp = .6;
	float  pid_Ki = 0.0;
	float  pid_Kd = 0.001;
	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	bool pidRunning = true;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastError  = 0;
	pidIntegral   = 0;

	while(1){

		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = SensorValue[ master ];

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
			writeDebugStreamLine("P: %3.3f, I: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError), (pid_Ki * pidIntegral), (pid_Kd * pidDerivative),pidDrive);

			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			motor[leftFront] = LEFTFRONT*pidDrive;
			motor[leftBack] = LEFTBACK*pidDrive;

			/*if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
			pidRunning = false;
			}*/
			writeDebugStreamLine("right: %d, left: %d", SensorValue[rightDrive], SensorValue[leftDrive]);
			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}

task PIDController(){
	float pid_Kp = 0.4;
	float  pid_Ki = 0.0;
	float  pid_Kd = 1.0;
	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	bool pidRunning;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastError  = 0;
	pidIntegral   = 0;

	while(1){

		if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
			stopTask(PIDController);
			}else{
			pidRunning = true;
		}
		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = SensorValue[ master ];

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
			writeDebugStreamLine("P: %3.3f, I: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError), (pid_Ki * pidIntegral), (pid_Kd * pidDerivative),pidDrive);

			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			motor[leftFront] = pidDrive;
			motor[leftBack] = pidDrive;

				motor[rightFront] = -pidDrive;
				motor[rightBack] = -pidDrive;

			if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
				pidRunning = false;
			}

			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}

void startPID(int aim, tSensors master1) {
	pidRequestedValue = aim;
	master = master1;
	enIsRunning = false;
	startTask(PIDController);
}

void startPID(int aim, tSensors master1, bool b) {
	writeDebugStream("Started with %d", master1);
	pidRequestedValue = aim;
	master = master1;

	startTask(PIDControllerEnFriend);
}

task PIDControllerEn(){
	float pid_Kp = 2;
	float  pid_Ki = 0.0;
	float  pid_Kd = 1.5;

	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	bool pidRunning = true;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastError  = 0;
	pidIntegral   = 0;
	startPID(pidRequestedValue, master, true);

	wait1Msec(200);

	while(1){


		if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
			stopTask(PIDControllerEn);
			}else{
			pidRunning = true;
		}
		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = SensorValue[ slave ];

			// calculate error
			if(-SensorValue[master] -70< -pidRequestedValue) {
				pidError = pidSensorCurrentValue - (-SensorValue[ master ]);
				}else{

				pidError = pidSensorCurrentValue - (-SensorValue[ master ]-70);
			}

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
			writeDebugStreamLine("SLAVE: P: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError),  (pid_Kd * pidDerivative),pidDrive);

			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			motor[rightFront]= RIGHTFRONT*pidDrive;
			motor[rightBack] = RIGHTBACK* pidDrive;

			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}



void startPID(int aim, tSensors master1, tSensors slave1, bool b) {
	enIsRunning = true;
	pidRequestedValue = aim;
	slave = slave1;
	master = master1;
	foreward = b;
	startTask(PIDControllerEn);
}



/*task PIDControllerEnDifference(){
	float  pid_Kp = 0.4;
	float  pid_Ki = 0.0;
	float  pid_Kd = 0.0;

	float  pidSensorCurrentValueR;
	float  pidSensorCurrentValueL;

	float  pidErrorR;
	float  pidErrorL;
	float  pidLastErrorR;
	float  pidLastErrorL;
	float  pidIntegral = 0;
	float  pidDerivativeR;
	float  pidDerivativeL;
	float  pidDriveR;
	float  pidDriveL;
	bool pidRunning = true;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastErrorR  = 0;
	pidLastErrorL = 0;
	pidIntegral   = 0;

	while(1){
		//startPID(pidRequestedValue, master);


		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValueR = SensorValue[ rightDrive ];
			pidSensorCurrentValueL = SensorValue[ leftDrive ];

			// calculate error
			pidErrorR = pidSensorCurrentValueR - pidRequestedValue;
			pidErrorL = pidSensorCurrentValueL - pidRequestedValue;
			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivativeR = pidErrorR - pidLastErrorR;
			pidDerivativeL = pidErrorL - pidLastErrorL;

			pidLastErrorR  = pidErrorR;
			pidLastErrorL  = pidErrorL;

			// calculate drive
			pidDriveR = (pid_Kp * pidErrorR) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivativeR);
			pidDriveL = (pid_Kp * pidErrorL) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivativeL);
			//writeDebugStreamLine("P: %3.3f, I: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError), (pid_Ki * pidIntegral), (pid_Kd * pidDerivative),pidDrive);

			// limit drive
			if( pidDriveR > PID_DRIVE_MAX )
				pidDriveR = PID_DRIVE_MAX;
			if( pidDriveR < PID_DRIVE_MIN )
				pidDriveR = PID_DRIVE_MIN;
			if( pidDriveL > PID_DRIVE_MAX )
				pidDriveL = PID_DRIVE_MAX;
			if( pidDriveL < PID_DRIVE_MIN )
				pidDriveL = PID_DRIVE_MIN;
			// send to motor
			motor[rightFront] = pidDriveR;
			motor[rightBack] = pidDriveR;
			motor[leftFront] = pidDriveL;
			motor[leftBack] = pidDriveL;
			if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
				pidRunning = false;
			}

			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidErrorR      = 0;
			pidLastErrorR  = 0;
			pidIntegral   = 0;
			pidDerivativeR = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}*/

task PIDControllerAngleDrive(){
	float pid_Kp = 0.15;
	float  pid_Ki = 0.0;
	float  pid_Kd = 0.0;
	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	bool pidRunning = true;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastError  = 0;
	pidIntegral   = 0;

	while(1){


		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = SensorValue[ master ];

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedValue;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
			writeDebugStreamLine("Angle: P: %3.3f, I: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError), (pid_Ki * pidIntegral), (pid_Kd * pidDerivative),pidDrive);

			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			leftPIDAngle = pidDrive;
			rightPIDAngle = pidDrive;

			//if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
			//pidRunning = false;
			//	}

			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}

void startPIDAngle(int aim, tSensors master1) {
	pidRequestedValue = aim;
	master = master1;
	enIsRunning = false;
	startTask(PIDControllerAngleDrive);
}
int pidRequestedSonar = 0;

task PIDSonar() {
	float pid_Kp = 0.2;
	float  pid_Ki = 0.0;
	float  pid_Kd = 0.4;
	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	bool pidRunning = true;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastError  = 0;
	pidIntegral   = 0;

	while(1){

		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = SensorValue[ frontSonar ];

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedSonar;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
			writeDebugStreamLine("Sonar: P: %3.3f, I: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError), (pid_Ki * pidIntegral), (pid_Kd * pidDerivative),pidDrive);

			// limit drive
			if( pidDrive > 90 )
				pidDrive = 90;
			if( pidDrive < -90 )
				pidDrive = -90;

			// send to motor
			leftPIDSonar = pidDrive;
			rightPIDSonar = pidDrive;

			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}

void startPIDSonar(int aim, tSensors master1) {
	pidRequestedSonar = aim;
	//master = master1;
	enIsRunning = false;
	startTask(PIDSonar);
}
//__________________________________________________________________________________________________________________________________________________________________
int pidRequestedEl = 0;
task PIDControllerEl(){
	float pid_Kp = -0.90;
	float  pid_Ki = 0.0;
	float  pid_Kd = 0.0;
	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	bool pidRunning = true;

	// If we are using an encoder then clear it
	//if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	// SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init vars
	pidLastError  = 0;
	pidIntegral   = 0;

	while(1){


		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = abs(nMotorEncoder(rightEl));

			// calculate error
			pidError = pidSensorCurrentValue - pidRequestedEl;

			// integral - if Ki is not 0
			if( pid_Ki != 0 )
			{
				// If we are inside controlable window then integrate the error
				if( abs(pidError) < PID_INTEGRAL_LIMIT )
					pidIntegral = pidIntegral + pidError;
				else
					pidIntegral = 0;
			}
			else
				pidIntegral = 0;

			// calculate the derivative
			pidDerivative = pidError - pidLastError;
			pidLastError  = pidError;

			// calculate drive
			pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
			writeDebugStreamLine("El: P: %3.3f, I: %3.3f, D: %3.3f, drive: %3.3f" ,(pid_Kp * pidError), (pid_Ki * pidIntegral), (pid_Kd * pidDerivative),pidDrive);
			writeDebugStreamLine("El: %i", abs(nMotorEncoder(rightEl)));
			// limit drive
			if( pidDrive > PID_DRIVE_MAX )
				pidDrive = PID_DRIVE_MAX;
			if( pidDrive < PID_DRIVE_MIN )
				pidDrive = PID_DRIVE_MIN;

			// send to motor
			motor[leftEl] = pidDrive;
			motor[bLeftEl] =pidDrive;
			motor[rightEl] = pidDrive;
			motor[bRightEl] = pidDrive;



			}else{
			writeDebugStreamLine("Stopped");
			// clear all
			pidError      = 0;
			pidLastError  = 0;
			pidIntegral   = 0;
			pidDerivative = 0;
			stopDrive();
		}

		wait1Msec(25);
	}
}

void startPIDEl(int aim, tMotor master1) {
	pidRequestedEl = aim;
	//master = master1;
	enIsRunning = false;
	startTask(PIDControllerEl);
}
