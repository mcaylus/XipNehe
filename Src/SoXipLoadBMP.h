#ifndef SOXIPLOADBMP_H
#define SOXIPLOADBMP_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>

class SoXipLoadBMP : public SoEngine  
{
	SO_ENGINE_HEADER(SoXipLoadBMP);

public:
	SoXipLoadBMP();
	static void initClass();    

public: 
	SoSFString fileName;

	SoEngineOutput output;

protected:
	virtual ~SoXipLoadBMP();

private:
	virtual void evaluate();
	virtual void inputChanged(SoField *which);
	SbXipImage* loadBMP(const char *fileName);

	//bool needLoad;
	SoXipDataImage *mDataImage;

};
    
#endif //SOXIPLOADBMP_H