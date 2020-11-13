
// ------------------------------------------------------------------
// PIMPGeometry - SPIPixel Ge Pixel
// DRW 3/3/04
// ------------------------------------------------------------------

#include "PIMPGeomSPIPixel.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trap.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
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


// G4LogicalVolume* Sensitive ;

PIMPGeomSPIPixel::PIMPGeomSPIPixel(const G4MaterialTable* Materials, PIMPSensitive* Sens)
{

  // Now to define the detector element ...
  
  const G4String SPIDetectorPixelName = "SPIDetectorPixel"; // SDPX
  const G4double DetPixZ[2] = {11.0*cm, 20.87*cm} ;
  const G4double DetPixInner[2] = {0.*cm,0.*cm} ; 
  const G4double DetPixOuter[2] = {3.0*cm,3.0*cm} ;  
  G4Polyhedra* s_SPIDetectorPixel = new G4Polyhedra(SPIDetectorPixelName,
						    30.*deg,360.*deg,
						    6,2,
						    DetPixZ, DetPixInner, DetPixOuter) ;
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials);
  l_SPIDetectorPixel = new G4LogicalVolume(s_SPIDetectorPixel,
					   Material,
					   SPIDetectorPixelName);

  const G4String SPIDetectorPixLowName = "SPIDetectorPixLow"; // SDP1
  const G4double PixLZ[2] = {5.0*cm,8.0*cm} ;
  G4Polyhedra* s_SPIDetectorPixLow = new G4Polyhedra(SPIDetectorPixLowName,
						     30.*deg,360.*deg,
						     6,2,
						     PixLZ, DetPixInner, DetPixOuter) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  l_SPIDetectorPixLow = new G4LogicalVolume(s_SPIDetectorPixLow,
					    Material,
					    SPIDetectorPixLowName);
  /*
  G4VPhysicalVolume* p_SPIDetectorPixLow = new G4PVPlacement(0,
							     G4ThreeVector(9.85*cm,
									   0.*cm,
									   23.3*cm),
							     l_SPIDetectorPixLow,
							     SPIDetectorPixLowName,
							     l_SPIDetectorUnit,
							     false,
							     0);
  */
  const G4String SPIDetectorPixBottomName = "SPIDetectorPixBottom"; // SDP2
  const G4double PixBZ[2] = {0.0*cm,4.5*cm} ;
  G4Polyhedra* s_SPIDetectorPixBottom = new G4Polyhedra(SPIDetectorPixBottomName,
							30.*deg,360.*deg,
							6,2,
							PixBZ, DetPixInner, DetPixOuter) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  l_SPIDetectorPixBottom = new G4LogicalVolume(s_SPIDetectorPixBottom,
					       Material,
					       SPIDetectorPixBottomName);
  /*
    G4VPhysicalVolume* p_SPIDetectorPixBottom = new G4PVPlacement(0,
    G4ThreeVector(9.85*cm,
    0.*cm,
										23.3*cm),
								  l_SPIDetectorPixBottom,
								  SPIDetectorPixBottomName,
								  l_SPIDetectorUnit,
								  false,
								  0);
  */


  //************************* New Ge geometry more accurate (M. Chauvin 01/2012) ***********************************************
  //--- Germanium crystal built from 3 volume association
  const G4String GeHexaName = "GeHexa";		//Theorical shape of the Ge crystal
  const G4double GeHexaZ[4] = 	  {0.0*cm, 0.5*cm, 6.442*cm, 6.942*cm} ;
  const G4double GeHexaInner[4] = {0.0*cm, 0.0*cm, 0.0*cm, 0.0*cm} ; 
  const G4double GeHexaOuter[4] = {2.3*cm,2.8*cm, 2.8*cm,2.3*cm} ;
  G4Polyhedra* s_GeHexa = new G4Polyhedra(GeHexaName,
					  30.*deg, 360.*deg, 
					  6, 4,
					  GeHexaZ, GeHexaInner, GeHexaOuter) ;											 
  const G4String GeRmaxName = "GeRmax";		//External Ge crystal diameter
  G4Tubs* s_GeRmax = new G4Tubs(GeRmaxName, 0.*cm, 3.03*cm, 6.942*cm,
				0.*deg,360.*deg) ;
  const G4String GeHoleName = "GeHole";		//Hole in the Ge crystal
  G4Tubs* s_GeHole = new G4Tubs(GeHoleName, 0.*cm, 0.3*cm, 5.5*cm,
				0.*deg,360.*deg) ;

  const G4String SPIDetGermaniumName = "SPIDetGermanium"; //Final SDGE germanium crystal
  G4IntersectionSolid* s_inter = new G4IntersectionSolid("Hexa*Tube", s_GeHexa, s_GeRmax);
  G4SubtractionSolid* s_SPIDetGermanium = new G4SubtractionSolid(SPIDetGermaniumName, s_inter, s_GeHole);

  Material =  PIMPSelectMaterial("Germanium", Materials);
  G4LogicalVolume* l_SPIDetGermanium = new G4LogicalVolume(s_SPIDetGermanium,
							   Material,
							   SPIDetGermaniumName);
  G4VPhysicalVolume* p_SPIDetGermanium = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 13.37*cm),
							   l_SPIDetGermanium,
							   SPIDetGermaniumName,
							   l_SPIDetectorPixel,
							   false,
							   0);

  /*
  //--- Old Germanium crystal geometry
  const G4String SPIDetGermaniumName = "SPIDetGermanium"; // SDGE germanium crystal
  const G4double GePixZ[4] = {0.0*cm,0.5*cm,6.5*cm,7.0*cm} ;
  const G4double GePixInner[4] = {0.*cm,0.*cm, 0.*cm,0.*cm} ; 
  const G4double GePixOuter[4] = {2.31*cm,2.81*cm, 2.81*cm,2.31*cm} ; 
  G4Polyhedra* s_SPIDetGermanium = new G4Polyhedra(SPIDetGermaniumName,
						   30.*deg,360.*deg,
						   6,4,
						   GePixZ, GePixInner, GePixOuter) ;
  Material =  PIMPSelectMaterial("Germanium", Materials);
  G4LogicalVolume* l_SPIDetGermanium = new G4LogicalVolume(s_SPIDetGermanium,
							   Material,
							   SPIDetGermaniumName);
  G4VPhysicalVolume* p_SPIDetGermanium = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 13.37*cm),
							   l_SPIDetGermanium,
							   SPIDetGermaniumName,
							   l_SPIDetectorPixel,
							   false,
							   0);

  const G4String SPIDetGermHoleName = "SPIDetGermHole"; // SHOL
  G4Tubs* s_SPIDetGermHole = new G4Tubs(SPIDetGermHoleName, 0.*cm, 0.3*cm, 3.0*cm
					,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPIDetGermHole = new G4LogicalVolume(s_SPIDetGermHole,
							  Material,
							  SPIDetGermHoleName);
  G4VPhysicalVolume* p_SPIDetGermHole = new G4PVPlacement(0,
							  G4ThreeVector(0.*cm,
									0.*cm,
									3.0*cm),
							  l_SPIDetGermHole,
							  SPIDetGermHoleName,
							  l_SPIDetGermanium,
							  false,
							  0);
  */

  const G4String SPIDetCap1suleName = "SPIDetCap1sule"; // SCA1
  const G4double Cap1Z[4] = {0.0*cm,3.0*cm,3.0*cm,9.0*cm} ;
  const G4double Cap1Inner[4] = {2.85*cm,2.85*cm,2.85*cm,2.85*cm} ; 
  const G4double Cap1Outer[4] = {2.97*cm,2.97*cm, 2.95*cm,2.95*cm} ; 
  G4Polyhedra* s_SPIDetCap1sule = new G4Polyhedra(SPIDetCap1suleName,
						 30.*deg,360.*deg,
						 6,4,
						 Cap1Z, Cap1Inner, Cap1Outer) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIDetCap1sule = new G4LogicalVolume(s_SPIDetCap1sule,
							 Material,
							 SPIDetCap1suleName);
  G4VPhysicalVolume* p_SPIDetCap1sule = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       11.0*cm),
							 l_SPIDetCap1sule,
							 SPIDetCap1suleName,
							 l_SPIDetectorPixel,
							 false,
							 0);

  const G4String SPIDetCap2suleName = "SPIDetCap2sule"; // SCA2
  const G4double Cap2Z[4] = {0.0*cm,0.4*cm,0.4*cm,0.48*cm} ;
  const G4double Cap2Inner[4] = {2.85*cm,2.45*cm,0.0*cm,0.0*cm} ; 
  const G4double Cap2Outer[4] = {2.95*cm,2.55*cm, 2.55*cm,2.47*cm} ; 
  G4Polyhedra* s_SPIDetCap2sule = new G4Polyhedra(SPIDetCap2suleName,
						  30.*deg,360.*deg,
						  6,4,
						  Cap2Z, Cap2Inner, Cap2Outer) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIDetCap2sule = new G4LogicalVolume(s_SPIDetCap2sule,
							  Material,
							  SPIDetCap2suleName);
  G4VPhysicalVolume* p_SPIDetCap2sule = new G4PVPlacement(0,
							  G4ThreeVector(0.*cm,
									0.*cm,
									20.0*cm),
							  l_SPIDetCap2sule,
							  SPIDetCap2suleName,
							  l_SPIDetectorPixel,
							  false,
							  0);
  
  const G4String SPIDetBotCoverName = "SPIDetBotCover"; // SCOU
  const G4double BotCovZ[8] = {0.0*cm,0.4*cm,0.4*cm,0.95*cm, 
			 0.95*cm,1.25*cm, 1.25*cm, 1.35*cm} ;
  const G4double BotCovInner[8] = {0.78*cm,0.78*cm,1.48*cm,1.48*cm, 
			     1.78*cm, 1.78*cm, 1.98*cm, 1.98*cm } ; 
  const G4double BotCovOuter[8] = {2.85*cm,2.85*cm, 2.85*cm,2.85*cm, 
			     2.25*cm, 2.25*cm, 2.25*cm, 2.25*cm} ; 
  G4Polyhedra* s_SPIDetBotCover = new G4Polyhedra(SPIDetBotCoverName,
						  30.*deg,360.*deg,
						  6,8,
						  BotCovZ, BotCovInner, BotCovOuter) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIDetBotCover = new G4LogicalVolume(s_SPIDetBotCover,
							  Material,
							  SPIDetBotCoverName);
  G4VPhysicalVolume* p_SPIDetBotCover = new G4PVPlacement(0,
							  G4ThreeVector(0.*cm,
									0.*cm,
									11.0*cm),
							  l_SPIDetBotCover,
							  SPIDetBotCoverName,
							  l_SPIDetectorPixel,
							  false,
							  0);

  const G4String SPIDetPoussoirName = "SPIDetPoussoir"; // SPOU
  const G4double PouZ[4] = {0.0*cm,0.1*cm,0.1*cm,0.5*cm} ;
  const G4double PouInner[4] = {1.98*cm,1.98*cm,1.78*cm,1.78*cm} ; 
  const G4double PouOuter[4] = {2.73*cm,2.73*cm, 2.73*cm,2.73*cm} ; 
  G4Polyhedra* s_SPIDetPoussoir = new G4Polyhedra(SPIDetPoussoirName,
						  30.*deg,360.*deg,
						  6,4,
						  PouZ, PouInner, PouOuter) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIDetPoussoir = new G4LogicalVolume(s_SPIDetPoussoir,
							  Material,
							  SPIDetPoussoirName);
  G4VPhysicalVolume* p_SPIDetPoussoir = new G4PVPlacement(0,
							  G4ThreeVector(0.*cm,
									0.*cm,
									12.35*cm),
							  l_SPIDetPoussoir,
							  SPIDetPoussoirName,
							  l_SPIDetectorPixel,
							  false,
							  0);
  
  const G4String SPIDetRessortName = "SPIDetRessort"; // SRES
  G4Tubs* s_SPIDetRessort = new G4Tubs(SPIDetRessortName, 0.7*cm, 1.98*cm, 0.06*cm
				       ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Stainless", Materials);
  G4LogicalVolume* l_SPIDetRessort = new G4LogicalVolume(s_SPIDetRessort,
							 Material,
							 SPIDetRessortName);
  G4VPhysicalVolume* p_SPIDetRessort = new G4PVPlacement(0,
							  G4ThreeVector(0.*cm,
									0.*cm,
									12.31*cm),
							  l_SPIDetRessort,
							  SPIDetRessortName,
							  l_SPIDetectorPixel,
							  false,
							  0);
  /* Not used in original TIMM
  const G4String SPIDetScrewMountingName = "SPIDetScrewMounting"; // SCMS
  G4Tubs* s_SPIDetScrewMounting = new G4Tubs(SPIDetScrewMountingName, 2.183*cm, 2.5*cm, 1.0*cm
					     ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Titanium", Materials);
  G4LogicalVolume* l_SPIDetScrewMounting = new G4LogicalVolume(s_SPIDetScrewMounting,
							       Material,
							       SPIDetScrewMountingName);
  G4VPhysicalVolume* p_SPIDetScrewMounting = new G4PVPlacement(0,
							       G4ThreeVector(0.*cm,
									     0.*cm,
									     12.31*cm),
							       l_SPIDetScrewMounting,
							       SPIDetScrewMountingName,
							       l_SPIDetectorPixel,
							       false,
							       0);
  */
  const G4String SPIDetScrew1sName = "SPIDetScrew1s"; // SP1S
  G4Tubs* s_SPIDetScrew1s = new G4Tubs(SPIDetScrew1sName, 0.*cm, 3.0*cm, 0.047*cm
				      ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Titanium", Materials);
  G4LogicalVolume* l_SPIDetScrew1s = new G4LogicalVolume(s_SPIDetScrew1s,
							Material,
							SPIDetScrew1sName);
  G4VPhysicalVolume* p_SPIDetScrew1s = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       7.953*cm),
							 l_SPIDetScrew1s,
							 SPIDetScrew1sName,
							 l_SPIDetectorPixLow,
							 false,
							 0);
  const G4String SPIDetScrew1aName = "SPIDetScrew1a"; // SP1A  Al
  G4Tubs* s_SPIDetScrew1a = new G4Tubs(SPIDetScrew1aName, 0.*cm, 3.0*cm, 0.033*cm
				       ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIDetScrew1a = new G4LogicalVolume(s_SPIDetScrew1a,
							 Material,
							 SPIDetScrew1aName);
  G4VPhysicalVolume* p_SPIDetScrew1a = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       7.873*cm),
							 l_SPIDetScrew1a,
							 SPIDetScrew1aName,
							 l_SPIDetectorPixLow,
							 false,
							 0);
  const G4String SPIDetScrew2sName = "SPIDetScrew2s"; // SP2S
  G4Tubs* s_SPIDetScrew2s = new G4Tubs(SPIDetScrew2sName, 0.*cm, 3.0*cm, 0.059*cm
				       ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Titanium", Materials);
  G4LogicalVolume* l_SPIDetScrew2s = new G4LogicalVolume(s_SPIDetScrew2s,
							 Material,
							 SPIDetScrew2sName);
  G4VPhysicalVolume* p_SPIDetScrew2s = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       4.441*cm),
							 l_SPIDetScrew2s,
							 SPIDetScrew2sName,
							 l_SPIDetectorPixBottom,
							 false,
							 0);  
  const G4String SPIDetScrew2aName = "SPIDetScrew2a"; // SP2A  Al
  G4Tubs* s_SPIDetScrew2a = new G4Tubs(SPIDetScrew2aName, 0.*cm, 3.0*cm, 0.059*cm
				       ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIDetScrew2a = new G4LogicalVolume(s_SPIDetScrew2a,
							 Material,
							 SPIDetScrew2aName);
  G4VPhysicalVolume* p_SPIDetScrew2a = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       4.282*cm),
							 l_SPIDetScrew2a,
							 SPIDetScrew2aName,
							 l_SPIDetectorPixBottom,
							 false,
							 0);
  const G4String SPIDetScrew2cName = "SPIDetScrew2c"; // SP2C
  G4Tubs* s_SPIDetScrew2c = new G4Tubs(SPIDetScrew2cName, 0.*cm, 3.0*cm, 0.059*cm
				       ,0.*deg,360.*deg) ;
  Material =  PIMPSelectMaterial("Copper", Materials);
  G4LogicalVolume* l_SPIDetScrew2c = new G4LogicalVolume(s_SPIDetScrew2c,
							 Material,
							 SPIDetScrew2cName);
  G4VPhysicalVolume* p_SPIDetScrew2c = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       4.132*cm),
							 l_SPIDetScrew2c,
							 SPIDetScrew2cName,
							 l_SPIDetectorPixBottom,
							 false,
							 0); 
 
  // ------------------- VISUALISATION -----------------------
  
  l_SPIDetGermanium->SetVisAttributes(RoyalBlue);

 // -------------------- SENSITIVITY ---------------------------.
 // Sensitive = l_SPIDetGermanium ;
 l_SPIDetGermanium->SetSensitiveDetector(Sens);


}


