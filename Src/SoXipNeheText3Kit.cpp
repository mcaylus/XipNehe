#include "SoXipNeheText3Kit.h"

SO_KIT_SOURCE(SoXipNeheText3Kit);

void
SoXipNeheText3Kit::initClass()
{
  SO_KIT_INIT_CLASS(SoXipNeheText3Kit, SoBaseKit, "BaseKit");
}

// Constructor
SoXipNeheText3Kit::SoXipNeheText3Kit()
{
  SO_KIT_CONSTRUCTOR(SoXipNeheText3Kit); 

  isBuiltIn = TRUE;

  // Initialize children catalog and add entries to it
  // These are the macros you use to make a catalog.
  // Use combinations of ...ADD_CATALOG_ENTRY 
  // and ...ADD_CATALOG_LIST_ENTRY.  See SoSubKit.h for more
  // info on syntax of these macros.
  SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, FALSE, this, \0 ,TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(transform, SoMatrixTransform, FALSE, separator, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(materialSwitch, SoSwitch, FALSE, separator, \0, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(material, SoMaterial,FALSE, materialSwitch, \0, TRUE );
  SO_KIT_ADD_CATALOG_ENTRY(text3, SoXipText3, FALSE, separator,\0 ,TRUE );

  SO_KIT_INIT_INSTANCE();

}