#include <windows.h>
#include <Inventor/SoDB.h>

#include "SoXipLoadBMP.h"
#include "SoXipNeheStar.h"
#include "SoXipNeheStarGenerator.h"
#include "SoXipBitmapFont.h"
#include "SoXipText3.h"
#include "SoXipNeheText3.h"
#include "SoXipNeheSkull.h"
#include "SoXipNeheFlagGenerator.h"
#include "SoXipNeheBox.h"
#include "SoXipNeheBoxGenerator.h"
#include "SoXipNehe3DWorldLoader.h"

#include "XipNehe.h"


int XIPNEHE_API xipnehe_init()
{
	// Initialization goes here
	SoXipLoadBMP::initClass();

  // Star for lesson 9
  SoXipNeheStarKit::initClass();
  SoXipNeheStar::initClass();
  SoXipNeheStarGenerator::initClass();

  // 3D world loader for lesson 10
  SoXipNehe3DWorldLoader::initClass();

  // Cubes for lesson 11
  SoXipNeheBoxKit::initClass();
  SoXipNeheCompleteBoxKit::initClass();
  SoXipNeheBox::initClass();
  SoXipNeheBoxGenerator::initClass();

  // Flag geom for lesson 12
  SoXipNeheFlagGenerator::initClass();

  // Text for lesson 13 (2D Font)
  SoXipBitmapFont::initClass();

  // Text for lesson 14 (3D Font)
  SoXipText3::initClass();
  SoXipNeheText3Kit::initClass();
  SoXipNeheText3::initClass();

  // Skull for lesson 15 (3D Font)
  SoXipNeheSkull::initClass();


	return 1;
}

BOOL APIENTRY DllMain( HINSTANCE hinstDLL, DWORD reason, LPVOID )
{
	if( reason == DLL_PROCESS_ATTACH )
	{
		if (SoDB::isInitialized())
		{
			xipnehe_init();
		}
    }
	return TRUE;
}
