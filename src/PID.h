#ifndef PID_H
#define PID_H
#include <uWS/uWS.h>
class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  float tolerance;
  double delta_p;
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

 void Twiddle(double total_error, double hyperparameter);


   
  void Restart(uWS::WebSocket<uWS::SERVER> ws);
};

#endif /* PID_H */
