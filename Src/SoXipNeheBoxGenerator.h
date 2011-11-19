#ifndef SOXIPNEHEBOXGENERATOR_H
#define SOXIPNEHEBOXGENERATOR_H

#include "Inventor/nodes/SoGroup.h"
#include "xip/inventor/core/SoXipKit.h"

class SoXipNeheBoxGenerator : public SoXipKit {

  SO_NODE_HEADER(SoXipNeheBoxGenerator);

public:
    SoXipNeheBoxGenerator();
    static void initClass();
};


#endif //SOXIPNEHEBOXGENERATOR_H