#include "SoXipNeheFlagGenerator.h"
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoIndexedFaceSet.h> // contains SO_END_FACE_INDEX definition

SO_ENGINE_SOURCE(SoXipNeheFlagGenerator);

// Initializes the SoXipNeheFlagGenerator class.
void
SoXipNeheFlagGenerator::initClass()
{
  SO_ENGINE_INIT_CLASS(SoXipNeheFlagGenerator, SoEngine, "Engine");
}


// Constructor
SoXipNeheFlagGenerator::SoXipNeheFlagGenerator()
{
  // Do standard constructor stuff
  SO_ENGINE_CONSTRUCTOR(SoXipNeheFlagGenerator);
 
  // Define the output, specifying its type
  SO_ENGINE_ADD_OUTPUT(gridVerticeCoords, SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(gridTextCoords, SoMFVec2f);
  SO_ENGINE_ADD_OUTPUT(vertexIndex, SoMFInt32);

  _sensor = new SoTimerSensor(timerSensorCBFunc, this);
  _sensor->setInterval(0.015);	// 1/2s 
  _sensor->schedule(); 
  
  // initialize vertex coordinates for the grid
  for(int x = 0; x < MAX_POINT; x++) // x plane
  {
    for(int y = 0; y < MAX_POINT; y++) // y plane 
    { 
      _gridVerticeCoords[x][y][0] = float( (x / 5.0f) - 4.5f );
      _gridVerticeCoords[x][y][1] = float( (y / 5.0f) - 4.5f );
      _gridVerticeCoords[x][y][2] = float( sin((((x / 5.0f) * 40.0f) / 360.0f) * 3.141592654 * 2.0f) );
    }
  }

  // initialize texture coordinates for the grid
  int i = 0;
  for(int x = 0; x < MAX_POINT; x++ )
  {
    for(int  y = 0; y < MAX_POINT; y++ )
    {
      _gridTextCoords[x][y][0] = float(x) / (MAX_POINT - 1);
      _gridTextCoords[x][y][1] = float(y) / (MAX_POINT - 1);
    }
  }

  // initialize vertex index
  int j = 0;
  for (int i = 0; i < NB_SQUARE; i++)
  {
    _gridVertexIndex[j] = i;                      // index bottom left
    _gridVertexIndex[j + 1] = i + MAX_POINT;      // index top left
    _gridVertexIndex[j + 2] = i + MAX_POINT + 1;  // index top right
    _gridVertexIndex[j + 3] = i + 1;              // index bottom right
    _gridVertexIndex[j + 4] = SO_END_FACE_INDEX;  // index end of face / square
    j += 5;
   }

}


SoXipNeheFlagGenerator::~SoXipNeheFlagGenerator()
{
  if (_sensor)
    delete _sensor;
}



void 
SoXipNeheFlagGenerator::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
  ((SoXipNeheFlagGenerator*)usr)->timer(sensor);

} 

void
SoXipNeheFlagGenerator::timer(SoSensor* sensor)
{
  float hold = 0;
  for(int y = 0; y < MAX_POINT; y++ )        
  {
    hold = _gridVerticeCoords[0][y][2];           // Store current value one left side of wave
    for(int  x = 0; x < MAX_POINT - 1; x++)       // Loop through the X plane
    {
      // current wave value equals value to the right
      _gridVerticeCoords[x][y][2] = _gridVerticeCoords[x+1][y][2];
    }
    _gridVerticeCoords[44][y][2] = hold;            // last value becomes the far left stored value
  }
   
  // will force the evaluate call
  this->touch();
     
}


void
SoXipNeheFlagGenerator::evaluate()
{

  int numVertex = sizeof(_gridVerticeCoords) / sizeof(SbVec3f);

  if (!numVertex)
    return;

  int numIndex = sizeof(_gridVertexIndex) / sizeof(int);
  if (!numIndex)
    return;

  SO_ENGINE_OUTPUT(gridVerticeCoords, SoMFVec3f, setNum(numVertex));
  SO_ENGINE_OUTPUT(gridTextCoords, SoMFVec2f, setNum(numVertex));
  SO_ENGINE_OUTPUT(vertexIndex, SoMFInt32, setNum(numIndex));


  int i = 0;
  for (int x = 0; x < MAX_POINT; x++) 
  {
    for (int y = 0; y < MAX_POINT; y++)
    {

      SO_ENGINE_OUTPUT(gridVerticeCoords, SoMFVec3f, set1Value(i, _gridVerticeCoords[x][y]));
      SO_ENGINE_OUTPUT(gridTextCoords, SoMFVec2f, set1Value(i, _gridTextCoords[x][y]));
      i++;
    }
  }

  for (int j = 0; j < NB_INDEX; j++)
  {
    SO_ENGINE_OUTPUT(vertexIndex, SoMFInt32, set1Value(j, _gridVertexIndex[j]));
  }
}