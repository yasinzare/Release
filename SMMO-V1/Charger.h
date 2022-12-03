
#ifndef CHARGER_H
#define CHARGER_H

#include "Headers.h"

#define BatterVoltagePin    12
#define BatteryVoltageEnPin 13
#define ChargStandbyPin     14
#define ChargerEnPin        26
#define ChargCompletePin    27

bool ChargerStandbyState();
bool ChargerCompleteState();
void ChargerPinInit();
void ChargerEnPinState (bool State);
float ReadBatteryVoltage();


#endif