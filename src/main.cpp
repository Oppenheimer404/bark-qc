#include <iostream>
#include <thread>
#include <chrono>
#include "pid/pid.hpp"
#include "sim/sim.hpp"

using namespace std;

int main() {
    // * Create PIDController object with basic PID values
    double kP = 5.0, kI = 0.01, kD = 1.0;
    PIDController tempController(
        kP,
        kI,
        kD
    );

    // * Create ThermalBody simulation mass object with standard values
    double ambientTempF = 70, currentTempF = 70;
    double solidMassKg = 0.345, liquidMassKg = 0.140;
    double diameterCm = 20;
    ThermalBody mass(
        ambientTempF,
        diameterCm,
        solidMassKg,
        liquidMassKg
    );

    // * Set maximum thermal output for simulation
    double maximumEnergyJ = 1000;

    // TODO: Replace this
    double degreesPerSecondF = 0.1, targetTempF = 180, maxTempF = 310;
    
    // * Run simulation
    int simulationStepS = 1, simulationDurationM = 50;
    for (
        // * The simulation always starts at step 0
        int simulationStep = 0;
        // * The simulation will run while:
        // * time elapsed in seconds (<) simulation duration in seconds
        // ? ( simulationStep * simulationStepS ) time elapsed in seconds
        // ? ( simulationDurationM * 60 ) simulation duration in seconds
        ( simulationStep * simulationStepS ) < ( simulationDurationM * 60 );
        simulationStep++
    ) {
        // TODO: Replace this
        if ( !( currentTempF < targetTempF ) ) {
            targetTempF += degreesPerSecondF;
        }
        if ( targetTempF > maxTempF ) {
            targetTempF = maxTempF;
        }

        double appliedEnergy = tempController.run( currentTempF, targetTempF );
        double joulesEnergy = ( appliedEnergy * maximumEnergyJ );

        currentTempF = mass.simulate(
            currentTempF,
            joulesEnergy,
            simulationStepS
        );

        cout << "> " << simulationStep  << endl;
        cout << "Targ = " << targetTempF << endl;
        cout << "Temp = " << currentTempF << endl;
        cout << "Outp = " << joulesEnergy / maximumEnergyJ << endl;
        cout << "Mass = " << mass.getTotalMass() << endl;
        cout << " Liq = " << mass.getLiquidMass() << endl;

        this_thread::sleep_for(
            chrono::milliseconds( ( simulationStepS * 10 ) )
        );
    }

    return 0;
}