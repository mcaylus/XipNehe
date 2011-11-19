#ifndef SO_XIP_BITMAP_FONT_H
#define SO_XIP_BITMAP_FONT_H

#include "Inventor/nodekits/SoBaseKit.h"
#include "Inventor/fields/SoSFString.h"
#include "Inventor/fields/SoSFInt32.h"

#include "Inventor/actions/SoGLRenderAction.h"



class SoTimerSensor;

class SoXipBitmapFont : public SoBaseKit {

  SO_KIT_HEADER(SoXipBitmapFont)

  SO_KIT_CATALOG_ENTRY_HEADER( separator );
  SO_KIT_CATALOG_ENTRY_HEADER( orthoCamera );
  SO_KIT_CATALOG_ENTRY_HEADER( separatorText );
  SO_KIT_CATALOG_ENTRY_HEADER( material );
  SO_KIT_CATALOG_ENTRY_HEADER( translation );
  SO_KIT_CATALOG_ENTRY_HEADER( text );

public:
  // Constructor
  SoXipBitmapFont();
  static void initClass();

  /// String to be displayed
  SoSFString		string;
  

protected:
  void timer(SoSensor* sensor);
  static void timerSensorCBFunc(void *usr, SoSensor *sensor);
  ~SoXipBitmapFont();

private:
  SoTimerSensor* _sensor;
  float          _cnt1;
  float          _cnt2;

};

#endif

