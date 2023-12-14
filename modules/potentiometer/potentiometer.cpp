#include "mbed.h"
#include "potentiometer.h"
#include "control_temp_system.h"

//=====[Declaration of private defines]========================================

#define MAXTEMP 40
#define MINTEMP 20

//=====[Declaration and initialization of public global objects]===============

AnalogIn potentiometer(A0);

//=====[Implementations of public functions]===================================

int potenciometerReading(){
    float aux_poten;
    aux_poten = 20 + potentiometer.read()*(40-20); //20.0 + x * (40.0 - 20.0)
    return static_cast<int>(aux_poten);
}