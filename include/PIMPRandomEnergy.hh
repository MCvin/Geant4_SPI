// ------------------------------------------------------------------
// Random Energy generator
// ------------------------------------------------------------------

#ifndef PIMPRandomEnergy_H
#define PIMPRandomEnergy_H 1

#include "globals.hh" 

class PIMPRandomEnergy 
{
public:
  PIMPRandomEnergy();
  ~PIMPRandomEnergy();
   
  /*  G4double GenerateRandomEnergy(G4int* Regions, 
				G4double Boundaries[], 
				G4double Indecies[],
				G4double Norms[]) ;
  
  G4double GenerateRandomEnergy(G4int* NumOfLines, 
				G4double Energy[], 
				G4double Probability[]) ;
  */
  G4double GenerateRandomEnergy(G4double Alpha, 
				G4double Beta, 
				G4double Ebreak,
				G4double LowEnergyTotal,
				G4double HighEnergyTotal) ;

private:
  G4double Random ;
};

#endif

