#include "PID.h"


#include <math.h>

#define WINDOW_SIZE 20
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  PID::Kp = Kp;
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  
  p_error = 0;
  i_error = 0;
  d_error = 0;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
 
}

double PID::TotalError() {
	return Kp*p_error + Ki*i_error + Kd*d_error;

}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws) {
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

void PID::Twiddle(double total_error, double parameter) {
  static double min_error = std::numeric_limits<double>::max();
  static bool is_twiddle_init = false;
  static bool reinit_param = false;
  static double prev = 0;
  cout<<"Current best error is: "<< min_error<<endl;
  cout<<"param delta is: "<<delta_p<<endl;
  if (!is_twiddle_init) {
  	min_error = total_error;
  	is_twiddle_init = true;
  	return;
  }
  if ((fabs(delta_p) > tolerance)) {
  	if (reinit_param) {
  		prev = parameter;
  		parameter += delta_p;
  		reinit_param = false;
  	} else {
  		if (total_error < min_error) {
  			delta_p *= 1.1;
  			reinit_param = true;
  			min_error = total_error;
  		} else {
  			if (fabs(prev) < fabs(parameter)) {
  				prev = parameter;
  				parameter -= 2.0 * delta_p;
  			} else {
  				prev = parameter;
  				parameter += delta_p;
  				delta_p *= 0.9;
  				reinit_param = true;
  			}
  		}
  	}
  }
}
