// ------------------------------------------------------------------
// PIMPGeometry - detector stuff
// DRW
// ------------------------------------------------------------------

#ifndef PIMPGeometry_H
#define PIMPGeometry_H 1

class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSensitive.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeometry : public G4VUserDetectorConstruction,
		     public PIMPBaseSelectMaterial,
		     public PIMPSetVisColours
{
public:
  PIMPGeometry(PIMPSensitive* SensIn);
  ~PIMPGeometry();
  
  // PIMPSensitiveGe *SGe; // pointer to sensitive detector
  /*
  const G4VPhysicalVolume* GetPhysSens()   {return physSens;};
  const G4LogicalVolume* GetLogiSens()   {return logiSens;};
  */

public:
  G4VPhysicalVolume* Construct();

  //  G4VPhysicalVolume *physSens; // pointer to sensitive vol
  
  G4LogicalVolume* SensitiveLogical ; // pointer to sensitive vol

  PIMPSensitive* Sens;

};

#endif

