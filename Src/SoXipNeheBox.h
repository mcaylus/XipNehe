#ifndef SOXIPNEHEBOX_H
#define SOXIPNEHEBOX_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFMatrix.h>


class SoFieldSensor;


// will be used to build a box and its top
class SoXipNeheBoxKit : public SoBaseKit {

  SO_KIT_HEADER(SoXipNeheBoxKit)

  SO_KIT_CATALOG_ENTRY_HEADER(separator);
  SO_KIT_CATALOG_ENTRY_HEADER(material);
  SO_KIT_CATALOG_ENTRY_HEADER(vertexProperty);
  SO_KIT_CATALOG_ENTRY_HEADER(faceset);

public:
  // Constructor
  SoXipNeheBoxKit();
  static void initClass();

};

// use the two previous nodekits to create a new one
class SoXipNeheCompleteBoxKit : public SoBaseKit {
  
  
  SO_KIT_HEADER(SoXipNeheCompleteBoxKit)

  SO_KIT_CATALOG_ENTRY_HEADER(separator);
  SO_KIT_CATALOG_ENTRY_HEADER(matrixTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(neheboxboxkit);
  SO_KIT_CATALOG_ENTRY_HEADER(nehetopboxkit);

public:
  // Constructor
  SoXipNeheCompleteBoxKit();
  static void initClass();

};

class SoXipNeheBox : public SoXipNeheCompleteBoxKit
{
  SO_KIT_HEADER(SoXipNeheBox);

public:
  SoXipNeheBox();

  SoSFColor   topColor;
  SoSFColor   boxColor;
  SoSFMatrix  transform;
 
  static void initClass();
  static void fieldSensorCBFunc(void *user, SoSensor *sensor);

protected:
  void inputChanged(SoField* which, SoSensor *sensor);
  ~SoXipNeheBox();

private:
  static const int MAX_FIELDS_SENSORS = 3;
  SoFieldSensor*  _fieldsSensors[MAX_FIELDS_SENSORS];

};

#endif // SOXIPNEHEBOX_H