// Space Environment

#ifndef PIMPSpaceEnvironment_H
#define PIMPSpaceEnvironment_H 1

#include "globals.hh"

class PIMPSpaceEnvironment
{
public:
  PIMPSpaceEnvironment();
  ~PIMPSpaceEnvironment();

  G4int PIMPSetSpectralDetails(G4String SpecType);

  G4double Boundry[6];
  G4double Index[5];
  G4double Norm[5];
  G4int Breaks;

};

#endif

