#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	float e /*! Error value */;
	float i /*! Integrator value */;
	float max /*! Max manipulated value */;
	float min /*! Miniumum manipulated value */;
	float kp /*! Proportional constant */;
	float ki /*! Integrator constant */;
	float kd /*! Differential constant */;
} pid_control;

/*! Initialize data in PID structure.*/
void f_pid_init(pid_control * p, float min, float max) {
	//memset(p, 0, sizeof(pid_control));
	p->min = min;
	p->max = max;
	p->kp = 0.0035102;
	p->ki = 0.039448;
}

/*! Updates the manipulated variable
 * based on the PID loop current state.
 */
float f_pid_control(float set_point, float process_variable, pid_control * pid) {

	// Variables declaration
	float present_error;
	float result;
	float temp_integrator;

	// Values setup
	present_error = pid->e;
	pid->e = set_point - process_variable;
	temp_integrator = pid->i + pid->e;

	// Bound integral
	result = (pid->kp * pid->e) + (pid->ki * temp_integrator) + (pid->kd * (present_error - pid->e));
	if ((result < pid->max) && (result > pid->min))
		pid->i = temp_integrator;
	else if (result > pid->max)
		result = pid->max;
	else if (result < pid->min)
		result = pid->min;

	return result;
}

int main() {

	pid_control* pid_init;
	//int i = 0;
	//float value = 0;
	float min_value = 413;
	float max_value = 4650;
	float set_point = 200;
	float adc_value = 245;

	f_pid_init(pid_init, min_value, max_value);

	/*
	while (i < 2) {
		value = f_pid_control(set_point, adc_value, pid_init);
		i++;
		printf("%f \n", value);
	}
*/

	while (1) {
		f_pid_control(set_point, adc_value, pid_init);
	}

}
