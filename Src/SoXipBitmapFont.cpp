#include "SoXipBitmapFont.h"

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/sensors/SoTimerSensor.h>

#include <xip/inventor/overlay/SoXipText2.h>
#include <stdio.h>

SO_KIT_SOURCE(SoXipBitmapFont);

SoXipBitmapFont::SoXipBitmapFont() : _cnt1(0), _cnt2(0)
{
  SO_KIT_CONSTRUCTOR( SoXipDisplayImageText );

  SO_KIT_ADD_CATALOG_ENTRY( separator, SoSeparator, FALSE, this, \0 , FALSE );
  SO_KIT_ADD_CATALOG_ENTRY( orthoCamera, SoOrthographicCamera, FALSE, separator, \0 , FALSE );

  // upper left
  SO_KIT_ADD_CATALOG_ENTRY( separatorText, SoSeparator, FALSE, separator, \0 , FALSE );
  SO_KIT_ADD_CATALOG_ENTRY( material, SoMaterial, FALSE, separator, \0 , FALSE );
  SO_KIT_ADD_CATALOG_ENTRY( translation, SoTranslation, FALSE, separator, \0 , FALSE );
  SO_KIT_ADD_CATALOG_ENTRY( text, SoXipText2, FALSE, separator, \0 , FALSE );

  SO_KIT_INIT_INSTANCE();

  SO_NODE_ADD_FIELD( string, ("one test") );

  SoNode* text = (SoNode *) getAnyPart( "text", TRUE );

  SoSFEnum* justification = (SoSFEnum *)text->getField("justification");
  justification->setValue(0 /*left*/);

  SoSFEnum* vAlignement = (SoSFEnum *)text->getField("vAlignment");
  vAlignement->setValue( 2 /*centered*/ );
  
  _sensor = new SoTimerSensor(timerSensorCBFunc, this);
  _sensor->setInterval(0.015);	// 60 fps
  _sensor->schedule();
}

void
SoXipBitmapFont::initClass()
{
  SO_KIT_INIT_CLASS(SoXipBitmapFont, SoBaseKit, "BaseKit");
}




void 
SoXipBitmapFont::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
  ((SoXipBitmapFont*)usr)->timer(sensor);
}

void
SoXipBitmapFont::timer(SoSensor * sensor)
{
  _cnt1 += 0.050f;										
  _cnt2 += 0.005f;	

  float xOffset = 0.7f * float(cos(_cnt1) - 0.2);
  float yOffset = 0.9f * float(sin(_cnt2));
 
  SoTranslation* trans = (SoTranslation *)getAnyPart("translation", TRUE );
  trans->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

  SoNode* mat = (SoNode*)getAnyPart( "material", TRUE );
  SoMFColor* colorField = (SoMFColor *) mat->getField( "diffuseColor" );
 
  // Pulsing colors based on text position: magic formula from Nehe!
  if( colorField  )
    colorField->setValue( SbVec3f(1.0f*float(cos(_cnt1)),1.0f*float(sin(_cnt2)),1.0f-0.5f*float(cos(_cnt1+_cnt2)) ));

  char textDisplay[MAX_PATH];
  sprintf_s(textDisplay,"Active OpenGL Text With XipNeHe - %3.2f", _cnt1);
  
  SoNode* text = (SoNode *)getAnyPart( "text", TRUE );
  SoSFString* textField = (SoSFString *)text->getField("string");
  textField->setValue(SbString(textDisplay));


}

SoXipBitmapFont::~SoXipBitmapFont()
{
  if (_sensor)
  {
     delete(_sensor);
  }
   
}



