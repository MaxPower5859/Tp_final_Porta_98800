#include "mbed.h"
#include "arm_book_lib.h"
#include "stabilizer.h"
#include "potentiometer.h"
#include "temperature_sensor.h"
#include "non_blocking_delay.h"

#define TIEMPO_ESTABILIZADO_MS 21600000
DigitalInOut peltierPin1(PF_2);
DigitalInOut peltierPin2(PE_3);
DigitalOut luzEstabilizo(LED3);
DigitalOut luzError(LED2);

static nonBlockingDelay_t stabilizedDelay;
states_t peltierState;

float tempSup;
float tempInf;
float tempSupPeltier;
float tempInfPeltier;
int tempSet;
int tempSetNueva;
float promedio;
bool llegoEstabilizar = false;

void peltierControlInit(){
    peltierPin1.mode(OpenDrain);
    peltierPin2.mode(OpenDrain);
    
    peltierPin1.input();
    peltierPin2.input();

    peltierState = APAGADO;
    tempSet = potenciometerReading();
    //nonBlockingDelayInit( &stabilizedDelay, TIEMPO_ESTABILIZADO_MS );
}

states_t statesRead(){
    return peltierState;
}

void peltierControlUpdate(){
    tempSet = potenciometerReading();
    temperatureSensors(tempSupPeltier, tempInfPeltier);
    promedio = (tempSupPeltier + tempInfPeltier)/2;
    if(tempSet < promedio){
        peltierState = ENFRIANDO;
        peltierPin1.input();
        peltierPin2.output();
        peltierPin2 = LOW;
    }else{
        peltierState = CALENTANDO;
        peltierPin2.input();
        peltierPin1.output();
        peltierPin1 = LOW;
    }
}

void peltierfast(){
    tempSet = potenciometerReading();
    temperatureSensors(tempSupPeltier, tempInfPeltier);
    //promedio = (temperatureSensorsInf() + temperatureSensorsSup())/2;
    promedio = (tempSupPeltier + tempInfPeltier)/2;
    if(tempSet < promedio){
        peltierState = ENFRIANDO;
        peltierPin1.input();
        peltierPin2.output();
        peltierPin2 = LOW;
    }else{
        peltierState = CALENTANDO;
        peltierPin2.input();
        peltierPin1.output();
        peltierPin1 = LOW;
    }
}