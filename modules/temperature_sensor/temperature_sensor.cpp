#include "mbed.h"
#include "arm_book_lib.h"
#include "temperature_sensor.h"
#include "control_temp_system.h"

//=====[Declaration of private defines]========================================

#define LM35_NUMBER_OF_AVG_SAMPLES    30

//=====[Declaration and initialization of public global objects]===============

AnalogIn lm35_inf(A1);
AnalogIn lm35_sup(A2); //ME FALTA AGREGARLO EN LA FUNCION


//=====[Declaration and initialization of private global variables]============

float lm35TemperatureC_inf = 0.0;
float lm35TemperatureC_sup = 0.0;

float lm35ReadingsArray_inf[LM35_NUMBER_OF_AVG_SAMPLES];
float lm35ReadingsArray_sup[LM35_NUMBER_OF_AVG_SAMPLES];

//=====[Declarations (prototypes) of private functions]========================

static float analogReadingScaledWithTheLM35Formula( float analogReading );

//=====[Implementations of public functions]===================================

void temperatureSensorInit()
{
    int i;
    
    for( i=0; i<LM35_NUMBER_OF_AVG_SAMPLES ; i++ ) {
        lm35ReadingsArray_inf[i] = 0;
    }

    for( i=0; i<LM35_NUMBER_OF_AVG_SAMPLES ; i++ ) {
        lm35ReadingsArray_sup[i] = 0;
    }
}

void temperatureSensorUpdate()
{
    static int lm35SampleIndex = 0;
    float lm35ReadingsSum_inf = 0.0;
    float lm35ReadingsAverage_inf = 0.0;
    float lm35ReadingsSum_sup = 0.0;
    float lm35ReadingsAverage_sup = 0.0;
    
    int i = 0;

    delay(20);
    lm35ReadingsArray_inf[lm35SampleIndex] = lm35_inf.read();
    delay(20);
    lm35ReadingsArray_sup[lm35SampleIndex] = lm35_sup.read();
    lm35SampleIndex++;

    if ( lm35SampleIndex >= LM35_NUMBER_OF_AVG_SAMPLES) {
        lm35SampleIndex = 0;
    }
    lm35ReadingsSum_inf = 0.0;
    lm35ReadingsSum_sup = 0.0;
    for (i = 0; i < LM35_NUMBER_OF_AVG_SAMPLES; i++) {
        lm35ReadingsSum_inf = lm35ReadingsSum_inf + lm35ReadingsArray_inf[i];
        lm35ReadingsSum_sup = lm35ReadingsSum_sup + lm35ReadingsArray_sup[i];
    }

    lm35ReadingsAverage_inf = lm35ReadingsSum_inf / LM35_NUMBER_OF_AVG_SAMPLES;
    lm35TemperatureC_inf = analogReadingScaledWithTheLM35Formula ( lm35ReadingsAverage_inf );  

    lm35ReadingsAverage_sup = lm35ReadingsSum_sup / LM35_NUMBER_OF_AVG_SAMPLES;
    lm35TemperatureC_sup = analogReadingScaledWithTheLM35Formula ( lm35ReadingsAverage_sup );   
}

void temperatureSensors(float &tempSup, float &tempInf){
    tempSup = lm35TemperatureC_sup;
    tempInf = lm35TemperatureC_inf;
}

float temperatureSensorsInf(){
    return ( lm35_inf.read() * 3.3 / 0.01 );
}

float temperatureSensorsSup(){
    return ( lm35_sup.read() * 3.3 / 0.01 );
}

float temperatureSensorReadCelsius()
{
    return lm35TemperatureC_inf;
} 

float temperatureSensorReadFahrenheit()
{
    return celsiusToFahrenheit( lm35TemperatureC_inf );
}

float celsiusToFahrenheit( float tempInCelsiusDegrees )
{
    return ( tempInCelsiusDegrees * 9.0 / 5.0 + 32.0 );
} 

//=====[Implementations of private functions]==================================

static float analogReadingScaledWithTheLM35Formula( float analogReading )
{
    return ( analogReading * 3.3 / 0.01 );
}

