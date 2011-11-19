#ifndef SOXIPTEXT3_H
#define SOXIPTEXT3_H

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/SbBox.h>

#include <FTLibrary.h>

class SoGLRenderAction;
class SoBoundingBoxAction;
class FTFont;


class SoXipText3: public SoNode
{
  SO_NODE_HEADER(SoXipText3);

public:
 
  /// Constructor
  SoXipText3();

  /// String to be displayed
  SoSFString		string;
  SoSFBool      bboxOn; 
  SoSFVec3f     bboxCenter;
  SoSFFloat     depth;

  /// Open Inventor class initialization
  static void initClass();

protected:
  /// Destructor
  virtual ~SoXipText3();

  SbBool createFont( const SbName& fontName, int fontSize );
  void deleteFont();
 
 
  virtual void GLRender( SoGLRenderAction* action );
  virtual void computeBBox(SoAction* action, SbBox3f& bbox, SbVec3f& center);
  //virtual void generatePrimitives(SoAction* action);
  virtual void getBoundingBox( SoGetBoundingBoxAction* action);

  void onStringChange();


  SbName	        _currentFontName;
  int				      _currentFontType;
  float           _depth;
  FTFont*	        _font;
  SbBox3f			    _BBox;
};

#endif // SOXIPTEXT3_H