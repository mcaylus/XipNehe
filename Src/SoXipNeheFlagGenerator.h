#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFInt32.h>

// 45 * 45 points grid
const int MAX_POINT = 45;
const int NB_VERTEX = MAX_POINT * MAX_POINT;
const int NB_SQUARE = (MAX_POINT - 1) * (MAX_POINT - 1);
const int NB_INDEX = NB_SQUARE * 5; // 4 index for a square + SO_END_FACE_INDEX -> total 5

class SoTimerSensor;

class SoXipNeheFlagGenerator : public SoEngine {

    SO_ENGINE_HEADER(SoXipNeheFlagGenerator);

 public:

    // Outputs:
    SoEngineOutput gridVerticeCoords; // SoMFVec3f
    SoEngineOutput gridTextCoords;    // SoMFVec2f
    SoEngineOutput vertexIndex;       // SoMFInt32
  
    // Initialization
    static void initClass();
  
    // Constructor
    SoXipNeheFlagGenerator();

private:
 
    // Destructor
    virtual ~SoXipNeheFlagGenerator();

    // Evaluation method
    virtual void evaluate();

    static void timerSensorCBFunc(void *usr, SoSensor *sensor);
    void timer(SoSensor* sensor);

    SoTimerSensor*  _sensor;
    SbVec3f         _gridVerticeCoords[MAX_POINT][MAX_POINT];
    SbVec2f         _gridTextCoords[MAX_POINT][MAX_POINT];
    int             _gridVertexIndex[NB_INDEX];
};