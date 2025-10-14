#ifndef THERMAL_SYSTEM_H
#define THERMAL_SYSTEM_H

class PIDController {
public:
    PIDController(float kp, float ki, float kd, float outMin, float outMax);
};

#endif