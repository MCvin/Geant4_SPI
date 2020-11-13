// ------------------------------------------------------------------
// PIMPGeometry - SPIMidVeto
// ------------------------------------------------------------------

#ifndef PIMPGeomSPIMidVeto_H
#define PIMPGeomSPIMidVeto_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPSensitive.hh"
#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomSPIMidVeto : public PIMPBaseSelectMaterial,
			     public PIMPSetVisColours
{
public:
  PIMPGeomSPIMidVeto(const G4MaterialTable* Materials, PIMPSensitive* Sens);
  ~PIMPGeomSPIMidVeto();
  
  void Create(G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation,
	      G4int Copy);

private:
  G4LogicalVolume* l_SPIMidVETO ;

 
};

#endif


