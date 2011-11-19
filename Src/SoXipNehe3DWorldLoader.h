#ifndef SOXIPNEHE3DWORLDLOADER_H
#define SOXIPNEHE3DWORLDLOADER_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFvec2f.h>
#include <Inventor/fields/SoMFUInt32.h>

#include <string>
#include <vector>

class SoXipNehe3DWorldLoader : public SoEngine
{
  SO_ENGINE_HEADER(SoXipNehe3DWorldLoader);

public:
  SoXipNehe3DWorldLoader();
  
  // Initialization
  static void initClass();

  SoSFString fileName;

	SoEngineOutput verticesCoords;
  SoEngineOutput textCoords;
  SoEngineOutput numVertices; // number of vertices to use for each triangle strip in the set
  
private:
  std::vector<SbVec3f>   _verticesCoords;
  std::vector<SbVec2f>   _textCoords;
  std::vector<int>       _numVertices;

  virtual void inputChanged(SoField *which);
  bool loadNehe3DWorld(const std::string filename);
  virtual void evaluate();
};


#endif //SOXIPNEHEWORLDLOADER_H