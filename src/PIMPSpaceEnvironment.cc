// Space Environment

#include "PIMPSpaceEnvironment.hh"
#include "globals.hh"

PIMPSpaceEnvironment::PIMPSpaceEnvironment()
{;}

PIMPSpaceEnvironment::~PIMPSpaceEnvironment()
{;}

G4int PIMPSpaceEnvironment::PIMPSetSpectralDetails(G4String SpecType)
{
  G4cout << "SpecType: " << SpecType << G4endl ;

  G4int Status = 0 ;

  if (SpecType == "CDX")
    {

      Breaks = 2;

      /*
      Boundry[0] = 0.01 ;
      Boundry[1] = 0.02 ;
      Boundry[2] = 0.1 ;
      Boundry[3] = 10.0 ;
      
      Index[0] = -1.4 ;
      Index[1] = -2.38 ;
      Index[2] = -2.3 ;

      Norm[0] = 0.54 ;
      Norm[1] = 0.0117 ;
      Norm[2] = 0.014 ;
      */
      /*
      Boundry[0] = 0.02 ;
      Boundry[1] = 0.1 ;
      Boundry[2] = 10.0 ;
      

      Index[0] = -2.38 ;
      Index[1] = -2.3 ;


      Norm[0] = 0.0117 ;
      Norm[1] = 0.014 ;
      */

      //  GRB 041219 ignoring first 2 points
      Boundry[0] = 0.02 ;   // lower bound 40 keV
      Boundry[1] = 0.345 ;  // 345.0 +/- 49.01 keV
      Boundry[2] = 8.0 ;    // upper boune 8 MeV
      

      Index[0] = -1.494 ;   // -1.494 +/- 0.03213
      Index[1] = -2.209 ;   // -2.209 +/- 0.1103  


      Norm[0] = 0.0117 ;
      Norm[1] = 0.014 ;

    }
  else if (SpecType == "CR")
    {
      Breaks = 5;

      Boundry[0] = 40. ;
      Boundry[1] = 193.0 ;
      Boundry[2] = 565.0 ;
      Boundry[3] = 3440.0 ;
      Boundry[4] = 25500.0 ;
      Boundry[5] = 1000000.0 ;

      Index[0] = 1.0 ;
      Index[1] = 0.04 ;
      Index[2] =-1.14 ;
      Index[3] = -2.04 ;
      Index[4] = -2.69 ;

      Norm[0] = 7.85E-7 ;
      Norm[1] = 1.29E-4 ;
      Norm[2] = 0.225 ;
      Norm[3] = 344. ;
      Norm[4] = 244000.;
    }
  else if (SpecType == "GRB")
    {
      Status = 0;
    }
  else
    {
      Status = 1 ;
    }


  return Status;

}







