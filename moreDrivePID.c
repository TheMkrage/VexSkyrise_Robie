




task PIDControllerDIF(){
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

		/*if(SensorValue[master] < pidRequestedValue - 20 && SensorValue[master] > pidRequestedValue + 20) {
			stopTask(PIDController);
		}else{
			pidRunning = true;
		}*/
		// Is PID control active
		if( pidRunning == true)  {

			// Read the sensor value
			pidSensorCurrentValue = SensorValue[ rightDrive ] + SensorValue[leftDrive];

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
			if(!enIsRunning) {
				motor[rightFront] = pidDrive;
				motor[rightBack] = pidDrive;
			}
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


void startDIFPID(int req) {
	enIsRunning = true;
	pidRequestedValue = req;
	startTask(PIDControllerDIF);
}
