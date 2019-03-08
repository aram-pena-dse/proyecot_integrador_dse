/*
 ============================================================================
 Name        : Test.c
 Author      : Team 3 & 4
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float MAX; // Max manipulated value
	float MIN; // Minimum manipulated value
	float e; // Error value
	float i; // Integrator value
	float d; // Derivative value
	float KP; // Proportional constant
	float KI; // Integrator constant
	float KD; // Differential constant
	float DT; // Time constant
	float up1; // Previous proportional Output
	float out; // PID output
	float set;
	float adc;
} pid_par;

void fPID_Init(pid_par * pid){
	pid->MAX = 413.0; // Max manipulated value
	pid->MIN = 4650.0; // Minimum manipulated value
	pid->e = 0; // Error value
	pid->i = 0; // Integrator value
	pid->d = 0; // Derivative value
	pid->KP = 0.0035102; // Proportional constant
	pid->KI = 0.039448; // Integrator constant
	pid->KD = 0; // Differential constant
	pid->DT = 1; // Time constant
	pid->up1 = 0; // Previous proportional Output
	pid->out = 0; // PID output
	pid->set = 0;
	pid->adc = 0;
}

void fPID_Control(pid_par * pid) {
	float cal_result; /*! Calculation result */
	float present_err; /*! Calculation result */

	/* present error */
	present_err = pid->set - pid->adc;

	/* Integral term calculation */
	/* Add Integral terms (Ui * Ki) */
	cal_result= pid->KI * present_err;

	if (cal_result > pid->MAX)
		cal_result = pid->MAX;
	else if (cal_result < pid->MIN)
		cal_result = pid->MIN;

	/* Add Proportional terms */
	cal_result += pid->KP * present_err;

	/* Sum of instantaneous error */
	pid->i += present_err * pid->DT;

	/* Slope of error over time */
	pid->d = (present_err - pid->up1)/(pid->DT);

	/* Add Derivative terms */
	cal_result += pid->KD * pid->d;
	pid->up1 = present_err;

	/* Result check here */
	if (cal_result > pid->MAX){
		pid->out = pid->MAX;
		pid->e = -1;
	}
	else if (cal_result < pid->MIN){
		pid->out = pid->MIN;
		pid->e = -1;
	}
	else{
		pid->out = cal_result;
		pid->e = 0;
	}
}



int main (){

	pid_par* pid;
	int i = 0;
	float var = 0;

	fPID_Init(pid);

	while(1){
		fPID_Control(pid);
		var = pid->out;
		printf("%f\n", var);
	}
}
