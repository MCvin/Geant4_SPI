// ------------------------------------------------------------------
// PIMPGeometry - IBIS
// ------------------------------------------------------------------

#ifndef PIMPGeomIBIS_H
#define PIMPGeomIBIS_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomIBIS : public PIMPBaseSelectMaterial,
		      public PIMPSetVisColours
{
public:
  PIMPGeomIBIS(const G4MaterialTable* Materials);
  ~PIMPGeomIBIS();

  void Create(const G4MaterialTable* Materials, 
	      G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation);

private:
  G4LogicalVolume* l_IBIS;
};

#endif


