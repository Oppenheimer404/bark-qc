#ifndef SIM_H
#define SIM_H

class ThermalBody
{
private:
    // * Heating properties
    double ambientTempF; // ? F
    
    // * Mass properties
    double solidMassKg; // ? kg
    double liquidMassKg; // ? kg
    
    // * Evaporation & heat loss properties
    double surfaceAreaCm2; // ? cm^2

    const double solidMassCapacityJKgF;
    const double liquidMassCapacityJKgF;

    double calculateSurfaceArea(
        double diameterCm,
        double solidKg,
        double liquidKg
    );

    double calculateHeatGainF(double joules);
    double calculateHeatLossF(double currentTempF, double deltaTimeS);

public:
    ThermalBody(
        double ambientTempF,
        double diameterCm,
        double solidKg,
        double liquidKg
    );

    // * Returns new temperature in Fahrenheit
    double simulate(
        double currentTempF,
        double powerWatts,
        int deltaTimeS
    );

    // * Returns mass in kg
    double getLiquidMass() const { return liquidMassKg; }
    double getSolidMass() const { return solidMassKg; }
    double getTotalMass() const { return solidMassKg + liquidMassKg; }
};

#endif