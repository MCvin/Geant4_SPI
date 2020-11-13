// ------------------------------------------------------------------
// PIMPGeometry - JEMX
// ------------------------------------------------------------------

#ifndef PIMPGeomJEMX_H
#define PIMPGeomJEMX_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomJEMX : public PIMPBaseSelectMaterial,
		     public PIMPSetVisColours
{
public:
  PIMPGeomJEMX(const G4MaterialTable* Materials);
  ~PIMPGeomJEMX();

  void Create(const G4MaterialTable* Materials, 
	      G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation);

private:
  G4LogicalVolume* l_JEMX;
};

#endif


