// Space Environment
// DRW 10/4/03

#include "PIMPGammaRayBurst.hh"
#include "globals.hh"

PIMPGammaRayBurst::PIMPGammaRayBurst()
{;}

PIMPGammaRayBurst::~PIMPGammaRayBurst()
{;}

G4int PIMPGammaRayBurst::PIMPSetGammaRayBurstDetails(G4String SpecType)
{
  G4cout << "SpecType, inside: " << SpecType << G4endl ;

  G4int Status = 0 ;

  if (SpecType == "GRB")
    {
      // Effectively trigger 5614
      //Alpha = -0.3480 ;
      //Beta = -9.987 ;
      //Ebreak = 251.0 ; // in keV 
      // Seeing as the generic equation has an open solution when integrated
      // Energy range integrated from 12 keV to 30 MeV
      //LowEnergyTotal = 213.862;
      //HighEnergyTotal = 0.006 ;
	
      // Effectively trigger 5614
      // Alpha = -1.2386 ;
      // Beta = -2.4641 ;
      // Ebreak = 439.5 ; // in keV 
      // Seeing as the generic equation has an open solution when integrated
      // Energy range integrated from 12 keV to 30 MeV
      // LowEnergyTotal = 335.339248;
      // HighEnergyTotal = 13.38169 ;
	  
//       // Peak Burst GRB041219
//       Alpha  = -1.263 ;
//       Beta   = -1.918 ;
//       Ebreak =  441.165 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 20 keV to 30 MeV
//       LowEnergyTotal = 243.22;
//       HighEnergyTotal = 42.201;

//       // Peak Burst GRB041219  Second Analysis
//       Alpha  = -1.36317 ;
//       Beta   = -3.0 ;
//       Ebreak =  632.189 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 20 keV to 30 MeV
//       LowEnergyTotal = 300.961;
//       HighEnergyTotal = 4.159331;
 

 //   // High Limits Test GRB041219
//       Alpha  = -1.32317;
//       Beta   = -3.0 ;
//       Ebreak = 787.889 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 20 keV to 30 MeV
//       LowEnergyTotal = 311.582;
// 	HighEnergyTotal = 4.05163;
//  //   // Low Limits Test GRB041219
//       Alpha  = -1.40317;
//       Beta   = -3.0 ;
//       Ebreak = 525.789 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 20 keV to 30 MeV
//       LowEnergyTotal = 293.366;
// 	HighEnergyTotal = 4.29119;

 //   // Second Burst GRB041219
//       Alpha  = -1.76155 ;
//       Beta   = -3.0 ;
//       Ebreak = 364.537 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 20 keV to 30 MeV
//       LowEnergyTotal = 334.772;
//       HighEnergyTotal = 4.5972;

//Burst GRB061122

//       Alpha  = -1.11264 ;
//       Beta   = -2.5312 ;
//       Ebreak = 196.764 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 20 keV to 30 MeV
//       LowEnergyTotal = 180.344;
//       HighEnergyTotal = 14.0716;

//Burst GRB060901

      Alpha  = -0.6052 ;
      Beta   = -1.9513 ;
      Ebreak = 95.5697 ; // in keV 
      // Seeing as the generic equation has an open solution when integrated
      // Energy range integrated from 20 keV to 30 MeV
      LowEnergyTotal = 77.8563;
      HighEnergyTotal = 30.0492;



//       // Burst GRB041219
//       Alpha  = -1.494 ;
//       Beta   = -2.209 ;
//       Ebreak =  345.0 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 12 keV to 30 MeV
//       LowEnergyTotal = 262.866;
//       HighEnergyTotal = 25.825 ;

//       // Burst GRB041219
//       Alpha  = -1.09 ;
//       Beta   = -2.16445 ;
//       Ebreak =  101.0 ; // in keV 
//       // Seeing as the generic equation has an open solution when integrated
//       // Energy range integrated from 12 keV to 30 MeV
//       LowEnergyTotal = 112.287;
//       HighEnergyTotal = 29.069 ;

    }
  else
    {
      Status = 1 ;
    }


  return Status;

}
