#ifndef SOXIPNEHESTAR_H
#define SOXIPNEHESTAR_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoMFUInt32.h>


class SoFieldSensor;

class SoXipNeheStarKit : public SoBaseKit {

  SO_KIT_HEADER(SoXipNeheStar)

  SO_KIT_CATALOG_ENTRY_HEADER(separator);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(vertexProperty);
  SO_KIT_CATALOG_ENTRY_HEADER(faceset);

public:
  // Constructor
  SoXipNeheStarKit();

  SoINTERNAL public:
  static void initClass();

};


class SoXipNeheStar : public SoXipNeheStarKit 
{
  SO_KIT_HEADER(SoXipNeheStar);

public:
  SoXipNeheStar();
  static void initClass();

private:
  virtual ~SoXipNeheStar();
  static void fieldSensorCBFunc(void *user, SoSensor *sensor);

protected:
  void inputChanged(SoField* which, SoSensor *sensor);

public:
  SoSFMatrix trans;   // unique trans field to expose
  SoMFUInt32  color;  // star color (hexadecimal)

private:
  static const int MAX_FIELDS_SENSORS = 2;
  SoFieldSensor* _fieldsSensors[MAX_FIELDS_SENSORS];
   

};

#endif