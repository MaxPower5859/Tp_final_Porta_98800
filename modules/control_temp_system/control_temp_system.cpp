//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "control_temp_system.h"
#include "pc_serial_com.h"
#include "non_blocking_delay.h"
#include "potentiometer.h"
#include "stabilizer.h"
#include "display.h"
#include "temperature_sensor.h"
//#include "strobe_light.h"
#include "user_interface.h"

DigitalOut luz(LED1);
static nonBlockingDelay_t controlTempSystemDelay;
static nonBlockingDelay_t temp;
static nonBlockingDelay_t tickerEstabilizo;
float ts1;
float ts2;
bool estabilizo = false;
int potenciometroAnterior = 0;
int potenciometroActual = 0;
int contador;
float promTemp = 0.0;    // Valor de temperatura
float tolerancia = 0.1;   // Tolerancia del 10%


//=====[Implementations of public functions]===================================

void controlTempSystemInit(){
    tickInit();
    userInterfaceDisplayInit();
    pcSerialComInit();
    temperatureSensorInit();
    peltierControlInit();
    nonBlockingDelayInit( &controlTempSystemDelay, 10000 );
    nonBlockingDelayInit( &temp, 2000 );
    nonBlockingDelayInit( &tickerEstabilizo, 1000 );
}

void controlTempSystemUpdate(){

        pcSerialComUpdate();

        if( nonBlockingDelayRead(&temp) ) {
        temperatureSensorUpdate();
        }

        potenciometroActual = potenciometerReading();
        if(potenciometroAnterior != potenciometroActual){
            potenciometroAnterior = potenciometroActual;
            nonBlockingDelayInit( &tickerEstabilizo, 1000 );
        }

        temperatureSensors(ts1,ts2);
        promTemp = (ts1 + ts2)/2;

        if (promTemp >= (potenciometroActual - (potenciometroActual * tolerancia)) && promTemp <= (potenciometroActual + (potenciometroActual * tolerancia))) {
            if( nonBlockingDelayRead(&tickerEstabilizo) ) {
                contador++; // Incrementa el contador si la temperatura está dentro del rango
            }
        } else {
            nonBlockingDelayInit( &tickerEstabilizo, 1000 );
            contador = 0; // Resetea el contador si la temperatura está fuera del rango
        }




        userInterfaceDisplayUpdate();

        /* Como el PI no funciono, dejo un delay para que el peltier no
        se la pase saltando de un estado a otro, asi logro un menor desgaste.        
         */

        if( nonBlockingDelayRead(&controlTempSystemDelay) ) {
        peltierControlUpdate();
        }

        delay(SYSTEM_TIME_INCREMENT_MS);
}

int contadorValor(){
    return contador;
}