#ifndef SOXIPNEHESKULL_H
#define SOXIPNEHESKULL_H


#include "SoXipNeheText3Kit.h"

class SoTimerSensor;

class SoXipNeheSkull : public SoXipNeheText3Kit 
{
  SO_KIT_HEADER(SoXipNeheStar);

public:
  SoXipNeheSkull();
  static void initClass();

protected:
  void timer(SoSensor* sensor);
  static void timerSensorCBFunc(void *usr, SoSensor *sensor);


private:
  virtual ~SoXipNeheSkull();   
  SoTimerSensor*    _sensor;
  float             _rot;

  //fix me: we could add a text field here

};

#endif // SOXIPNEHESKULL_H