#include "pid.hpp"

PIDController::PIDController(double kp, double ki, double kd)
: Kp(kp), Ki(ki), Kd(kd), totalError(0.0), lastError(0.0), outputMin(0), outputMax(5) {}

double PIDController::step(double current, double target) {
    double error = target - current;
    totalError += error;
    double P = Kp * error;
    double I = Ki * totalError;
    double D = Kd * (error - lastError);
    lastError = error;
    double output = P + I + D;

    if (output > outputMax) {
        output = outputMax;
    } else if (output < outputMin) {
        output = outputMin;
    }

    if (!(output >= outputMax || output <= outputMin)) {
        totalError += error;
    }

    return output;
}