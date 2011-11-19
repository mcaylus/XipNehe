#ifndef SOXIPNEHETEXT3KIT_H
#define SOXIPNEHETEXT3KIT_H

#include "Inventor/nodekits/SoBaseKit.h"

class SoXipNeheText3Kit : public SoBaseKit {

  SO_KIT_HEADER(SoXipNeheStar)

  SO_KIT_CATALOG_ENTRY_HEADER(separator);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
  SO_KIT_CATALOG_ENTRY_HEADER(material); 
  SO_KIT_CATALOG_ENTRY_HEADER(materialSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(text3);

public:
  // Constructor
  SoXipNeheText3Kit();

  SoINTERNAL public:
  static void initClass();

};


#endif //SOXIPNEHETEXT3KIT_H