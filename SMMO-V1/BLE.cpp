
#include "BLE.h"

BLEServer *pServer = NULL;
BLECharacteristic * pCharacteristic ;
BLEService *pService;

std::string BLE_Recieve("") ;

const uint8_t* U_BleMac;
uint8_t BLE_Payload_Size_Rec ;
uint8_t BLE_Payload_Rec[16];  
uint8_t BLE_Device_ID = 0x03 ;

bool BLE_Connected = false;
bool oldDeviceConnected = false;
bool New_BLE_Data_Flag = false ;

char BLEMac[20];
char BTNameSTR[20];

BLEUUID  SERVICE_UUID((uint16_t)0xFFE0); // UART service UUID //"0000FFE0-0000-1000-8000-00805F9B34FB"
BLEUUID  CHARACTERISTIC_UUID ((uint16_t)0xFFE1); //"0000FFE1-0000-1000-8000-00805F9B34FB"

class MyServerCallbacks: public BLEServerCallbacks 
{
 void onConnect(BLEServer* pServer) 
  {
   BLE_Connected = true;
  //Serial.println("Connect");   
  };

 void onDisconnect(BLEServer* pServer) 
  {
   BLE_Connected = false ;
   //Serial.println("Disconnect");       
  }
};

class MyCallbacks: public BLECharacteristicCallbacks 
{
 void onWrite(BLECharacteristic *pCharacteristic) 
  {
   BLE_Recieve = pCharacteristic->getValue();          
   New_BLE_Data_Flag = true;
   if(DEBUG)
    Serial.println("BLE Data Recieved");
  }
};

void Bluetooth_Init(char* Name)
{
 
 BLEDevice::init(Name);

 pServer = BLEDevice::createServer();
 pServer->setCallbacks(new MyServerCallbacks());
 pService = pServer->createService(SERVICE_UUID);
 pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ  |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                                 );

 pCharacteristic->setCallbacks(new MyCallbacks());
 pCharacteristic->addDescriptor(new BLE2902());                                                   
 pService->start();
 pServer->getAdvertising()->start();

}

void BleInit()
{
    Bluetooth_Init("ESP");
    BLEgetMac();
    sprintf(BTNameSTR,"SMMOPOD-%02X%02X",(int)U_BleMac[4],(int)U_BleMac[5]);
    BLEDevice::deinit();
    Bluetooth_Init(BTNameSTR);
}

void BLE_CheckConnection()
{ 
 if (!BLE_Connected && oldDeviceConnected) 
  {
    pServer->startAdvertising();
    oldDeviceConnected = BLE_Connected;     
  }
 if (BLE_Connected && !oldDeviceConnected) 
  {
   oldDeviceConnected = BLE_Connected;
  }
}

void Print_BLE(uint8_t Payload_Send[10], uint8_t Payload_Size_Send , uint8_t BLE_CMD , uint8_t Value_ID) 
{
 if(BLE_Connected)
  {
   uint8_t BLE_Data_Send[20];

   memset (BLE_Data_Send, 0, sizeof(BLE_Data_Send));
  
//    BLE_Data_Send[0] = Start_Byte;
//    BLE_Data_Send[1] = Station_ID;
//    BLE_Data_Send[2] = Program_Version;
//    BLE_Data_Send[3] = BLE_CMD;
//    BLE_Data_Send[4] = Value_ID;
//    BLE_Data_Send[5] = Payload_Size_Send;
//    BLE_Data_Send[6+Payload_Size_Send] = End_Byte;
//    BLE_Data_Send[7+Payload_Size_Send] = '\n';
  
   for (int i = 0; i < Payload_Size_Send; i++) 
    {
     BLE_Data_Send[6+i] = Payload_Send[i];
    } 
   
   pCharacteristic->setValue(BLE_Data_Send , Payload_Size_Send + 8);
   pCharacteristic->notify(); 
   delay(10);
  }
}

void BLERead() 
{    
 if(New_BLE_Data_Flag)
  {    
//    if ( (BLE_Recieve[0] == Start_Byte) && (BLE_Recieve[1] == BLE_Device_ID) && (BLE_Recieve[BLE_Recieve.length() - 1] == End_Byte)  ) 
//     {
//      BLE_Analyse_Recived_Data((uint8_t *)BLE_Recieve.c_str() );
//      BLE_Recieve = "";
//     }
   New_BLE_Data_Flag = false ;
  }
}

void BLE_Analyse_Recived_Data(uint8_t Data[30]) 
{
 uint8_t BLE_CMD = Data[2] ;
   BLE_Device_ID = Data[1] ;
 BLE_Payload_Size_Rec = Data[3];
 
 for (int i = 0; i < BLE_Payload_Size_Rec; i++) 
  {
   BLE_Payload_Rec[i] = Data[i+4];
  }
  
 BLE_Payload_Rec[BLE_Payload_Size_Rec] = 0;
 // Serial.println(BLE_CMD) ;
  switch (BLE_CMD) 
   {
    // case  :
    // break ;
    
    // case :    
    // break ; 
   
    // case  : 
    // break ; 
        
    // case  : 
    // break ; 

    // case 
    // break ; 
    
    // case 
    // break ; 
    
    // case 
    // break ;
    
    // case 
    // break ;

    // case 
    // break ;

    // case 
    // break ;

    // case 
    // break ;

    // case 
    // break ;
   }
}

void BLEHeartBit() 
{ 
 //Print_BLE( _Data , 2 , BLE_Heart_Bit , 0x01 )  ; 
}
   
void BLEMacAddress()
{
 //Print_BLE( (uint8_t*)U_BleMac , 12 , BLE_Get_Mac , 0x01 )  ;
}

void BLEgetMac()
{
 U_BleMac = esp_bt_dev_get_address();
 sprintf(BLEMac,"%02X:%02X:%02X:%02X:%02X:%02X", (int)U_BleMac[0] , (int)U_BleMac[1] , (int)U_BleMac[2] , (int)U_BleMac[3] , (int)U_BleMac[4] , (int)U_BleMac[5] );    
 Serial.print("BLE Macaddres:");
 Serial.println(BLEMac);
}
        



       
