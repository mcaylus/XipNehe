#ifndef SOXIPNEHESTARGENERATOR_H
#define SOXIPNEHESTARGENERATOR_H

#include "Inventor/nodes/SoGroup.h"
#include "xip/inventor/core/SoXipKit.h"

class SoXipNeheStarGenerator : public SoXipKit {

  SO_NODE_HEADER(SoXipNeheStarGenerator);

public:
    SoXipNeheStarGenerator();
    static void initClass();


protected:
    virtual void GLRender(SoGLRenderAction *action);

private:

  struct starInfo {
      float distance;
      float angle;
      unsigned int r;
      unsigned int g;
      unsigned int b; 
  };
  
  static const unsigned int MAX_STARS = 50;
  starInfo _starInfos[MAX_STARS];

  //Fix Me: add tilt option as part of the field

};


#endif //SOXIPNEHESTARGENERATOR_H