// ------------------------------------------------------------------
// PIMPGeometry - SPI
// ------------------------------------------------------------------

#ifndef PIMPGeomSPI_H
#define PIMPGeomSPI_H 1

class G4VPhysicalVolume;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MaterialTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "PIMPSensitive.hh"
#include "PIMPBaseSelectMaterial.hh"
#include "PIMPSetVisColours.hh"

class PIMPGeomSPI : public PIMPBaseSelectMaterial,
		    public PIMPSetVisColours
{
public:
  PIMPGeomSPI(const G4MaterialTable* Materials, PIMPSensitive* Sens);
  ~PIMPGeomSPI();

  void Create(const G4MaterialTable* Materials, 
	      G4LogicalVolume* Parent,  
	      const G4ThreeVector* Position, 
	      G4RotationMatrix* Rotation);

  void PlacePixel(G4LogicalVolume* Child,
		  G4LogicalVolume* Parent,
		  G4int TileNum,  
		  G4double Xposition,
		  G4double Yposition) ;
    		  

private:
  G4LogicalVolume* l_SPI;
};

#endif


