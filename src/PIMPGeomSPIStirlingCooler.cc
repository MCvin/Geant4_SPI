
// ------------------------------------------------------------------
// PIMPGeometry - SPIStirlingCooler
// DRW 3/3/04
// ------------------------------------------------------------------

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
// #include "G4VPhysicalVolume.hh"

PIMPGeomSPIStirlingCooler::PIMPGeomSPIStirlingCooler(const G4MaterialTable* Materials)
{

   
  const G4String SPIStirlingCoolerName = "SPIStirlingCooler"; // SACM
  const G4double SCFacesZ[3] = {0.*cm,67.6*cm,142.9*cm} ;
  const G4double SCFacesRmin[3] = {54.7*cm,43.2*cm,42.2*cm} ; 
  const G4double SCFacesRmax[3] = {95.0*cm,95.0*cm,95.0*cm} ;  
  G4Polycone* s_SPIStirlingCooler = new G4Polycone(SPIStirlingCoolerName,
						   25.*deg,130*deg,
						   3,
						   SCFacesZ, SCFacesRmin, SCFacesRmax) ;
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials);
  l_SPIStirlingCooler = new G4LogicalVolume(s_SPIStirlingCooler,
					    Material,
					    SPIStirlingCoolerName);



  const G4String SPISCCoolerName = "SPISCCooler"; // STCM
  G4Trap* s_SPISCCooler = new G4Trap(SPISCCoolerName,
				     27.45*cm,
				     5.0*deg,270.0*deg,
				     7.5*cm,34.5*cm, 34.5*cm,0.*deg,
				     12.5*cm,34.5*cm,34.5*cm,0.*deg); 
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPISCCooler = new G4LogicalVolume(s_SPISCCooler,
						       Material,
						       SPISCCoolerName);
  G4VPhysicalVolume* p_SPISCCooler = new G4PVPlacement(0, G4ThreeVector(0.0*cm,
									60.*cm,33.35*cm),
						       l_SPISCCooler, SPISCCoolerName,
						       l_SPIStirlingCooler, false, 0);

  const G4String SPISCElectronicsName = "SPISCElectronics"; // SAFE
  G4Box* s_SPISCElectronics = new G4Box(SPISCElectronicsName,
					12.0*cm, 11.5*cm, 20.0*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPISCElectronics = new G4LogicalVolume(s_SPISCElectronics,
							    Material,
							    SPISCElectronicsName);
  G4VPhysicalVolume* p_SPISCElectronics = new G4PVPlacement(0, 
							    G4ThreeVector(49.*cm,
									  59.*cm,
									  20.*cm),
							    l_SPISCElectronics, 
							    SPISCElectronicsName,
							    l_SPIStirlingCooler, 
							    false, 0);
  
  const G4String SPISCDFEEName = "SPISCDFEE"; // SDFE
  G4Box* s_SPISCDFEE = new G4Box(SPISCDFEEName,
				 12.0*cm, 10.*cm, 20.0*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPISCDFEE = new G4LogicalVolume(s_SPISCDFEE,
						     Material,
						     SPISCDFEEName);
  G4VPhysicalVolume* p_SPISCDFEE = new G4PVPlacement(0, 
						     G4ThreeVector(-49.*cm,
								   61.*cm,
								   20.*cm),
						     l_SPISCDFEE, 
						     SPISCDFEEName,
						     l_SPIStirlingCooler, 
						     false, 0);
  
  const G4String SPISCBottomName = "SPISCBottom"; // SSCB
  G4Box* s_SPISCBottom = new G4Box(SPISCBottomName,
				  30.5*cm, 26.75*cm, 2.0*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCBottom = new G4LogicalVolume(s_SPISCBottom,
						      Material,
						      SPISCBottomName);
  G4RotationMatrix* RotateBottom = new G4RotationMatrix ;
  RotateBottom->rotateX(90.0*deg);
  G4VPhysicalVolume* p_SPISCBottom = new G4PVPlacement(RotateBottom, 
						       G4ThreeVector(0.*cm,
								     7.9*cm,
								     0.*cm),
						       l_SPISCBottom, 
						       SPISCBottomName,
						       l_SPISCCooler, 
						       false, 0);



  const G4String SPISCSidesName = "SPISCSides"; // SSCS
  G4Trap* s_SPISCSides = new G4Trap(SPISCSidesName,
				    27.45*cm,
				    5.0*deg,270.0*deg,
				    5.*cm,2.*cm, 2.*cm,0.*deg,
				    10.*cm,2.*cm,2.*cm,0.*deg); 
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCSides = new G4LogicalVolume(s_SPISCSides,
						      Material,
						      SPISCSidesName);
  G4VPhysicalVolume* p_SPISCSides = new G4PVPlacement(0, G4ThreeVector(32.5*cm,
								       2.4*cm,0.*cm),
						      l_SPISCSides, SPISCSidesName,
						      l_SPISCCooler, false, 0);
  p_SPISCSides = new G4PVPlacement(0, G4ThreeVector(-32.5*cm,
						    2.4*cm,0.*cm),
				   l_SPISCSides, SPISCSidesName,
				   l_SPISCCooler, false, 1);
 
  const G4String SPISCConeShapeName = "SPISCConeShape"; // SSCC
  G4Cons* s_SPISCConeShape = new G4Cons(SPISCConeShapeName,
					0.,4.*cm,
					0.,2.*cm,
					10.0*cm,0*deg,360.0*deg); 
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCConeShape = new G4LogicalVolume(s_SPISCConeShape,
							  Material,
							  SPISCConeShapeName);
  G4RotationMatrix* RotateCone = new G4RotationMatrix;
  RotateCone->rotateY(180*deg);
  G4VPhysicalVolume* p_SPISCConeShape = new G4PVPlacement(0, G4ThreeVector(26.0*cm,
									   1.75*cm,
									   15.*cm),
							  l_SPISCConeShape, 
							  SPISCConeShapeName,
							  l_SPISCCooler, false, 0);
  p_SPISCConeShape = new G4PVPlacement(RotateCone, G4ThreeVector(26.0*cm,
							1.75*cm,
							-15.*cm),
				       l_SPISCConeShape, SPISCConeShapeName,
				       l_SPISCCooler, false, 1);
   p_SPISCConeShape = new G4PVPlacement(0, G4ThreeVector(-26.0*cm,
							 1.75*cm,
							 15.*cm),
				       l_SPISCConeShape, SPISCConeShapeName,
				       l_SPISCCooler, false, 1);
  p_SPISCConeShape = new G4PVPlacement(RotateCone, G4ThreeVector(-26.0*cm,
							1.75*cm,
							-15.*cm),
				       l_SPISCConeShape, SPISCConeShapeName,
				       l_SPISCCooler, false, 1); 

  const G4String SPISCTubeShapeName = "SPISCTubeShape"; // SSCT

  G4Tubs* s_SPISCTubeShape = new G4Tubs(SPISCTubeShapeName,
					0.,3.25*cm, 6.5*cm,
					0*deg,360.0*deg); 
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCTubeShape = new G4LogicalVolume(s_SPISCTubeShape,
							  Material,
							  SPISCTubeShapeName);
  G4RotationMatrix* RotateTube = new G4RotationMatrix;
  RotateTube->rotateY(180*deg);
  G4VPhysicalVolume* p_SPISCTubeShape = new G4PVPlacement(0, G4ThreeVector(5.37*cm,
									   0.*cm,
									   19.6*cm),
							  l_SPISCTubeShape, 
							  SPISCTubeShapeName,
							  l_SPISCCooler, false, 0);
  p_SPISCTubeShape = new G4PVPlacement(RotateCone, G4ThreeVector(5.37*cm,
								 0.*cm,
								 -19.6*cm),
				       l_SPISCTubeShape, 
				       SPISCTubeShapeName,
				       l_SPISCCooler, false, 1);
  p_SPISCTubeShape = new G4PVPlacement(0, G4ThreeVector(-5.37*cm,
							0.*cm,
							19.6*cm),
				       l_SPISCTubeShape, 
				       SPISCTubeShapeName,
				       l_SPISCCooler, false, 2);
  p_SPISCTubeShape = new G4PVPlacement(RotateCone, G4ThreeVector(-5.37*cm,
								 0.*cm,
								 -19.6*cm),
				       l_SPISCTubeShape, 
				       SPISCTubeShapeName,
				       l_SPISCCooler, false, 3);
  
  
  const G4String SPISCSupStrutName = "SPISCSupStrut"; // SSCU
  G4Box* s_SPISCSupStrut = new G4Box(SPISCSupStrutName,
				     10.*cm, 13.*cm, 5.35*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCSupStrut = new G4LogicalVolume(s_SPISCSupStrut,
							 Material,
							 SPISCSupStrutName);
  G4RotationMatrix* RotateSupStrut = new G4RotationMatrix ;
  RotateSupStrut->rotateX(90.0*deg);
  G4VPhysicalVolume* p_SPISCSupStrut = new G4PVPlacement(RotateBottom, 
							 G4ThreeVector(0.*cm,
								       0.05*cm,
								       0.*cm),
							 l_SPISCSupStrut, 
							 SPISCSupStrutName,
							 l_SPISCCooler, 
							 false, 0);


  const G4String SPISCRadiatorName = "SPISCRadiator"; // SRAD
  G4Box* s_SPISCRadiator = new G4Box(SPISCRadiatorName,
				     20.75*cm, 2.*cm, 34.*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCRadiator = new G4LogicalVolume(s_SPISCRadiator,
							 Material,
							 SPISCRadiatorName);
  G4RotationMatrix* RotateRadiator = new G4RotationMatrix ;
  RotateRadiator->rotateX(90.0*deg);
  G4VPhysicalVolume* p_SPISCRadiator = new G4PVPlacement(0, 
							 G4ThreeVector(0.*cm,
								       50.*cm,
								       108.9*cm),
							 l_SPISCRadiator, 
							 SPISCRadiatorName,
							 l_SPIStirlingCooler, 
							 false, 0);

  const G4String SPISCHingeName = "SPISCHinge"; // SHIN
  G4Box* s_SPISCHinge = new G4Box(SPISCHingeName,
				  5.*cm, 5.*cm, 1.5*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPISCHinge = new G4LogicalVolume(s_SPISCHinge,
						      Material,
						      SPISCHingeName);
  G4VPhysicalVolume* p_SPISCHinge = new G4PVPlacement(RotateBottom, 
						      G4ThreeVector(15.75*cm,
								    45.*cm,
								    137.9*cm),
						      l_SPISCHinge, 
						      SPISCHingeName,
						      l_SPIStirlingCooler, 
						      false, 0);
  p_SPISCHinge = new G4PVPlacement(RotateBottom, 
				   G4ThreeVector(-15.75*cm,
						 45.*cm,
						 137.9*cm),
				   l_SPISCHinge, 
				   SPISCHingeName,
				   l_SPIStirlingCooler, 
				   false, 1);
  p_SPISCHinge = new G4PVPlacement(RotateBottom, 
				   G4ThreeVector(15.75*cm,
						 45.*cm,
						 79.9*cm),
				   l_SPISCHinge, 
				   SPISCHingeName,
				   l_SPIStirlingCooler, 
				   false, 2);
  p_SPISCHinge = new G4PVPlacement(RotateBottom, 
				   G4ThreeVector(-15.75*cm,
						 45.*cm,
						 79.9*cm),
				   l_SPISCHinge, 
				   SPISCHingeName,
				   l_SPIStirlingCooler, 
				   false, 3);

  // electronics box 1
  const G4String SPISCElec1Name = "SPISCElec1"; // SEL1
  G4Box* s_SPISCElec1 = new G4Box(SPISCElec1Name,
				  10.*cm, 13.75*cm, 27.75*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPISCElec1 = new G4LogicalVolume(s_SPISCElec1,
						      Material,
						      SPISCElec1Name);
  G4RotationMatrix* rotateElec = new G4RotationMatrix;
  rotateElec->rotateZ(60.*deg);
  G4VPhysicalVolume* p_SPISCElec1 = new G4PVPlacement(rotateElec, 
						      G4ThreeVector(47.32*cm,
								    35.66*cm,
								    78.75*cm),
						      l_SPISCElec1, 
						      SPISCElec1Name,
						      l_SPIStirlingCooler, 
						      false, 0);
  const G4String SPISCElecComponentAName = "SPISCElecComponentA"; // SPSD
  G4Box* s_SPISCElecComponentA = new G4Box(SPISCElecComponentAName,
					   9.5*cm, 13.75*cm, 10.*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPISCElecComponentA = new G4LogicalVolume(s_SPISCElecComponentA,
							       Material,
							       SPISCElecComponentAName);
  G4VPhysicalVolume* p_SPISCElecComponentA = new G4PVPlacement(0, 
							       G4ThreeVector(0.*cm,
									     0.*cm,
									     -17.75*cm),
							       l_SPISCElecComponentA, 
							       SPISCElecComponentAName,
							       l_SPISCElec1, 
							       false, 0);
  const G4String SPISCElecComponentBName = "SPISCElecComponentB"; // SAF2
  G4Box* s_SPISCElecComponentB = new G4Box(SPISCElecComponentBName,
					   9.5*cm, 13.75*cm, 10.*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPISCElecComponentB = new G4LogicalVolume(s_SPISCElecComponentB,
							       Material,
							       SPISCElecComponentBName);
  G4VPhysicalVolume* p_SPISCElecComponentB = new G4PVPlacement(0, 
							       G4ThreeVector(0.*cm,
									     0.*cm,
									     14.*cm),
							       l_SPISCElecComponentB, 
							       SPISCElecComponentBName,
							       l_SPISCElec1, 
							       false, 0);

  // electronics box 2
  const G4String SPISCElec2Name = "SPISCElec2"; // SEL2
  G4Box* s_SPISCElec2 = new G4Box(SPISCElec2Name,
				  11.*cm, 12*cm, 27.75*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPISCElec2 = new G4LogicalVolume(s_SPISCElec2,
						      Material,
						      SPISCElec2Name);
  G4RotationMatrix* rotateElec2 = new G4RotationMatrix;
  rotateElec2->rotateZ(-60.*deg);
  G4VPhysicalVolume* p_SPISCElec2 = new G4PVPlacement(rotateElec2, 
						      G4ThreeVector(-45.92*cm,
								    34.6*cm,
								    78.75*cm),
						      l_SPISCElec2, 
						      SPISCElec2Name,
						      l_SPIStirlingCooler, 
						      false, 0);
  const G4String SPISCElec2ComponentBName = "SPISCElec2ComponentB"; // SEVC
  G4Box* s_SPISCElec2ComponentB = new G4Box(SPISCElec2ComponentBName,
					    9.5*cm, 12.*cm, 10.*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPISCElec2ComponentB = new G4LogicalVolume(s_SPISCElec2ComponentB,
								Material,
								SPISCElec2ComponentBName);
  G4VPhysicalVolume* p_SPISCElec2ComponentB = new G4PVPlacement(0, 
								G4ThreeVector(0.*cm,
									      0.*cm,
									      -17.75*cm),
								l_SPISCElec2ComponentB, 
								SPISCElec2ComponentBName,
								l_SPISCElec2, 
								false, 0);
  const G4String SPISCElec2ComponentAName = "SPISCElec2ComponentA"; // SESE
  G4Box* s_SPISCElec2ComponentA = new G4Box(SPISCElec2ComponentAName,
					    10.*cm, 12.*cm, 13.75*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPISCElec2ComponentA = new G4LogicalVolume(s_SPISCElec2ComponentA,
								Material,
								SPISCElec2ComponentAName);
  G4VPhysicalVolume* p_SPISCElec2ComponentA = new G4PVPlacement(0, 
								G4ThreeVector(0.*cm,
									      0.*cm,
									      14.*cm),
								l_SPISCElec2ComponentA, 
								SPISCElec2ComponentAName,
								l_SPISCElec2, 
								false, 0);

  // ---------- Visualisation -------------

  // l_SPI->SetVisAttributes(Yellow);
  //l_SPI->SetVisAttributes (G4VisAttributes::Invisible);
  l_SPISCElectronics->SetVisAttributes(Yellow);
  l_SPISCDFEE->SetVisAttributes(Red);
  l_SPISCBottom->SetVisAttributes(White);
 l_SPISCTubeShape->SetVisAttributes(White);
  l_SPISCElecComponentA->SetVisAttributes(White);
  l_SPISCElecComponentB->SetVisAttributes(Red);
  l_SPISCElec2ComponentA->SetVisAttributes(White);
  l_SPISCElec2ComponentB->SetVisAttributes(Red);
  //  l_SPIStirlingCooler->SetVisAttributes(White); 
}


PIMPGeomSPIStirlingCooler::~PIMPGeomSPIStirlingCooler()
{;}

void PIMPGeomSPIStirlingCooler::Create(G4LogicalVolume* Parent, 
				const G4ThreeVector* Position, 
				G4RotationMatrix* Rotation,
				G4int Copy)
{  
  G4VPhysicalVolume* p_SPIStirlingCooler = new G4PVPlacement(Rotation,
							     *Position,	
							     l_SPIStirlingCooler,
							     "StirlingCooler",
							     Parent,
							     false,
							     Copy);
 
 // ------------------- VISUALISATION -----------------------


  return ;
}
