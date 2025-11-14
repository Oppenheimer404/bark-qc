#include <iostream>
#include "pid/pid.hpp"

int main() {
    PIDController tempController(1.0, 0.1, 1.0);

    double target = 1;
    double current = 1;

    for (int i = 0; i < 500; i++) {
        double thermalEnergy = tempController.step(current, target);

        current += thermalEnergy;

        current = current * 0.99;

        target = target * 1.01;

        double error = current - target;

        std::cout << "Temp = " << current << std::endl;
        std::cout << "Targ = " << target << std::endl;
        std::cout << "Err  = " << error << std::endl;
        std::cout << "Out  = " << thermalEnergy << std::endl;
    }

    return 0;
}