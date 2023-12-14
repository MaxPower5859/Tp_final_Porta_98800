#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

//=====[Declarations (prototypes) of public functions]=========================

void temperatureSensorInit();
void temperatureSensorUpdate();
void temperatureSensors(float &tempSup, float &tempInf);
float temperatureSensorsInf();
float temperatureSensorsSup();

//float temperatureSensorReadCelsius();
float temperatureSensorReadFahrenheit();
float celsiusToFahrenheit( float tempInCelsiusDegrees );

/* void temperatureSensorInit();
void temperatureSensorUpdate();
float temperatureSensorReadCelsius();
float temperatureSensorReadFahrenheit();
float celsiusToFahrenheit( float tempInCelsiusDegrees ); */

#endif // _TEMPERATURE_SENSOR_H_