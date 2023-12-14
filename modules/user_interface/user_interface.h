#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate();
void userInterfaceDisplayInit();
void userInterfaceDisplayUpdate();
bool userInterfaceCodeCompleteRead();
void userInterfaceCodeCompleteWrite( bool state );
void userInterfaceDisplayUpdateNew(float &tsup,float &tinf);

bool incorrectCodeStateRead();
void incorrectCodeStateWrite( bool state );

bool systemBlockedStateRead();
void systemBlockedStateWrite( bool state );

#endif // _USER_INTERFACE_H_