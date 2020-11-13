// Space Environment
// DRW 14/1/03

#ifndef PIMPGammaRayBurst_H
#define PIMPGammaRayBurst_H 1

#include "globals.hh"

class PIMPGammaRayBurst
{
public:
  PIMPGammaRayBurst();
  ~PIMPGammaRayBurst();

  G4int PIMPSetGammaRayBurstDetails(G4String SpecType);

  G4double Alpha;
  G4double Beta;
  G4double Ebreak;
  G4double LowEnergyTotal ;
  G4double HighEnergyTotal ;

};

#endif
