#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/sensors/SoTimerSensor.h>

#include "SoXipNeheText3.h"


SO_KIT_SOURCE(SoXipNeheText3);


void 
SoXipNeheText3::initClass()
{
   SO_KIT_INIT_CLASS(SoXipNeheText3, SoXipNeheText3Kit, "SoXipNeheText3Kit");
}


SoXipNeheText3::SoXipNeheText3(): _rot(0)
{
  SO_KIT_CONSTRUCTOR(SoXipNeheStar);
  SO_KIT_INIT_INSTANCE();

  // turn on switch for material
  SoNode* matSwitch = (SoNode *)getAnyPart("materialSwitch", TRUE);
  SoSFInt32* matSwitchF = (SoSFInt32*)matSwitch->getField("whichChild");
  matSwitchF->setValue(0);

  _sensor = new SoTimerSensor(timerSensorCBFunc, this);
  _sensor->setInterval(0.015);	// 60 fps
  _sensor->schedule(); 

}

SoXipNeheText3::~SoXipNeheText3()
{
  if (_sensor)
    delete _sensor;
}

void 
SoXipNeheText3::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
  ((SoXipNeheText3*)usr)->timer(sensor);
}

void
SoXipNeheText3::timer(SoSensor * sensor)
{
  SbRotation rotX = SbRotation::identity(); 
  SbMatrix rotXM = SbMatrix::identity();
  SbRotation rotY = SbRotation::identity(); 
  SbMatrix rotYM = SbMatrix::identity();
  SbRotation rotZ = SbRotation::identity(); 
  SbMatrix rotZM = SbMatrix::identity();
  SbMatrix trans = SbMatrix::identity();

  rotX.setValue(SbVec3f(1, 0, 0), _rot * M_PI/ 180);
  rotX.getValue(rotXM);
  
  rotY.setValue(SbVec3f(0, 1, 0), _rot * 1.5f * M_PI/ 180);
  rotY.getValue(rotYM);

  rotZ.setValue(SbVec3f(0, 0, 1), _rot * 1.4f * M_PI/ 180);
  rotZ.getValue(rotZM);

  // position text
  SoNode* text = (SoNode *) getAnyPart( "text3", TRUE );
  SoSFVec3f* bboxCenter = (SoSFVec3f *)text->getField("bboxCenter");
  trans.setTranslate(bboxCenter->getValue());

  SbMatrix compM = trans.inverse() * rotZM * rotYM * rotXM * trans;
  SoNode* transform = (SoNode *) getAnyPart( "transform", TRUE );
  SoSFMatrix* transformM =  (SoSFMatrix *)transform->getField("matrix");
  transformM->setValue(compM);

  // set the color (colors values based on the rotation angle)
  SoNode* mat = (SoNode *) getAnyPart( "material", TRUE );
  SoMFColor* color =  (SoMFColor *)mat->getField("diffuseColor");
  const float rgb[3] = { 1.0f*float(cos(_rot/20.0f)), 1.0f*float(sin(_rot/25.0f)), 1.0f-0.5f*float(cos(_rot/17.0f)) };
  color->set1Value(0, SbVec3f(rgb));

  
  // set the text
  SoSFString* string = (SoSFString *)text->getField("string");
 
  char textDisplay[MAX_PATH];
  sprintf_s(textDisplay,"XipNeHe - %3.2f", _rot/50);
  
  string->setValue(textDisplay);

  _rot += 1.0f; 

}