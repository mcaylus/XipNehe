#include "SoXipNeheStar.h"

#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <Inventor/nodes/SoFont.h>

SO_KIT_SOURCE(SoXipNeheStarKit);
SO_KIT_SOURCE(SoXipNeheStar);

void
SoXipNeheStarKit::initClass()
{
  SO_KIT_INIT_CLASS(SoXipNeheStarKit, SoBaseKit, "BaseKit");
}

//    Constructor
SoXipNeheStarKit::SoXipNeheStarKit()
{
  SO_KIT_CONSTRUCTOR(SoXipNeheStarKit); 
 
  isBuiltIn = TRUE;
  
  // Initialize children catalog and add entries to it
  // These are the macros you use to make a catalog.
  // Use combinations of ...ADD_CATALOG_ENTRY 
  // and ...ADD_CATALOG_LIST_ENTRY.  See SoSubKit.h for more
  // info on syntax of these macros.
  SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, TRUE, this, \0 ,TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(transform, SoMatrixTransform, TRUE, separator, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(lightModel, SoLightModel,TRUE, separator, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(vertexProperty,SoVertexProperty,  TRUE, separator,\0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(faceset,  SoFaceSet, TRUE, separator, \0, TRUE );
  
  SO_KIT_INIT_INSTANCE();
}


void 
SoXipNeheStar::initClass()
{
   SO_KIT_INIT_CLASS(SoXipNeheStar, SoXipNeheStarKit, "SoXipNeheStarKit");
}


SoXipNeheStar::SoXipNeheStar()
{
  SO_KIT_CONSTRUCTOR(SoXipNeheStar);
  SO_KIT_INIT_INSTANCE();

  // set attributes to some parts
  set("lightModel { model BASE_COLOR}");

  set("faceset { numVertices 4 }");
  set("vertexProperty { normal [0 0 1] }");

  set("vertexProperty { vertex [ -1 -1 0, 1 -1 0, 1 1 0, -1 1 0 ] }");
  set("vertexProperty { texCoord [ 0 0, 1 0, 1 1, 0 1 ]}");
  set("vertexProperty { materialBinding PER_VERTEX}");
  set("vertexProperty { normalBinding PER_FACE}");

  SO_NODE_ADD_FIELD(trans, (SbMatrix::identity()));
  SO_NODE_ADD_FIELD(color, (0));

  SoField *fields[] = { &trans , &color };
  for (int i = 0; i < MAX_FIELDS_SENSORS ; i++)
  {
    _fieldsSensors[i] = new SoFieldSensor(&fieldSensorCBFunc, this);
    _fieldsSensors[i]->attach(fields[i]);
  }
}


void SoXipNeheStar::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
  if (user)
  {
    ((SoXipNeheStar*)user)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField(), sensor);
  }
}


void SoXipNeheStar::inputChanged(SoField *which, SoSensor *sensor)
{
  // to do: remove magic numbers!
  if (which == &trans )
   {
      SoMatrixTransform* tr = (SoMatrixTransform*)getPart("transform", TRUE);
      _fieldsSensors[0]->detach();
      tr->matrix.setValue(trans.getValue());
      _fieldsSensors[0]->attach(&trans);

   }
   else if (which == &color)
   {
     SoVertexProperty* vp = (SoVertexProperty*)getPart("vertexProperty", TRUE);
     _fieldsSensors[1]->detach();
     vp->orderedRGBA.setValues( 0, color.getNum(), color.getValues(0) );
     _fieldsSensors[1]->attach(&color);

   }
}

SoXipNeheStar::~SoXipNeheStar()
{}









