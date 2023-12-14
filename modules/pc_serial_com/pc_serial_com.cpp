//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "pc_serial_com.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "potentiometer.h"
#include "stabilizer.h"

/* #include "siren.h"
#include "fire_alarm.h"
#include "code.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "gas_sensor.h"
#include "event_log.h"
#include "motor.h"
#include "gate.h"
#include "motion_sensor.h"
#include "alarm.h" */

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================
states_t peltierStateSerial;

typedef enum{
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

/* char codeSequenceFromPcSerialCom[CODE_NUMBER_OF_KEYS]; */

//=====[Declaration and initialization of private global variables]============

static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;
static bool codeComplete = false;
static int numberOfCodeChars = 0;

float tempSupSerial;
float tempInfSerial;

//=====[Declarations (prototypes) of private functions]========================

static void pcSerialComStringRead( char* str, int strLength );

static void pcSerialComGetCodeUpdate( char receivedChar );
static void pcSerialComSaveNewCodeUpdate( char receivedChar );

static void pcSerialComCommandUpdate( char receivedChar );

static void availableCommands();
static void commandSetDateAndTime();
static void commandShowDateAndTime();

static void commandShowCurrentPotentiometer();

static void commandShowCurrentPeltierState();
static void commandShowCurrentTemperatureInCelsius();

//=====[Implementations of public functions]===================================

void pcSerialComInit(){
    availableCommands();
}

char pcSerialComCharRead(){
    char receivedChar = '\0';
    if( uartUsb.readable() ) {
        uartUsb.read( &receivedChar, 1 );
    }
    return receivedChar;
}

void pcSerialComStringWrite( const char* str ){
    uartUsb.write( str, strlen(str) );
}

void pcSerialComUpdate(){
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                pcSerialComCommandUpdate( receivedChar );
            break;

            case PC_SERIAL_GET_CODE:
                pcSerialComGetCodeUpdate( receivedChar );
            break;

            case PC_SERIAL_SAVE_NEW_CODE:
                pcSerialComSaveNewCodeUpdate( receivedChar );
            break;
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }    
}

bool pcSerialComCodeCompleteRead(){
    return codeComplete;
}

void pcSerialComCodeCompleteWrite( bool state ){
    codeComplete = state;
}

//=====[Implementations of private functions]==================================

static void pcSerialComStringRead( char* str, int strLength )
{
    int strIndex;
    for ( strIndex = 0; strIndex < strLength; strIndex++) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[strLength]='\0';
}


static void pcSerialComCommandUpdate( char receivedChar )
{
    switch (receivedChar) {
        case 'p': case 'P': commandShowCurrentPotentiometer(); break;
        case 'c': case 'C': commandShowCurrentTemperatureInCelsius(); break;
        case 's': case 'S': commandSetDateAndTime(); break;
        case 't': case 'T': commandShowDateAndTime(); break;
        case 'e': case 'E': commandShowCurrentPeltierState(); break;
        default: availableCommands(); break;
    } 
}

static void availableCommands()
{
    pcSerialComStringWrite( "Comandos Disponibles:\r\n" );
    pcSerialComStringWrite( "Presione P para obtener el valor de temperatura seteado del potenciometro\r\n" );
    pcSerialComStringWrite( "Presione C para obtener el valor de temperatura de la camara\r\n" );
    pcSerialComStringWrite( "Presione S para setear la hora\r\n" );
    pcSerialComStringWrite( "Presione T para ver la hora\r\n" );
    pcSerialComStringWrite( "Presione E para ver el estado del peltier\r\n" );
    pcSerialComStringWrite( "\r\n" );
}

static void commandShowCurrentPotentiometer(){
    char str[100] = "";
    //int stringLength;
    sprintf ( str, "Temperatura Seteada: %d\r\n", potenciometerReading() );
    pcSerialComStringWrite( str );
}

static void commandShowCurrentPeltierState(){
    peltierStateSerial = statesRead();
    if(peltierStateSerial == 0){ //calentando
        pcSerialComStringWrite( "El peltier esta CALENTANDO" );
    }else{
       pcSerialComStringWrite( "El peltier esta ENFRIANDO" ); 
    }
}
static void commandShowCurrentTemperatureInCelsius()
{
    temperatureSensors(tempSupSerial,tempInfSerial);

    char str[100] = "";
    sprintf ( str, "Temperatura Superior: %.2f \xB0 C\r\n",
                    tempSupSerial );
    pcSerialComStringWrite( str );   

    char str2[100] = "";
    sprintf ( str2, "Temperatura Inferior: %.2f \xB0 C\r\n",
                    tempInfSerial );
    pcSerialComStringWrite( str2 );   
} 

static void commandSetDateAndTime()
{
    char year[5] = "";
    char month[3] = "";
    char day[3] = "";
    char hour[3] = "";
    char minute[3] = "";
    char second[3] = "";
    
    pcSerialComStringWrite("\r\nType four digits for the current year (YYYY): ");
    pcSerialComStringRead( year, 4);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current month (01-12): ");
    pcSerialComStringRead( month, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current day (01-31): ");
    pcSerialComStringRead( day, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current hour (00-23): ");
    pcSerialComStringRead( hour, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current minutes (00-59): ");
    pcSerialComStringRead( minute, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current seconds (00-59): ");
    pcSerialComStringRead( second, 2);
    pcSerialComStringWrite("\r\n");
    
    pcSerialComStringWrite("Date and time has been set\r\n");

    dateAndTimeWrite( atoi(year), atoi(month), atoi(day), 
        atoi(hour), atoi(minute), atoi(second) );
}

static void commandShowDateAndTime()
{
    char str[100] = "";
    sprintf ( str, "Date and Time = %s", dateAndTimeRead() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}

