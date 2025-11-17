#include "sim.hpp"
#include <cmath>

ThermalBody::ThermalBody(
    double ambientTempF,
    double diameterCm,
    double solidKg,
    double liquidKg
):
ambientTempF(ambientTempF),
solidMassKg(solidKg),
liquidMassKg(liquidKg),
surfaceAreaCm2(ThermalBody::calculateSurfaceArea(
    diameterCm,
    solidKg,
    liquidKg
)),
solidMassCapacityJKgF(691),
liquidMassCapacityJKgF(2326)
{}

double ThermalBody::simulate(
    double currentTempF,
    double powerWatts,
    int deltaTimeS
) {
    double deltaHeatGainF = calculateHeatGainF(
        powerWatts * deltaTimeS
    );

    double deltaHeatLossF = calculateHeatLossF(
        currentTempF,
        deltaTimeS
    );

    double newTempF = currentTempF + deltaHeatGainF - deltaHeatLossF;
 
    return newTempF;
}

double ThermalBody::calculateSurfaceArea(
    double diameterCm,
    double solidKg,
    double liquidKg
) {
    double liquidVolumeCm3 = liquidKg / 0.001;
    double solidVolumeCm3 = solidKg / 0.0011;
    double totalVolumeCm3 = liquidVolumeCm3 + solidVolumeCm3;
    double surfaceAreaTopCm2 = ((M_PI) * pow( ( diameterCm / 2 ), 2) );
    double surfaceAreaSideCm2 = (
        ((M_PI) * diameterCm ) * ( totalVolumeCm3 / surfaceAreaTopCm2 )
    );

    double totalSurfaceArea = surfaceAreaSideCm2 + surfaceAreaTopCm2;
    return totalSurfaceArea;
}

double ThermalBody::calculateHeatGainF(
    double joules
) {
    double totalMass = ( liquidMassKg + solidMassKg );
    double totalMassCapacityJKgF = (
        ( liquidMassCapacityJKgF * liquidMassKg )
        + ( solidMassCapacityJKgF * solidMassKg )
    )
    /
    totalMass;
    double deltaHeatGainF = joules / ( totalMass * totalMassCapacityJKgF );
    return deltaHeatGainF;
}

double ThermalBody::calculateHeatLossF(
    double currentTempF,
    double deltaTimeS
) {
    double heatTransferCoefficient = 0.0015;
    double heatLossJoules = (
        heatTransferCoefficient
        * surfaceAreaCm2
        * (currentTempF - ambientTempF) 
        * deltaTimeS
    );

    double totalMass = liquidMassKg + solidMassKg;
    double totalMassCapacityJKgF = (
        (liquidMassCapacityJKgF * liquidMassKg) + 
        (solidMassCapacityJKgF * solidMassKg)
    ) / totalMass;

    double deltaHeatLossF = (
        heatLossJoules
        / (totalMass * totalMassCapacityJKgF)
    );
    return deltaHeatLossF;
}