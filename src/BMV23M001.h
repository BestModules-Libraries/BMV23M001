/*****************************************************************
File:       BMV23M001.h
Author:     BEST MODULES CORP.
Description:Define classes and required variables
History:    V1.0.2   -- 2024-08-20 
******************************************************************/
#ifndef _BMV23M001_H_
#define _BMV23M001_H_

#include <arduino.h>
#include <Wire.h>

#define BMV23M001_ADDR  (0x4B)
#define IIC_FREQUENCY   (100000)  
#define FAIL            (0)
#define StatusFAIL      (3)
#define CHECK_OK        0
#define CHECK_ERROR     1
#define TIMEOUT_ERROR   2

class BMV23M001
{
  public:
    BMV23M001(uint8_t statusPin,TwoWire* theWire = &Wire);
    void begin(uint8_t i2c_addr = BMV23M001_ADDR,uint32_t frequency = IIC_FREQUENCY);
    uint8_t getStatus();
    uint8_t readSoundStatus();
    uint16_t readSoundEnvelopeADC();
    uint16_t getFWVer();
  
  private:
   void writeBytes(uint8_t wbuf[], uint8_t wlen);
   uint8_t readBytes(uint8_t rbuf[], uint8_t rlen);
    uint8_t   _slaverAddr;
    uint8_t _statusPin;
    TwoWire*  _wire = NULL;
};


#endif
