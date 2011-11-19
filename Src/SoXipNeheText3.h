#ifndef SOXIPNEHETEXT3_H
#define SOXIPNEHETEXT3_H
  

#include "SoXipNeheText3Kit.h"

class SoTimerSensor;

class SoXipNeheText3 : public SoXipNeheText3Kit 
{
  SO_KIT_HEADER(SoXipNeheStar);

public:
  SoXipNeheText3();
  static void initClass();
  
protected:
  void timer(SoSensor* sensor);
  static void timerSensorCBFunc(void *usr, SoSensor *sensor);


private:
  virtual ~SoXipNeheText3();   
  SoTimerSensor*    _sensor;
  float             _rot;

  //fix me: we could add a text field here

};

#endif // SOXIPNEHETEXT3_H