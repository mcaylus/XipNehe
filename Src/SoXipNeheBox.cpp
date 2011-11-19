#include "SoXipNeheBox.h"
 
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/sensors/SoFieldSensor.h>

SO_KIT_SOURCE(SoXipNeheBoxKit);
SO_KIT_SOURCE(SoXipNeheCompleteBoxKit);
SO_KIT_SOURCE(SoXipNeheBox);

void
SoXipNeheBoxKit::initClass()
{
  SO_KIT_INIT_CLASS(SoXipNeheBoxKit, SoBaseKit, "BaseKit");
}

//    Constructor
SoXipNeheBoxKit::SoXipNeheBoxKit()
{
  SO_KIT_CONSTRUCTOR(SoXipNeheBoxKit); 

  // Initialize children catalog and add entries to it
  // These are the macros you use to make a catalog.
  // Use combinations of ...ADD_CATALOG_ENTRY 
  // and ...ADD_CATALOG_LIST_ENTRY.  See SoSubKit.h for more
  // info on syntax of these macros.
  SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, TRUE, this, \0 ,TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(material, SoMaterial, TRUE, separator, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(vertexProperty,SoVertexProperty,  TRUE, separator,\0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(faceset,  SoFaceSet, TRUE, separator, \0, TRUE );

  SO_KIT_INIT_INSTANCE();
}


void
SoXipNeheCompleteBoxKit::initClass()
{
  SO_KIT_INIT_CLASS(SoXipNeheCompleteBoxKit, SoBaseKit, "BaseKit");
}

//    Constructor
SoXipNeheCompleteBoxKit::SoXipNeheCompleteBoxKit()
{
  SO_KIT_CONSTRUCTOR(SoXipNeheCompleteBoxKit); 

  SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, TRUE, this, \0 ,TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(matrixTransform, SoMatrixTransform, TRUE, separator, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(neheboxboxkit, SoXipNeheBoxKit, TRUE, separator, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(nehetopboxkit, SoXipNeheBoxKit,  TRUE, separator,\0 ,TRUE );

  SO_KIT_INIT_INSTANCE();
}


SoXipNeheBox::~SoXipNeheBox()
{
  if (_fieldsSensors)
  {
    for (int i = 0; i < (sizeof(_fieldsSensors)/sizeof(_fieldsSensors[0])); i++)
      if (_fieldsSensors[i])
        delete _fieldsSensors[i];
  }
}

void 
SoXipNeheBox::initClass()
{
  SO_KIT_INIT_CLASS(SoXipNeheBox, SoXipNeheCompleteBoxKit, "SoXipNeheCompleteBoxKit");
}


SoXipNeheBox::SoXipNeheBox()
{
  SO_KIT_CONSTRUCTOR(SoXipNeheBox);
  SO_KIT_INIT_INSTANCE();

  SO_NODE_ADD_FIELD(topColor, ( .8, .8, .8));
  SO_NODE_ADD_FIELD(boxColor, ( .8, .8, .8));
  SO_NODE_ADD_FIELD(transform, (SbMatrix::identity()) );

  // access to the nehe box boxkit
  SoXipNeheBoxKit* nbb = (SoXipNeheBoxKit*)getPart("neheboxboxkit", TRUE);

  SoVertexProperty* vtp = (SoVertexProperty*)nbb->getPart("vertexProperty",TRUE);
  const float verticeCoordsBox[][3] = { {-1, -1,  1}, { 1, -1, 1}, {1, 1, 1},  {-1, 1, 1 }, 
                                  {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1},
                                  {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}, {-1, -1, 1}, 
                                  { 1, -1, -1}, {1,  1, -1}, {1,  1, 1}, {1, -1,  1}, 
                                  {-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1} };
  int nbVertex = sizeof(verticeCoordsBox) / sizeof(verticeCoordsBox[0]);
  vtp->vertex.setValues(0, nbVertex ,verticeCoordsBox);
 

  const float normalBox[][3] = { {0, 0, 1}, {0, 0, -1}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0} };
  int nbNormal = sizeof(normalBox) / sizeof(normalBox[0]);
  vtp->normal.setValues(0, nbNormal, normalBox);

  const float textCoordsBox[][2] = { {0, 0}, {1, 0}, {1, 1}, {0, 1},
                                     {1, 0}, {1, 1}, {0, 1}, {0, 0}, 
                                     {1, 1}, {0, 1}, {0, 0}, {1, 0}, 
                                     {1, 0}, {1, 1}, {0, 1}, {0, 0}, 
                                     {0, 0}, {1, 0}, {1, 1}, {0, 1} };
  int nbTexCoordsBox = sizeof(textCoordsBox) / sizeof(textCoordsBox[0]);
  vtp->texCoord.setValues(0, nbTexCoordsBox, textCoordsBox);
  vtp->materialBinding.setValue(SoVertexProperty::PER_FACE);
  vtp->normalBinding.setValue(SoVertexProperty::PER_FACE);

  SoFaceSet* fs = (SoFaceSet*)nbb->getPart("faceset", TRUE);
  const int numVerticeBox[] = { 4, 4, 4, 4, 4 };
  fs->numVertices.setValues(0, 5 /* 5 faces*/  , numVerticeBox); 
  
  // access to the nehe top boxkit
  SoXipNeheBoxKit* ntb = (SoXipNeheBoxKit*)getPart("nehetopboxkit", TRUE);
  vtp = (SoVertexProperty*)ntb->getPart("vertexProperty",TRUE); 

  const float verticeCoordsTop[][3] = { {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1} };
  int nbVertexTop = sizeof(verticeCoordsTop) /  sizeof(verticeCoordsTop[0]);
  vtp->vertex.setValues(0, nbVertexTop ,verticeCoordsTop);
  vtp->materialBinding.setValue(SoVertexProperty::PER_FACE);
  vtp->normalBinding.setValue(SoVertexProperty::PER_FACE);

  const float normalTop[][3] = { { 0, 1, 0} };
  int nbNormalTop = sizeof(normalTop) / sizeof(normalTop[0]);
  vtp->normal.setValues(0, nbNormalTop, normalTop);

  const float textCoordsTop[][2] = { {0, 1}, {0, 0}, {1, 0}, {1, 1} };
  int nbTexCoordsTop = sizeof(textCoordsTop) / sizeof(textCoordsTop[0]);
  vtp->texCoord.setValues(0, nbTexCoordsTop, textCoordsTop);

  fs = (SoFaceSet*)ntb->getPart("faceset", TRUE);
  const int numVerticeTop[] = { 4 };
  fs->numVertices.setValues(0, 1 /* one face: only the top! */ , numVerticeTop); 

  
  SoField *fields[] = { &transform, &boxColor, &topColor};
  for (int i = 0; i < MAX_FIELDS_SENSORS ; i++)
  {
    _fieldsSensors[i] = new SoFieldSensor(&fieldSensorCBFunc, this);
    _fieldsSensors[i]->attach(fields[i]);
  }
}


void SoXipNeheBox::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
  if (user)
  {
    ((SoXipNeheBox*)user)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField(), sensor);
  }
}


void SoXipNeheBox::inputChanged(SoField *which, SoSensor *sensor)
{
  // to do: remove magic numbers!
  if (which == &transform   )
   {
      SoMatrixTransform* tr = (SoMatrixTransform*)getPart("matrixTransform", TRUE);
      _fieldsSensors[0]->detach();
      tr->matrix.setValue(transform.getValue());
      _fieldsSensors[0]->attach(&transform);

   }
   else if (which == &boxColor)
   {
     SoXipNeheBoxKit* ntb = (SoXipNeheBoxKit*)getPart("neheboxboxkit", TRUE);
     SoMaterial* mat = (SoMaterial*)ntb->getPart("material",TRUE); 
     _fieldsSensors[1]->detach();
     mat->diffuseColor.setValue( boxColor.getValue() );
     _fieldsSensors[1]->attach(&boxColor);

   }
   else if (which == &topColor)
   {
      SoXipNeheBoxKit* ntb = (SoXipNeheBoxKit*)getPart("nehetopboxkit", TRUE);
      SoMaterial* mat = (SoMaterial*)ntb->getPart("material",TRUE); 
      _fieldsSensors[2]->detach();
      mat->diffuseColor.setValue( topColor.getValue() );
      _fieldsSensors[2]->attach(&topColor);

   }
}


