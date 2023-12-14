//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "user_interface.h"
#include "display.h"
#include "control_temp_system.h"
#include "temperature_sensor.h"
#include "potentiometer.h"
#include "stabilizer.h"
#include "non_blocking_delay.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration and initialization of public global objects]===============

DigitalOut regulationProblem(LED3);
DigitalOut regulationOk(LED2);
states_t peltier;

float tempSupDisplay;
float tempInfDisplay;
int contadorDisplay;
int horas;
int minutos;
int segundos;


void userInterfaceDisplayInit(){
    displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Temp Seteada:" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Temp Camara:" );
    
    displayCharPositionWrite ( 0,2 );
    displayStringWrite( "Peltier:" );

    displayCharPositionWrite ( 0,3 );
    displayStringWrite( "Tiempo Est:" );
}

void userInterfaceDisplayUpdate(){
    
    static int accumulatedDisplayTime = 0;
    char temperatureString[4] = "";
    float sup;
    float inf;

    temperatureSensors(sup,inf);

    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        sprintf(temperatureString, "%d", potenciometerReading());
        displayCharPositionWrite ( 14,0 );
        displayStringWrite( temperatureString );

        sprintf(temperatureString, "%.1f", (sup+inf)/2);
        displayCharPositionWrite ( 14,1 );
        displayStringWrite( temperatureString );
        //displayCharPositionWrite ( 14,0 );
        //displayStringWrite( "'C" );


        sprintf(temperatureString, "%.1f", inf);
        displayCharPositionWrite ( 9,2 );
        peltier = statesRead();
 /*        if(peltier = ENFRIANDO){
            displayStringWrite( "Enfriando" );
        }else{
            displayStringWrite( "Calentando" );
        } */
        switch (peltier) {
        case ENFRIANDO: displayStringWrite( "Enfriando" ); break;
        case CALENTANDO: displayStringWrite( "Calentando" ); break;
        default: displayStringWrite( "Apagado" ); break;
        }
        
        //displayStringWrite( "Enfriando" );
        contadorDisplay = contadorValor();
        horas = contadorDisplay / 3600;
        minutos = (contadorDisplay % 3600) / 60;
        segundos = (contadorDisplay % 3600) % 60;

        sprintf(temperatureString, "%d", horas);

        if(horas < 10){
            displayCharPositionWrite ( 11,3 );
            displayStringWrite( "0" );
            displayCharPositionWrite ( 12,3 );
            displayStringWrite( temperatureString );
        }else{
            displayCharPositionWrite ( 11,3 );
            displayStringWrite( temperatureString );
        }

        displayCharPositionWrite ( 13,3 );
        displayStringWrite( ":" );

        sprintf(temperatureString, "%d", minutos);
        if(minutos < 10){
            displayCharPositionWrite ( 14,3 );
            displayStringWrite( "0" );
            displayCharPositionWrite ( 15,3 );
            displayStringWrite( temperatureString );
        }else{
            displayCharPositionWrite ( 14,3 );
            displayStringWrite( temperatureString );
        }

/*         displayCharPositionWrite ( 14,3 );
        displayStringWrite( temperatureString ); */
        displayCharPositionWrite ( 16,3 );
        displayStringWrite( ":" );

        sprintf(temperatureString, "%d", segundos);
        if(segundos < 10){
            displayCharPositionWrite ( 17,3 );
            displayStringWrite( "0" );
            displayCharPositionWrite ( 18,3 );
            displayStringWrite( temperatureString );
        }else{
            displayCharPositionWrite ( 17,3 );
            displayStringWrite( temperatureString );
        }

/*         sprintf(temperatureString, "%d", segundos);
        displayCharPositionWrite ( 17,3 );
        displayStringWrite( temperatureString ); */


    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

void userInterfaceDisplayUpdateNew(float &tsup,float &tinf){
    
    static int accumulatedDisplayTime = 0;
    char temperatureString[4] = "";
    //temperatureSensors(sup,inf);
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        sprintf(temperatureString, "%d", potenciometerReading());
        displayCharPositionWrite ( 14,0 );
        displayStringWrite( temperatureString );

        sprintf(temperatureString, "%.1f", (tsup+tinf)/2);
        displayCharPositionWrite ( 14,1 );
        displayStringWrite( temperatureString );
        //displayCharPositionWrite ( 14,0 );
        //displayStringWrite( "'C" );


        
        displayCharPositionWrite ( 9,2 );
        peltier = statesRead();
 /*        if(peltier = ENFRIANDO){
            displayStringWrite( "Enfriando" );
        }else{
            displayStringWrite( "Calentando" );
        } */
        switch (peltier) {
        case ENFRIANDO: displayStringWrite( "Enfriando" ); break;
        case CALENTANDO: displayStringWrite( "Calentando" ); break;
        default: displayStringWrite( "Apagado" ); break;
        }
        
        //displayStringWrite( "Enfriando" );



    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}