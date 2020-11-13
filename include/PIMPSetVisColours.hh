// ------------------------------------------------------------------
// PIMPSetVisColours - detector stuff
// ------------------------------------------------------------------

#ifndef PIMPSetVisColours_H
#define PIMPSetVisColours_H 1

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

class PIMPSetVisColours 
{
public:
  PIMPSetVisColours();
  ~PIMPSetVisColours();
  
  G4VisAttributes* Green ;
  G4VisAttributes* RoyalBlue;
  G4VisAttributes* Red;
  G4VisAttributes* Yellow;
  G4VisAttributes* Purple;
  G4VisAttributes* Black;
  G4VisAttributes* SkyBlue;
  G4VisAttributes* White;
  G4VisAttributes* Grey;
  G4VisAttributes* DarkRed;
  G4VisAttributes* DarkYellow;
  G4VisAttributes* Orange;
  G4VisAttributes* Pink;

};

#endif
