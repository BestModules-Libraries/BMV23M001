/*****************************************************************
File:        example03_readSoundEnvelopeADCWithIIC.ino 
Description:  1.  The Sound Detector is a small board that combines a microphone and some processing circuitry.
                  It provides not only an audio output, but also a binary indication of the presence of sound,
                  an analog representation of it's amplitude and I2C interface.  
              2.hardware Serial (BAUDRATE 115200) is used to communicate with Serial port monitor.When there is a sound, 
              read the sensor data displayed on the serial port monitor.
              3.This project introduces the use of I2C interface.
          
connection method(Sound Detector:Arduino pin):GND:GND VDD:3V3 SDA:SDA1 SCL:SCL1 STA:STATUS1
******************************************************************/
#include "BMV23M001.h"

BMV23M001 soundDetector(2,&Wire);//Please comment out this line of code if you don't use Wire
//BMV23M001 soundDetector(22,&Wire1);//Please uncomment out this line of code if you use Wire1 on BMduino
//BMV23M001 soundDetector(25,&Wire2);//Please uncomment out this line of code if you use Wire2 on BMduino

uint16_t envelopeADC  = 0;
void setup() 
{
  soundDetector.begin();   //IIC rate 100kHz
  Serial.begin(115200);  // start serial for Debug

}

void loop() 
{ 
   if(!soundDetector.getStatus())
   {
      envelopeADC = soundDetector.readSoundEnvelopeADC();
      if(envelopeADC == FAIL)//read Envelope ADC 
      {
        Serial.println("Communication fail,please check your connection!");
      }
      else
      {
        //Convert envelope value into a message
        Serial.print("Environmental Status: ");
        Serial.print(envelopeADC);
        if( envelopeADC <= 200)
        {
          Serial.println("-Quiet.");
        }
        else if( (envelopeADC > 200) && ( envelopeADC <= 600) )
        {
          Serial.println("-Moderate.");
        }
        else if(envelopeADC > 600)
        {
          Serial.println("-Loud.");
        }          
      }         
   }
  // pause for 10 ms
   delay(10);
}
