// ------------------------------------------------------------------
// PIMPGeometry - SPI
// DRW 31/1/03
// M. Chauvin 20/03/2013 Central Hub + cleaning
// ------------------------------------------------------------------

#include "PIMPGeomSPI.hh"
#include "PIMPGeomSPIPixel.hh"
#include "PIMPGeomSPIUpperVeto.hh"
#include "PIMPGeomSPIMidVeto.hh"
#include "PIMPGeomSPILowVeto.hh"
#include "PIMPGeomSPIStirlingCooler.hh"

#include "G4Trd.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trap.hh"
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
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4SubtractionSolid.hh"

PIMPGeomSPI::PIMPGeomSPI(const G4MaterialTable* Materials, PIMPSensitive* Sens)
{
  //-------------------- Initialise -----------------------------------------
  G4RotationMatrix* NullRotation = new G4RotationMatrix;

  const G4String Name = "SPI";
  G4Box* s_SPI = new G4Box(Name,90.0*cm,76.0*cm,127.6*cm);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_SPI = new G4LogicalVolume(s_SPI,
			      Material,
			      Name);

  
  
  // Not entirely sure what this is :
  /*FROM THE GEANT 3
C     Volume added by cf, to contain the upper part of the tube and
c     the mask.  A tube shaped vacuum.  The mask will sit initially in 
C     this, though later might move up by <1cm.
  */
  
  
  
  const G4String SPIUpperTubeName = "SPIUpperTube"; // SUTM
  G4Tubs* s_SPIUpperTube = new G4Tubs(SPIUpperTubeName,0.*cm,51.1*cm,40.55*cm, 0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIUpperTube = new G4LogicalVolume(s_SPIUpperTube,
							Material,
							SPIUpperTubeName);
  G4RotationMatrix* RotateSPIUpperTube = new  G4RotationMatrix ;
  RotateSPIUpperTube->rotateZ(120.*deg) ; // Check this rotation once complete
  G4VPhysicalVolume* p_SPIUpperTube = new G4PVPlacement(RotateSPIUpperTube,
							G4ThreeVector(0.,20.5*cm,69.45*cm),
							l_SPIUpperTube,
							SPIUpperTubeName,
							l_SPI,
							false,
							0); 
  // Aluminium cone section
  const G4String SPIUpTubeConeName = "SPIUpTubeCone"; // SUTB
  const G4double UpTubConFacesZ[2] = {-27.45*cm,27.45*cm} ;
  const G4double UpTubConFacesRmin[2] = {41.85*cm,40.0*cm} ; 
  const G4double UpTubConFacesRmax[2] = {42.01*cm,40.16*cm} ; 
 
  G4Polycone* s_SPIUpTubeCone = new G4Polycone(SPIUpTubeConeName,
					       0.*deg,360*deg,
					       2,
					       UpTubConFacesZ,  
					       UpTubConFacesRmin,  
					       UpTubConFacesRmax) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPIUpTubeCone = new G4LogicalVolume(s_SPIUpTubeCone,
							 Material,
							 SPIUpTubeConeName);
  G4VPhysicalVolume* p_SPIUpTubeCone = new G4PVPlacement(0,
							 G4ThreeVector(0., 0., -13.1*cm),
							 l_SPIUpTubeCone,
							 SPIUpTubeConeName,
							 l_SPIUpperTube,
							 false,
							 0);


  // Mask and PSAC Volume Mother
  const G4String SPIMaskName = "SPIMask"; // SMSK
  G4Tubs* s_SPIMask = new G4Tubs(SPIMaskName,0.*cm,51.1*cm,13.1*cm,
				 0.*deg, 360.*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIMask = new G4LogicalVolume(s_SPIMask,
						   Material,
						   SPIMaskName);
  G4VPhysicalVolume* p_SPIMask = new G4PVPlacement(0,
						   G4ThreeVector(0.,0.,27.45*cm),
						   l_SPIMask,
						   SPIMaskName,
						   l_SPIUpperTube,
						   false,
						   0);
  

  const G4String SPIMaskSuppStRingName = "SPIMaskSuppStRing"; // SMRI
  G4Tubs* s_SPIMaskSuppStRing = new G4Tubs(SPIMaskSuppStRingName,41.7*cm,44.2*cm,4.1*cm, 
					   0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;  // where the spelling mistake was
  G4LogicalVolume* l_SPIMaskSuppStRing = new G4LogicalVolume(s_SPIMaskSuppStRing,
							     Material,
							     SPIMaskSuppStRingName);
  G4VPhysicalVolume* p_SPIMaskSuppStRing = new G4PVPlacement(0,
							     G4ThreeVector(0.*cm,
									   0.*cm,
									   9.*cm),
							     l_SPIMaskSuppStRing,
							     SPIMaskSuppStRingName,
							     l_SPIMask,
							     false,
							     0);
  
  const G4String SPIMaskSuppStRingVName = "SPIMaskSuppStRingV"; // SMRV
  G4Tubs* s_SPIMaskSuppStRingV = new G4Tubs(SPIMaskSuppStRingVName,42.0*cm,44.2*cm,3.7*cm, 
					   0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIMaskSuppStRingV = new G4LogicalVolume(s_SPIMaskSuppStRingV,
							     Material,
							     SPIMaskSuppStRingVName);
  G4VPhysicalVolume* p_SPIMaskSuppStRingV = new G4PVPlacement(0,
							     G4ThreeVector(0.*cm,
									   0.*cm,
									   0.*cm),
							     l_SPIMaskSuppStRingV,
							     SPIMaskSuppStRingVName,
							     l_SPIMaskSuppStRing,
							     false,
							     0);
  
  const G4String SPIMaskSuppEpoxyName = "SPIMaskSuppEpoxy"; // SMPO
  G4Tubs* s_SPIMaskSuppEpoxy = new G4Tubs(SPIMaskSuppEpoxyName,39.3*cm,41.7*cm,4.1*cm, 
					   0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Epoxy", Materials) ;
  G4LogicalVolume* l_SPIMaskSuppEpoxy = new G4LogicalVolume(s_SPIMaskSuppEpoxy,
							     Material,
							     SPIMaskSuppEpoxyName);
  G4VPhysicalVolume* p_SPIMaskSuppEpoxy = new G4PVPlacement(0,
							     G4ThreeVector(0.*cm,
									   0.*cm,
									   9.*cm),
							     l_SPIMaskSuppEpoxy,
							     SPIMaskSuppEpoxyName,
							     l_SPIMask,
							     false,
							     0);
  const G4String SPIMaskSuppHoneyName = "SPIMaskSuppHoney"; // SMCH
  G4Tubs* s_SPIMaskSuppHoney = new G4Tubs(SPIMaskSuppHoneyName,
					  0.5*cm,39.3*cm,
					  4.*cm,
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("SPIHoney", Materials) ;
  G4LogicalVolume* l_SPIMaskSuppHoney = new G4LogicalVolume(s_SPIMaskSuppHoney,
							     Material,
							     SPIMaskSuppHoneyName);
  G4VPhysicalVolume* p_SPIMaskSuppHoney = new G4PVPlacement(0,
							    G4ThreeVector(0.*cm,0.*cm,9.*cm),
							    l_SPIMaskSuppHoney,
							    SPIMaskSuppHoneyName,
							    l_SPIMask,
							    false,
							    0);
  const G4String SPIMaskSuppCarbonName = "SPIMaskSuppCarbon"; // SMCV
  G4Tubs* s_SPIMaskSuppCarbon = new G4Tubs(SPIMaskSuppCarbonName,
					   0.5*cm,41.7*cm,
					   0.05*cm, 
					   0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("CarbonFibre", Materials) ;
  G4LogicalVolume* l_SPIMaskSuppCarbon = new G4LogicalVolume(s_SPIMaskSuppCarbon,
							     Material,
							     SPIMaskSuppCarbonName);
  G4VPhysicalVolume* p_SPIMaskSuppCarbon = new G4PVPlacement(0,
							     G4ThreeVector(0.*cm,0.*cm,13.05*cm),
							     l_SPIMaskSuppCarbon,
							     SPIMaskSuppCarbonName,
							     l_SPIMask,
							     false,
							     0);
		     p_SPIMaskSuppCarbon = new G4PVPlacement(0,
							     G4ThreeVector(0.*cm,0.*cm,4.95*cm),
							     l_SPIMaskSuppCarbon,
							     SPIMaskSuppCarbonName,
							     l_SPIMask,
							     false,
							     1);

  // Alignment structure (Central Pixel) of the Mask - 07/03/2013 M.Chauvin from top to bottom
  const G4String SPIMaskT2Name = "SPIMaskT2"; // SMT2
  G4Tubs* s_SPIMaskT2 = new G4Tubs(SPIMaskT2Name,
				     0.5*cm, 2.0*cm,
				     0.065*cm,
				     0.*deg, 360.*deg);
  Material =  PIMPSelectMaterial("TiAlV", Materials) ;
  G4LogicalVolume* l_SPIMaskT2 = new G4LogicalVolume(s_SPIMaskT2,
						     Material,
						     SPIMaskT2Name);
  G4VPhysicalVolume* p_SPIMaskT2 = new G4PVPlacement(0,
						     G4ThreeVector(0.*cm,0.*cm,13.165*cm),
						     l_SPIMaskT2,
						     SPIMaskT2Name,
						     l_SPIMask,
						     false,
						     0);
  const G4String SPIMaskPottingName = "SPIMaskPotting"; // SMPA-SMHL
  const G4double zPlanePA[2] = {0.*cm,8.0*cm};
  const G4double rInnerPA[2] = {0.*cm,0.*cm};
  const G4double rOuterPA[2] = {1.40*cm,1.40*cm};
  G4Polyhedra* s_SPIMaskPA = new G4Polyhedra("SPIMaskPA",
					     30.*deg,360.*deg,
					     6,2,
					     zPlanePA,rInnerPA,rOuterPA); // SMPA
  G4Tubs* s_SPIMaskHL = new G4Tubs("SPIMaskHL",
				   0.*cm, 0.5*cm,
				   8.*cm,
				   0.*deg, 360.*deg);   // SMHL
  G4SubtractionSolid* s_SPIMaskPotting = new G4SubtractionSolid(SPIMaskPottingName, s_SPIMaskPA, s_SPIMaskHL);
  Material =  PIMPSelectMaterial("Potting", Materials) ;
  G4LogicalVolume* l_SPIMaskPotting = new G4LogicalVolume(s_SPIMaskPotting,
							  Material,
							  SPIMaskPottingName);
  G4VPhysicalVolume* p_SPIMaskPotting = new G4PVPlacement(0,
							  G4ThreeVector(0.*cm,0.*cm,-4.*cm),
							  l_SPIMaskPotting,
							  SPIMaskPottingName,
							  l_SPIMaskSuppHoney,
							  false,
							  0);
  const G4String SPIMaskT1Name = "SPIMaskT1"; // SMT1 + SMPT
  const G4double zPlaneT1[4] = {0.*cm,0.13*cm,0.13*cm,0.3*cm};
  const G4double rInnerT1[4] = {0.3*cm,0.3*cm,0.3*cm,0.3*cm};
  const G4double rOuterT1[4] = {2.0*cm,2.0*cm,0.5*cm,0.5*cm};
  G4Polycone* s_SPIMaskT1 = new G4Polycone(SPIMaskT1Name,
					   0.*deg,360.*deg,
					   4,
					   zPlaneT1,rInnerT1,rOuterT1);
  Material =  PIMPSelectMaterial("TiAlV", Materials) ;
  G4LogicalVolume* l_SPIMaskT1 = new G4LogicalVolume(s_SPIMaskT1,
						     Material,
						     SPIMaskT1Name);
  G4VPhysicalVolume* p_SPIMaskT1 = new G4PVPlacement(0,
						     G4ThreeVector(0.*cm,0.*cm,4.77*cm),
						     l_SPIMaskT1,
						     SPIMaskT1Name,
						     l_SPIMask,
						     false,
						     0);
  
  
  // Mask pixel
  const G4String SPIMaskPixelName = "SPIMaskPixel"; // SMEL
  const G4double PixZ[2] = {0.*cm,3.0*cm} ;
  const G4double PixInner[2] = {0.*cm,0.*cm} ;
  const G4double PixOuter[2] = {3.0*cm,3.0*cm} ;
  G4Polyhedra* s_SPIMaskPixel = new G4Polyhedra(SPIMaskPixelName,
						30.*deg,360.*deg,
						6,2,
						PixZ, PixInner, PixOuter) ;
  Material =  PIMPSelectMaterial("Tungsten", Materials);
  G4LogicalVolume* l_SPIMaskPixel = new G4LogicalVolume(s_SPIMaskPixel,
							Material,
							SPIMaskPixelName);

  // Place 63 Pixels (numbering offset by 1, i.e. 1-63)
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 1, -6.000000,  0.000000) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 2,-12.000000,  0.000000) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 3,-24.000000,  0.000000) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 4,-33.000000, -5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 5,  0.000000,-10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 6,  3.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 7, -3.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 8, -9.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask, 9,-15.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,10,-21.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,11,-27.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,12,  0.000000,-20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,13, -6.000000,-20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,14,-18.000000,-20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,15, -3.000000,-25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,16, -9.000000,-25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,17,-15.000000,-25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,18, 12.000000,-31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,19,  6.000000,-31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,20, -6.000000,-31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,21,-18.000000,-31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,22,  3.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,23,  6.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,24, 12.000000, 20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,25, 12.000000, 31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,26, -9.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,27,-15.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,28,-12.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,29, -9.000000, 15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,30, -6.000000, 20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,31, -3.000000, 25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,32,  0.000000, 31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,33,-18.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,34,-15.000000, 15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,35, -9.000000, 25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,36,-21.000000, 15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,37,-18.000000, 20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,38,-15.000000, 25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,39,-33.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,40,-30.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,41,-24.000000, 20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,42,-18.000000, 31.176918) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,43,  3.000000, -5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,44,  6.000000,-10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,45, 12.000000,-20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,46, 21.000000,-25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,47,  9.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,48, 12.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,49, 15.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,50, 18.000000,  0.000000) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,51, 21.000000, -5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,52, 24.000000,-10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,53, 27.000000,-15.588460) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,54, 18.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,55, 21.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,56, 27.000000, -5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,57, 24.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,58, 27.000000,  5.196153) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,59, 30.000000,  0.000000) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,60, 21.000000, 25.980765) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,61, 24.000000, 20.784612) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,62, 30.000000, 10.392305) ;
  PlacePixel(l_SPIMaskPixel, l_SPIMask,63, 36.000000,  0.000000) ;

  
  // Plastic Scintillator VETO (PSAC)
  const G4String SPIMaskVetoName = "SPIMaskVeto"; // SMVM
  G4Tubs* s_SPIMaskVeto = new G4Tubs(SPIMaskVetoName,
				     0.*cm,51.1*cm,
				     7.5*cm, 
				     0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIMaskVeto = new G4LogicalVolume(s_SPIMaskVeto,
						       Material,
						       SPIMaskVetoName);
  G4RotationMatrix* RotateSPIMaskVeto = new G4RotationMatrix ;
  RotateSPIMaskVeto->rotateZ(180.*deg) ; // check rotation
  G4VPhysicalVolume* p_SPIMaskVeto = new G4PVPlacement(RotateSPIMaskVeto,
						       G4ThreeVector(0.,0.,-5.6*cm),
						       l_SPIMaskVeto,
						       SPIMaskVetoName,
						       l_SPIMask,
						       false,
						       0);

  // Alignment structure (Central Pixel) of the PSAC - 07/03/2013 M.Chauvin from top to bottom
  const G4String SPIMaskVetoPLG1Name = "SPIMaskVetoPLG1"; // PLG1
  const G4double zPlanePLG1[12] = {0.*cm,0.29459*cm,0.80023*cm,1.45035*cm,1.95599*cm,2.24493*cm,
			  2.24493*cm,2.56276*cm,2.56276*cm,4.12304*cm,4.12304*cm,4.26751*cm};
  const G4double rInnerPLG1[12] = {0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,
			  0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm};
  const G4double rOuterPLG1[12] = {2.30430*cm,2.30430*cm,1.39414*cm,1.39414*cm,2.30430*cm,2.30430*cm,
			  1.0*cm,1.0*cm,1.58917*cm,1.58917*cm,1.0*cm,1.0*cm};
  G4Polycone* s_SPIMaskVetoPLG1 = new G4Polycone(SPIMaskVetoPLG1Name,
						 0., 360.*deg,
						 12,
						 zPlanePLG1,rInnerPLG1,rOuterPLG1);
  Material =  PIMPSelectMaterial("Hosta", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoPLG1 = new G4LogicalVolume(s_SPIMaskVetoPLG1,
							   Material,
							   SPIMaskVetoPLG1Name);
  G4VPhysicalVolume* p_SPIMaskVetoPLG1 = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 1.25*cm),
							   l_SPIMaskVetoPLG1,
							   SPIMaskVetoPLG1Name,
							   l_SPIMaskVeto,
							   false,
							   0);
  
  const G4String SPIMaskVetoPLG2Name = "SPIMaskVetoPLG2"; // PLG2
  const G4double zPlanePLG2[14] = {0.*cm,0.14447*cm,0.14447*cm,1.70475*cm,1.70475*cm,2.02258*cm,2.02258*cm,
			 2.31152*cm,3.03387*cm,3.75622*cm,4.47857*cm,4.76751*cm,4.76751*cm, 5.26751*cm};
  const G4double rInnerPLG2[14] = {0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,
			 0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm,0.60*cm};
  const G4double rOuterPLG2[14] = {1.0*cm,1.0*cm,1.58917*cm,1.58917*cm,1.0*cm,1.0*cm,2.30430*cm,
			 2.30430*cm,1.09075*cm,1.09075*cm,2.30430*cm,2.30430*cm,1.10520*cm,1.10520*cm};
  G4Polycone* s_SPIMaskVetoPLG2 = new G4Polycone(SPIMaskVetoPLG2Name,
						 0., 360.*deg,
						 14,
						 zPlanePLG2,rInnerPLG2,rOuterPLG2);
  Material =  PIMPSelectMaterial("Hosta", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoPLG2 = new G4LogicalVolume(s_SPIMaskVetoPLG2,
							   Material,
							   SPIMaskVetoPLG2Name);
  G4VPhysicalVolume* p_SPIMaskVetoPLG2 = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 -4.01751*cm),
							   l_SPIMaskVetoPLG2,
							   SPIMaskVetoPLG2Name,
							   l_SPIMaskVeto,
							   false,
							   0);


  // PMTs
  const G4String SPIMaskVetoPMTName = "SPIMaskVetoPMT"; // SMVP
  G4Tubs* s_SPIMaskVetoPMT = new G4Tubs(SPIMaskVetoPMTName,0.*cm,4.5*cm,4.495*cm, 
					0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoPMT = new G4LogicalVolume(s_SPIMaskVetoPMT,
							  Material,
							  SPIMaskVetoPMTName);
  G4RotationMatrix* RotateSPIMaskVetoPMT1 = new G4RotationMatrix ;
  RotateSPIMaskVetoPMT1->rotateX(90.*deg) ; 
  RotateSPIMaskVetoPMT1->rotateY(-45.*deg) ;
  G4RotationMatrix* RotateSPIMaskVetoPMT2 = new G4RotationMatrix ;
  RotateSPIMaskVetoPMT2->rotateX(90.*deg) ;
  RotateSPIMaskVetoPMT2->rotateY(45.*deg) ;
  G4VPhysicalVolume* p_SPIMaskVetoPMT = new G4PVPlacement(RotateSPIMaskVetoPMT1,
							  G4ThreeVector(32.9512*cm,
									32.9512*cm,
									1.0*cm),
							  l_SPIMaskVetoPMT,
							  SPIMaskVetoPMTName,
							  l_SPIMaskVeto,
							  false,
							  0); 
  p_SPIMaskVetoPMT = new G4PVPlacement(RotateSPIMaskVetoPMT1,
				       G4ThreeVector(-32.9512*cm,
						     -32.9512*cm,
						     1.0*cm),
				       l_SPIMaskVetoPMT,
				       SPIMaskVetoPMTName,
				       l_SPIMaskVeto,
				       false,
				       1); 
  p_SPIMaskVetoPMT = new G4PVPlacement(RotateSPIMaskVetoPMT2,
				       G4ThreeVector(-32.9512*cm,
						     32.9512*cm,
						     1.0*cm),
				       l_SPIMaskVetoPMT,
				       SPIMaskVetoPMTName,
				       l_SPIMaskVeto,
				       false,
				       2); 
  p_SPIMaskVetoPMT = new G4PVPlacement(RotateSPIMaskVetoPMT2,
				       G4ThreeVector(32.9512*cm,
						     -32.9512*cm,
						     1.0*cm),
				       l_SPIMaskVetoPMT,
				       SPIMaskVetoPMTName,
				       l_SPIMaskVeto,
				       false,
				       3); 
  // Scintillator
  const G4String SPIMaskVetoScintName = "SPIMaskVetoScint"; // SMVE
  G4Tubs* s_SPIMaskVetoScint = new G4Tubs(SPIMaskVetoScintName,1.10520*cm,40.*cm,0.25*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("PlasticScint", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoScint = new G4LogicalVolume(s_SPIMaskVetoScint,
							    Material,
							    SPIMaskVetoScintName);
  G4VPhysicalVolume* p_SPIMaskVetoScint = new G4PVPlacement(0,
							    G4ThreeVector(0.*cm,
									  0.*cm,
									  1.0*cm),
							    l_SPIMaskVetoScint,
							    SPIMaskVetoScintName,
							    l_SPIMaskVeto,
							    false,
							    0); 
  

  // Disk Supports for Veto
  const G4String SPIMaskVetoSuppName = "SPIMaskVetoSupp"; // SMVC
  G4Tubs* s_SPIMaskVetoSupp = new G4Tubs(SPIMaskVetoSuppName,1.10520*cm,41.2*cm,0.05*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("CarbonFibre", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoSupp = new G4LogicalVolume(s_SPIMaskVetoSupp,
							   Material,
							   SPIMaskVetoSuppName);
  G4VPhysicalVolume* p_SPIMaskVetoSupp = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 -3.35*cm),
							   l_SPIMaskVetoSupp,
							   SPIMaskVetoSuppName,
							   l_SPIMaskVeto,
							   false,
							   0);
  p_SPIMaskVetoSupp = new G4PVPlacement(0,
					G4ThreeVector(0.*cm,
						      0.*cm,
						      5.45*cm),
					l_SPIMaskVetoSupp,
					SPIMaskVetoSuppName,
					l_SPIMaskVeto,
					false,
					1);
  // Ring Supports for Veto
  const G4String SPIMaskVetoRingName = "SPIMaskVetoRing"; // SMVR
  G4Tubs* s_SPIMaskVetoRing = new G4Tubs(SPIMaskVetoRingName,39.7*cm,41.2*cm,0.3*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("CarbonFibre", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoRing = new G4LogicalVolume(s_SPIMaskVetoRing,
							   Material,
							   SPIMaskVetoRingName);
  G4VPhysicalVolume* p_SPIMaskVetoRing = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 -3.7*cm),
							   l_SPIMaskVetoRing,
							   SPIMaskVetoRingName,
							   l_SPIMaskVeto,
							   false,
							   0);
  p_SPIMaskVetoRing = new G4PVPlacement(0,
					G4ThreeVector(0.*cm,
						      0.*cm,
						      5.8*cm),
					l_SPIMaskVetoRing,
					SPIMaskVetoRingName,
					l_SPIMaskVeto,
					false,
					1);
  // Aluminium support ring for Veto
  const G4String SPIMaskVetoAlumName = "SPIMaskVetoAlum"; // SMVS
  G4Tubs* s_SPIMaskVetoAlum = new G4Tubs(SPIMaskVetoAlumName,41.2*cm,41.5*cm,6.4*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPIMaskVetoAlum = new G4LogicalVolume(s_SPIMaskVetoAlum,
							   Material,
							   SPIMaskVetoAlumName);
  G4VPhysicalVolume* p_SPIMaskVetoAlum = new G4PVPlacement(0,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 0.*cm),
							   l_SPIMaskVetoAlum,
							   SPIMaskVetoAlumName,
							   l_SPIMaskVeto,
							   false,
							   0);

  const G4String SPIMaskVetoTitName = "SPIMaskVetoTit"; // SMVT
  const G4double TiFacesZ[4] = {0.*cm,0.6*cm,0.6*cm,3.2*cm} ;
  const G4double TiFacesRmin[4] = {41.5*cm,41.5*cm,41.5*cm,41.5*cm} ; 
  const G4double TiFacesRmax[4] = {44.2*cm,44.2*cm,42.1*cm,42.1*cm} ;  
  G4Polycone* s_SPIMaskVetoTit = new G4Polycone(SPIMaskVetoTitName,
						0.*deg,360*deg,
						4,
						TiFacesZ, TiFacesRmin, TiFacesRmax) ;
  Material =  PIMPSelectMaterial("Titanium", Materials);
  G4LogicalVolume* l_SPIMaskVetoTit = new G4LogicalVolume(s_SPIMaskVetoTit,
							  Material,
							  SPIMaskVetoTitName);
  G4VPhysicalVolume* p_SPIMaskVetoTit = new G4PVPlacement(0,
							  G4ThreeVector(0., 0.,-7.5*cm),
							  l_SPIMaskVetoTit,
							  SPIMaskVetoTitName,
							  l_SPIMaskVeto,
							  false,
							  0);
  G4RotationMatrix* RotateTit = new G4RotationMatrix ;
  RotateTit->rotateX(180.*deg);
  p_SPIMaskVetoTit = new G4PVPlacement(RotateTit,
				       G4ThreeVector(0., 0.,7.5*cm),
				       l_SPIMaskVetoTit,
				       SPIMaskVetoTitName,
				       l_SPIMaskVeto,
				       false,
				       1);

  
  /*  
  // ----------------Cryo as a sperate object-----------------------//
  // Mother volume for the detector systemn
  const G4String SPIDetMothConeName = "SPIDetMothCone"; // SVLO
  const G4double DetMothConFacesZ[2] = {-37.4025*cm,37.4025*cm} ;
  const G4double DetMothConFacesRmin[2] = {0.*cm,0.*cm} ; 
  const G4double DetMothConFacesRmax[2] = {54.7*cm,43.15*cm} ; 
  G4Polycone* s_SPIDetMothCone = new G4Polycone(SPIDetMothConeName,
						0.*deg,360*deg,
						2,
						DetMothConFacesZ,  
						DetMothConFacesRmin,  
						DetMothConFacesRmax) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPIDetMothCone = new G4LogicalVolume(s_SPIDetMothCone,
							  Material,
							  SPIDetMothConeName);
  G4VPhysicalVolume* p_SPIDetMothCone = new G4PVPlacement(0,
							  G4ThreeVector(0., 
									20.5*cm, 
									-90.0975*cm),
							  l_SPIDetMothCone,
							  SPIDetMothConeName,
							  l_SPI,
							  false,
							  0);

  const G4String SPIDetectorUnitName = "SPIDetectorUnit"; // SDET
  const G4double DetZ[2] = {-2.224*cm,23.75*cm} ;
  const G4double DetInner[2] = {0.*cm,0.*cm} ; 
  const G4double DetOuter[2] = {20.75*cm,20.75*cm} ;  
  G4Polyhedra* s_SPIDetectorUnit = new G4Polyhedra(SPIDetectorUnitName,
						   30.*deg,360.*deg,
						   6,2,
						   DetZ, DetInner, DetOuter) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPIDetectorUnit = new G4LogicalVolume(s_SPIDetectorUnit,
							   Material,
							   SPIDetectorUnitName);
  G4RotationMatrix* RotateDetectorUnit = new G4RotationMatrix ; // Check rotation
  RotateDetectorUnit->rotateZ(90.*deg);
  G4VPhysicalVolume* p_SPIDetectorUnit = new G4PVPlacement(RotateDetectorUnit,
							   G4ThreeVector(0.*cm,
									 0.*cm,
									 -2.4725*cm),
							   l_SPIDetectorUnit,
							   SPIDetectorUnitName,
							   l_SPIDetMothCone,
							   false,
							   0);
  // a series of shielding units - beryllium
  const G4String SPIDetBeryl1Name = "SPIDetBeryl1"; // SS06
  G4Trap* s_SPIDetBeryl1 = new G4Trap(SPIDetBeryl1Name,
				      10.85*cm,
				      0.*deg,0.*deg,
				      23.325*cm,1.*cm,1.*cm,0*deg,
				      10.797*cm,1.*cm,1.*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIDetBeryl1 = new G4LogicalVolume(s_SPIDetBeryl1,
							Material,
							SPIDetBeryl1Name);
  G4RotationMatrix* RotateBeryl1 = new G4RotationMatrix ;
  RotateBeryl1->rotateY(-90.*deg);
  G4VPhysicalVolume* p_SPIDetBeryl1 = new G4PVPlacement(RotateBeryl1,
							G4ThreeVector(9.85*cm,
								      0.*cm,
								      -1.0*cm),
							l_SPIDetBeryl1,
							SPIDetBeryl1Name,
							l_SPIDetectorUnit,
							false,
							0);
  const G4String SPIDetBeryl2Name = "SPIDetBeryl2"; // SS07
  G4Trap* s_SPIDetBeryl2 = new G4Trap(SPIDetBeryl2Name,
				      9.6*cm,
				      0.*deg,0.*deg,
				      23.325*cm,1.*cm,1.*cm,0*deg,
				      12.2398*cm,1.*cm,1.*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIDetBeryl2 = new G4LogicalVolume(s_SPIDetBeryl2,
							Material,
							SPIDetBeryl2Name);
  G4RotationMatrix* RotateBeryl2 = new G4RotationMatrix ;
  RotateBeryl2->rotateY(90.*deg);
  G4VPhysicalVolume* p_SPIDetBeryl2 = new G4PVPlacement(RotateBeryl2,
							G4ThreeVector(-10.6*cm,
								      0.*cm,
								      -1.0*cm),
							l_SPIDetBeryl2,
							SPIDetBeryl2Name,
							l_SPIDetectorUnit,
							false,
							0);   
  const G4String SPIDetBeryl3Name = "SPIDetBeryl3"; // SV22
  G4Trap* s_SPIDetBeryl3 = new G4Trap(SPIDetBeryl3Name,
				      9.6*cm,
				      0.*deg,0.*deg,
				      12.2398*cm,0.3*cm,0.3*cm,0*deg,
				      23.325*cm,0.3*cm,0.3*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIDetBeryl3 = new G4LogicalVolume(s_SPIDetBeryl3,
							Material,
							SPIDetBeryl3Name);
  G4RotationMatrix* RotateBeryl3 = new G4RotationMatrix ;
  RotateBeryl3->rotateY(-90.*deg);
  G4VPhysicalVolume* p_SPIDetBeryl3 = new G4PVPlacement(RotateBeryl3,
							G4ThreeVector(-10.6*cm,
								      0.*cm,
								      23.3*cm),
							l_SPIDetBeryl3,
							SPIDetBeryl3Name,
							l_SPIDetectorUnit,
							false,
							0); 
  const G4String SPIDetBeryl4Name = "SPIDetBeryl4"; // SV23
  G4Trap* s_SPIDetBeryl4 = new G4Trap(SPIDetBeryl4Name,
				      10.85*cm,
				      0.*deg,0.*deg,
				      10.7965*cm,0.3*cm,0.3*cm,0*deg,
				      23.325*cm,0.3*cm,0.3*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIDetBeryl4 = new G4LogicalVolume(s_SPIDetBeryl4,
							Material,
							SPIDetBeryl4Name);
  G4RotationMatrix* RotateBeryl4 = new G4RotationMatrix ;
  RotateBeryl4->rotateY(90.*deg);
  G4VPhysicalVolume* p_SPIDetBeryl4 = new G4PVPlacement(RotateBeryl4,
							G4ThreeVector(9.85*cm,
								      0.*cm,
								      23.3*cm),
							l_SPIDetBeryl4,
							SPIDetBeryl4Name,
							l_SPIDetectorUnit,
							false,
							0); 

  
  
  // Now to define the detector element ...
  PIMPGeomSPIPixel* SPIPixel = new PIMPGeomSPIPixel(Materials, Sens) ; // creates object
  const G4ThreeVector* SPIPixelPosition = new G4ThreeVector(0.*cm,0.*cm,0.*cm);
  G4RotationMatrix* RotateDetPix  = new  G4RotationMatrix ;
  RotateDetPix->rotateZ(30*deg);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(0.*cm,      0.*cm,0.*cm),RotateDetPix, 0);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(0.*cm,      6.*cm,0.*cm),RotateDetPix, 1);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(5.196*cm,   3.*cm,0.*cm),RotateDetPix, 2);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(5.196*cm,  -3.*cm,0.*cm),RotateDetPix, 3);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(0.*cm,     -6.*cm,0.*cm),RotateDetPix, 4);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-5.196*cm, -3.*cm,0.*cm),RotateDetPix, 5);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-5.196*cm,  3.*cm,0.*cm),RotateDetPix, 6);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(0.*cm,     12.*cm,0.*cm),RotateDetPix, 7);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(5.196*cm,   9.*cm,0.*cm),RotateDetPix, 8);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(10.39*cm,   6.*cm,0.*cm),RotateDetPix, 9);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(10.39*cm,   0.*cm,0.*cm),RotateDetPix, 10);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(10.39*cm,  -6.*cm,0.*cm),RotateDetPix, 11);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(5.139*cm,  -9.*cm,0.*cm),RotateDetPix, 12);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(0.*cm,    -12.*cm,0.*cm),RotateDetPix, 13);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-5.139*cm, -9.*cm,0.*cm),RotateDetPix, 14);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-10.39*cm, -6.*cm,0.*cm),RotateDetPix, 15);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-10.39*cm,  0.*cm,0.*cm),RotateDetPix, 16);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-10.39*cm,  6.*cm,0.*cm),RotateDetPix, 17);
  SPIPixel->Create(l_SPIDetectorUnit,&G4ThreeVector(-5.139*cm,  9.*cm,0.*cm),RotateDetPix, 18);
*/

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Now build the VETO - the veto ring around the collimator
  
  
  // Upper
  PIMPGeomSPIUpperVeto* SPIUpperVeto = new PIMPGeomSPIUpperVeto(Materials, Sens) ; // creates object
  G4RotationMatrix* RotateUpperVeto = new  G4RotationMatrix ;
  RotateUpperVeto->rotateZ(120*deg);
  //SPIUpperVeto->Create(l_SPI,&G4ThreeVector(0.*cm,20.5*cm,2.4*cm), RotateUpperVeto, 0);
  const G4ThreeVector* SPIUpperVetoPosition = new G4ThreeVector(0.*cm,20.5*cm,7.4*cm); 
  SPIUpperVeto->Create(l_SPI,SPIUpperVetoPosition, RotateUpperVeto, 0);


  // Middle
  PIMPGeomSPIMidVeto* SPIMidVeto = new PIMPGeomSPIMidVeto(Materials, Sens) ; // creates object
  G4RotationMatrix* RotateMidVeto = new  G4RotationMatrix ;
  RotateMidVeto->rotateZ(120*deg);
  const G4ThreeVector* SPIMidVetoPosition = new G4ThreeVector(0.*cm,20.5*cm,-33.4*cm); 
  SPIMidVeto->Create(l_SPI,SPIMidVetoPosition, RotateMidVeto, 0);

  
  // Lower
  PIMPGeomSPILowVeto* SPILowVeto = new PIMPGeomSPILowVeto(Materials, Sens) ; // creates object
  G4RotationMatrix* RotateLowVeto = new  G4RotationMatrix ;
  RotateLowVeto->rotateZ(0*deg);
  const G4ThreeVector* SPILowVetoPosition = new G4ThreeVector(0.*cm,20.5*cm,-90.0975*cm); 
  SPILowVeto->Create(l_SPI,SPILowVetoPosition, RotateLowVeto, 0);


  // Stirling Cooler
  PIMPGeomSPIStirlingCooler* SPIStirlingCooler = new PIMPGeomSPIStirlingCooler(Materials) ; // creates object
  G4RotationMatrix* RotateStirlingCooler = new  G4RotationMatrix ;
  RotateStirlingCooler->rotateZ(180*deg);
  const G4ThreeVector* SPIStirlingCoolerPosition = new G4ThreeVector(0., 20.5*cm, -120.9*cm); 
  SPIStirlingCooler->Create(l_SPI,SPIStirlingCoolerPosition,RotateStirlingCooler, 0);
  

  /*
  // Include infomation on the cryostat ..
  // SV05
  const G4String SPICryoWall1Name = "SPICryoWall1"; 
  G4Trap* s_SPICryoWall1 = new G4Trap(SPICryoWall1Name,
				      0.65*cm,
				      0.*deg,0.*deg,
				      11.5*cm,11.9512*cm,11.9512*cm,0*deg,
				      11.5*cm,11.2006*cm,11.2006*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPICryoWall1 = new G4LogicalVolume(s_SPICryoWall1,
							Material,
							SPICryoWall1Name);
  G4RotationMatrix* RotateWall = new G4RotationMatrix ;
  RotateWall->rotateZ(-90.*deg);
  RotateWall->rotateX(-90.*deg);
  G4VPhysicalVolume* p_SPICryoWall1 = new G4PVPlacement(RotateWall,
							G4ThreeVector(-19.05*cm,
								      0.*cm,
								      11.5*cm),
							l_SPICryoWall1,
							SPICryoWall1Name,
							l_SPIDetectorUnit,
							false,
							0);

  // SV06
  const G4String SPICryoWall2Name = "SPICryoWall2"; 
  G4Trap* s_SPICryoWall2 = new G4Trap(SPICryoWall2Name,
				      0.65*cm,
				      0.*deg,0.*deg,
				      11.5*cm,10.7965*cm,10.7965*cm,0*deg,
				      11.5*cm,10.0459*cm,10.0459*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPICryoWall2 = new G4LogicalVolume(s_SPICryoWall2,
							Material,
							SPICryoWall2Name);
  G4RotationMatrix* RotateWalla = new G4RotationMatrix ;
  RotateWalla->rotateX(90.*deg);
  RotateWalla->rotateY(-30.*deg);
  
  G4RotationMatrix* RotateWallb = new G4RotationMatrix ;
  RotateWallb->rotateX(-90.*deg);
  RotateWallb->rotateY(-30.*deg);
   
  G4VPhysicalVolume* p_SPICryoWall2 = new G4PVPlacement(RotateWalla,
							G4ThreeVector(-10.025*cm,
								      -16.7865*cm,
								      11.5*cm),
							l_SPICryoWall2,
							SPICryoWall2Name,
							l_SPIDetectorUnit,
							false,
							0);
  p_SPICryoWall2 = new G4PVPlacement(RotateWallb,
				     G4ThreeVector(-10.025*cm,
						   16.7865*cm,
						   11.5*cm),
				     l_SPICryoWall2,
				     SPICryoWall2Name,
				     l_SPIDetectorUnit,
				     false,
				     1);
 
  // SV07
  const G4String SPICryoWall3Name = "SPICryoWall3"; 
  G4Trap* s_SPICryoWall3 = new G4Trap(SPICryoWall3Name,
				      0.65*cm,
				      0.*deg,0.*deg,
				      11.5*cm,12.2398*cm,12.2398*cm,0*deg,
				      11.5*cm,11.4893*cm,11.4893*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPICryoWall3 = new G4LogicalVolume(s_SPICryoWall3,
							Material,
							SPICryoWall3Name);
  G4RotationMatrix* RotateWallc = new G4RotationMatrix ;
  RotateWallc->rotateX(90.*deg);
  RotateWallc->rotateY(30.*deg);
  
  G4RotationMatrix* RotateWalld = new G4RotationMatrix ;
  RotateWalld->rotateX(-90.*deg);
  RotateWalld->rotateY(30.*deg);
   
  G4VPhysicalVolume* p_SPICryoWall3 = new G4PVPlacement(RotateWallc,
							G4ThreeVector(9.275*cm,
								      -16.0648*cm,
								      11.5*cm),
							l_SPICryoWall3,
							SPICryoWall3Name,
							l_SPIDetectorUnit,
							false,
							0);
  p_SPICryoWall3 = new G4PVPlacement(RotateWalld,
				     G4ThreeVector(9.275*cm,
						   16.0648*cm,
						   11.5*cm),
				     l_SPICryoWall3,
				     SPICryoWall3Name,
				     l_SPIDetectorUnit,
				     false,
				     1);

  // SV08
  const G4String SPICryoWall4Name = "SPICryoWall4"; 
  G4Trap* s_SPICryoWall4 = new G4Trap(SPICryoWall4Name,
				      0.65*cm,
				      0.*deg,0.*deg,
				      11.5*cm,10.5078*cm,10.5078*cm,0*deg,
				      11.5*cm,9.7572*cm,9.7572*cm,0*deg );
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPICryoWall4 = new G4LogicalVolume(s_SPICryoWall4,
							Material,
							SPICryoWall4Name);
  G4RotationMatrix* RotateWall4 = new G4RotationMatrix ;
  RotateWall4->rotateZ(-90.*deg);
  RotateWall4->rotateX(90.*deg);
  G4VPhysicalVolume* p_SPICryoWall4 = new G4PVPlacement(RotateWall4,
							G4ThreeVector(19.55*cm,
								      0.*cm,
								      11.5*cm),
							l_SPICryoWall4,
							SPICryoWall4Name,
							l_SPIDetectorUnit,
							false,
							0);

  // SV09
  const G4String SPICryoHole1Name = "SPICryoHole1"; 
  G4Box* s_SPICryoHole1 = new G4Box(SPICryoHole1Name,
				    5.45*cm,3.95*cm,0.65*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPICryoHole1 = new G4LogicalVolume(s_SPICryoHole1,
							Material,
							SPICryoHole1Name);
  G4VPhysicalVolume* p_SPICryoHole1 = new G4PVPlacement(0,
							G4ThreeVector(0.*cm,
								      -2.92*cm,
								      0.*cm),
							l_SPICryoHole1,
							SPICryoHole1Name,
							l_SPICryoWall1,
							false,
							0);
  // SV10
  const G4String SPICryoHole2Name = "SPICryoHole2"; 
  G4Trap* s_SPICryoHole2 = new G4Trap(SPICryoHole2Name,
				      0.75*cm,
				      0.*deg,0.*deg,
				      3.95*cm,0.65*cm,0.65*cm,0*deg,
				      2.45*cm,0.65*cm,0.65*cm,0*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPICryoHole2 = new G4LogicalVolume(s_SPICryoHole2,
							Material,
							SPICryoHole2Name);
  G4RotationMatrix* RotateHole2a = new G4RotationMatrix ;
  RotateHole2a->rotateY(-90.*deg);
  G4RotationMatrix* RotateHole2b = new G4RotationMatrix ;
  RotateHole2b->rotateY(90.*deg);

  G4VPhysicalVolume* p_SPICryoHole2 = new G4PVPlacement(RotateHole2a,
							G4ThreeVector(6.2*cm,
								      -2.92*cm,
								      0.*cm),
							l_SPICryoHole2,
							SPICryoHole2Name,
							l_SPICryoWall1,
							false,
							0);
  p_SPICryoHole2 = new G4PVPlacement(RotateHole2b,
				     G4ThreeVector(-6.2*cm,
						   -2.92*cm,
						   0.*cm),
				     l_SPICryoHole2,
				     SPICryoHole2Name,
				     l_SPICryoWall1,
				     false,
				     0);
  // SV11
  const G4String SPICryoHole3Name = "SPICryoHole3"; 
  G4Box* s_SPICryoHole3 = new G4Box(SPICryoHole3Name,
				    6.25*cm,6.75*cm,0.65*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPICryoHole3 = new G4LogicalVolume(s_SPICryoHole3,
							Material,
							SPICryoHole3Name);
  G4VPhysicalVolume* p_SPICryoHole3 = new G4PVPlacement(0,
							G4ThreeVector(0.2887*cm,
								      0.*cm,
								      0.*cm),
							l_SPICryoHole3,
							SPICryoHole3Name,
							l_SPICryoWall2,
							false,
							0);
  p_SPICryoHole3 = new G4PVPlacement(0,
				     G4ThreeVector(0.*cm,
						   0.*cm,
						   0.*cm),
				     l_SPICryoHole3,
				     SPICryoHole3Name,
				     l_SPICryoWall4,
				     false,
				     0);
  
  // SV12
  const G4String SPICryoHole4Name = "SPICryoHole4"; 
  G4Trap* s_SPICryoHole4 = new G4Trap(SPICryoHole4Name,
				      0.75*cm,
				      0.*deg,0.*deg,
				      6.75*cm,0.65*cm,0.65*cm,0*deg,
				      5.25*cm,0.65*cm,0.65*cm,0*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPICryoHole4 = new G4LogicalVolume(s_SPICryoHole4,
							Material,
							SPICryoHole4Name);

  G4VPhysicalVolume* p_SPICryoHole4 = new G4PVPlacement(RotateHole2a,
							G4ThreeVector(7.2887*cm,
								      0.*cm,
								      0.*cm),
							l_SPICryoHole4,
							SPICryoHole4Name,
							l_SPICryoWall2,
							false,
							0);
  p_SPICryoHole4 = new G4PVPlacement(RotateHole2b,
				     G4ThreeVector(-6.7113*cm,
						   0.*cm,
						   0.*cm),
				     l_SPICryoHole4,
				     SPICryoHole4Name,
				     l_SPICryoWall2,
				     false,
				     0);
  p_SPICryoHole4 = new G4PVPlacement(RotateHole2b,
				     G4ThreeVector(-6.9999*cm,
						   0.*cm,
						   0.0001*cm),
				     l_SPICryoHole4,
				     SPICryoHole4Name,
				     l_SPICryoWall4,
				     false,
				     0);
  p_SPICryoHole4 = new G4PVPlacement(RotateHole2a,
				     G4ThreeVector(7.0011*cm,
						   -0.0003*cm,
						   0.*cm),
				     l_SPICryoHole4,
				     SPICryoHole4Name,
				     l_SPICryoWall4,
				     false,
				     0);


  // SV13
  const G4String SPICryoHole5Name = "SPICryoHole5"; 
  G4Box* s_SPICryoHole5 = new G4Box(SPICryoHole5Name,
				    7.5*cm,7.8*cm,0.65*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPICryoHole5 = new G4LogicalVolume(s_SPICryoHole5,
							Material,
							SPICryoHole5Name);
  G4VPhysicalVolume* p_SPICryoHole5 = new G4PVPlacement(0,
							G4ThreeVector(0.0003*cm,
								      -0.0002*cm,
								      0.*cm),
							l_SPICryoHole5,
							SPICryoHole5Name,
							l_SPICryoWall3,
							false,
							0);
  // SV14
  const G4String SPICryoHole6Name = "SPICryoHole6"; 
  G4Trap* s_SPICryoHole6 = new G4Trap(SPICryoHole6Name,
				      0.7502*cm,
				      0.*deg,0.*deg,
				      7.8*cm,0.65*cm,0.65*cm,0*deg,
				      6.3*cm,0.65*cm,0.65*cm,0*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPICryoHole6 = new G4LogicalVolume(s_SPICryoHole6,
							Material,
							SPICryoHole6Name);

  G4VPhysicalVolume* p_SPICryoHole6 = new G4PVPlacement(RotateHole2a,
							G4ThreeVector(8.2516*cm,
								      -0.0005*cm,
								      0.*cm),
							l_SPICryoHole6,
							SPICryoHole6Name,
							l_SPICryoWall3,
							false,
							0);
  p_SPICryoHole6 = new G4PVPlacement(RotateHole2b,
				     G4ThreeVector(-8.2499*cm,
						   0.*cm,
						   0.*cm),
				     l_SPICryoHole6,
				     SPICryoHole6Name,
				     l_SPICryoWall3,
				     false,
				     0);

  // SDT1
  const G4String SPIColdPlate1Name = "SPIColdPlate1"; 
  G4Box* s_SPIColdPlate1 = new G4Box(SPIColdPlate1Name,
				     0.5*cm,5.5*cm,1.2794*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIColdPlate1 = new G4LogicalVolume(s_SPIColdPlate1,
							 Material,
							 SPIColdPlate1Name);
  G4VPhysicalVolume* p_SPIColdPlate1 = new G4PVPlacement(RotateHole2a,
							 G4ThreeVector(-15.4206*cm,
								       0.*cm,
								       10.5*cm),
							 l_SPIColdPlate1,
							 SPIColdPlate1Name,
							 l_SPIDetectorUnit,
							 false,
							 0);
  // SDT2 and subsequent dodgy approximations all amalgamated into
  // something that will actually work, rather than some dodgy coding 
  // that would introduce errors, like what was in TIMM.
  const G4String SPIColdPlate2Name = "SPIColdPlate2"; // SDT2+3+4+5
  const G4double CPPixZ[2] = {-1.5*cm,1.5*cm} ;
  const G4double CPPixInner[2] = {0.*cm,0.*cm} ; 
  const G4double CPPixOuter[2] = {12.89*cm,12.89*cm} ;  
  G4Polyhedra* s_SPIColdPlate2 = new G4Polyhedra(SPIColdPlate2Name,
						 30.*deg,360.*deg,
						 6,2,
						 CPPixZ, CPPixInner, CPPixOuter) ;
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIColdPlate2 = new G4LogicalVolume(s_SPIColdPlate2,
							 Material,
							 SPIColdPlate2Name);
  G4VPhysicalVolume* p_SPIColdPlate2 = new G4PVPlacement(0,
							 G4ThreeVector(0.*cm,
								       0.*cm,
								       9.5*cm),
							 l_SPIColdPlate2,
							 SPIColdPlate2Name,
							 l_SPIDetectorUnit,
							 false,
							 0);
  
  const G4String SPITitRingName = "SPITitRing"; // SCMS
  G4Tubs* s_SPITitRing = new G4Tubs(SPITitRingName,
				    2.183*cm,2.5*cm,1.0*cm, 0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Titanium", Materials) ;
  G4LogicalVolume* l_SPITitRing = new G4LogicalVolume(s_SPITitRing,
						      Material,
						      SPITitRingName);
  G4VPhysicalVolume* p_SPITitRing ;
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,0.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 0); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 1); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.196*cm ,3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 2); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.196*cm ,-3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 3); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,-6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 4); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.196*cm ,3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 5); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.196*cm ,-3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 6); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,12.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 17);
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.139*cm ,-9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 18); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(10.39*cm ,6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 7); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(10.39*cm ,0.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 8); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(10.39*cm ,-6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 9); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.139*cm ,9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 10); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,-12.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 11); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.139*cm ,-9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 12); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-10.39*cm ,-6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 13); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-10.39*cm ,0.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 14); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-10.39*cm ,6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 15); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.139*cm ,9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 16); 


 // SDT6
  const G4String SPIColdPlate3Name = "SPIColdPlate3"; 
  G4Trap* s_SPIColdPlate3 = new G4Trap(SPIColdPlate3Name,
				       7.5908*cm,
				       0.*deg,0.*deg,
				       6.3719*cm,0.25*cm,0.25*cm,0*deg,
				       15.1371*cm,0.25*cm,0.25*cm,0*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIColdPlate3 = new G4LogicalVolume(s_SPIColdPlate3,
							 Material,
							 SPIColdPlate3Name);
  G4RotationMatrix* RotateColdPlate3 = new G4RotationMatrix ;
  RotateColdPlate3->rotateY(-90*deg);
  G4VPhysicalVolume* p_SPIColdPlate3 = new G4PVPlacement(RotateColdPlate3,
							 G4ThreeVector(-6.2091*cm,
								       0.*cm,
								       4.75*cm),
							 l_SPIColdPlate3,
							 SPIColdPlate3Name,
							 l_SPIDetectorUnit,
							 false,
							 0);
 // SDT7
  const G4String SPIColdPlate4Name = "SPIColdPlate4"; 
  G4Trap* s_SPIColdPlate4 = new G4Trap(SPIColdPlate4Name,
				       5.5182*cm,
				       0.*deg,0.*deg,
				       15.1371*cm,0.25*cm,0.25*cm,0*deg,
				       8.7652*cm,0.25*cm,0.25*cm,0*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIColdPlate4 = new G4LogicalVolume(s_SPIColdPlate4,
							 Material,
							 SPIColdPlate4Name);
  G4VPhysicalVolume* p_SPIColdPlate4 = new G4PVPlacement(RotateColdPlate3,
							 G4ThreeVector(6.9*cm,
								       0.*cm,
								       4.75*cm),
							 l_SPIColdPlate4,
							 SPIColdPlate4Name,
							 l_SPIDetectorUnit,
							 false,
							 0);
  // SDT8
  const G4String SPIColdPlate5Name = "SPIColdPlate5"; 
  G4Trap* s_SPIColdPlate5 = new G4Trap(SPIColdPlate5Name,
				       1.2319*cm,
				       0.*deg,0.*deg,
				       8.7652*cm,0.25*cm,0.25*cm,0*deg,
				       3.0924*cm,0.25*cm,0.25*cm,0*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIColdPlate5 = new G4LogicalVolume(s_SPIColdPlate5,
							 Material,
							 SPIColdPlate5Name);
  G4VPhysicalVolume* p_SPIColdPlate5 = new G4PVPlacement(RotateColdPlate3,
							 G4ThreeVector(13.6502*cm,
								       0.*cm,
								       4.75*cm),
							 l_SPIColdPlate5,
							 SPIColdPlate5Name,
							 l_SPIDetectorUnit,
							 false,
							 0);
  // SDT9
  const G4String SPIColdPlate6Name = "SPIColdPlate6"; 
  G4Trap* s_SPIColdPlate6 = new G4Trap(SPIColdPlate6Name,
				       1.232*cm,
				       0.*deg,0.*deg,
				       8.7652*cm,0.25*cm,0.25*cm,0*deg,
				       3.0924*cm,0.25*cm,0.25*cm,0*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPIColdPlate6 = new G4LogicalVolume(s_SPIColdPlate6,
							 Material,
							 SPIColdPlate6Name);
  G4RotationMatrix* RotateColdPlate6a = new G4RotationMatrix ;
  RotateColdPlate6a->rotateY(-90*deg);
  RotateColdPlate6a->rotateX(-120*deg); 
  G4RotationMatrix* RotateColdPlate6b = new G4RotationMatrix ;
  RotateColdPlate6b->rotateY(-90*deg);
  RotateColdPlate6b->rotateX(120*deg); 
  G4VPhysicalVolume* p_SPIColdPlate6 = new G4PVPlacement(RotateColdPlate6a,
							 G4ThreeVector(-6.8251*cm,
								       -11.8214*cm,
								       4.75*cm),
							 l_SPIColdPlate6,
							 SPIColdPlate6Name,
							 l_SPIDetectorUnit,
							 false,
							 0);
  p_SPIColdPlate6 = new G4PVPlacement(RotateColdPlate6b,
				      G4ThreeVector(-6.8251*cm,
						    11.8214*cm,
						    4.75*cm),
				      l_SPIColdPlate6,
				      SPIColdPlate6Name,
				      l_SPIDetectorUnit,
				      false,
				      1);
  // ST01
  const G4String SPITrappe1Name = "SPITrappe1"; 
  G4Trap* s_SPITrappe1 = new G4Trap(SPITrappe1Name,
				       1.*cm,
				       0.*deg,0.*deg,
				       9.8*cm,0.25*cm,0.25*cm,0*deg,
				       7.8*cm,0.25*cm,0.25*cm,0*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe1 = new G4LogicalVolume(s_SPITrappe1,
							 Material,
							 SPITrappe1Name);
  G4RotationMatrix* RotateTrappeA = new G4RotationMatrix ;
  RotateTrappeA->rotateX(-90*deg);
  RotateTrappeA->rotateY(120*deg);
  G4RotationMatrix* RotateTrappeB = new G4RotationMatrix ;
  RotateTrappeB->rotateX(-90*deg);
  RotateTrappeB->rotateY(300*deg);
  G4RotationMatrix* RotateTrappeC = new G4RotationMatrix ;
  RotateTrappeC->rotateX(-90*deg);
  RotateTrappeC->rotateY(-120*deg);
  G4RotationMatrix* RotateTrappeD = new G4RotationMatrix ;
  RotateTrappeD->rotateX(-90*deg);
  RotateTrappeD->rotateY(-300*deg);

  G4VPhysicalVolume* p_SPITrappe1 = new G4PVPlacement(RotateTrappeA,
						      G4ThreeVector(1.0647*cm,
								    21.8442*cm,
								    11.5*cm),
						      l_SPITrappe1,
						      SPITrappe1Name,
						      l_SPIDetectorUnit,
						      false,
						      0);
  p_SPITrappe1 = new G4PVPlacement(RotateTrappeB,
				   G4ThreeVector(18.3853*cm,
						 11.8442*cm,
						 11.5*cm),
				   l_SPITrappe1,
				   SPITrappe1Name,
				   l_SPIDetectorUnit,
				   false,
				   1) ;
  p_SPITrappe1 = new G4PVPlacement(RotateTrappeC,
				   G4ThreeVector(18.3853*cm,
						 -11.8442*cm,
						 11.5*cm),
				   l_SPITrappe1,
				   SPITrappe1Name,
				   l_SPIDetectorUnit,
				   false,
				   2) ;
  p_SPITrappe1 = new G4PVPlacement(RotateTrappeD,
				   G4ThreeVector(1.0647*cm,
						 -21.8442*cm,
						 11.5*cm),
				   l_SPITrappe1,
				   SPITrappe1Name,
				   l_SPIDetectorUnit,
				   false,
				   3) ;

  // ST02
  const G4String SPITrappe2Name = "SPITrappe2"; 
  G4Box* s_SPITrappe2 = new G4Box(SPITrappe2Name,
				  0.25*cm, 9.*cm, 1.025*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe2 = new G4LogicalVolume(s_SPITrappe2,
							 Material,
							 SPITrappe2Name);

  G4RotationMatrix* RotateTrappe2A = new G4RotationMatrix ;
  RotateTrappe2A->rotateZ(120*deg);
  G4RotationMatrix* RotateTrappe2B = new G4RotationMatrix ;
  RotateTrappe2B->rotateZ(60*deg);

  G4VPhysicalVolume* p_SPITrappe2 = new G4PVPlacement(RotateTrappe2A,
						      G4ThreeVector(9.725*cm,
								    16.8442*cm,
								    2.725*cm),
						      l_SPITrappe2,
						      SPITrappe2Name,
						      l_SPIDetectorUnit,
						      false,
						      0);
  p_SPITrappe2 = new G4PVPlacement(RotateTrappe2A,
				   G4ThreeVector(9.725*cm,
						 16.8441*cm,
						 20.2751*cm),
				   l_SPITrappe2,
				   SPITrappe2Name,
				   l_SPIDetectorUnit,
				   false,
				   1) ;
  p_SPITrappe2 = new G4PVPlacement(RotateTrappe2B,
				   G4ThreeVector(9.725*cm,
						 -16.8441*cm,
						 2.725*cm),
				   l_SPITrappe2,
				   SPITrappe2Name,
				   l_SPIDetectorUnit,
				   false,
				   2) ;
  p_SPITrappe2 = new G4PVPlacement(RotateTrappe2B,
				   G4ThreeVector(9.725*cm,
						 -16.8441*cm,
						 20.2715*cm),
				   l_SPITrappe2,
				   SPITrappe2Name,
				   l_SPIDetectorUnit,
				   false,
				   3) ;
  // ST03
  const G4String SPITrappe3Name = "SPITrappe3"; 
  G4Box* s_SPITrappe3 = new G4Box(SPITrappe3Name,
				  7.75*cm, 5.725*cm, 0.2*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe3 = new G4LogicalVolume(s_SPITrappe3,
							 Material,
							 SPITrappe3Name);

  G4RotationMatrix* RotateTrappe3A = new G4RotationMatrix ;
  RotateTrappe3A->rotateY(90*deg);
  RotateTrappe3A->rotateX(-60*deg); 
  G4RotationMatrix* RotateTrappe3B = new G4RotationMatrix ;
  RotateTrappe3B->rotateY(90*deg);
  RotateTrappe3B->rotateX(60*deg); 

  G4VPhysicalVolume* p_SPITrappe3 = new G4PVPlacement(RotateTrappe3A,
						      G4ThreeVector(11.4707*cm,
								    16.8178*cm,
								    11.5*cm),
						      l_SPITrappe3,
						      SPITrappe3Name,
						      l_SPIDetectorUnit,
						      false,
						      0);
  p_SPITrappe3 = new G4PVPlacement(RotateTrappe3B,
				   G4ThreeVector(8.8293*cm,
						 -18.3428*cm,
						 11.5*cm),
				   l_SPITrappe3,
				   SPITrappe3Name,
				   l_SPIDetectorUnit,
				   false,
				   1);

  // ST04
  const G4String SPITrappe4Name = "SPITrappe4"; 
  G4Trap* s_SPITrappe4 = new G4Trap(SPITrappe4Name,
				       0.85*cm,
				       0.*deg,0.*deg,
				       7.75*cm,0.2*cm,0.2*cm,0*deg,
				       6.05*cm,0.2*cm,0.2*cm,0*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe4 = new G4LogicalVolume(s_SPITrappe4,
							 Material,
							 SPITrappe4Name);
  G4VPhysicalVolume* p_SPITrappe4 = new G4PVPlacement(RotateTrappeB,
						      G4ThreeVector(17.1648*cm,
								    13.5303*cm,
								    11.5*cm),
						      l_SPITrappe4,
						      SPITrappe4Name,
						      l_SPIDetectorUnit,
						      false,
						      0);
  p_SPITrappe4 = new G4PVPlacement(RotateTrappeD,
				   G4ThreeVector(3.1352*cm,
						 -21.6303*cm,
						 11.5*cm),
				   l_SPITrappe4,
				   SPITrappe4Name,
				   l_SPIDetectorUnit,
				   false,
				   1);
  // ST05
  const G4String SPITrappe5Name = "SPITrappe5"; 
  G4Box* s_SPITrappe5 = new G4Box(SPITrappe5Name,
				  1.75*cm, 5.725*cm, 0.275*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe5 = new G4LogicalVolume(s_SPITrappe5,
						      Material,
						      SPITrappe5Name);

  G4VPhysicalVolume* p_SPITrappe5 = new G4PVPlacement(RotateTrappe2A,
						      G4ThreeVector(10.4957*cm,
								    15.1291*cm,
								    4.025*cm),
						      l_SPITrappe5,
						      SPITrappe5Name,
						      l_SPIDetectorUnit,
						      false,
						      0);
  p_SPITrappe5 = new G4PVPlacement(RotateTrappe2A,
				   G4ThreeVector(10.4957*cm,
						 15.1291*cm,
						 18.7949*cm),
				   l_SPITrappe5,
				   SPITrappe5Name,
				   l_SPIDetectorUnit,
				   false,
				   1);
  p_SPITrappe5 = new G4PVPlacement(RotateTrappe2B,
				   G4ThreeVector(7.8546*cm,
						 -16.6539*cm,
						 18.7949*cm),
				   l_SPITrappe5,
				   SPITrappe5Name,
				   l_SPIDetectorUnit,
				   false,
				   2);
  p_SPITrappe5 = new G4PVPlacement(RotateTrappe2B,
				   G4ThreeVector(7.8546*cm,
						 -16.6541*cm,
						 4.025*cm),
				   l_SPITrappe5,
				   SPITrappe5Name,
				   l_SPIDetectorUnit,
				   false,
				   3);

  // ST07
  const G4String SPITrappe7Name = "SPITrappe7"; 
  G4Box* s_SPITrappe7 = new G4Box(SPITrappe7Name,
				  1.75*cm, 6.05*cm, 0.5251*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe7 = new G4LogicalVolume(s_SPITrappe7,
						      Material,
						      SPITrappe7Name);

  G4RotationMatrix* RotateTrappe7A = new G4RotationMatrix ;
  RotateTrappe7A->rotateX(90*deg);
  RotateTrappe7A->rotateY(60*deg); 
  G4RotationMatrix* RotateTrappe7B = new G4RotationMatrix ;
  RotateTrappe7B->rotateX(90*deg);
  RotateTrappe7B->rotateY(-60*deg); 

  G4VPhysicalVolume* p_SPITrappe7 = new G4PVPlacement(RotateTrappe7A,
						      G4ThreeVector(16.4712*cm,
								    11.6791*cm,
								    5.908*cm),
						      l_SPITrappe7,
						      SPITrappe7Name,
						      l_SPIDetectorUnit,
						      false,
						      0);
  p_SPITrappe7 = new G4PVPlacement(RotateTrappe7A,
				   G4ThreeVector(1.8788*cm,
						 -20.104*cm,
						 5.908*cm),
				   l_SPITrappe7,
				   SPITrappe7Name,
				   l_SPIDetectorUnit,
				   false,
				   1);

  // ST08
  const G4String SPITrappe8Name = "SPITrappe8"; 
  G4Box* s_SPITrappe8 = new G4Box(SPITrappe8Name,
				  0.275*cm, 1.525*cm, 1.55*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe8 = new G4LogicalVolume(s_SPITrappe8,
						      Material,
						      SPITrappe8Name);
  
  G4RotationMatrix* RotateTrappe8A = new G4RotationMatrix ;
  RotateTrappe8A->rotateY(-90*deg);
  RotateTrappe8A->rotateX(-30*deg); 
  G4RotationMatrix* RotateTrappe8B = new G4RotationMatrix ;
  RotateTrappe8B->rotateY(-90*deg);
  RotateTrappe8B->rotateX(30*deg); 

  G4VPhysicalVolume* p_SPITrappe8 = new G4PVPlacement(RotateTrappe8A,
						      G4ThreeVector(4.117*cm,
								    18.5808*cm,
								    18.9749*cm),
						      l_SPITrappe8,
						      SPITrappe8Name,
						      l_SPIDetectorUnit,
						      false,
						      0); 
  p_SPITrappe8 = new G4PVPlacement(RotateTrappe8A,
				   G4ThreeVector(4.0829*cm,
						 18.5717*cm,
						 4.025*cm),
				   l_SPITrappe8,
				   SPITrappe8Name,
				   l_SPIDetectorUnit,
				   false,
				   1);
  p_SPITrappe8 = new G4PVPlacement(RotateTrappe8B,
				   G4ThreeVector(14.0421*cm,
						 -12.8217*cm,
						 4.025*cm),
				   l_SPITrappe8,
				   SPITrappe8Name,
				   l_SPIDetectorUnit,
				   false,
				   2);
  p_SPITrappe8 = new G4PVPlacement(RotateTrappe8B,
				   G4ThreeVector(14.0421*cm,
						 -12.8217*cm,
						 18.9749*cm),
				   l_SPITrappe8,
				   SPITrappe8Name,
				   l_SPIDetectorUnit,
				   false,
				   3);

 // ST09
  const G4String SPITrappe9Name = "SPITrappe9"; 
  G4Box* s_SPITrappe9 = new G4Box(SPITrappe9Name,
				  0.4*cm, 6.05*cm, 1.55*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe9 = new G4LogicalVolume(s_SPITrappe9,
						      Material,
						      SPITrappe9Name);
    
  G4RotationMatrix* RotateTrappe9A = new G4RotationMatrix ;
  RotateTrappe9A->rotateX(90*deg);
  RotateTrappe9A->rotateY(150*deg); 
  G4RotationMatrix* RotateTrappe9B = new G4RotationMatrix ;
  RotateTrappe9B->rotateX(90*deg);
  RotateTrappe9B->rotateY(30*deg); 

  G4VPhysicalVolume* p_SPITrappe9 = new G4PVPlacement(RotateTrappe9A,
						      G4ThreeVector(1.6705*cm,
								    19.9934*cm,
								    11.5*cm),
						      l_SPITrappe9,
						      SPITrappe9Name,
						      l_SPIDetectorUnit,
						      false,
						      0); 
  p_SPITrappe9 = new G4PVPlacement(RotateTrappe9B,
				   G4ThreeVector(16.4795*cm,
						 -11.1153*cm,
						 11.5*cm),
				   l_SPITrappe9,
				   SPITrappe9Name,
				   l_SPIDetectorUnit,
				   false,
				   1);
  // ST10
  const G4String SPITrappe10Name = "SPITrappe10"; 
  G4Box* s_SPITrappe10 = new G4Box(SPITrappe10Name,
				  6.05*cm, 0.7625*cm, 0.3079*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe10 = new G4LogicalVolume(s_SPITrappe10,
						      Material,
						      SPITrappe10Name);
    
  G4RotationMatrix* RotateTrappe10A = new G4RotationMatrix ;
  RotateTrappe10A->rotateY(90*deg);
  RotateTrappe10A->rotateX(30*deg); 
  G4RotationMatrix* RotateTrappe10B = new G4RotationMatrix ;
  RotateTrappe10B->rotateY(90*deg);
  RotateTrappe10B->rotateX(-30*deg); 

  G4VPhysicalVolume* p_SPITrappe10 = new G4PVPlacement(RotateTrappe10A,
						      G4ThreeVector(1.8898*cm,
								    18.9574*cm,
								    11.5*cm),
						      l_SPITrappe10,
						      SPITrappe10Name,
						      l_SPIDetectorUnit,
						      false,
						      0); 
  p_SPITrappe10 = new G4PVPlacement(RotateTrappe10B,
				   G4ThreeVector(15.4727*cm,
						 -11.1153*cm,
						 11.5*cm),
				   l_SPITrappe10,
				   SPITrappe10Name,
				   l_SPIDetectorUnit,
				   false,
				   1);

  // ST11
  const G4String SPITrappe11Name = "SPITrappe11"; 
  G4Box* s_SPITrappe11 = new G4Box(SPITrappe11Name,
				  6.05*cm, 0.7625*cm, 0.3079*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe11 = new G4LogicalVolume(s_SPITrappe11,
						      Material,
						      SPITrappe11Name);
    
  G4RotationMatrix* RotateTrappe11A = new G4RotationMatrix ;
  RotateTrappe11A->rotateY(90*deg);
  RotateTrappe11A->rotateX(30*deg); 
  G4RotationMatrix* RotateTrappe11B = new G4RotationMatrix ;
  RotateTrappe11B->rotateY(90*deg);
  RotateTrappe11B->rotateX(-30*deg); 

  G4VPhysicalVolume* p_SPITrappe11 = new G4PVPlacement(RotateTrappe11A,
						      G4ThreeVector(4.114*cm,
								    18.9769*cm,
								    11.5*cm),
						      l_SPITrappe11,
						      SPITrappe11Name,
						      l_SPIDetectorUnit,
						      false,
						      0); 
  p_SPITrappe11 = new G4PVPlacement(RotateTrappe11B,
				   G4ThreeVector(14.3775*cm,
						 -13.0512*cm,
						 11.5*cm),
				   l_SPITrappe11,
				   SPITrappe11Name,
				   l_SPIDetectorUnit,
				   false,
				   1);

  // ST12
  const G4String SPITrappe12Name = "SPITrappe12"; 
  G4Box* s_SPITrappe12 = new G4Box(SPITrappe12Name,
				   0.275*cm, 1.75*cm, 0.875*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe12 = new G4LogicalVolume(s_SPITrappe12,
						       Material,
						       SPITrappe12Name);

  G4VPhysicalVolume* p_SPITrappe12 = new G4PVPlacement(RotateTrappe11A,
						       G4ThreeVector(16.2114*cm,
								     11.8291*cm,
								     18.9749*cm),
						       l_SPITrappe12,
						       SPITrappe12Name,
						       l_SPIDetectorUnit,
						       false,
						       0); 
  p_SPITrappe12 = new G4PVPlacement(RotateTrappe11A,
				    G4ThreeVector(16.2114*cm,
						  11.8291*cm,
						  4.025*cm),
				    l_SPITrappe12,
				    SPITrappe12Name,
				    l_SPIDetectorUnit,
				    false,
				    2);
  p_SPITrappe12 = new G4PVPlacement(RotateTrappe11B,
				    G4ThreeVector(2.1387*cm,
						  -19.954*cm,
						  18.125*cm),
				    l_SPITrappe12,
				    SPITrappe12Name,
				    l_SPIDetectorUnit,
				    false,
				    1);
  p_SPITrappe12 = new G4PVPlacement(RotateTrappe11B,
				    G4ThreeVector(2.1387*cm,
						  -19.954*cm,
						  4.025*cm),
				    l_SPITrappe12,
				    SPITrappe12Name,
				    l_SPIDetectorUnit,
				    false,
				    3);


 // ST13
  const G4String SPITrappe13Name = "SPITrappe13"; 
  G4Box* s_SPITrappe13 = new G4Box(SPITrappe13Name,
				   0.5251*cm, 0.5749*cm, 1.75*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe13 = new G4LogicalVolume(s_SPITrappe13,
						       Material,
						       SPITrappe13Name);
  
  G4RotationMatrix* RotateTrappe13A = new G4RotationMatrix ;
  RotateTrappe13A->rotateY(90*deg);
  RotateTrappe13A->rotateX(-120*deg); 

  G4VPhysicalVolume* p_SPITrappe13 = new G4PVPlacement(RotateTrappe3A,
						       G4ThreeVector(16.4712*cm,
								     11.6791*cm,
								     18.125*cm),
						       l_SPITrappe13,
						       SPITrappe13Name,
						       l_SPIDetectorUnit,
						       false,
						       0); 
  p_SPITrappe13 = new G4PVPlacement(RotateTrappe3A,
				    G4ThreeVector(16.4712*cm,
						  11.6791*cm,
						  4.8751*cm),
				    l_SPITrappe13,
				    SPITrappe13Name,
				    l_SPIDetectorUnit,
				    false,
				    2);
  p_SPITrappe13 = new G4PVPlacement(RotateTrappe13A,
				    G4ThreeVector(1.8788*cm,
						  -20.104*cm,
						  18.1249*cm),
				    l_SPITrappe13,
				    SPITrappe13Name,
				    l_SPIDetectorUnit,
				    false,
				    1);
  p_SPITrappe13 = new G4PVPlacement(RotateTrappe13A,
				    G4ThreeVector(1.8788*cm,
						  -20.104*cm,
						  4.8751*cm),
				    l_SPITrappe13,
				    SPITrappe13Name,
				    l_SPIDetectorUnit,
				    false,
				    3);

 // ST14
  const G4String SPITrappe14Name = "SPITrappe14"; 
  G4Box* s_SPITrappe14 = new G4Box(SPITrappe14Name,
				   0.275*cm, 1.525*cm, 0.475*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe14 = new G4LogicalVolume(s_SPITrappe14,
						       Material,
						       SPITrappe14Name);
  
  G4RotationMatrix* RotateTrappe14A = new G4RotationMatrix ;
  RotateTrappe14A->rotateY(90*deg);
  RotateTrappe14A->rotateX(-120*deg); 

  G4VPhysicalVolume* p_SPITrappe14 = new G4PVPlacement(RotateTrappe8A,
						       G4ThreeVector(2.3725*cm,
								     19.55921*cm,
								     4.025*cm),
						       l_SPITrappe14,
						       SPITrappe14Name,
						       l_SPIDetectorUnit,
						       false,
						       0); 
  p_SPITrappe14 = new G4PVPlacement(RotateTrappe8A,
				    G4ThreeVector(2.4157*cm,
						  19.5342*cm,
						  18.9749*cm),
				    l_SPITrappe14,
				    SPITrappe14Name,
				    l_SPIDetectorUnit,
				    false,
				    2);
  p_SPITrappe14 = new G4PVPlacement(RotateTrappe8B,
				    G4ThreeVector(15.7528*cm,
						  -11.834*cm,
						  18.9749*cm),
				    l_SPITrappe14,
				    SPITrappe14Name,
				    l_SPIDetectorUnit,
				    false,
				    1);
  p_SPITrappe14 = new G4PVPlacement(RotateTrappe8B,
				    G4ThreeVector(15.7526*cm,
						  -11.834*cm,
						  4.0249*cm),
				    l_SPITrappe14,
				    SPITrappe14Name,
				    l_SPIDetectorUnit,
				    false,
				    3);

  // ST15
  const G4String SPITrappe15Name = "SPITrappe15"; 
  G4Box* s_SPITrappe15 = new G4Box(SPITrappe15Name,
				   0.4*cm, 1.55*cm, 0.85*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPITrappe15 = new G4LogicalVolume(s_SPITrappe15,
						       Material,
						       SPITrappe15Name);

  G4RotationMatrix* RotateTrappe15A = new G4RotationMatrix ;
  RotateTrappe15A->rotateY(180*deg);
  RotateTrappe15A->rotateZ(-30*deg); 
  G4RotationMatrix* RotateTrappe15B = new G4RotationMatrix ;
  RotateTrappe15B->rotateY(180*deg);
  RotateTrappe15B->rotateZ(30*deg); 

  G4VPhysicalVolume* p_SPITrappe15 = new G4PVPlacement(RotateTrappe15A,
						       G4ThreeVector(1.6705*cm,
								     19.9934*cm,
								     4.6*cm),
						       l_SPITrappe15,
						       SPITrappe15Name,
						       l_SPIDetectorUnit,
						       false,
						       0); 
  p_SPITrappe15 = new G4PVPlacement(RotateTrappe15A,
				    G4ThreeVector(1.6705*cm,
						  19.9934*cm,
						  18.4*cm),
				    l_SPITrappe15,
				    SPITrappe15Name,
				    l_SPIDetectorUnit,
				    false,
				    2);
  p_SPITrappe15 = new G4PVPlacement(RotateTrappe15B,
				    G4ThreeVector(16.4795*cm,
						  -11.4434*cm,
						  18.4*cm),
				    l_SPITrappe15,
				    SPITrappe15Name,
				    l_SPIDetectorUnit,
				    false,
				    1);
  p_SPITrappe15 = new G4PVPlacement(RotateTrappe15B,
				    G4ThreeVector(16.4795*cm,
						  -11.4434*cm,
						  4.6*cm),
				    l_SPITrappe15,
				    SPITrappe15Name,
				    l_SPIDetectorUnit,
				    false,
				    3);
  

  */
  // SP26
  const G4String SPIPompage26Name = "SPIPompage26"; 
  G4Trap* s_SPIPompage26 = new G4Trap(SPIPompage26Name,
				      0.75*cm,
				      0.*deg,0.*deg,
				      2.72*cm, 0.3*cm, 0.3*cm, 0.*deg,
				      1.22*cm, 0.3*cm, 0.3*cm, 0.*deg);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage26 = new G4LogicalVolume(s_SPIPompage26,
							Material,
							SPIPompage26Name);
  
  G4RotationMatrix* RotatePom26a = new G4RotationMatrix ;
  RotatePom26a->rotateX(-90*deg);
  RotatePom26a->rotateY(-30*deg);
  G4RotationMatrix* RotatePom26b = new G4RotationMatrix ;
  RotatePom26b->rotateX(-90*deg);
  RotatePom26b->rotateY(-210*deg);
  
  G4VPhysicalVolume* p_SPIPompage26 = new G4PVPlacement(RotatePom26a,
							G4ThreeVector(45.4297*cm,
								      46.0132*cm,
								      -82.3901*cm),
							l_SPIPompage26,
							SPIPompage26Name,
							l_SPI,
							false,
							0);
  p_SPIPompage26 = new G4PVPlacement(RotatePom26b,
				     G4ThreeVector(39.8599*cm,
						   55.8368*cm,
						   -82.39*cm),
				     l_SPIPompage26,
				     SPIPompage26Name,
				     l_SPI,
				     false,
				     1);

  // SP25
  const G4String SPIPompage25Name = "SPIPompage25"; 
  G4Box* s_SPIPompage25 = new G4Box(SPIPompage25Name,
				    0.3*cm, 4.82*cm, 2.72*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage25 = new G4LogicalVolume(s_SPIPompage25,
							Material,
							SPIPompage25Name);
  
  G4RotationMatrix* RotatePom25a = new G4RotationMatrix ;
  RotatePom25a->rotateY(180*deg);
  RotatePom25a->rotateZ(30*deg);
  
  G4VPhysicalVolume* p_SPIPompage25 = new G4PVPlacement(RotatePom25a,
							G4ThreeVector(42.6449*cm,
								      50.8368*cm,
								      -82.39*cm),
							l_SPIPompage25,
							SPIPompage25Name,
							l_SPI,
							false,
							0);
 
  // not including SPs 30, 29, 21, 23, 24, 31,33, 32, 20
  // leaving out SP03, SP28, SF 01&02
  /*
  // SF03
  const G4String SPICryoAux03Name = "SPICryoAux03"; 
  G4Trap* s_SPICryoAux03 = new G4Trap(SPICryoAux03Name,
				      0.433*cm,
				      0.*deg, 0.*deg,
				      5.05*cm, 0.3*cm, 0.3*cm, 0.*deg,
				      4.45*cm, 0.3*cm, 0.3*cm, 0.*deg);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPICryoAux03 = new G4LogicalVolume(s_SPICryoAux03,
							Material,
							SPICryoAux03Name);
  G4RotationMatrix* RotateAux03a = new G4RotationMatrix ;
  RotateAux03a->rotateX(-90*deg);
  G4RotationMatrix* RotateAux03b = new G4RotationMatrix ;
  RotateAux03b->rotateX(-90*deg);
  RotateAux03b->rotateY(180*deg); 
  G4VPhysicalVolume* p_SPICryoAux03 = new G4PVPlacement(RotateAux03a,
							G4ThreeVector(-20.0*cm,
								      -8.517*cm,
								      9.63*cm),
							l_SPICryoAux03,
							SPICryoAux03Name,
							l_SPIDetectorUnit,
							false,
							0);
  p_SPICryoAux03 = new G4PVPlacement(RotateAux03b,
				     G4ThreeVector(-20.0*cm,
						   8.517*cm,
						   9.63*cm),
				     l_SPICryoAux03,
				     SPICryoAux03Name,
				     l_SPIDetectorUnit,
				     false,
				     1);

  // SF04
  const G4String SPICryoAux04Name = "SPICryoAux04"; 
  G4Box* s_SPICryoAux04 = new G4Box(SPICryoAux04Name,
				    8.084*cm, 0.3*cm, 1.85*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPICryoAux04 = new G4LogicalVolume(s_SPICryoAux04,
							Material,
							SPICryoAux04Name);
  G4RotationMatrix* RotateAux04 = new G4RotationMatrix ;
  RotateAux04->rotateX(180*deg);
  RotateAux04->rotateZ(-90*deg);

  G4VPhysicalVolume* p_SPICryoAux04 = new G4PVPlacement(RotateAux04,
							G4ThreeVector(-20.0*cm,
								      0.*cm,
								      13.73*cm),
							l_SPICryoAux04,
							SPICryoAux04Name,
							l_SPIDetectorUnit,
							false,
							0);
  p_SPICryoAux04 = new G4PVPlacement(RotateAux04,
				     G4ThreeVector(-20.0*cm,
						   0.*cm,
						   5.5299*cm),
				     l_SPICryoAux04,
				     SPICryoAux04Name,
				     l_SPIDetectorUnit,
				     false,
				     1);
  // SF05
  const G4String SPICryoAux05Name = "SPICryoAux05"; 
  G4Box* s_SPICryoAux05 = new G4Box(SPICryoAux05Name,
				    0.3*cm, 2.2501*cm, 2.042*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPICryoAux05 = new G4LogicalVolume(s_SPICryoAux05,
							Material,
							SPICryoAux05Name);
  G4RotationMatrix* RotateAux05 = new G4RotationMatrix ;
  RotateAux05->rotateX(180*deg);
  RotateAux05->rotateZ(-90*deg);

  G4VPhysicalVolume* p_SPICryoAux05 = new G4PVPlacement(RotateAux03a,
							G4ThreeVector(-20.0*cm,
								      -6.042*cm,
								      9.63*cm),
							l_SPICryoAux05,
							SPICryoAux05Name,
							l_SPIDetectorUnit,
							false,
							0);
  p_SPICryoAux05 = new G4PVPlacement(RotateAux03a,
				     G4ThreeVector(-20.0*cm,
						   6.042*cm,
						   9.63*cm),
				     l_SPICryoAux05,
				     SPICryoAux05Name,
				     l_SPIDetectorUnit,
				     false,
				     1);

  // leaving out SF06, 07, 10, 
  */
  
 // CPSP
  const G4String SJemxStrutName = "SJemxStrut";
  G4Trap* s_SJemxStrut = new G4Trap(SJemxStrutName,
				    (180/2)*cm,
				    11.004*deg, 0*deg,
				    (4/2)*cm, 80/2.*cm, 80/2.*cm, 0.*deg,
				    (4/2)*cm, 10/2.*cm, 10/2.*cm, 0.*deg);
  Material =  PIMPSelectMaterial("PLMHoney", Materials) ;
  G4LogicalVolume* l_SJemxStrut = new G4LogicalVolume(s_SJemxStrut,
						      Material,
						      SJemxStrutName);

  G4RotationMatrix* RotateStrut1 = new G4RotationMatrix ;
  RotateStrut1->rotateZ(-90*deg);
  G4VPhysicalVolume* p_SJemxStrut = new G4PVPlacement(RotateStrut1,
						      G4ThreeVector(57.1*cm,
								    57.4*cm,
								    -38.35*cm),
						      l_SJemxStrut,
						      SJemxStrutName,
						      l_SPI,
						      false,
						      0);
  p_SJemxStrut = new G4PVPlacement(RotateStrut1,
				   G4ThreeVector(-57.1*cm,
						 57.4*cm,
						 -38.35*cm),
				   l_SJemxStrut,
				   SJemxStrutName,
				   l_SPI,
				   false,
				   1);
  
  // CDPM - external electronics inside mother
  const G4String SPIExtElec1Name = "SPIExtElec1"; 
  G4Box* s_SPIExtElec1 = new G4Box(SPIExtElec1Name,
				   11.6*cm, 12.5*cm,8.75*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIExtElec1 = new G4LogicalVolume(s_SPIExtElec1,
						       Material,
						       SPIExtElec1Name);
  G4VPhysicalVolume* p_SPIExtElec1 = new G4PVPlacement(0,
						       G4ThreeVector(78.4*cm,
								     60.8*cm,
								     -118.85*cm),
						       l_SPIExtElec1,
						       SPIExtElec1Name,
						       l_SPI,
						       false,
						       0);
  p_SPIExtElec1 = new G4PVPlacement(0,
				    G4ThreeVector(-78.4*cm,
						  60.8*cm,
						  -118.85*cm),
				    l_SPIExtElec1,
				    SPIExtElec1Name,
				    l_SPI,
				    false,
				    1);

  // CCCM - external electronics inside mother
  const G4String SPIExtElec2Name = "SPIExtElec2"; 
  G4Box* s_SPIExtElec2 = new G4Box(SPIExtElec2Name,
				   14.47*cm, 10.6*cm, 10.*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIExtElec2 = new G4LogicalVolume(s_SPIExtElec2,
						       Material,
						       SPIExtElec2Name);
  G4VPhysicalVolume* p_SPIExtElec2 = new G4PVPlacement(0,
						       G4ThreeVector(75.53*cm,
								     29.8*cm,
								     -117.6*cm),
						       l_SPIExtElec2,
						       SPIExtElec2Name,
						       l_SPI,
						       false,
						       0);
  p_SPIExtElec2 = new G4PVPlacement(0,
				    G4ThreeVector(-75.53*cm,
						  29.8*cm,
						  -117.6*cm),
				    l_SPIExtElec2,
				    SPIExtElec2Name,
				    l_SPI,
				    false,
				    1);
   
 
  // ------------------- VISUALISATION -----------------------

   //l_SPIMaskVeto->SetVisAttributes(Green);
   //l_SPIMaskVetoPMT->SetVisAttributes(Green);
   //l_SPIMaskVetoScint->SetVisAttributes(Red);
   //l_SPIMaskVetoAlum->SetVisAttributes(Purple);
   //l_SPIMaskVetoSupp->SetVisAttributes(SkyBlue); 
   //l_SPIMaskVetoTit->SetVisAttributes(Purple);
   //l_SPIDetectorUnit->SetVisAttributes(Green);
   //l_SPIDetBeryl3->SetVisAttributes(Green);
   //l_SPIDetBeryl4->SetVisAttributes(Yellow);
   //l_SPICryoWall3->SetVisAttributes(SkyBlue);

  //l_SPIExtElec2->SetVisAttributes(Yellow);
  //l_SPIMaskSuppHoney->SetVisAttributes(Green);
  //l_SPIMaskSuppCarbon->SetVisAttributes(Purple);
  l_SPIMaskPixel->SetVisAttributes(Yellow);
  
  l_SPIMaskT2->SetVisAttributes(Pink);
  l_SPIMaskPotting->SetVisAttributes(Purple);
  l_SPIMaskT1->SetVisAttributes(Pink);
  
  l_SPIMaskVetoPLG1->SetVisAttributes(Pink);
  l_SPIMaskVetoPLG2->SetVisAttributes(Pink);


 // -------------------- SENSITIVITY ---------------------------.
 //l_SPIMaskVetoScint->SetSensitiveDetector(Sens);	//next the plastic will be on with a threshold (~500keV)

}

PIMPGeomSPI::~PIMPGeomSPI()
{;}

void PIMPGeomSPI::PlacePixel(G4LogicalVolume* Child,
			     G4LogicalVolume* Parent, 
			     G4int TileNum,
			     G4double Xposition,
			     G4double Yposition)
{
  G4ThreeVector TilePosition = G4ThreeVector(Xposition*cm,Yposition*cm,1.9*cm);
  G4VPhysicalVolume* p_SPIMaskPixel= new G4PVPlacement(0,
						       TilePosition,
						       Child,
						       "SPIMaskPixel",
						       Parent,
						       false,
						       TileNum); 

  return ;
}



void PIMPGeomSPI::Create(const G4MaterialTable* Materials, 
			 G4LogicalVolume* Parent, 
			 const G4ThreeVector* Position, 
			 G4RotationMatrix* Rotation)
{  

  // Create SPI Mother volume 
  const G4String Name = "SPI" ;
  G4VPhysicalVolume* p_SPI = new G4PVPlacement(Rotation,
					       *Position,
					       l_SPI,
					       Name,
					       Parent,
					       false,
					       0);	
  
   // ------------------- VISUALISATION -----------------------

  // l_SPI->SetVisAttributes(Yellow);
  // l_SPI->SetVisAttributes (G4VisAttributes::Invisible);

  return ;
}













