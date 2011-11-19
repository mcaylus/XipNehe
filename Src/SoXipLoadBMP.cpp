#include "SoXipLoadBMP.h"
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoError.h>

#include <EasyBMP.h>

SO_ENGINE_SOURCE(SoXipLoadBMP);

void SoXipLoadBMP::initClass() 
{
	SO_ENGINE_INIT_CLASS(SoXipLoadBMP, SoEngine, "Engine");
}

SoXipLoadBMP::SoXipLoadBMP() 
{
	SO_ENGINE_CONSTRUCTOR(SoXipLoadBMP);

	SO_ENGINE_ADD_INPUT(fileName, (""));

	SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataImage);

	//needLoad = false;
	mDataImage = NULL;
}

SoXipLoadBMP::~SoXipLoadBMP() 
{
	if (mDataImage) 
	{
		mDataImage->unref();
		mDataImage = NULL;
	}
}

void SoXipLoadBMP::inputChanged(SoField *which) 
{
	if (mDataImage)	{
		mDataImage->unref();
		mDataImage = NULL;
	}
}

void SoXipLoadBMP::evaluate() 
{
	if (!mDataImage) 
	{
		if (fileName.getValue().getLength() == 0) {
			return;
		}

		SbXipImage *image = loadBMP(fileName.getValue().getString());

		if (image) {
			mDataImage = new SoXipDataImage;
			mDataImage->ref();
			mDataImage->set(image);
		}
	}

	// update output
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(mDataImage));

	return;
}

SbXipImage* SoXipLoadBMP::loadBMP(const char *fileName)
{
	try
	{
		BMP bmp;
		bmp.ReadFromFile(fileName);

		int numBits = bmp.TellBitDepth();
		int width = bmp.TellWidth();
		int height = bmp.TellHeight();

		int bitsStored = 8;
		int samplesPerPixel = 0;
		SbXipImage::ComponentType compType = SbXipImage::INTERLEAVED;
		SbXipImage::ComponentLayoutType compLayoutType = SbXipImage::RGB;

		if(numBits<=24)
		{
			samplesPerPixel = 3;
			compLayoutType = SbXipImage::RGB;
		}
		else if(numBits == 32)
		{
			samplesPerPixel = 4;
			compLayoutType = SbXipImage::RGBA;
		}

		SbVec3f pos(0, 0, 0);
		SbVec3f scale(width, height, 1);
		SbMatrix rotMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1);

		SbMatrix modelMatrix;
		modelMatrix.setScale(scale);
		//modelMatrix.setTransform(pos, SbRotation(rotMatrix), scale);

		SbXipImage *image = new SbXipImage(SbXipImageDimensions(width, height, 1), SbXipImageDimensions(width, height, 1),
			SbXipImage::UNSIGNED_BYTE, bitsStored, samplesPerPixel, compType, compLayoutType, modelMatrix);
		unsigned char *buffer = (unsigned char *) image->refBufferPtr();

		if(numBits<=24)
		{
			for(int i = 0; i < height; i++)
			{
				for(int j = 0; j < width; j++)
				{
					RGBApixel pixel = bmp.GetPixel(j,(height -1) - i );

					buffer[3*i*width+3*j] = pixel.Red;
					buffer[3*i*width+3*j+1] = pixel.Green;
					buffer[3*i*width+3*j+2] = pixel.Blue;

				}
			}
		}
		else if(numBits == 32)
		{
			for(int i=0; i<height; i++)
			{
				for(int j=0; j<width; j++)
				{
					RGBApixel pixel = bmp.GetPixel(j, height-i);

					buffer[4*i*width+4*j] = pixel.Red;
					buffer[4*i*width+4*j+1] = pixel.Green;
					buffer[4*i*width+4*j+2] = pixel.Blue;
					buffer[4*i*width+4*j+3] = pixel.Alpha;
				}
			}
		}

		image->unrefBufferPtr();

		return image;
	}
	catch(...)
	{
		SoDebugError::postInfo(__FILE__, "Exception loadBMP");

    // Fix me need to delete allocated memory!
		return 0;
	}
}