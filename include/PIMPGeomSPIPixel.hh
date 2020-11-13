// ------------------------------------------------------------------
// PIMPGeometry - SPIPixel
// ------------------------------------------------------------------

#ifndef PIMPGeomSPIPixel_H
#define PIMPGeomSPIPixel_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPSensitive.hh"
#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomSPIPixel : public PIMPBaseSelectMaterial,
			 public PIMPSetVisColours
{
public:
  PIMPGeomSPIPixel(const G4MaterialTable* Materials, PIMPSensitive* Sens);
  ~PIMPGeomSPIPixel();

  void Create(G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation,
	      G4int Copy);

private:
  G4LogicalVolume* l_SPIDetectorPixel ;
  G4LogicalVolume* l_SPIDetectorPixLow ;
  G4LogicalVolume* l_SPIDetectorPixBottom ;
 
};

#endif


