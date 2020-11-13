// ------------------------------------------------------------------
// PIMPGeometry - SideStructures
// ------------------------------------------------------------------

#include "PIMPGeomSideStructures.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trap.hh"
#include "G4Sphere.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4MaterialTable.hh"

// #include "G4VPhysicalVolume.hh"

PIMPGeomSideStructures::PIMPGeomSideStructures(const G4MaterialTable* Materials)
{
  
  G4cout << "Create: SideStructures" << G4endl ;

  // CSBP
  const G4String Name = "SideStructure";
  G4Box* s_SideStructurePlusY = new G4Box(Name,
					  (289/2)*cm,
					  (49.65/2)*cm,
					  (350/2)*cm);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_SideStructurePlusY = new G4LogicalVolume(s_SideStructurePlusY,
				     Material,
				     Name);
  // CSBM
  G4Box* s_SideStructureMinusY = new G4Box(Name,
					   (289/2)*cm,
					   (49.65/2)*cm,
					   (350/2)*cm);  
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_SideStructureMinusY = new G4LogicalVolume(s_SideStructureMinusY,
				     Material,
				     Name);

  // CPZ1
  const G4String SSTrianglesName = "SSTriangles";
  G4Trap* s_SSTriangles = new G4Trap(SSTrianglesName,
				     (237/2)*cm,
				     5.98*deg, 90*deg,
				     (49.65/2)*cm, 2.*cm, 2.*cm, 0.*deg,
				     0.001*cm, 2.*cm,2.*cm, 0.*deg);
  Material =  PIMPSelectMaterial("PLMHoney", Materials) ;
  G4LogicalVolume* l_SSTriangles = new G4LogicalVolume(s_SSTriangles,
				      Material,
				      SSTrianglesName);
  G4VPhysicalVolume* p_SSTriangles = new G4PVPlacement(0,
						       G4ThreeVector(-27.8*cm,
								     (49.65/4)*cm,
								     (-350/2 + 237/2)*cm),
						       l_SSTriangles,
						       SSTrianglesName,
						       l_SideStructurePlusY,
						       false,
						       0);
  G4RotationMatrix* Rotate1 = new G4RotationMatrix ;
  Rotate1->rotateZ(180*deg);
  p_SSTriangles = new G4PVPlacement(Rotate1,
				    G4ThreeVector(-27.8*cm,
						  (-49.65/4)*cm,
						  (-350/2 + 237/2)*cm),
				    l_SSTriangles,
				    SSTrianglesName,
				    l_SideStructureMinusY,
				    false,
				    0);
  

  // ------------------- VISUALISATION -----------------------

  l_SSTriangles->SetVisAttributes(SkyBlue);
  // l_SideStructurePlusY->SetVisAttributes(SkyBlue);
  
}

PIMPGeomSideStructures::~PIMPGeomSideStructures()
{;}

void PIMPGeomSideStructures::CreatePlusY(const G4MaterialTable* Materials, 
					 G4LogicalVolume* Parent, 
					 const G4ThreeVector* Position, 
					 G4RotationMatrix* Rotation)
{  

  // Create SideStructures Mother volume 
  
  const G4String Name = "SideStructures" ;
  G4VPhysicalVolume* p_SideStructurePlusY = new G4PVPlacement(Rotation,
							      *Position,
							      l_SideStructurePlusY,
							      Name,
							      Parent,
							      false,
							      0);	

  return ;
}

void PIMPGeomSideStructures::CreateMinusY(const G4MaterialTable* Materials, 
					  G4LogicalVolume* Parent, 
					  const G4ThreeVector* Position, 
					  G4RotationMatrix* Rotation)
{  

  // Create SideStructures Mother volume 
  
  const G4String Name = "SideStructures" ;
  G4VPhysicalVolume* p_SideStructureMinusY = new G4PVPlacement(Rotation,
							       *Position,
							       l_SideStructureMinusY,
							       Name,
							       Parent,
							       false,
							       0);	

  return ;
}













