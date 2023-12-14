//=====[#include guards - begin]===============================================

#ifndef _STABILIZER_H_
#define _STABILIZER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    CALENTANDO,
    ENFRIANDO,
    APAGADO,
    ESTABILIZO
} states_t;

//=====[Declarations (prototypes) of public functions]=========================

void peltierControlInit();
states_t statesRead();
void peltierControlUpdate();
void peltierfast();

//=====[#include guards - end]=================================================

#endif // _STABILIZER_H_