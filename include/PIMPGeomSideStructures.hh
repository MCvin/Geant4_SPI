// ------------------------------------------------------------------
// PIMPGeometry - SideStructures
// ------------------------------------------------------------------

#ifndef PIMPGeomSideStructures_H
#define PIMPGeomSideStructures_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomSideStructures : public PIMPBaseSelectMaterial,
			       public PIMPSetVisColours
{
public:
  PIMPGeomSideStructures(const G4MaterialTable* Materials);
  ~PIMPGeomSideStructures();
  
  void CreatePlusY(const G4MaterialTable* Materials, 
		   G4LogicalVolume* Parent,  
		   const G4ThreeVector* Position, 
		   G4RotationMatrix* Rotation);

  void CreateMinusY(const G4MaterialTable* Materials, 
		   G4LogicalVolume* Parent,  
		   const G4ThreeVector* Position, 
		   G4RotationMatrix* Rotation);
  


private:
  G4LogicalVolume* l_SideStructurePlusY;
  G4LogicalVolume* l_SideStructureMinusY;

  
};

#endif


