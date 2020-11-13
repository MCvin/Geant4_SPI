// ------------------------------------------------------------------
// PIMPGeometry - SPIStirlingCooler
// ------------------------------------------------------------------

#ifndef PIMPGeomSPIStirlingCooler_H
#define PIMPGeomSPIStirlingCooler_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomSPIStirlingCooler : public PIMPBaseSelectMaterial,
				  public PIMPSetVisColours
{
public:
  PIMPGeomSPIStirlingCooler(const G4MaterialTable* Materials);
  ~PIMPGeomSPIStirlingCooler();
  
  void Create(G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation,
	      G4int Copy);

private:
  G4LogicalVolume* l_SPIStirlingCooler ;
 
}; 

#endif


