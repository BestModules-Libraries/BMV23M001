/*****************************************************************
File:        example04_readGateStatusInput.ino 
Description:  1.  The Sound Detector is a small board that combines a microphone and some processing circuitry.
                  It provides not only an audio output, but also a binary indication of the presence of sound,
                  an analog representation of it's amplitude and I2C interface.  
              2.This project introduces the use of an audio output, a binary indication and an analog representation.
          
connection method(Sound Detector:Arduino pin):GND:GND VDD:3V3 Gate:D2 Envelope:A0 Audio:A1
******************************************************************/
//Define hardware connections
#define PIN_GATE_IN     (2)

void setup() 
{
  Serial.begin(115200);  // start serial for Debug
  //configure input to interrupt
  pinMode(PIN_GATE_IN,INPUT);
}

void loop() 
{
    Serial.print("Sound Status:");
   //Convert raw data into message
   if(digitalRead(PIN_GATE_IN))
   {
     Serial.println("Sound.");
   }
   else
   {
     Serial.println("Quiet.");
   }
}
