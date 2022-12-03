
#include "Headers.h"


void setup()
{
 Serial.begin(115200);
 Serial.println("Im SMMO POD");
 ChargerPinInit();
 BleInit();
}

void loop()
{
 float BatteryVoltage ;
 BatteryVoltage = ReadBatteryVoltage();
 Serial.print("BatteryVoltage:");
 Serial.print(BatteryVoltage); 
 Serial.print("\tChargerCMP:");
 Serial.print(ChargerStandbyState());
 Serial.print("\tChargerSTD:");
 Serial.print(ChargerCompleteState()); 
 Serial.println();
 delay(1000);
}