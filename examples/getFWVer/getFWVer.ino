/*****************************************************************
File:        getFWVer.ino 
Description:  1.  The Sound Detector is a small board that combines a microphone and some processing circuitry.
                  It provides not only an audio output, but also a binary indication of the presence of sound,
                  an analog representation of it's amplitude and I2C interface.  
              2.hardware Serial (BAUDRATE 115200) is used to communicate with Serial port monitor.
              3.This project introduces the use of I2C interface.
note:
******************************************************************/
#include <BMV23M001.h>

BMV23M001 soundDetector(2,&Wire);//Please comment out this line of code if you don't use Wire
//BMV23M001 soundDetector(22,&Wire1);//Please uncomment out this line of code if you use Wire1 on BMduino
//BMV23M001 soundDetector(25,&Wire2);//Please uncomment out this line of code if you use Wire2 on BMduino
uint16_t verNum = 0;

void setup() 
{
  soundDetector.begin();   //IIC addr 0x4B,rate 100kHz
  Serial.begin(115200);  // start serial for Debug
}

void loop() 
{
  verNum=soundDetector.getFWVer();
  if(verNum==FAIL)  //read f/w version
  {
   Serial.println("Communication fail,please check your connection!");
  }
  else
  {
    String version = "Firmware version: V" + (String)(uint8_t)(verNum>>8)  + "." + (String)(uint8_t)(verNum);
    Serial.println(version);
  }
  // pause for 10 ms
  delay(10);
}
