#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/sensors/SoTimerSensor.h>

#include "SoXipNeheSkull.h"


SO_KIT_SOURCE(SoXipNeheSkull);


void 
  SoXipNeheSkull::initClass()
{
  SO_KIT_INIT_CLASS(SoXipNeheSkull, SoXipNeheText3Kit, "SoXipNeheText3Kit");
}


SoXipNeheSkull::SoXipNeheSkull(): _rot(0)
{
  SO_KIT_CONSTRUCTOR(SoXipNeheSkull);
  SO_KIT_INIT_INSTANCE();

  // set the text
  SoNode* text = (SoNode *) getAnyPart( "text3", TRUE );
  SoSFString* string = (SoSFString *)text->getField("string");
  string->setValue("N");

  _sensor = new SoTimerSensor(timerSensorCBFunc, this);
  _sensor->setInterval(0.015);	// 60 fps
  _sensor->schedule(); 

}

SoXipNeheSkull::~SoXipNeheSkull()
{
  if (_sensor)
    delete _sensor;
}

void 
  SoXipNeheSkull::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
  ((SoXipNeheSkull*)usr)->timer(sensor);
}

void
  SoXipNeheSkull::timer(SoSensor * sensor)
{
  SbRotation rotX     = SbRotation::identity(); 
  SbMatrix rotXM      = SbMatrix::identity();
  SbRotation rotY     = SbRotation::identity(); 
  SbMatrix rotYM      = SbMatrix::identity();
  SbRotation rotZ     = SbRotation::identity(); 
  SbMatrix rotZM      = SbMatrix::identity();
  SbMatrix trans      = SbMatrix::identity();
  SbMatrix transSwing = SbMatrix::identity();

  rotX.setValue(SbVec3f(1, 0, 0), _rot * M_PI/ 180);
  rotX.getValue(rotXM);

  rotY.setValue(SbVec3f(0, 1, 0), _rot * 1.2f * M_PI/ 180);
  rotY.getValue(rotYM);

  rotZ.setValue(SbVec3f(0, 0, 1), _rot * 1.4f * M_PI/ 180);
  rotZ.getValue(rotZM);

  transSwing.setTranslate(SbVec3f(1.1f*float(cos(_rot/16.0f)),0.8f*float(sin(_rot/20.0f)),-3.0f));
 

  // position text
  SoNode* text = (SoNode *) getAnyPart( "text3", TRUE );
  SoSFVec3f* bboxCenter = (SoSFVec3f *)text->getField("bboxCenter");
 
  trans.setTranslate(bboxCenter->getValue());

  SoSFFloat* depth = (SoSFFloat* )text->getField("depth");
  depth->setValue(.2f);

  SbMatrix compM = trans.inverse() * rotZM * rotYM * rotXM  * transSwing * trans;

  SoNode* transform = (SoNode *) getAnyPart( "transform", TRUE );
  SoSFMatrix* transformM =  (SoSFMatrix *)transform->getField("matrix");
  transformM->setValue(compM);

  _rot += .5f; 

}