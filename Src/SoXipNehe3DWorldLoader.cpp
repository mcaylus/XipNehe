#include "SoXipNehe3DWorldLoader.h"

#include <fstream>
#include <sstream>

SO_ENGINE_SOURCE(SoXipNehe3DWorldLoader);

void 
SoXipNehe3DWorldLoader::initClass() 
{
	SO_ENGINE_INIT_CLASS(SoXipNehe3DWorldLoader, SoEngine, "Engine");
}

SoXipNehe3DWorldLoader::SoXipNehe3DWorldLoader() 
{
	SO_ENGINE_CONSTRUCTOR(SoXipNehe3DWorldLoader);

	SO_ENGINE_ADD_INPUT(fileName, (""));
	SO_ENGINE_ADD_OUTPUT(verticesCoords, SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(textCoords, SoMFVec2f);
  SO_ENGINE_ADD_OUTPUT(numVertices, SoMFUInt32);

  _verticesCoords.clear();
  _textCoords.clear();
  _numVertices.clear();


}

void
SoXipNehe3DWorldLoader::inputChanged(SoField *which)
{

  _verticesCoords.clear();
  _textCoords.clear();
  _numVertices.clear();
 // if (_verticesCoords)
 //   delete [] _verticesCoords;

 // if (_textCoords)
 //   delete [] _textCoords;
}

bool
SoXipNehe3DWorldLoader::loadNehe3DWorld(const std::string fileName)
{
  
  std::ifstream fin;
  std::string line;

  fin.open(fileName);
  
  if (!fin.good())
  {
    SoDebugError::postInfo(__FILE__, "File specified cannot be loaded");
    return false;
  }

  int nbVertex = 0;
  int nbTriangles = 0;
 
  // loop till non empty first line
  while (!fin.eof() && line.empty())
  {
    // read first line
    std::getline(fin, line);
    std::stringstream convertor(line);
   
    if ( !line.empty() && convertor.fail() )
    {
      SoDebugError::postInfo(__FILE__, "Can't read the first line");
      fin.close();
      return false;
    }

    std::string nbTrianglesStr;
    convertor >> nbTrianglesStr >> nbTriangles;
    nbVertex = nbTriangles * 3; 
  }

  
  // allocate memory for each vertex info to collect
  if (nbVertex)
  {
    _verticesCoords.resize(nbVertex);
    _textCoords.resize(nbVertex);
    _numVertices.resize(nbTriangles/2);
  }

  int vindex = 0; // vertex index 
  while ( !fin.eof() || ( vindex < nbVertex) )
  {
    std::getline(fin, line);

    // skip any empty line
    if (line.empty())
      continue;

    // skip any line starting with "//"
    if (std::string::npos != line.find(std::string("//")) )
      continue;

    // otherwise collect vertex and texture info
    std::stringstream convertor(line);
    float x, y, z, u, v;
    
    convertor >> x >> y >> z >> u >> v;

    if (convertor.fail())
    {
      SoDebugError::postInfo(__FILE__, "Failed to read vertex info");
      _verticesCoords.clear();
      _textCoords.clear();
      _numVertices.clear();
      fin.close();
      return false;
    }

    _verticesCoords[vindex][0] = x;
    _verticesCoords[vindex][1] = y;
    _verticesCoords[vindex][2] = z;

    _textCoords[vindex][0] = u;
    _textCoords[vindex][1] = v;

    vindex++;
  }

  for (int i = 0; i < nbTriangles / 2; i++)
  {
    _numVertices[i] = 6;
  }

  return true;
 
}

void
SoXipNehe3DWorldLoader::evaluate()
{
   if (!fileName.getValue().getLength())
     return;

   if (_verticesCoords.empty() && _textCoords.empty())
   {
      if (!loadNehe3DWorld(std::string(fileName.getValue().getString())))
      {
         SoDebugError::postInfo(__FILE__, "Nehe 3D World can't be loaded :-( ");
         return;
      }
   }


   int numVertex = _verticesCoords.size();

   if (!numVertex)
     return;

   SO_ENGINE_OUTPUT(verticesCoords, SoMFVec3f, setNum(numVertex));
   SO_ENGINE_OUTPUT(textCoords, SoMFVec2f, setNum(numVertex));

   for (int i = 0; i < numVertex; i++)
   {
     SO_ENGINE_OUTPUT(verticesCoords, SoMFVec3f, set1Value(i, _verticesCoords[i]));
     SO_ENGINE_OUTPUT(textCoords, SoMFVec2f, set1Value(i, _textCoords[i]));
   }
   
   int numQuads = _numVertices.size();
   if (!numQuads)
     return;

   SO_ENGINE_OUTPUT(numVertices, SoMFUInt32, setNum(numQuads));
   for (int i= 0; i < numQuads; i++)
   {
     SO_ENGINE_OUTPUT(numVertices, SoMFUInt32, set1Value(i, _numVertices[i]));
   }
}