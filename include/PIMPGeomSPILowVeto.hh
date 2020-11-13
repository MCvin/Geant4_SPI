// ------------------------------------------------------------------
// PIMPGeometry - SPILowVeto
// ------------------------------------------------------------------

#ifndef PIMPGeomSPILowVeto_H
#define PIMPGeomSPILowVeto_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trap.hh"

#include "PIMPSensitive.hh"
#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomSPILowVeto : public PIMPBaseSelectMaterial,
			   public PIMPSetVisColours
{
public:
  PIMPGeomSPILowVeto(const G4MaterialTable* Materials, PIMPSensitive* Sens);
  ~PIMPGeomSPILowVeto();
  
  void Create(G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation,
	      G4int Copy);

  void PlacePMT(G4LogicalVolume* Child,
		G4LogicalVolume* Parent,
		G4int PMTNum,  
		G4double Xposition,
		G4double Yposition,
		G4double Zposition,
		G4RotationMatrix* Rotation) ;
 
  void PlaceElec(G4LogicalVolume* EChild,
		 G4LogicalVolume* EParent,
		 G4int ElecNum,  
		 G4double EXposition,
		 G4double EYposition,
		 G4double EZposition,
		 G4RotationMatrix* ERotation) ;

private:
  G4LogicalVolume* l_SPILowVETO ;
  G4VPhysicalVolume* p_SPILowVetoPMT;
  G4VPhysicalVolume* p_SPILowSmallElec;
};

#endif