PIMPGeomSPIPixel::~PIMPGeomSPIPixel()
{;}

void PIMPGeomSPIPixel::Create(G4LogicalVolume* Parent, 
			      const G4ThreeVector* Position, 
			      G4RotationMatrix* Rotation,
			      G4int Copy)
{  
  //  G4cout << "test3" << G4endl ;
  const G4String SPIDetectorPixelName = "SPIDetectorPixel" ;

  // G4cout << *Position << G4endl ;
  // G4cout << *Rotation << G4endl ;
  // G4cout << l_SPIDetectorPixel->GetName() << G4endl ;
  // G4cout << SPIDetectorPixelName << G4endl ;
  // G4cout << Parent->GetName() << G4endl ;
  
  // Create 

  G4VPhysicalVolume* p_SPIDetectorPixel = new G4PVPlacement(Rotation,
							    *Position,
							    l_SPIDetectorPixel,
							    SPIDetectorPixelName,
							    Parent,
							    false,
							    Copy);
  
  // G4cout << "test3" << G4endl ;	
  const G4String SPIDetectorPixelLowName = "SPIDetectorPixelLow" ;
  G4VPhysicalVolume* p_SPIDetectorPixelLow = new G4PVPlacement(Rotation,
							       *Position,
							       l_SPIDetectorPixLow,
							       SPIDetectorPixelLowName,
							       Parent,
							       false,
							       Copy);
  // G4cout << "test3" << G4endl ;
  const G4String SPIDetectorPixelBottomName = "SPIDetectorPixelBottom" ;
  G4VPhysicalVolume* p_SPIDetectorPixelBottom = new G4PVPlacement(Rotation,
								  *Position,
								  l_SPIDetectorPixBottom,
								  SPIDetectorPixelBottomName,
								  Parent,
								  false,
								  Copy);	
  
  // ------------------- VISUALISATION -----------------------

  // l_SPIDetectorPixBottom->SetVisAttributes(Yellow);
  // l_SPIDetectorPixLow->SetVisAttributes(Green);
 
  
  // l_SPI->SetVisAttributes (G4VisAttributes::Invisible);

  return ;
}

