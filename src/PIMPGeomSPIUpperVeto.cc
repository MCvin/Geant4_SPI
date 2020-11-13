
// ------------------------------------------------------------------
// PIMPGeometry - SPIUpperVeto
// DRW 3/3/04
// ------------------------------------------------------------------

#include "PIMPGeomSPIUpperVeto.hh"

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

PIMPGeomSPIUpperVeto::PIMPGeomSPIUpperVeto(const G4MaterialTable* Materials, PIMPSensitive* Sens)
{

  // Now build the VETO - the veto ring around the collimator
  
  const G4String SPIUpperVETOName = "SPIUpperVETO"; // SVUP
  G4Tubs* s_SPIUpperVETO = new G4Tubs(SPIUpperVETOName,0.*cm,42.2*cm,21.5*cm,0.*deg,360.*deg);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_SPIUpperVETO = new G4LogicalVolume(s_SPIUpperVETO,
				       Material,
				       SPIUpperVETOName); 
    

  const G4String SPIUpVetoAlTubeName = "SPIUpVetoAlTube"; // SMTB
  G4Tubs* s_SPIUpVetoAlTube = new G4Tubs(SPIUpVetoAlTubeName,
					 41.85*cm,42.05*cm,21.5*cm,0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPIUpVetoAlTube = new G4LogicalVolume(s_SPIUpVetoAlTube,
							   Material,
							   SPIUpVetoAlTubeName);
  G4VPhysicalVolume* p_SPIUpVetoAlTube = new G4PVPlacement(0,
							   G4ThreeVector(0.,0.*cm,0.*cm),
							   l_SPIUpVetoAlTube,
							   SPIUpVetoAlTubeName,
							   l_SPIUpperVETO,
							   false,
							   0);
  
  // Rotation Matrixes for VETO slabs
  G4RotationMatrix* RotateVetoA = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoB = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoC = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoD = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoE = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoF = new G4RotationMatrix ;
  RotateVetoA->rotateZ(0.*deg);
  RotateVetoB->rotateZ(60.*deg);
  RotateVetoC->rotateZ(120.*deg);
  RotateVetoD->rotateZ(180.*deg);
  RotateVetoE->rotateZ(240.*deg);
  RotateVetoF->rotateZ(300.*deg);


  // Carbon structure
  const G4String SPIUpVetoSupp1Name = "SPIUpVetoSupp1"; // SVCA
  G4Trap* s_SPIUpVetoSupp1 = new G4Trap(SPIUpVetoSupp1Name,
					0.075*cm,
					0.*deg,0.*deg,
					0.8*cm,14.1*cm,13.6381*cm,-16.1*deg,
					0.8*cm,14.1*cm,13.6381*cm,-16.1*deg );
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIUpVetoSupp1 = new G4LogicalVolume(s_SPIUpVetoSupp1,
							  Material,
							  SPIUpVetoSupp1Name); 
  G4VPhysicalVolume* p_SPIUpVetoSupp1 ;
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								  23.6*cm,
								  21.425*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 0);

  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								  13.5288*cm,
								  21.425*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 1);

  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								  -10.0712*cm,
								  21.425*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 2);

  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								  -23.6*cm,
								  21.425*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 3);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								  -13.5288*cm,
								  21.425*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 4);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								  10.0712*cm,
								  21.425*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 5);

  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								  23.6*cm,
								  -15.725*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 6);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								  13.5288*cm,
								  -15.725*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 7);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								  -10.0712*cm,
								  -15.725*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 8);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								  -23.6*cm,
								  -15.725*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 9);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								  -13.5288*cm,
								  -15.725*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 10);
  p_SPIUpVetoSupp1 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								  10.0712*cm,
								  -15.725*cm),
				       l_SPIUpVetoSupp1, SPIUpVetoSupp1Name,
				       l_SPIUpperVETO, false, 11);


  // Carbon structure - twice the thickness
  const G4String SPIUpVetoSupp2Name = "SPIUpVetoSupp2"; // SVCB
  G4Trap* s_SPIUpVetoSupp2 = new G4Trap(SPIUpVetoSupp2Name,
					0.325*cm,
					0.*deg,0.*deg,
					0.8*cm,14.1*cm,13.6381*cm,-16.1*deg,
					0.8*cm,14.1*cm,13.6381*cm,-16.1*deg );
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIUpVetoSupp2 = new G4LogicalVolume(s_SPIUpVetoSupp2,
							  Material,
							  SPIUpVetoSupp2Name);
  G4VPhysicalVolume* p_SPIUpVetoSupp2 ;
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								  23.6*cm,
								  9.125*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 0);

  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								  13.5288*cm,
								  9.125*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 1);

  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								  -10.0712*cm,
								  9.125*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 2);

  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								  -23.6*cm,
								  9.125*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 3);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								  -13.5288*cm,
								  9.125*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 4);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								  10.0712*cm,
								  9.125*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 5);

  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								  23.6*cm,
								  -3.425*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 6);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								  13.5288*cm,
								  -3.425*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 7);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								  -10.0712*cm,
								  -3.425*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 8);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								  -23.6*cm,
								  -3.425*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 9);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								  -13.5288*cm,
								  -3.425*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 10);
  p_SPIUpVetoSupp2 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								  10.0712*cm,
								  -3.425*cm),
				       l_SPIUpVetoSupp2, SPIUpVetoSupp2Name,
				       l_SPIUpperVETO, false, 11);

  // BGO slabs for veto ...
  const G4String SPIUpVetoBGOName = "SPIUpVetoBGO"; // SVBA
  G4Trap* s_SPIUpVetoBGO = new G4Trap(SPIUpVetoBGOName,
					5.95*cm,
					0.*deg,0.*deg,
					0.8*cm,14.1*cm,13.6381*cm,-16.1*deg,
					0.8*cm,14.1*cm,13.6381*cm,-16.1*deg );
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPIUpVetoBGO = new G4LogicalVolume(s_SPIUpVetoBGO,
							Material,
							SPIUpVetoBGOName);
  
  G4VPhysicalVolume* p_SPIUpVetoBGO ;
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								23.6*cm,
								15.4*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 0);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								13.5288*cm,
								15.4*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 1);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								-10.0712*cm,
								15.4*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 2);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								-23.6*cm,
								15.4*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 3);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								-13.5288*cm,
								15.4*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 4);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								10.0712*cm,
								15.4*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 5);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								23.6*cm,
								2.85*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 6);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								13.5288*cm,
								2.85*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 7);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								-10.0712*cm,
								2.85*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 8);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								-23.6*cm,
								2.85*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 9);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								-13.5288*cm,
								2.85*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 10);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								10.0712*cm,
								2.85*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 11);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								23.6*cm,
								-9.7*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 12);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoB, G4ThreeVector(19.4401*cm,
								13.5288*cm,
								-9.7*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 13);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoC, G4ThreeVector(21.4363*cm,
								-10.0712*cm,
								-9.7*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 14);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								-23.6*cm,
								-9.7*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 15);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoE, G4ThreeVector(-19.4401*cm,
								-13.5288*cm,
								-9.7*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 16);
  p_SPIUpVetoBGO = new G4PVPlacement(RotateVetoF, G4ThreeVector(-21.4363*cm,
								10.0712*cm,
								-9.7*cm),
				     l_SPIUpVetoBGO, SPIUpVetoBGOName,
				     l_SPIUpperVETO, false, 17);
  
  // The electronics ....
  const G4String SPIUpVetoBigElecName = "SPIUpVetoBigElec"; // SEBX
  G4Box* s_SPIUpVetoBigElec = new G4Box(SPIUpVetoBigElecName,
					 5.0*cm, 4.0*cm, 6.0*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIUpVetoBigElec = new G4LogicalVolume(s_SPIUpVetoBigElec,
							    Material,
							    SPIUpVetoBigElecName);
  G4VPhysicalVolume* p_SPIUpVetoBigElec ;
  p_SPIUpVetoBigElec = new G4PVPlacement(RotateVetoA, G4ThreeVector(-1.9962*cm,
								    33.6*cm,
								    2.95*cm),
					 l_SPIUpVetoBigElec, SPIUpVetoBigElecName,
					 l_SPIUpperVETO, false, 0);
  p_SPIUpVetoBigElec = new G4PVPlacement(RotateVetoC, G4ThreeVector(30.4872*cm,
								    -14.3232*cm,
								    2.95*cm),
					 l_SPIUpVetoBigElec, SPIUpVetoBigElecName,
					 l_SPIUpperVETO, false, 1);
  p_SPIUpVetoBigElec = new G4PVPlacement(RotateVetoE, G4ThreeVector(-27.6481*cm,
								    -19.2408*cm,
								    2.95*cm),
					 l_SPIUpVetoBigElec, SPIUpVetoBigElecName,
					 l_SPIUpperVETO, false, 2);
  const G4String SPIUpVetoSmallElecName = "SPIUpVetoSmallElec"; // SPIE
  G4Box* s_SPIUpVetoSmallElec = new G4Box(SPIUpVetoSmallElecName,
					  4.0*cm, 2.0*cm, 3.0*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIUpVetoSmallElec = new G4LogicalVolume(s_SPIUpVetoSmallElec,
							      Material,
							      SPIUpVetoSmallElecName);
  G4VPhysicalVolume* p_SPIUpVetoSmallElec ;
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoB, G4ThreeVector(27.6481*cm,
								      19.2408*cm,
								      15.25*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 0);
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoB, G4ThreeVector(27.6481*cm,
								      19.2408*cm,
								      2.95*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 1);
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoB, G4ThreeVector(27.6481*cm,
								      19.2408*cm,
								      -9.35*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 2); 
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								      -33.6*cm,
								      15.25*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 3);
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								      -33.6*cm,
								      2.95*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 4);
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoD, G4ThreeVector(1.9962*cm,
								      -33.6*cm,
								      -9.35*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 5); 
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoF, G4ThreeVector(-30.4872*cm,
								      14.3232*cm,
								      15.25*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 6);
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoF, G4ThreeVector(-30.4872*cm,
								      14.3232*cm,
								      2.95*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 7);
  p_SPIUpVetoSmallElec = new G4PVPlacement(RotateVetoF, G4ThreeVector(-30.4872*cm,
								      14.3232*cm,
								      -9.35*cm),
					   l_SPIUpVetoSmallElec, SPIUpVetoSmallElecName,
					   l_SPIUpperVETO, false, 8); 

  // PMT's
  const G4String SPIUpVetoPMTName = "SPIUpVetoPMT"; // SPMT
  G4Tubs* s_SPIUpVetoPMT = new G4Tubs(SPIUpVetoPMTName,
				      0.*cm,2.0*cm,2.0*cm, 
				      0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIUpVetoPMT = new G4LogicalVolume(s_SPIUpVetoPMT,
							Material,
							SPIUpVetoPMTName);

  G4RotationMatrix* RotateVetoPMTA = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoPMTB = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoPMTC = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoPMTD = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoPMTE = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoPMTF = new G4RotationMatrix ;
  
  RotateVetoPMTA->rotateX(90.*deg);
  RotateVetoPMTB->rotateX(90.*deg);
  RotateVetoPMTC->rotateX(90.*deg);
  RotateVetoPMTD->rotateX(90.*deg);
  RotateVetoPMTE->rotateX(90.*deg);
  RotateVetoPMTF->rotateX(90.*deg);

  RotateVetoPMTA->rotateY(0.*deg);
  RotateVetoPMTB->rotateY(-60.*deg);
  RotateVetoPMTC->rotateY(-120.*deg);
  RotateVetoPMTD->rotateY(-180.*deg);
  RotateVetoPMTE->rotateY(-240.*deg);
  RotateVetoPMTF->rotateY(-300.*deg);

  G4VPhysicalVolume* p_SPIUpVetoPMT ; 
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(12.104*cm,
								   29.6*cm,
								   15.25*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 0);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(32.3561*cm,
								   4.7288*cm,
								   15.25*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 1);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(21.2922*cm,
								   -29.6*cm,
								   15.25*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 2);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-12.104*cm,
								   -29.6*cm,
								   15.25*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 3);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-32.3561*cm,
								   -4.7288*cm,
								   15.25*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 4);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-21.2922*cm,
								   26.6*cm,
								   15.25*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 5);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(12.104*cm,
								   29.6*cm,
								   2.95*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 6);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(32.3561*cm,
								   4.7288*cm,
								   2.95*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 7);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(21.2922*cm,
								   -29.6*cm,
								   2.95*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 8);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-12.104*cm,
								   -29.6*cm,
								   2.95*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 9);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-32.3561*cm,
								   -4.7288*cm,
								   2.95*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 10);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-21.2922*cm,
								   26.6*cm,
								   2.95*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 11);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(12.104*cm,
								   29.6*cm,
								   -9.35*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 12);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(32.3561*cm,
								   4.7288*cm,
								   -9.35*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 13);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(21.2922*cm,
								   -29.6*cm,
								   -9.35*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 14);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-12.104*cm,
								   -29.6*cm,
								   -9.35*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 15);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-32.3561*cm,
								   -4.7288*cm,
								   -9.35*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 16);
  p_SPIUpVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-21.2922*cm,
								   26.6*cm,
								   -9.35*cm),
				     l_SPIUpVetoPMT, SPIUpVetoPMTName,
				     l_SPIUpperVETO, false, 17);
  
  // Veto support structure
  const G4String SPIUpVetoSuppStrutName = "SPIUpVetoSuppStrut"; // SVES
  G4Trd* s_SPIUpVetoSuppStrut = new G4Trd(SPIUpVetoSuppStrutName,
					  3.0*cm, 2.0*cm, 
					  0.5*cm, 0.5*cm,
					  20.0*cm);
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIUpVetoSuppStrut = new G4LogicalVolume(s_SPIUpVetoSuppStrut,
							      Material,
							      SPIUpVetoSuppStrutName);
  G4VPhysicalVolume* p_SPIUpVetoSuppStrut ;
  G4RotationMatrix* rotateVetoSuppA = new G4RotationMatrix ;
  G4RotationMatrix* rotateVetoSuppB = new G4RotationMatrix ;
  G4RotationMatrix* rotateVetoSuppC = new G4RotationMatrix ;
  G4RotationMatrix* rotateVetoSuppD = new G4RotationMatrix ;
  G4RotationMatrix* rotateVetoSuppE = new G4RotationMatrix ;
  G4RotationMatrix* rotateVetoSuppF = new G4RotationMatrix ;

  rotateVetoSuppA->rotateZ(90*deg) ;
  rotateVetoSuppB->rotateZ(90*deg) ;
  rotateVetoSuppC->rotateZ(90*deg) ;
  rotateVetoSuppD->rotateZ(90*deg) ;
  rotateVetoSuppE->rotateZ(90*deg) ;
  rotateVetoSuppF->rotateZ(90*deg) ;

  rotateVetoSuppA->rotateZ(0*deg) ;
  rotateVetoSuppB->rotateZ(60*deg) ;
  rotateVetoSuppC->rotateZ(120*deg) ;
  rotateVetoSuppD->rotateZ(180*deg) ;
  rotateVetoSuppE->rotateZ(240*deg) ;
  rotateVetoSuppF->rotateZ(300*deg) ;

  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppA, G4ThreeVector(9.604*cm,
									   29.6*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 1);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppB, G4ThreeVector(16.404*cm,
									   29.6*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 2);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppB, G4ThreeVector(31.1061*cm,
									   6.8938*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 3);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppC, G4ThreeVector(34.3561*cm,
									   1.2648*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 4);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppC, G4ThreeVector(22.5422*cm,
									   -24.435*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 5);  
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppD, G4ThreeVector(19.2922*cm,
									   -30.064*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 6);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppD, G4ThreeVector(-9.604*cm,
									   -29.6*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 7);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppE, G4ThreeVector(-16.604*cm,
									   -29.6*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 8);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppE, G4ThreeVector(-31.1061*cm,
									   -6.8938*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 9);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppF, G4ThreeVector(-34.3561*cm,
									   -1.2648*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 10);
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppF, G4ThreeVector(-22.5422*cm,
									   24.435*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 11); 
  p_SPIUpVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppA, G4ThreeVector(-19.2922*cm,
									   30.064*cm,
									   1.5*cm),
					    l_SPIUpVetoSuppStrut, 
					    SPIUpVetoSuppStrutName,
					    l_SPIUpperVETO, false, 0);

 
  // ------------------- VISUALISATION -----------------------
  l_SPIUpVetoBGO->SetVisAttributes(Red);
  l_SPIUpVetoSuppStrut->SetVisAttributes(Red);
  l_SPIUpVetoSupp1->SetVisAttributes(Red);
  l_SPIUpVetoSupp2->SetVisAttributes(Yellow);
  //  l_SPIUpVetoBigElec->SetVisAttributes(Yellow);
  l_SPIUpVetoSmallElec->SetVisAttributes(SkyBlue);
  l_SPIUpVetoPMT->SetVisAttributes(Red);

  // -------------------- SENSITIVITY ---------------------------.
  
  l_SPIUpVetoBGO->SetSensitiveDetector(Sens); 
 
}


PIMPGeomSPIUpperVeto::~PIMPGeomSPIUpperVeto()
{;}

void PIMPGeomSPIUpperVeto::Create(G4LogicalVolume* Parent, 
				  const G4ThreeVector* Position, 
				  G4RotationMatrix* Rotation,
				  G4int Copy)
{  
  // G4cout << "test3" << G4endl ;
  const G4String SPIUpperVetoName = "SPIUpperVeto" ;
  // G4cout << *Position << G4endl ;
  // G4cout << Rotation << G4endl ;
  // G4cout << l_SPIUpperVETO->GetName() << G4endl ;
  // G4cout << SPIUpperVetoName << G4endl ;
  // G4cout << Parent->GetName() << G4endl ;
  
  // Create 
  // G4RotationMatrix* RotateUpperVeto = new G4RotationMatrix ;
  //  RotateUpperVeto->rotateZ(120*deg);
  
  G4VPhysicalVolume* p_SPIUpperVETO = new G4PVPlacement(Rotation,
							*Position,
							l_SPIUpperVETO,
							SPIUpperVetoName,
							Parent,
							false,
							Copy); 
  
  
   
 // ------------------- VISUALISATION -----------------------


  return ;
}

