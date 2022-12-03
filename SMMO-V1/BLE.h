
#ifndef  BLE_H
#define  BLE_H

#include "Headers.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"


void Bluetooth_Init();
void BleInit();
void BLE_CheckConnection();
void Print_BLE(uint8_t Payload_Send[10], uint8_t Payload_Size_Send , uint8_t BLE_CMD , uint8_t Value_ID) ;
void BLE_Analyse_Recived_Data(uint8_t Data[30]) ;
void BLERead();
void BLEHeartBit() ;
void BLEMacAddress() ;
void BLEgetMac();







#endif