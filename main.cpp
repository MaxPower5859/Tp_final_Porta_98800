//=====[Libraries]=============================================================

#include "control_temp_system.h"
//#include mbed.h

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    controlTempSystemInit();
    while (true) {
        controlTempSystemUpdate();
    }
}

