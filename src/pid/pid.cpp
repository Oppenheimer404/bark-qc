#include "pid.hpp"

PIDController::PIDController(
    double kp, double ki, double kd
):
Kp(kp), Ki(ki), Kd(kd),
totalError(0.0), lastError(0.0),
outputMin(0), outputMax(100)
{}

double PIDController::run(double current, double target) {

    // * Calculate PID values in full
    double error = target - current;
    double P = Kp * error;
    double I = Ki * totalError;
    double D = Kd * (error - lastError);
    double outputPID = P + I + D;

    // * Clamp PID output between min and max
    if (outputPID > outputMax) {
        outputPID = outputMax;
    } else if (outputPID < outputMin) {
        outputPID = outputMin;
    }

    // * Accumulate error only if outputPID isn't saturated
    if ( !( ( outputPID > outputMax ) || ( outputPID < outputMin ) ) ) {
        totalError += error;
    }

    // * Save previous error value for derivitive calculation
    lastError = error;

    // * Convert to percentage value from default ( 0 - 100 )
    outputPID = ( outputPID / 100 );
    return outputPID;
}