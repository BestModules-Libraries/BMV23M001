/*****************************************************************
File:        example05_readEnvelopeInput.ino 
Description:  1.  The Sound Detector is a small board that combines a microphone and some processing circuitry.
                  It provides not only an audio output, but also a binary indication of the presence of sound,
                  an analog representation of it's amplitude and I2C interface.  
              2.This project introduces the use of an audio output, a binary indication and an analog representation.
          
connection method(Sound Detector:Arduino pin):GND:GND VDD:3V3 Gate:D2 Envelope:A0 Audio:A1
******************************************************************/
//Define hardware connections
#define PIN_ENVELOPE_IN (A0)

uint16_t envelopeADC = 0;

void setup() 
{
  Serial.begin(115200);  // start serial for Debug
}

void loop() 
{
  //Check envelope input
  analogReadResolution(12); //change the resolution to 12 bits
  envelopeADC = analogRead(PIN_ENVELOPE_IN);
  Serial.print("envelopeADC:");
  Serial.println(envelopeADC);
  //Convert raw data into message
  if(envelopeADC <= 200)
  {
    Serial.println("Quiet.");
  }
  else if( (envelopeADC > 200) && ( envelopeADC <= 600) )
  {
    Serial.println("Moderate.");
  }
  else if(envelopeADC > 600)
  {
    Serial.println("Loud.");
  }  
}
