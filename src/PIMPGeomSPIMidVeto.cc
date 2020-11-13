
// ------------------------------------------------------------------
// PIMPGeometry - SPIMidVeto
// DRW 3/3/04
// ------------------------------------------------------------------

#include "PIMPGeomSPIMidVeto.hh"

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

PIMPGeomSPIMidVeto::PIMPGeomSPIMidVeto(const G4MaterialTable* Materials, PIMPSensitive* Sens)
{

  // Now build the VETO - the veto ring around the collimator
  
  const G4String SPIMidVETOName = "SPIMidVETO"; // SVMI
  G4Tubs* s_SPIMidVETO = new G4Tubs(SPIMidVETOName,0.*cm,42.1*cm,19.3*cm,0.*deg,360.*deg);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_SPIMidVETO = new G4LogicalVolume(s_SPIMidVETO,
				       Material,
				       SPIMidVETOName); 
    

  const G4String SPIMidVetoAlTubeName = "SPIMidVetoAlTube"; // SLTB
  G4Tubs* s_SPIMidVetoAlTube = new G4Tubs(SPIMidVetoAlTubeName,
					 41.85*cm,42.1*cm,19.3*cm,0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPIMidVetoAlTube = new G4LogicalVolume(s_SPIMidVetoAlTube,
							   Material,
							   SPIMidVetoAlTubeName);
  G4VPhysicalVolume* p_SPIMidVetoAlTube = new G4PVPlacement(0,
							   G4ThreeVector(0.,0.*cm,0.*cm),
							   l_SPIMidVetoAlTube,
							   SPIMidVetoAlTubeName,
							   l_SPIMidVETO,
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
  const G4String SPIMidVetoSupp1Name = "SPIMidVetoSupp1"; // SVCC
  G4Trap* s_SPIMidVetoSupp1 = new G4Trap(SPIMidVetoSupp1Name,
					0.085*cm,
					0.*deg,0.*deg,
					0.95*cm,12.115*cm,11.5665*cm,-16.1*deg,
					0.95*cm,12.115*cm,11.5665*cm,-16.1*deg );
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIMidVetoSupp1 = new G4LogicalVolume(s_SPIMidVetoSupp1,
							  Material,
							  SPIMidVetoSupp1Name); 
  G4VPhysicalVolume* p_SPIMidVetoSupp1 ;
  p_SPIMidVetoSupp1 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.335*cm,
								  19.75*cm,
								  18.785*cm),
				       l_SPIMidVetoSupp1, SPIMidVetoSupp1Name,
				       l_SPIMidVETO, false, 0);

  p_SPIMidVetoSupp1 = new G4PVPlacement(RotateVetoB, G4ThreeVector(15.9365*cm,
								  11.8972*cm,
								  18.785*cm),
				       l_SPIMidVetoSupp1, SPIMidVetoSupp1Name,
				       l_SPIMidVETO, false, 1);

  p_SPIMidVetoSupp1 = new G4PVPlacement(RotateVetoC, G4ThreeVector(18.2715*cm,
								  -7.8528*cm,
								  18.785*cm),
				       l_SPIMidVetoSupp1, SPIMidVetoSupp1Name,
				       l_SPIMidVETO, false, 2);

  p_SPIMidVetoSupp1 = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.335*cm,
								  -19.75*cm,
								  18.785*cm),
				       l_SPIMidVetoSupp1, SPIMidVetoSupp1Name,
				       l_SPIMidVETO, false, 3);
  p_SPIMidVetoSupp1 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-15.9365*cm,
								  -11.8972*cm,
								  18.785*cm),
				       l_SPIMidVetoSupp1, SPIMidVetoSupp1Name,
				       l_SPIMidVETO, false, 4);
  p_SPIMidVetoSupp1 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-18.2715*cm,
								  7.8528*cm,
								  18.785*cm),
				       l_SPIMidVetoSupp1, SPIMidVetoSupp1Name,
				       l_SPIMidVETO, false, 5);

  // Carbon structure - 
  const G4String SPIMidVetoSupp2Name = "SPIMidVetoSupp2"; // SVCD
  G4Trap* s_SPIMidVetoSupp2 = new G4Trap(SPIMidVetoSupp2Name,
					 0.325*cm,
					 0.*deg,0.*deg,
					 1.2*cm,12.115*cm,11.422*cm,-16.1*deg,
					 1.2*cm,12.115*cm,11.422*cm,-16.1*deg);
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIMidVetoSupp2 = new G4LogicalVolume(s_SPIMidVetoSupp2,
							   Material,
							   SPIMidVetoSupp2Name);
  G4VPhysicalVolume* p_SPIMidVetoSupp2 ;
  p_SPIMidVetoSupp2 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.6959*cm,
								   19.5*cm,
								   6.675*cm),
					l_SPIMidVetoSupp2, SPIMidVetoSupp2Name,
					l_SPIMidVETO, false, 0);
  p_SPIMidVetoSupp2 = new G4PVPlacement(RotateVetoB, G4ThreeVector(15.5395*cm,
								  12.0847*cm,
								  6.675*cm),
				       l_SPIMidVetoSupp2, SPIMidVetoSupp2Name,
				       l_SPIMidVETO, false, 1);
  p_SPIMidVetoSupp2 = new G4PVPlacement(RotateVetoC, G4ThreeVector(18.2354*cm,
								  -7.4153*cm,
								  6.675*cm),
				       l_SPIMidVetoSupp2, SPIMidVetoSupp2Name,
				       l_SPIMidVETO, false, 2);

  p_SPIMidVetoSupp2 = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.6959*cm,
								  -19.5*cm,
								  6.675*cm),
				       l_SPIMidVetoSupp2, SPIMidVetoSupp2Name,
				       l_SPIMidVETO, false, 3);
  p_SPIMidVetoSupp2 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-15.5395*cm,
								  -12.0847*cm,
								  6.675*cm),
				       l_SPIMidVetoSupp2, SPIMidVetoSupp2Name,
				       l_SPIMidVETO, false, 4);
  p_SPIMidVetoSupp2 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-18.2354*cm,
								  7.4153*cm,
								  6.675*cm),
				       l_SPIMidVetoSupp2, SPIMidVetoSupp2Name,
				       l_SPIMidVETO, false, 5);

  // Carbon structure - 
  const G4String SPIMidVetoSupp3Name = "SPIMidVetoSupp3"; // SVCE
  G4Trap* s_SPIMidVetoSupp3 = new G4Trap(SPIMidVetoSupp3Name,
					 0.325*cm,
					 0.*deg,0.*deg,
					 1.4*cm,12.115*cm,11.3067*cm,-16.1*deg,
					 1.4*cm,12.115*cm,11.3067*cm,-16.1*deg);
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIMidVetoSupp3 = new G4LogicalVolume(s_SPIMidVetoSupp3,
							   Material,
							   SPIMidVetoSupp3Name);
  G4VPhysicalVolume* p_SPIMidVetoSupp3 ;
  p_SPIMidVetoSupp3 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.9846*cm,
								   19.3*cm,
								   -5.675*cm),
					l_SPIMidVetoSupp3, SPIMidVetoSupp3Name,
					l_SPIMidVETO, false, 0);
  p_SPIMidVetoSupp3 = new G4PVPlacement(RotateVetoB, G4ThreeVector(15.222*cm,
								   12.2347*cm,
								   -5.675*cm),
					l_SPIMidVetoSupp3, SPIMidVetoSupp3Name,
					l_SPIMidVETO, false, 1);
  p_SPIMidVetoSupp3 = new G4PVPlacement(RotateVetoC, G4ThreeVector(18.2066*cm,
								   -7.0653*cm,
								   -5.675*cm),
					l_SPIMidVetoSupp3, SPIMidVetoSupp3Name,
					l_SPIMidVETO, false, 2);
  
  p_SPIMidVetoSupp3 = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.9846*cm,
								   -19.3*cm,
								   -5.675*cm),
					l_SPIMidVetoSupp3, SPIMidVetoSupp3Name,
					l_SPIMidVETO, false, 3);
  p_SPIMidVetoSupp3 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-15.222*cm,
								   -12.2347*cm,
								   -5.675*cm),
					l_SPIMidVetoSupp3, SPIMidVetoSupp3Name,
					l_SPIMidVETO, false, 4);
  p_SPIMidVetoSupp3 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-18.2066*cm,
								   7.0653*cm,
								   -5.675*cm),
					l_SPIMidVetoSupp3, SPIMidVetoSupp3Name,
					l_SPIMidVETO, false, 5);
  
 
  // leaving SVCF out as its only 0.085cm thick slice of carbon fibre 
  // It wouldn't stop an asmatic ant !

 // BGO slabs for veto ... PART A
  const G4String SPIMidVetoBGOaName = "SPIMidVetoBGOa"; // SVBA
  G4Trap* s_SPIMidVetoBGOa = new G4Trap(SPIMidVetoBGOaName,
					5.85*cm,
					0.*deg,0.*deg,
					0.95*cm,12.115*cm,11.5665*cm,-16.1*deg,
					0.95*cm,12.115*cm,11.5665*cm,-16.1*deg  );
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPIMidVetoBGOa = new G4LogicalVolume(s_SPIMidVetoBGOa,
							  Material,
							  SPIMidVetoBGOaName);
  
  G4VPhysicalVolume* p_SPIMidVetoBGOa ;
  p_SPIMidVetoBGOa = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.335*cm,
								  19.75*cm,
								  12.85*cm),
				       l_SPIMidVetoBGOa, SPIMidVetoBGOaName,
				       l_SPIMidVETO, false, 0);
  p_SPIMidVetoBGOa = new G4PVPlacement(RotateVetoB, G4ThreeVector(15.9365*cm,
								  11.8972*cm,
								  12.85*cm),
				       l_SPIMidVetoBGOa, SPIMidVetoBGOaName,
				       l_SPIMidVETO, false, 1);
  p_SPIMidVetoBGOa = new G4PVPlacement(RotateVetoC, G4ThreeVector(18.2715*cm,
								  -7.8528*cm,
								  12.85*cm),
				       l_SPIMidVetoBGOa, SPIMidVetoBGOaName,
				       l_SPIMidVETO, false, 2);
  p_SPIMidVetoBGOa = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.335*cm,
								  -19.75*cm,
								  12.85*cm),
				       l_SPIMidVetoBGOa, SPIMidVetoBGOaName,
				       l_SPIMidVETO, false, 3);
  p_SPIMidVetoBGOa = new G4PVPlacement(RotateVetoE, G4ThreeVector(-15.9365*cm,
								  -11.8972*cm,
								  12.85*cm),
				       l_SPIMidVetoBGOa, SPIMidVetoBGOaName,
				       l_SPIMidVETO, false, 4);
  p_SPIMidVetoBGOa = new G4PVPlacement(RotateVetoF, G4ThreeVector(-18.2715*cm,
								  7.8528*cm,
								  12.85*cm),
				       l_SPIMidVetoBGOa, SPIMidVetoBGOaName,
				       l_SPIMidVETO, false, 5);
  // BGO slabs for veto ... PART B
  const G4String SPIMidVetoBGObName = "SPIMidVetoBGOb"; // SVBC
  G4Trap* s_SPIMidVetoBGOb = new G4Trap(SPIMidVetoBGObName,
					5.85*cm,
					0.*deg,0.*deg,
					1.2*cm,12.115*cm,11.422*cm,-16.1*deg,
					1.2*cm,12.115*cm,11.422*cm,-16.1*deg  );
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPIMidVetoBGOb = new G4LogicalVolume(s_SPIMidVetoBGOb,
							  Material,
							  SPIMidVetoBGObName);
  
  G4VPhysicalVolume* p_SPIMidVetoBGOb ;
  p_SPIMidVetoBGOb = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.6959*cm,
								  19.5*cm,
								  0.5*cm),
				       l_SPIMidVetoBGOb, SPIMidVetoBGObName,
				       l_SPIMidVETO, false, 0);
  p_SPIMidVetoBGOb = new G4PVPlacement(RotateVetoB, G4ThreeVector(15.5395*cm,
								  12.0847*cm,
								  0.5*cm),
				       l_SPIMidVetoBGOb, SPIMidVetoBGObName,
				       l_SPIMidVETO, false, 1);
  p_SPIMidVetoBGOb = new G4PVPlacement(RotateVetoC, G4ThreeVector(18.2354*cm,
								  -7.4153*cm,
								  0.5*cm),
				       l_SPIMidVetoBGOb, SPIMidVetoBGObName,
				       l_SPIMidVETO, false, 2);
  p_SPIMidVetoBGOb = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.6959*cm,
								  -19.5*cm,
								  0.5*cm),
				       l_SPIMidVetoBGOb, SPIMidVetoBGObName,
				       l_SPIMidVETO, false, 3);
  p_SPIMidVetoBGOb = new G4PVPlacement(RotateVetoE, G4ThreeVector(-15.5395*cm,
								  -12.0847*cm,
								  0.5*cm),
				       l_SPIMidVetoBGOb, SPIMidVetoBGObName,
				       l_SPIMidVETO, false, 4);
  p_SPIMidVetoBGOb = new G4PVPlacement(RotateVetoF, G4ThreeVector(-18.2354*cm,
								  7.4153*cm,
								  0.5*cm),
				       l_SPIMidVetoBGOb, SPIMidVetoBGObName,
				       l_SPIMidVETO, false, 5);
  
  // BGO slabs for veto ... PART C
  const G4String SPIMidVetoBGOcName = "SPIMidVetoBGOc"; // SVBD
  G4Trap* s_SPIMidVetoBGOc = new G4Trap(SPIMidVetoBGOcName,
					5.85*cm,
					0.*deg,0.*deg,
					1.4*cm,12.115*cm,11.3067*cm,-16.1*deg,
					1.4*cm,12.115*cm,11.3067*cm,-16.1*deg);
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPIMidVetoBGOc = new G4LogicalVolume(s_SPIMidVetoBGOc,
							  Material,
							  SPIMidVetoBGOcName);
  
  G4VPhysicalVolume* p_SPIMidVetoBGOc ;
  p_SPIMidVetoBGOc = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.9846*cm,
								  19.3*cm,
								  -11.85*cm),
				       l_SPIMidVetoBGOc, SPIMidVetoBGOcName,
				       l_SPIMidVETO, false, 0);
  p_SPIMidVetoBGOc = new G4PVPlacement(RotateVetoB, G4ThreeVector(15.222*cm,
								  12.2347*cm,
								  -11.85*cm),
				       l_SPIMidVetoBGOc, SPIMidVetoBGOcName,
				       l_SPIMidVETO, false, 1);
  p_SPIMidVetoBGOc = new G4PVPlacement(RotateVetoC, G4ThreeVector(18.2066*cm,
								  -7.0653*cm,
								  -11.85*cm),
				       l_SPIMidVetoBGOc, SPIMidVetoBGOcName,
				       l_SPIMidVETO, false, 2);
  p_SPIMidVetoBGOc = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.9846*cm,
								  -19.3*cm,
								  -11.85*cm),
				       l_SPIMidVetoBGOc, SPIMidVetoBGOcName,
				       l_SPIMidVETO, false, 3);
  p_SPIMidVetoBGOc = new G4PVPlacement(RotateVetoE, G4ThreeVector(-15.222*cm,
								  -12.2347*cm,
								  -11.85*cm),
				       l_SPIMidVetoBGOc, SPIMidVetoBGOcName,
				       l_SPIMidVETO, false, 4);
  p_SPIMidVetoBGOc = new G4PVPlacement(RotateVetoF, G4ThreeVector(-18.2066*cm,
								  7.0653*cm,
								  -11.85*cm),
				       l_SPIMidVetoBGOc, SPIMidVetoBGOcName,
				       l_SPIMidVETO, false, 5);
  

  
  // The electronics ....

  const G4String SPIMidVetoSmallElecName = "SPIMidVetoSmallElec"; // SPIE
  G4Box* s_SPIMidVetoSmallElec = new G4Box(SPIMidVetoSmallElecName,
					  4.0*cm, 2.0*cm, 3.0*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIMidVetoSmallElec = new G4LogicalVolume(s_SPIMidVetoSmallElec,
							      Material,
							      SPIMidVetoSmallElecName);
  G4VPhysicalVolume* p_SPIMidVetoSmallElec ;
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.9846*cm,
								       25.3*cm,
								       12.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 0);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.9846*cm,
								       25.3*cm,
								       0.5*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 1);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoA, G4ThreeVector(-2.9846*cm,
								       25.3*cm,
								       -11.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 2); 
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoB, G4ThreeVector(20.418*cm,
								       15.2347*cm,
								       12.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 3);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoB, G4ThreeVector(20.418*cm,
								       15.2347*cm,
								       0.5*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 4);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoB, G4ThreeVector(20.418*cm,
								       15.2347*cm,
								       -11.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 5); 
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoC, G4ThreeVector(23.4026*cm,
								       -10.0653*cm,
								       12.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 6);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoC, G4ThreeVector(23.4026*cm,
								       -10.0653*cm,
								       0.5*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 7);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoC, G4ThreeVector(23.4026*cm,
								       -10.0653*cm,
								       -11.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 8); 
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.9846*cm,
								       -25.3*cm,
								       12.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 9);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.9846*cm,
								       -25.3*cm,
								       0.5*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 10);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoD, G4ThreeVector(2.9846*cm,
								       -25.3*cm,
								       -11.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 11); 
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoE, G4ThreeVector(-20.418*cm,
								       -15.2347*cm,
								       12.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 12);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoE, G4ThreeVector(-20.418*cm,
								       -15.2347*cm,
								       0.5*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 13);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoE, G4ThreeVector(-20.418*cm,
								       -15.2347*cm,
								       -11.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 14); 
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoF, G4ThreeVector(-23.4026*cm,
								       10.0653*cm,
								       12.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 15);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoF, G4ThreeVector(-23.4026*cm,
								       10.0653*cm,
								       0.5*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 16);
  p_SPIMidVetoSmallElec = new G4PVPlacement(RotateVetoF, G4ThreeVector(-23.4026*cm,
								       10.0653*cm,
								       -11.85*cm),
					    l_SPIMidVetoSmallElec, SPIMidVetoSmallElecName,
					    l_SPIMidVETO, false, 17);
  

  // PMT's
  const G4String SPIMidVetoPMTName = "SPIMidVetoPMT"; // SPMT
  G4Tubs* s_SPIMidVetoPMT = new G4Tubs(SPIMidVetoPMTName,
				      0.*cm,2.0*cm,2.0*cm, 
				      0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPIMidVetoPMT = new G4LogicalVolume(s_SPIMidVetoPMT,
							Material,
							SPIMidVetoPMTName);

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

  G4VPhysicalVolume* p_SPIMidVetoPMT ; 
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(10.0154*cm,
								    25.3*cm,
								    15.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 0);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(26.918*cm,
								    3.9764*cm,
								    15.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 1);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(16.9026*cm,
								    -21.3236*cm,
								    15.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 2);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-10.0154*cm,
								    -25.3*cm,
								    15.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 3);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-26.918*cm,
								    -3.9764*cm,
								    15.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 4);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-16.9026*cm,
								    21.3236*cm,
								    15.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 5);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(10.0154*cm,
								    25.3*cm,
								    9.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 6);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(26.918*cm,
								    3.9764*cm,
								    9.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 7);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(16.9026*cm,
								    -21.3236*cm,
								    9.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 8);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-10.0154*cm,
								    -25.3*cm,
								    9.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 9);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-26.918*cm,
								    -3.9764*cm,
								    9.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 10);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-16.9026*cm,
								    21.3236*cm,
								    9.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 11);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(10.0154*cm,
								    25.3*cm,
								    3.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 12);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(26.918*cm,
								    3.9764*cm,
								    3.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 13);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(16.9026*cm,
								    -21.3236*cm,
								    3.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 14);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-10.0154*cm,
								    -25.3*cm,
								    3.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 15);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-26.918*cm,
								    -3.9764*cm,
								    3.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 16);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-16.9026*cm,
								    21.3236*cm,
								    3.5*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 17);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(10.0154*cm,
								   25.3*cm,
								   -2.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 18);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(26.918*cm,
								    3.9764*cm,
								    -2.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 19);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(16.9026*cm,
								    -21.3236*cm,
								    -2.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 20);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-10.0154*cm,
								    -25.3*cm,
								    -2.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 21);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-26.918*cm,
								    -3.9764*cm,
								    -2.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 22);
  p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-16.9026*cm,
								    21.3236*cm,
								    -2.5*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				      l_SPIMidVETO, false, 23);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(10.0154*cm,
								   25.3*cm,
								   -8.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 24);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(26.918*cm,
								   3.9764*cm,
								   -8.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 25);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(16.9026*cm,
								   -21.3236*cm,
								   -8.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 26);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-10.0154*cm,
								   -25.3*cm,
								   -8.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 27);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-26.918*cm,
								   -3.9764*cm,
								   -8.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 28);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-16.9026*cm,
								   21.3236*cm,
								   -8.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 29);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTA, G4ThreeVector(10.0154*cm,
								   25.3*cm,
								   -14.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 30);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTB, G4ThreeVector(26.918*cm,
								   3.9764*cm,
								   -14.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 31);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTC, G4ThreeVector(16.9026*cm,
								   -21.3236*cm,
								   -14.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 32);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTD, G4ThreeVector(-10.0154*cm,
								   -25.3*cm,
								   -14.85*cm),
				      l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 33);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTE, G4ThreeVector(-26.918*cm,
								   -3.9764*cm,
								   -14.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 34);
 p_SPIMidVetoPMT = new G4PVPlacement(RotateVetoPMTF, G4ThreeVector(-16.9026*cm,
								   21.3236*cm,
								   -14.85*cm),
				     l_SPIMidVetoPMT, SPIMidVetoPMTName,
				     l_SPIMidVETO, false, 35);


 
  // Veto support structure
  const G4String SPIMidVetoSuppStrutName = "SPIMidVetoSuppStrut"; // SVS2 and SVS3
  G4Trd* s_SPIMidVetoSuppStrut = new G4Trd(SPIMidVetoSuppStrutName,
					   3.0*cm, 2.0*cm, 
					   0.5*cm, 0.5*cm,
					   19.3*cm);
  Material =  PIMPSelectMaterial("CarbonFibre", Materials);
  G4LogicalVolume* l_SPIMidVetoSuppStrut = new G4LogicalVolume(s_SPIMidVetoSuppStrut,
							       Material,
							       SPIMidVetoSuppStrutName);
  G4VPhysicalVolume* p_SPIMidVetoSuppStrut ;
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

  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppA, G4ThreeVector(7.0154*cm,
									    26.3*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 1);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppE, G4ThreeVector(26.284*cm,
									    7.0745*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 2);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppF, G4ThreeVector(18.4586*cm,
									    -19.2255*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 3);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppD, G4ThreeVector(-7.0154*cm,
									    -26.3*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 4);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppB, G4ThreeVector(-26.284*cm,
									    -7.0745*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 5);  
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppC, G4ThreeVector(-18.4586*cm,
									    19.2255*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 6);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppE, G4ThreeVector(14.0154*cm,
									    25.3*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 7);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppF, G4ThreeVector(28.918*cm,
									    0.5123*cm,
									    0.*cm),
					    l_SPIMidVetoSuppStrut, 
					    SPIMidVetoSuppStrutName,
					    l_SPIMidVETO, false, 8);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppD, G4ThreeVector(14.9026*cm,
									    -24.7877*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 9);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppB, G4ThreeVector(-14.0154*cm,
									    -25.3*cm,
									    0.*cm),
					    l_SPIMidVetoSuppStrut, 
					    SPIMidVetoSuppStrutName,
					    l_SPIMidVETO, false, 10);
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppC, G4ThreeVector(-28.918*cm,
									    -0.5123*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 11); 
  p_SPIMidVetoSuppStrut  = new G4PVPlacement(rotateVetoSuppA, G4ThreeVector(-14.9026*cm,
									    24.7877*cm,
									    0.*cm),
					     l_SPIMidVetoSuppStrut, 
					     SPIMidVetoSuppStrutName,
					     l_SPIMidVETO, false, 0);
  
   
 
  // ------------------- VISUALISATION -----------------------
  l_SPIMidVetoBGOa->SetVisAttributes(Red);
  l_SPIMidVetoBGOb->SetVisAttributes(Red);
  l_SPIMidVetoBGOc->SetVisAttributes(Red);
  l_SPIMidVetoSuppStrut->SetVisAttributes(Red);
  l_SPIMidVetoSupp1->SetVisAttributes(Red);
  l_SPIMidVetoSupp2->SetVisAttributes(Yellow);
  l_SPIMidVetoSupp3->SetVisAttributes(Red);
  //  l_SPIMidVetoBigElec->SetVisAttributes(Yellow);
  l_SPIMidVetoSmallElec->SetVisAttributes(SkyBlue);
  l_SPIMidVetoPMT->SetVisAttributes(Red);

  // -------------------- SENSITIVITY ---------------------------.
  
  l_SPIMidVetoBGOa->SetSensitiveDetector(Sens); 
  l_SPIMidVetoBGOb->SetSensitiveDetector(Sens);  
  l_SPIMidVetoBGOc->SetSensitiveDetector(Sens);  

}


PIMPGeomSPIMidVeto::~PIMPGeomSPIMidVeto()
{;}

void PIMPGeomSPIMidVeto::Create(G4LogicalVolume* Parent, 
				  const G4ThreeVector* Position, 
				  G4RotationMatrix* Rotation,
				  G4int Copy)
{  
  // G4cout << "test3" << G4endl ;
  const G4String SPIMidVetoName = "SPIMidVeto" ;
  // G4cout << *Position << G4endl ;
  // G4cout << Rotation << G4endl ;
  // G4cout << l_SPIMidVETO->GetName() << G4endl ;
  // G4cout << SPIMidVetoName << G4endl ;
  // G4cout << Parent->GetName() << G4endl ;
  
  // Create 
  // G4RotationMatrix* RotateMidVeto = new G4RotationMatrix ;
  //  RotateMidVeto->rotateZ(120*deg);
  
  G4VPhysicalVolume* p_SPIMidVETO = new G4PVPlacement(Rotation,
							*Position,
							l_SPIMidVETO,
							SPIMidVetoName,
							Parent,
							false,
							Copy); 

   
 // ------------------- VISUALISATION -----------------------


  return ;
}

