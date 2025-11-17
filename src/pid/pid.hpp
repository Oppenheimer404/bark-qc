#ifndef PID_H
#define PID_H

class PIDController
{
private:
    double Kp, Ki, Kd;
    double totalError, lastError;
    double outputMin, outputMax;
public:
    PIDController(double Kp, double Ki, double Kd);
    double run(double current, double target);
};

#endif