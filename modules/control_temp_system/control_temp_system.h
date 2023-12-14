//=====[#include guards - begin]===============================================

#ifndef _CONTROL_TEMP_SYSTEM_H_
#define _CONTROL_TEMP_SYSTEM_H_

//=====[Declaration of public defines]=========================================

#define SYSTEM_TIME_INCREMENT_MS   250
#define PELTIER_TIME_INCREMENT_MS   20000


//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void controlTempSystemInit();
void controlTempSystemUpdate();
int contadorValor();

//=====[#include guards - end]=================================================

#endif // _CONTROL_TEMP_SYSTEM_H_