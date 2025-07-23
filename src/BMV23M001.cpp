 /*****************************************************************
File:       BMV23M001.cpp
Author:     BEST MODULES CORP.
Description:Communicate with BMV23M001 through IIC and measure sound
History:    V1.0.3-- 2025-04-02 
******************************************************************/
#include "BMV23M001.h"

/**********************************************************
Description:  Constructor
Parameters:   statusPin:Sound interrupt pin
	      *theWire : TwoWire object if your board has more than one TwoWire interface                         
Return:          
Others:     
**********************************************************/
BMV23M001::BMV23M001(uint8_t statusPin,TwoWire* theWire)
{ 
   _statusPin = statusPin;
   _wire =  theWire;
} 
/**********************************************************
Description:  Module Initial
Parameters:   i2c_addr: Set the Module  slaverAddr(Unique Value 0x4B)
              frequency: IIC Communication frequency               
Return:          
Others:         
**********************************************************/
void BMV23M001::begin(uint8_t i2c_addr,uint32_t frequency)
{ 
   _slaverAddr = i2c_addr;
  if (_wire != NULL)
  {
    pinMode(_statusPin,INPUT);
     _wire->begin();
     _wire->setClock(frequency);
  }
} 

/**********************************************************
Description: get INT Status
Parameters:       
Return:      Returns the INT state  
             0:INT output low level  press
             1:INT output high level   unpress    
Others:      
**********************************************************/
uint8_t BMV23M001::getStatus()
{
  return (digitalRead(_statusPin));
} 

/**********************************************************
Description: Read the sound status with IIC
Parameters:       
Return:      0x03(StatusFAIL):fail 0x00:Sound quiet   0x01:Sound play 
Others:          
**********************************************************/
uint8_t BMV23M001::readSoundStatus()
{
  uint8_t checkSum = 0;
  uint8_t soundStatusBuf[7] = {0};
  uint8_t soundStatus=0;

  checkSum = (uint8_t)(0xA5+0x5A+0x01+0x01);
  uint8_t soundCMD[5]={0xA5,0x5A,0x01,0x01,checkSum};
  writeBytes(soundCMD,5);
  
  if(readBytes(soundStatusBuf,6) == CHECK_OK)//checksum success
  {
    soundStatus = soundStatusBuf[4];
    delay(1);
    return soundStatus;
  }
  else //checksum fail
  {
    return  StatusFAIL;
  }
}
/**********************************************************
Description: Read the envelope ADC with IIC
Parameters:     
Return:      EVN pin ADC value   
Others:          
**********************************************************/
uint16_t BMV23M001::readSoundEnvelopeADC( )
{
  uint8_t checkSum = 0;
  uint8_t ADCBuf[7] = {};
  uint16_t soundDetectorEnvelopeADC=0;

  checkSum = (uint8_t)(0xA5+0x5A+0x01+0x02);
  uint8_t ADCCMD[5]={0xA5,0x5A,0x01,0x02,checkSum};
  writeBytes(ADCCMD,5);
    
  if(readBytes(ADCBuf,7) == CHECK_OK)//checksum success
  {
    soundDetectorEnvelopeADC = ADCBuf[4];
    soundDetectorEnvelopeADC = (soundDetectorEnvelopeADC<<8)+ADCBuf[5];
    delay(1);
    return soundDetectorEnvelopeADC;
  }
  else //checksum fail
  {
    return  FAIL;
  }
}
/**********************************************************
Description: Get the version information with IIC
Parameters:
Return:      version information
		0:fail 
		other:VERSION
Others:      
**********************************************************/
uint16_t BMV23M001::getFWVer()
{
    uint8_t checkSum = 0;
    uint8_t verBuf[7] = {};
    uint16_t ver=0;
    
    checkSum = (uint8_t)(0xA5+0x5A+0x01+0x03);
    uint8_t FWVCMD[5]={0xA5,0x5A,0x01,0x03,checkSum};
    writeBytes(FWVCMD,5);
    
    if(readBytes(verBuf,7) == CHECK_OK)//checksum success
    {
        ver = verBuf[4];
        ver = (ver<<8)+verBuf[5];
        delay(1);
        return ver;
    }
    else //checksum fail
    {
    return  FAIL;
    }             
}
/**********************************************************
Description: writeBytes
Parameters:  wbuf :the bytes sent
             wlen :the length of the data sent          
Return:      void        
Others:      
**********************************************************/
void BMV23M001::writeBytes(uint8_t wbuf[], uint8_t wlen)
{
  if (_wire != NULL)
  {
    while (_wire->available() > 0)
    {
      _wire->read();
    }
    _wire->beginTransmission(_slaverAddr);
    _wire->write(wbuf, wlen);
    _wire->endTransmission();
  }
  delay(1);
}
/**********************************************************
Description: read Bytes
Parameters:  rbuf :the bytes receive
             rlen :the length of the data receive
Return:      0x00(CHECK_OK):ok 0x01(CHECK_ERROR):error 0x02(TIMEOUT_ERROR):time out    
Others: 
**********************************************************/
uint8_t BMV23M001::readBytes(uint8_t rbuf[], uint8_t rlen)
{
  uint8_t i = 0, checkSum = 0;
  _wire->requestFrom(_slaverAddr, rlen);
  if (_wire->available() == rlen)
  {
    for (i = 0; i < rlen; i++)
    {
      rbuf[i] = _wire->read();
    }
  }
  else
  {
    return TIMEOUT_ERROR;
  }

  /* Check Sum */
  for (i = 0; i < (rlen - 1); i++)
  {
    checkSum += rbuf[i];
  }
  if (checkSum == rbuf[rlen - 1])
  {
    return CHECK_OK; // Check correct
  }
  else
  {
    return CHECK_ERROR; // Check error
  }
}
