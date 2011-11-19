#include "SoXipNeheBoxGenerator.h"
#include "SoXipNeheBox.h"

// array for box colors
const float boxCol[5][3]=                               
{
  // Bright:  Red, Orange, Yellow, Green, Blue
  {1.0f,0.0f,0.0f},{1.0f,0.5f,0.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,1.0f,1.0f}
};
 
// array for top colors
const float topCol[5][3]=                               
{
  // Dark:  Red, Orange, Yellow, Green, Blue
  {.5f,0.0f,0.0f},{0.5f,0.25f,0.0f},{0.5f,0.5f,0.0f},{0.0f,0.5f,0.0f},{0.0f,0.5f,0.5f}
};


SO_NODE_SOURCE(SoXipNeheBoxGenerator)

void
SoXipNeheBoxGenerator::initClass()
{
   SO_NODE_INIT_CLASS(SoXipNeheBoxGenerator, SoXipKit, "Node")
}


SoXipNeheBoxGenerator::SoXipNeheBoxGenerator()
{
  SO_NODE_CONSTRUCTOR(SoXipNeheBoxGenerator);
  
  SbRotation pitch(SbVec3f(1, 0, 0), 0);  // rotation around X
  SbMatrix pitchM;

  SbRotation yaw(SbVec3f(0, 1, 0), 0);    // rotation around Y
  SbMatrix yawM;

  SbMatrix transM = SbMatrix::identity(); // translation
  SbMatrix compM = SbMatrix::identity();
 
  float xrot = 0;
  float yrot = 0;

  for (int yloop = 1; yloop < 6 /* number of rows */ ; yloop++)
	{
		for (int xloop = 0; xloop < yloop; xloop++)
		{
		
      // another magic formula from Nehe for the translation...
		  transM.setTranslate(SbVec3f(1.4f+(float(xloop)*2.8f)-(float(yloop)*1.4f),((6.0f-float(yloop))*2.4f)-7.0f,-20.0f));
			
      pitch.setValue(SbVec3f(1, 0, 0), (M_PI/180) * (45.0f-(2.0f*yloop)+ xrot));
      pitch.getValue(pitchM);
			
      yaw.setValue(SbVec3f(0,1,0), (M_PI/180) * (45.0f + yrot));
      yaw.getValue(yawM);

      compM = yawM * pitchM * transM;

			SoXipNeheBox* neheBox = new SoXipNeheBox();
      neheBox->transform.setValue(compM);
      neheBox->topColor.setValue(topCol[yloop - 1]);
      neheBox->boxColor.setValue(boxCol[yloop - 1]);
      this->addChild(neheBox);
    }
	}

  
}

