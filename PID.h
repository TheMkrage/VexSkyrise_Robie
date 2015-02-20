

struct PID {
	float kP;
	float kD;

	float previousError;
};

void PIDInit(struct PID controller, float kP, float kD);
float PIDRun(struct PID controller, float error);
