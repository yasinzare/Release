
#include "Charger.h"

bool ChargerEnPinLastState = LOW ;

void ChargerPinInit()
{
    pinMode(ChargCompletePin , INPUT-PULLUP) ;
    pinMode(ChargStandbyPin  , INPUT-PULLUP) ;
    pinMode(ChargerEnPin     , OUTPUT) ;
    pinMode(BatteryVoltageEnPin     , OUTPUT) ;
    digitalWrite(ChargerEnPin , HIGH);
    digitalWrite(BatteryVoltageEnPin , LOW);
}

bool ChargerStandbyState()
{
    if(!ChargerEnPinLastState) ChargerEnPinState(HIGH) ;
    delay(100) ;
    bool ChargStandbyPinState = digitalRead(ChargStandbyPin) ;
    if( ChargStandbyPinState ) ChargerEnPinState(LOW) ;
    return ChargStandbyPinState ;
}

bool ChargerCompleteState()
{
    bool ChargCompletePinState = digitalRead(ChargCompletePin) ;
    if (!ChargCompletePinState) ChargerEnPinState(LOW) ;
    return ChargCompletePinState ;
}

float ReadBatteryVoltage()
{
    uint32_t AdcValue ;
    float Voltage ;
    digitalWrite(BatteryVoltageEnPin , HIGH);
    delay(100);
    AdcValue = analogRead(BatterVoltagePin) ;
    Voltage = ((AdcValue * 3.3) / 4095 ) * 2 ;
    digitalWrite(BatteryVoltageEnPin , LOW);
    return Voltage ;
}

void ChargerEnPinState (bool State)
{
    digitalWrite(ChargerEnPin , State ) ;
    ChargerEnPinLastState = State ;
}
