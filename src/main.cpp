#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "PIDController.h"

using namespace std;

const float KP = 5.0f;
const float KI = 0.2f;
const float KD = 1.0f;

int main() {
    
    // Create PID controller
    PIDController pid(KP, KI, KD, 0.0f, 100.0f);

    return 0;
} 