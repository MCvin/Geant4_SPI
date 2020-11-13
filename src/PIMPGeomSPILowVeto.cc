
// ------------------------------------------------------------------
// PIMPGeometry - SPILowVeto
// DRW 3/3/04
// ------------------------------------------------------------------

#include "PIMPGeomSPILowVeto.hh"
#include "PIMPGeomSPIPixel.hh"

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

PIMPGeomSPILowVeto::PIMPGeomSPILowVeto(const G4MaterialTable* Materials, PIMPSensitive* Sens)
{

  // Now build the VETO
  //----------------------------------------------------------------------------------------------------//
  //					SPILowVETO Mother Volume					//
  //----------------------------------------------------------------------------------------------------//
  const G4String SPILowVETOName = "SPILowVETO"; // SVLO
  G4Cons* s_SPILowVETO = new G4Cons(SPILowVETOName,
				    0.*cm,54.7*cm,
				    0.*cm,43.15*cm,
				    37.4025*cm,
				    0.*deg,360.*deg);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_SPILowVETO = new G4LogicalVolume(s_SPILowVETO,
				     Material,
				     SPILowVETOName); 

  //----------------------------------------------------------------------------------------------------//
  //					The tubes around the veto					//
  //----------------------------------------------------------------------------------------------------//
  const G4String SPILowVetoAlUpTubeName = "SPILowVetoAlUpTube"; // SBT1
  G4Tubs* s_SPILowVetoAlUpTube = new G4Tubs(SPILowVetoAlUpTubeName,
					    41.85*cm,42.15*cm,10.9*cm,
					    0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPILowVetoAlUpTube = new G4LogicalVolume(s_SPILowVetoAlUpTube,
							      Material,
							      SPILowVetoAlUpTubeName);
  G4VPhysicalVolume* p_SPILowVetoAlUpTube = new G4PVPlacement(0,
							      G4ThreeVector(0.,0.*cm,26.4975*cm),
							      l_SPILowVetoAlUpTube,
							      SPILowVetoAlUpTubeName,
							      l_SPILowVETO,
							      false,
							      0);
  const G4String SPILowVetoAlLowTubeName = "SPILowVetoAlLowTube"; // SBT2
  G4Tubs* s_SPILowVetoAlLowTube = new G4Tubs(SPILowVetoAlLowTubeName,
					     40.75*cm,41.0*cm,2.0*cm,
					     0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPILowVetoAlLowTube = new G4LogicalVolume(s_SPILowVetoAlLowTube,
							       Material,
							       SPILowVetoAlLowTubeName);
  G4VPhysicalVolume* p_SPILowVetoAlLowTube = new G4PVPlacement(0,
							       G4ThreeVector(0.,0.*cm,13.5975*cm),
							       l_SPILowVetoAlLowTube,
							       SPILowVetoAlLowTubeName,
							       l_SPILowVETO,
							       false,
							       0);
  const G4String SPILowVetoAlRingerName = "SPILowVetoAlRinger"; // SBTR
  G4Tubs* s_SPILowVetoAlRinger = new G4Tubs(SPILowVetoAlRingerName,
					    38.75*cm,43.15*cm,0.5*cm,
					    0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPILowVetoAlRinger = new G4LogicalVolume(s_SPILowVetoAlRinger,
							      Material,
							      SPILowVetoAlRingerName);
  G4VPhysicalVolume* p_SPILowVetoAlRinger = new G4PVPlacement(0,
							      G4ThreeVector(0.,0.*cm,11.0975*cm),
							      l_SPILowVetoAlRinger,
							      SPILowVetoAlRingerName,
							      l_SPILowVETO,
							      false,
							      0);

  const G4String SPILowVetoAlLowConeName = "SPILowVetoAlLowCone"; // SBCN
  G4Cons* s_SPILowVetoAlLowCone = new G4Cons(SPILowVETOName,
					     51.25*cm,54.5*cm,
					     40.75*cm,41.*cm,
					     24.0*cm,
					     0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPILowVetoAlLowCone = new G4LogicalVolume(s_SPILowVetoAlLowCone,
							      Material,
							      SPILowVetoAlLowConeName);
  G4VPhysicalVolume* p_SPILowVetoAlLowCone = new G4PVPlacement(0,
							      G4ThreeVector(0.,0.,-13.4025*cm),
							      l_SPILowVetoAlLowCone,
							      SPILowVetoAlLowConeName,
							      l_SPILowVETO,
							      false,
							      0);
  const G4String SPILowVetoAlLCInnerName = "SPILowVetoAlLCInner"; // SBCM
  G4Cons* s_SPILowVetoAlLCInner = new G4Cons(SPILowVETOName,
					     51.*cm,51.1*cm,
					     19.9*cm,20.*cm,
					     10.85*cm,
					     0.*deg,360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_SPILowVetoAlLCInner = new G4LogicalVolume(s_SPILowVetoAlLCInner,
							      Material,
							      SPILowVetoAlLCInnerName);
  G4VPhysicalVolume* p_SPILowVetoAlLCInner = new G4PVPlacement(0,
							       G4ThreeVector(0.,0.,-25.7555*cm),
							       l_SPILowVetoAlLCInner,
							       SPILowVetoAlLCInnerName,
							       l_SPILowVETO,
							       false,
							       0);

  //----------------------------------------------------------------------------------------------------//
  //					The LowVeto Tiles (18)						//
  //----------------------------------------------------------------------------------------------------//
  const G4String SPILowVetoBeTile1Name = "SPILowVetoBeTile1"; // SVBE
  G4Trap* s_SPILowVetoBeTile1 = new G4Trap(SPILowVetoBeTile1Name,
					2.5*cm,
					5.86*deg,270.0*deg,
					7.862*cm,16.01955*cm,11.8275*cm,0.*deg,
					5.77255*cm,11.6509*cm,8.5731*cm,0.*deg );
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile1 = new G4LogicalVolume(s_SPILowVetoBeTile1,
							  Material,
							  SPILowVetoBeTile1Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile1 ;
  
  G4RotationMatrix* RotateVetoA = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoB = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoC = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoD = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoE = new G4RotationMatrix ;
  G4RotationMatrix* RotateVetoF = new G4RotationMatrix ;

  RotateVetoA->rotateZ(180*deg);
  RotateVetoB->rotateZ(240.*deg);
  RotateVetoC->rotateZ(300.*deg);
  RotateVetoD->rotateZ(0.*deg);
  RotateVetoE->rotateZ(60.*deg);
  RotateVetoF->rotateZ(120.*deg);

  RotateVetoA->rotateX(-62.5*deg);
  RotateVetoB->rotateX(-62.5*deg);
  RotateVetoC->rotateX(-62.5*deg);
  RotateVetoD->rotateX(-62.5*deg);
  RotateVetoE->rotateX(-62.5*deg);
  RotateVetoF->rotateX(-62.5*deg);

  p_SPILowVetoBeTile1 = new G4PVPlacement(RotateVetoA, G4ThreeVector(-3.2887*cm,
								     21.2663*cm,31.1975*cm),
					  l_SPILowVetoBeTile1, SPILowVetoBeTile1Name,
					  l_SPILowVETO, false, 0);
  
  p_SPILowVetoBeTile1 = new G4PVPlacement(RotateVetoB, G4ThreeVector(16.7728*cm,
								     13.4821*cm,31.1975*cm),
					  l_SPILowVetoBeTile1, SPILowVetoBeTile1Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile1 = new G4PVPlacement(RotateVetoC, G4ThreeVector(20.0615*cm,
								     -7.7851*cm,31.1975*cm),
					  l_SPILowVetoBeTile1, SPILowVetoBeTile1Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile1 = new G4PVPlacement(RotateVetoD, G4ThreeVector(3.2887*cm,
								     -21.2663*cm,31.1975*cm),
					  l_SPILowVetoBeTile1, SPILowVetoBeTile1Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile1 = new G4PVPlacement(RotateVetoE, G4ThreeVector(-16.7728*cm,
								     -13.4821*cm,31.1975*cm),
					  l_SPILowVetoBeTile1, SPILowVetoBeTile1Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile1 = new G4PVPlacement(RotateVetoF, G4ThreeVector(-20.0615*cm,
								     7.7851*cm,31.1975*cm),
					  l_SPILowVetoBeTile1, SPILowVetoBeTile1Name,
					  l_SPILowVETO, false, 5);


  const G4String SPILowVetoBeTile2Name = "SPILowVetoBeTile2"; // SVBF
  G4Trap* s_SPILowVetoBeTile2 = new G4Trap(SPILowVetoBeTile2Name,
					2.5*cm,
					30.0*deg,60.0*deg,
					10.55*cm,7.665*cm,7.665*cm,0.*deg,
					8.05*cm,6.2216*cm,6.2216*cm,0.*deg );
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile2 = new G4LogicalVolume(s_SPILowVetoBeTile2,
							  Material,
							  SPILowVetoBeTile2Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile2 ;
  
  G4RotationMatrix* RotateVeto2A = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto2B = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto2C = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto2D = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto2E = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto2F = new G4RotationMatrix ;
  
  RotateVeto2A->rotateX(90.*deg);
  RotateVeto2B->rotateX(90.*deg);
  RotateVeto2C->rotateX(90.*deg);
  RotateVeto2D->rotateX(90.*deg);
  RotateVeto2E->rotateX(90.*deg);
  RotateVeto2F->rotateX(90.*deg);
   
  RotateVeto2A->rotateZ(180.*deg);
  RotateVeto2B->rotateZ(180.*deg);
  RotateVeto2C->rotateZ(180.*deg);
  RotateVeto2D->rotateZ(180.*deg);
  RotateVeto2E->rotateZ(180.*deg);
  RotateVeto2F->rotateZ(180.*deg);
   
  RotateVeto2A->rotateY(0*deg);
  RotateVeto2B->rotateY(60.*deg);
  RotateVeto2C->rotateY(120.*deg);
  RotateVeto2D->rotateY(180.*deg);
  RotateVeto2E->rotateY(240.*deg);
  RotateVeto2F->rotateY(300.*deg);

  p_SPILowVetoBeTile2 = new G4PVPlacement(RotateVeto2A, G4ThreeVector(4.0153*cm,
								     25.0*cm,12.9445*cm),
					  l_SPILowVetoBeTile2, SPILowVetoBeTile2Name,
					  l_SPILowVETO, false, 0);
  
  p_SPILowVetoBeTile2 = new G4PVPlacement(RotateVeto2B, G4ThreeVector(23.6583*cm,
								     9.0226*cm,12.9445*cm),
					  l_SPILowVetoBeTile2, SPILowVetoBeTile2Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile2 = new G4PVPlacement(RotateVeto2C, G4ThreeVector(19.643*cm,
								     -15.9774*cm,12.9445*cm),
					  l_SPILowVetoBeTile2, SPILowVetoBeTile2Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile2 = new G4PVPlacement(RotateVeto2D, G4ThreeVector(-4.0153*cm,
								     -25.0*cm,12.9445*cm),
					  l_SPILowVetoBeTile2, SPILowVetoBeTile2Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile2 = new G4PVPlacement(RotateVeto2E, G4ThreeVector(-23.6583*cm,
								     -9.0226*cm,12.9445*cm),
					  l_SPILowVetoBeTile2, SPILowVetoBeTile2Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile2 = new G4PVPlacement(RotateVeto2F, G4ThreeVector(-19.643*cm,
								     15.9774*cm,12.9445*cm),
					  l_SPILowVetoBeTile2, SPILowVetoBeTile2Name,
					  l_SPILowVETO, false, 5); 


  const G4String SPILowVetoBeTile3Name = "SPILowVetoBeTile3"; // SVBG
  G4Trap* s_SPILowVetoBeTile3 = new G4Trap(SPILowVetoBeTile3Name,
					   0.38835*cm,
					   29.7*deg,106.1*deg,
					   2.5*cm,7.665*cm,6.2216*cm,-16.1*deg,
					   2.11165*cm,7.4408*cm,6.2216*cm,-16.1*deg );
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile3 = new G4LogicalVolume(s_SPILowVetoBeTile3,
							  Material,
							  SPILowVetoBeTile3Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile3 ;
  
  G4RotationMatrix* RotateVeto3A = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto3B = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto3C = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto3D = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto3E = new G4RotationMatrix ;
  G4RotationMatrix* RotateVeto3F = new G4RotationMatrix ;
  
  RotateVeto3A->rotateZ(0*deg);
  RotateVeto3B->rotateZ(60.*deg); 
  RotateVeto3C->rotateZ(120.*deg);
  RotateVeto3D->rotateZ(180.*deg);
  RotateVeto3E->rotateZ(240.*deg);
  RotateVeto3F->rotateZ(300.*deg);

  p_SPILowVetoBeTile3 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(3.9593*cm,
								      25.1942*cm,22.6328*cm),
					  l_SPILowVetoBeTile3, SPILowVetoBeTile3Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile3 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(23.7595*cm,
								      9.1457*cm,22.6328*cm),
					  l_SPILowVetoBeTile3, SPILowVetoBeTile3Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile3 = new G4PVPlacement(RotateVeto3C, G4ThreeVector(19.8002*cm,
								      -16.0035*cm,22.6328*cm),
					  l_SPILowVetoBeTile3, SPILowVetoBeTile3Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile3 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(-3.9593*cm,
								      -25.1942*cm,22.6328*cm),
					  l_SPILowVetoBeTile3, SPILowVetoBeTile3Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile3 = new G4PVPlacement(RotateVeto3E, G4ThreeVector(-23.7595*cm,
								      -9.1457*cm,22.6328*cm),
					  l_SPILowVetoBeTile3, SPILowVetoBeTile3Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile3 = new G4PVPlacement(RotateVeto3F, G4ThreeVector(-19.8002*cm,
								      16.0035*cm,22.6328*cm),
					  l_SPILowVetoBeTile3, SPILowVetoBeTile3Name,
					  l_SPILowVETO, false, 5); 


  const G4String SPILowVetoBeTile4Name = "SPILowVetoBeTile4"; // SVBH
  // this is not the same as G3 and we've actually left out a bit of BGO
  G4Trap* s_SPILowVetoBeTile4 = new G4Trap(SPILowVetoBeTile4Name,
					   1.612*cm,
					   26.565*deg,180.*deg,
					   2.112*cm,5.25*cm,5.25*cm,0.*deg,
					   0.5*cm,5.25*cm,5.25*cm,0.*deg);

  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile4 = new G4LogicalVolume(s_SPILowVetoBeTile4,
							  Material,
							  SPILowVetoBeTile4Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile4 ;
 
  p_SPILowVetoBeTile4 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(3.1126*cm,
								      26.1942*cm,24.6328*cm),
					  l_SPILowVetoBeTile4, SPILowVetoBeTile4Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile4 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(24.2411*cm,
								      10.4015*cm,24.6328*cm),
					  l_SPILowVetoBeTile4, SPILowVetoBeTile4Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile4 = new G4PVPlacement(RotateVeto3C, G4ThreeVector(21.1285*cm,
								      -15.7927*cm,24.6328*cm),
					  l_SPILowVetoBeTile4, SPILowVetoBeTile4Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile4 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(-3.1126*cm,
								      -26.1942*cm,24.6328*cm),
					  l_SPILowVetoBeTile4, SPILowVetoBeTile4Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile4 = new G4PVPlacement(RotateVeto3E, G4ThreeVector(-24.2411*cm,
								      -10.4015*cm,24.6328*cm),
					  l_SPILowVetoBeTile4, SPILowVetoBeTile4Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile4 = new G4PVPlacement(RotateVeto3F, G4ThreeVector(-21.1285*cm,
								      15.7929*cm,24.6328*cm),
					  l_SPILowVetoBeTile4, SPILowVetoBeTile4Name,
					  l_SPILowVETO, false, 5); 


  const G4String SPILowVetoBeTile5Name = "SPILowVetoBeTile5"; // SVBI
  G4Trap* s_SPILowVetoBeTile5 = new G4Trap(SPILowVetoBeTile5Name,
					   2.0*cm,
					   27.49*deg,73.9*deg,
					   2.5*cm,7.78*cm,6.336*cm,16.11*deg,
					   0.5*cm,6.6248*cm,6.336*cm,16.11*deg);

  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile5 = new G4LogicalVolume(s_SPILowVetoBeTile5,
							  Material,
							  SPILowVetoBeTile5Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile5 ;
 
  p_SPILowVetoBeTile5 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(-10.0972*cm,
								      26.0*cm,24.2445*cm),
					  l_SPILowVetoBeTile5, SPILowVetoBeTile5Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile5 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(17.4681*cm,
								      21.7444*cm,24.2445*cm),
					  l_SPILowVetoBeTile5, SPILowVetoBeTile5Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile5 = new G4PVPlacement(RotateVeto3C, G4ThreeVector(27.5653*cm,
								      -4.2556*cm,24.2445*cm),
					  l_SPILowVetoBeTile5, SPILowVetoBeTile5Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile5 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(10.0972*cm,
								      -26.0*cm,24.2445*cm),
					  l_SPILowVetoBeTile5, SPILowVetoBeTile5Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile5 = new G4PVPlacement(RotateVeto3E, G4ThreeVector(-17.4681*cm,
								      -21.7444*cm,24.2445*cm),
					  l_SPILowVetoBeTile5, SPILowVetoBeTile5Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile5 = new G4PVPlacement(RotateVeto3F, G4ThreeVector(-27.5653*cm,
								      4.2556*cm,24.2445*cm),
					  l_SPILowVetoBeTile5, SPILowVetoBeTile5Name,
					  l_SPILowVETO, false, 5); 


  const G4String SPILowVetoBeTile6Name = "SPILowVetoBeTile6"; // SVBJ
  G4Trap* s_SPILowVetoBeTile6 = new G4Trap(SPILowVetoBeTile6Name,
					   8.05*cm,
					   0.*deg,0.*deg,
					   2.5*cm,7.78*cm,6.336*cm,16.11*deg,
					   2.5*cm,7.78*cm,6.336*cm,16.11*deg);

  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile6 = new G4LogicalVolume(s_SPILowVetoBeTile6,
							  Material,
							  SPILowVetoBeTile6Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile6 ;
 
  p_SPILowVetoBeTile6 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(-10.386*cm,
								      25.0*cm,14.1945*cm),
					  l_SPILowVetoBeTile6, SPILowVetoBeTile6Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile6 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(16.4576*cm,
								      21.4945*cm,14.1945*cm),
					  l_SPILowVetoBeTile6, SPILowVetoBeTile6Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile6 = new G4PVPlacement(RotateVeto3C, G4ThreeVector(26.8436*cm,
								      -3.5055*cm,14.1945*cm),
					  l_SPILowVetoBeTile6, SPILowVetoBeTile6Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile6 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(10.386*cm,
								      -25.0*cm,14.1945*cm),
					  l_SPILowVetoBeTile6, SPILowVetoBeTile6Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile6 = new G4PVPlacement(RotateVeto3E, G4ThreeVector(-16.4576*cm,
								      -21.4945*cm,14.1945*cm),
					  l_SPILowVetoBeTile6, SPILowVetoBeTile6Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile6 = new G4PVPlacement(RotateVeto3F, G4ThreeVector(-26.8436*cm,
								      3.5055*cm,14.1945*cm),
					  l_SPILowVetoBeTile6, SPILowVetoBeTile6Name,
					  l_SPILowVETO, false, 5); 
   

  const G4String SPILowVetoBeTile7Name = "SPILowVetoBeTile7"; // SVBK
  // this is not the same as G3 and we've actually left out a bit of BGO
  G4Trap* s_SPILowVetoBeTile7 = new G4Trap(SPILowVetoBeTile7Name,
					   2.5*cm,
					   26.565*deg,180.0*deg,
					   0.01*mm,4.8952*cm,4.8952*cm,0.0*deg,
					   2.5*cm,4.8952*cm,4.8952*cm,0.0*deg); 

  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile7 = new G4LogicalVolume(s_SPILowVetoBeTile7,
							     Material,
				 			     SPILowVetoBeTile7Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile7 ;
  
  p_SPILowVetoBeTile7 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(-9.3046*cm,
								      23.75*cm,3.6445*cm),
					  l_SPILowVetoBeTile7, SPILowVetoBeTile7Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile7 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(15.9158*cm,
								      19.933*cm,3.6445*cm),
					  l_SPILowVetoBeTile7, SPILowVetoBeTile7Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile7 = new G4PVPlacement(RotateVeto3C, G4ThreeVector(25.2204*cm,
								      -3.817*cm,3.6445*cm),
					  l_SPILowVetoBeTile7, SPILowVetoBeTile7Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile7 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(9.3046*cm,
								      -23.75*cm,3.6445*cm),
					  l_SPILowVetoBeTile7, SPILowVetoBeTile7Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile7 = new G4PVPlacement(RotateVeto3E, G4ThreeVector(-15.9158*cm,
								      -19.933*cm,3.6445*cm),
					  l_SPILowVetoBeTile7, SPILowVetoBeTile7Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile7 = new G4PVPlacement(RotateVeto3F, G4ThreeVector(-25.2204*cm,
								      3.817*cm,3.6445*cm),
					  l_SPILowVetoBeTile7, SPILowVetoBeTile7Name,
					  l_SPILowVETO, false, 5); 


  const G4String SPILowVetoBeTile8Name = "SPILowVetoBeTile8"; // SVBL
  G4Trap* s_SPILowVetoBeTile8 = new G4Trap(SPILowVetoBeTile8Name,
					   2.5*cm,
					   23.321*deg,253.915*deg,
					   4.5*cm,8.096*cm,6.26*cm,-11.53*deg,
					   4.5*cm,7.499*cm,5.6626*cm,-11.53*deg); 

  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile8 = new G4LogicalVolume(s_SPILowVetoBeTile8,
							     Material,
				 			     SPILowVetoBeTile8Name); 
  G4RotationMatrix* RotateTileA = new G4RotationMatrix ;
  G4RotationMatrix* RotateTileB = new G4RotationMatrix ;
  G4RotationMatrix* RotateTileC = new G4RotationMatrix ;
  G4RotationMatrix* RotateTileD = new G4RotationMatrix ;
  G4RotationMatrix* RotateTileE = new G4RotationMatrix ;
  G4RotationMatrix* RotateTileF = new G4RotationMatrix ;
  
  RotateTileA->rotateZ(-180.0*deg);
  RotateTileB->rotateZ(-120.0*deg);
  RotateTileC->rotateZ(-60.0*deg);
  RotateTileD->rotateZ(-0.0*deg); 
  RotateTileE->rotateZ(-300.0*deg);
  RotateTileF->rotateZ(-240.0*deg);
  
  RotateTileA->rotateX(45.0*deg); 
  RotateTileB->rotateX(45.0*deg);
  RotateTileC->rotateX(45.0*deg);
  RotateTileD->rotateX(45.0*deg);
  RotateTileE->rotateX(45.0*deg);
  RotateTileF->rotateX(45.0*deg);
 
  G4VPhysicalVolume* p_SPILowVetoBeTile8 ;
  
  p_SPILowVetoBeTile8 = new G4PVPlacement(RotateTileA, G4ThreeVector(-6.9794*cm,
								      24.202*cm,-9.2205*cm),
					  l_SPILowVetoBeTile8, SPILowVetoBeTile8Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile8 = new G4PVPlacement(RotateTileB, G4ThreeVector(17.47*cm,
								      18.146*cm,-9.2205*cm),
					  l_SPILowVetoBeTile8, SPILowVetoBeTile8Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile8 = new G4PVPlacement(RotateTileC, G4ThreeVector(24.449*cm,
								      -6.056*cm,-9.2205*cm),
					  l_SPILowVetoBeTile8, SPILowVetoBeTile8Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile8 = new G4PVPlacement(RotateTileD, G4ThreeVector(6.9794*cm,
								      -24.202*cm,-9.2205*cm),
					  l_SPILowVetoBeTile8, SPILowVetoBeTile8Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile8 = new G4PVPlacement(RotateTileE, G4ThreeVector(-17.47*cm,
								      -18.146*cm,-9.2205*cm),
					  l_SPILowVetoBeTile8, SPILowVetoBeTile8Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile8 = new G4PVPlacement(RotateTileF, G4ThreeVector(-24.449*cm,
								      6.056*cm,-9.2205*cm),
					  l_SPILowVetoBeTile8, SPILowVetoBeTile8Name,
					  l_SPILowVETO, false, 5); 


  const G4String SPILowVetoBeTile9Name = "SPILowVetoBeTile9"; // SVBM
  G4Trap* s_SPILowVetoBeTile9 = new G4Trap(SPILowVetoBeTile9Name,
					   2.5*cm,
					   23.321*deg,286.085*deg,
					   4.5*cm,8.096*cm,6.26*cm,11.53*deg,
					   4.5*cm,7.499*cm,5.6626*cm,11.53*deg); 

  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile9 = new G4LogicalVolume(s_SPILowVetoBeTile9,
							     Material,
							     SPILowVetoBeTile9Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile9 ;
  
  p_SPILowVetoBeTile9 = new G4PVPlacement(RotateTileA, G4ThreeVector(6.9794*cm,
								     24.202*cm,-9.2205*cm),
					  l_SPILowVetoBeTile9, SPILowVetoBeTile9Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile9 = new G4PVPlacement(RotateTileB, G4ThreeVector(24.449*cm,
								     6.056*cm,-9.2205*cm),
					  l_SPILowVetoBeTile9, SPILowVetoBeTile9Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile9 = new G4PVPlacement(RotateTileC, G4ThreeVector(17.47*cm,
								     -18.146*cm,-9.2205*cm),
					  l_SPILowVetoBeTile9, SPILowVetoBeTile9Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile9 = new G4PVPlacement(RotateTileD, G4ThreeVector(-6.9794*cm,
								     -24.202*cm,-9.2205*cm),
					  l_SPILowVetoBeTile9, SPILowVetoBeTile9Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile9 = new G4PVPlacement(RotateTileE, G4ThreeVector(-24.449*cm,
								     -6.056*cm,-9.2205*cm),
					  l_SPILowVetoBeTile9, SPILowVetoBeTile9Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile9 = new G4PVPlacement(RotateTileF, G4ThreeVector(-17.47*cm,
								     18.146*cm,-9.2205*cm),
					  l_SPILowVetoBeTile9, SPILowVetoBeTile9Name,
					  l_SPILowVETO, false, 5);


  const G4String SPILowVetoBeTile10Name = "SPILowVetoBeTile10"; // SVBN
  G4Trap* s_SPILowVetoBeTile10 = new G4Trap(SPILowVetoBeTile10Name,
   					    2.5*cm,
   					    35.36*deg,265.174*deg,
   					    3.1315*cm,7.543*cm,7.543*cm,0.*deg,
   					    4.596*cm,7.543*cm,7.543*cm,0.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile10 = new G4LogicalVolume(s_SPILowVetoBeTile10,
							     Material,
							     SPILowVetoBeTile10Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile10 ; 
  
  p_SPILowVetoBeTile10 = new G4PVPlacement(RotateTileA, G4ThreeVector(-7.543*cm,
								      30.268*cm,-3.1545*cm),
					   l_SPILowVetoBeTile10, SPILowVetoBeTile10Name,
					  l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile10 = new G4PVPlacement(RotateTileB, G4ThreeVector(0.5935*cm+21.848*cm,
								      -1.028*cm+22.694*cm,
								      -3.1545*cm),
					  l_SPILowVetoBeTile10, SPILowVetoBeTile10Name,
					  l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile10 = new G4PVPlacement(RotateTileC, G4ThreeVector(-0.5935*cm+30.578*cm,
								      -1.028*cm-7.574*cm,
								      -3.1545*cm),
					  l_SPILowVetoBeTile10, SPILowVetoBeTile10Name,
					  l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile10 = new G4PVPlacement(RotateTileD, G4ThreeVector(7.543*cm,
								      -30.268*cm,-3.1545*cm),
					  l_SPILowVetoBeTile10, SPILowVetoBeTile10Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile10 = new G4PVPlacement(RotateTileE, G4ThreeVector(-0.5935*cm-21.848*cm,
								      1.028*cm-22.694*cm,
								      -3.1545*cm),
					  l_SPILowVetoBeTile10, SPILowVetoBeTile10Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile10 = new G4PVPlacement(RotateTileF, G4ThreeVector(0.5935*cm-30.578*cm,
								      1.028*cm+7.574*cm,
								      -3.1545*cm),
					  l_SPILowVetoBeTile10, SPILowVetoBeTile10Name,
					  l_SPILowVETO, false, 5); 

  
  const G4String SPILowVetoBeTile11Name = "SPILowVetoBeTile11"; // SVBO
  G4Trap* s_SPILowVetoBeTile11 = new G4Trap(SPILowVetoBeTile11Name,
					    2.5*cm,
					    35.36*deg,265.17*deg,
					    3.1315*cm,7.543*cm,7.543*cm,0.*deg,
		 			    4.596*cm,7.543*cm,7.543*cm,0.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile11 = new G4LogicalVolume(s_SPILowVetoBeTile11,
							     Material,
							     SPILowVetoBeTile11Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile11 ; 
  
  p_SPILowVetoBeTile11 = new G4PVPlacement(RotateTileA, G4ThreeVector(7.543*cm,
								      30.268*cm,-3.1545*cm),
					   l_SPILowVetoBeTile11, SPILowVetoBeTile11Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile11 = new G4PVPlacement(RotateTileB, G4ThreeVector(-0.5935*cm+30.578*cm,
								      1.028*cm+7.574*cm,
								      -3.1545*cm),
					   l_SPILowVetoBeTile11, SPILowVetoBeTile11Name,
					   l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile11 = new G4PVPlacement(RotateTileC, G4ThreeVector(0.5935*cm+21.848*cm,
								      1.028*cm-22.694*cm,
								      -3.1545*cm),
					   l_SPILowVetoBeTile11, SPILowVetoBeTile11Name,
					   l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile11 = new G4PVPlacement(RotateTileD, G4ThreeVector(-7.543*cm,
								      -30.268*cm,-3.1545*cm),
					  l_SPILowVetoBeTile11, SPILowVetoBeTile11Name,
					  l_SPILowVETO, false, 3);
  p_SPILowVetoBeTile11 = new G4PVPlacement(RotateTileE, G4ThreeVector(0.5935*cm-30.578*cm,
								      -1.028*cm-7.574*cm,
								      -3.1545*cm),
					  l_SPILowVetoBeTile11, SPILowVetoBeTile11Name,
					  l_SPILowVETO, false, 4);
  p_SPILowVetoBeTile11 = new G4PVPlacement(RotateTileF, G4ThreeVector(-0.5935*cm-21.848*cm,
								      -1.028*cm+22.694*cm,
								      -3.1545*cm),
					  l_SPILowVetoBeTile11, SPILowVetoBeTile11Name,
					  l_SPILowVETO, false, 5); 
					  
  // There is a significant piece missing at the corner of the veto here because 
  // fucking GEANT4 is too shit to be able to use the geometrical routines that
  // used to fucking work in GEANT3, the useless twat.
  

  const G4String SPILowVetoBeTile12Name = "SPILowVetoBeTile12"; // SVBP
  G4Trap* s_SPILowVetoBeTile12 = new G4Trap(SPILowVetoBeTile12Name,
					    2.5*cm,
					    0.0*deg,0.0*deg,
					    5.3925*cm,6.2267*cm,6.2267*cm,-30.*deg,
		 			    5.3925*cm,6.2267*cm,6.2267*cm,-30.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile12 = new G4LogicalVolume(s_SPILowVetoBeTile12,
							     Material,
							     SPILowVetoBeTile12Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile12 ; 
  
  p_SPILowVetoBeTile12 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(-6.3375*cm,
								      0.0*cm,-12.4025*cm),
					   l_SPILowVetoBeTile12, SPILowVetoBeTile12Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile12 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(6.3375*cm,
								      0.0*cm,-12.4025*cm),
					   l_SPILowVetoBeTile12, SPILowVetoBeTile12Name,
					   l_SPILowVETO, false, 1);


  const G4String SPILowVetoBeTile13Name = "SPILowVetoBeTile13"; // SVBQ
  G4Trap* s_SPILowVetoBeTile13 = new G4Trap(SPILowVetoBeTile13Name,
					    2.5*cm,
					    13.449*deg,0.0*deg,
					    5.3925*cm,6.2267*cm,6.2267*cm,30.*deg,
		 			    5.3925*cm,5.031*cm,5.031*cm,30.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile13 = new G4LogicalVolume(s_SPILowVetoBeTile13,
							     Material,
							     SPILowVetoBeTile13Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile13 ; 
  
  p_SPILowVetoBeTile13 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(-15.246*cm,
								       5.4884*cm,-12.4025*cm),
					   l_SPILowVetoBeTile13, SPILowVetoBeTile13Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile13 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(15.246*cm,
								       -5.4884*cm,-12.4025*cm),
					   l_SPILowVetoBeTile13, SPILowVetoBeTile13Name,
					   l_SPILowVETO, false, 1);


  const G4String SPILowVetoBeTile14Name = "SPILowVetoBeTile14"; // SVBR
  G4Trap* s_SPILowVetoBeTile14 = new G4Trap(SPILowVetoBeTile14Name,
					    2.5*cm,
					    13.449*deg,0.0*deg,
					    5.3925*cm,6.2267*cm,6.2267*cm,-30.*deg,
		 			    5.3925*cm,5.031*cm,5.031*cm,-30.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile14 = new G4LogicalVolume(s_SPILowVetoBeTile14,
							     Material,
							     SPILowVetoBeTile14Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile14 ; 
  
  p_SPILowVetoBeTile14 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(-15.246*cm,
								       -5.4884*cm,-12.4025*cm),
					   l_SPILowVetoBeTile14, SPILowVetoBeTile14Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile14 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(15.246*cm,
								       5.4884*cm,-12.4025*cm),
					   l_SPILowVetoBeTile14, SPILowVetoBeTile14Name,
					   l_SPILowVETO, false, 1);


  const G4String SPILowVetoBeTile15Name = "SPILowVetoBeTile15"; // SVBS
  G4Trap* s_SPILowVetoBeTile15 = new G4Trap(SPILowVetoBeTile15Name,
					    2.5*cm,
					    13.449*deg,300.0*deg,
					    5.3925*cm,6.2267*cm,6.2267*cm,30.*deg,
		 			    4.357*cm,5.031*cm,5.031*cm,30.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile15 = new G4LogicalVolume(s_SPILowVetoBeTile15,
							     Material,
							     SPILowVetoBeTile15Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile15 ; 
  
  p_SPILowVetoBeTile15 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(-9.2074*cm,
								       15.9476*cm,-12.4025*cm),
					   l_SPILowVetoBeTile15, SPILowVetoBeTile15Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile15 = new G4PVPlacement(RotateVeto3B, G4ThreeVector(9.2074*cm,
								       15.9476*cm,-12.4025*cm),
					   l_SPILowVetoBeTile15, SPILowVetoBeTile15Name,
					   l_SPILowVETO, false, 1);
  p_SPILowVetoBeTile15 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(9.2074*cm,
								       -15.9476*cm,-12.4025*cm),
					   l_SPILowVetoBeTile15, SPILowVetoBeTile15Name,
					   l_SPILowVETO, false, 2);
  p_SPILowVetoBeTile15 = new G4PVPlacement(RotateVeto3E, G4ThreeVector(-9.2074*cm,
								       -15.9476*cm,-12.4025*cm),
					   l_SPILowVetoBeTile15, SPILowVetoBeTile15Name,
					   l_SPILowVETO, false, 3);


  const G4String SPILowVetoBeTile16Name = "SPILowVetoBeTile16"; // SVBT
  G4Trap* s_SPILowVetoBeTile16 = new G4Trap(SPILowVetoBeTile16Name,
					    2.5*cm,
					    0.0*deg,0.0*deg,
					    5.3925*cm,6.2267*cm,0.00001*cm,0.*deg,
		 			    5.3925*cm,6.2267*cm,0.00001*cm,0.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile16 = new G4LogicalVolume(s_SPILowVetoBeTile16,
							     Material,
							     SPILowVetoBeTile16Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile16 ; 
  
  p_SPILowVetoBeTile16 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(0.0*cm,
								       5.4884*cm,-12.4025*cm),
					   l_SPILowVetoBeTile16, SPILowVetoBeTile16Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile16 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(0.0*cm,
								       -5.4884*cm,-12.4025*cm),
					   l_SPILowVetoBeTile16, SPILowVetoBeTile16Name,
					   l_SPILowVETO, false, 1);


  const G4String SPILowVetoBeTile17Name = "SPILowVetoBeTile17"; // SVBU
  G4Trap* s_SPILowVetoBeTile17 = new G4Trap(SPILowVetoBeTile17Name,
					    2.5*cm,
					    0.0*deg,0.0*deg,
					    4.405*cm,6.2267*cm,1.1403*cm,0.*deg,
		 			    4.405*cm,6.2267*cm,1.1403*cm,0.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile17 = new G4LogicalVolume(s_SPILowVetoBeTile17,
							     Material,
							     SPILowVetoBeTile17Name); 
  G4VPhysicalVolume* p_SPILowVetoBeTile17 ; 
  
  p_SPILowVetoBeTile17 = new G4PVPlacement(RotateVeto3A, G4ThreeVector(0.0*cm,
								       15.3819*cm,-12.4025*cm),
					   l_SPILowVetoBeTile17, SPILowVetoBeTile17Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile17 = new G4PVPlacement(RotateVeto3D, G4ThreeVector(0.0*cm,
								       -15.3819*cm,-12.4025*cm),
					   l_SPILowVetoBeTile17, SPILowVetoBeTile17Name,
					   l_SPILowVETO, false, 1);


  const G4String SPILowVetoBeTile18Name = "SPILowVetoBeTile18"; // SVBV
  G4Trap* s_SPILowVetoBeTile18 = new G4Trap(SPILowVetoBeTile18Name,
					    0.9875*cm,
					    50.36*deg,270.0*deg,
					    2.5*cm,1.1403*cm,1.1403*cm,0.*deg,
					    0.116*cm,0.00001*cm,0.00001*cm,0.*deg); 
  
  Material =  PIMPSelectMaterial("BGO", Materials);
  G4LogicalVolume* l_SPILowVetoBeTile18 = new G4LogicalVolume(s_SPILowVetoBeTile18,
							     Material,
							     SPILowVetoBeTile18Name); 
  G4RotationMatrix* RotateTile18A = new G4RotationMatrix ;
  G4RotationMatrix* RotateTile18B = new G4RotationMatrix ;
  
  RotateTile18A->rotateZ(180.0*deg);
  RotateTile18A->rotateX(-90.0*deg);
  RotateTile18B->rotateX(-90.0*deg);
  G4VPhysicalVolume* p_SPILowVetoBeTile18 ; 
  
  p_SPILowVetoBeTile18 = new G4PVPlacement(RotateTile18A, G4ThreeVector(0.0*cm,
									20.7744*cm,-13.5945*cm),
					   l_SPILowVetoBeTile18, SPILowVetoBeTile18Name,
					   l_SPILowVETO, false, 0);
  p_SPILowVetoBeTile18 = new G4PVPlacement(RotateTile18B, G4ThreeVector(0.0*cm,
									-20.7744*cm,-13.5945*cm),
					   l_SPILowVetoBeTile18, SPILowVetoBeTile18Name,
					   l_SPILowVETO, false, 1);


  //----------------------------------------------------------------------------------------------------//
  //					The PMT's around the veto					//
  //----------------------------------------------------------------------------------------------------//
  const G4String SPILowVetoPMTName = "SPILowVetoPMT"; // SPMT
  G4Tubs* s_SPILowVetoPMT = new G4Tubs(SPILowVetoPMTName,
				       0.*cm,2.0*cm,2.0*cm, 
				       0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPILowVetoPMT = new G4LogicalVolume(s_SPILowVetoPMT,
							 Material,
							 SPILowVetoPMTName,
							 0,0,0,
							 false);
  
  const G4String SPILowVetoSmallElecName = "SPILowVetoSmallElec"; // SPIE
  G4Box* s_SPILowVetoSmallElec = new G4Box(SPILowVetoSmallElecName,
					   4.0*cm, 2.0*cm, 3.0*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials);
  G4LogicalVolume* l_SPILowVetoSmallElec = new G4LogicalVolume(s_SPILowVetoSmallElec,
							       Material,
							       SPILowVetoSmallElecName,
							       0,0,0,
							       false);

  G4RotationMatrix* NoRotation = new G4RotationMatrix ;
  G4RotationMatrix* Rotate608 = RotateVetoA ;
  G4RotationMatrix* Rotate609 = RotateVetoB ;
  G4RotationMatrix* Rotate610 = RotateVetoC ;
  G4RotationMatrix* Rotate611 = RotateVetoD ;
  G4RotationMatrix* Rotate612 = RotateVetoE ;
  G4RotationMatrix* Rotate613 = RotateVetoF ;
  G4RotationMatrix* Rotate646 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate647 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate648 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate649 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate650 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate651 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate614 = RotateVeto2A ;
  G4RotationMatrix* Rotate615 = RotateVeto2B ;
  G4RotationMatrix* Rotate616 = RotateVeto2C ;
  G4RotationMatrix* Rotate617 = RotateVeto2D;
  G4RotationMatrix* Rotate618 = RotateVeto2E ;
  G4RotationMatrix* Rotate619 = RotateVeto2F ;
  G4RotationMatrix* Rotate652 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate653 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate654 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate655 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate656 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate657 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate658 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate659 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate660 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate661 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate662 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate663 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate664 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate665 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate666 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate667 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate668 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate669 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate670 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate671 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate672 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate673 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate674 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate675 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate676 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate677 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate678 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate679 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate680 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate681 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate682 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate683 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate684 = new G4RotationMatrix ;
  G4RotationMatrix* Rotate685 = new G4RotationMatrix ;
 
  Rotate646->rotateX(-62.5*deg);
  Rotate647->rotateX(-62.5*deg);
  Rotate648->rotateX(-62.5*deg);
  Rotate649->rotateX(-62.5*deg);
  Rotate650->rotateX(-62.5*deg);
  Rotate651->rotateX(-62.5*deg); 

  G4double Rotz = 0. ;
  Rotate652->rotateX(-34.78*deg); Rotate652->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate653->rotateX(-34.78*deg); Rotate653->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate654->rotateX(-34.78*deg); Rotate654->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate655->rotateX(-34.78*deg); Rotate655->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate656->rotateX(-34.78*deg); Rotate656->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate657->rotateX(-34.78*deg); Rotate657->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate658->rotateX(-34.78*deg); Rotate658->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate659->rotateX(-34.78*deg); Rotate659->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate660->rotateX(-34.78*deg); Rotate660->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate661->rotateX(-34.78*deg); Rotate661->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate662->rotateX(-34.78*deg); Rotate662->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate663->rotateX(-34.78*deg); Rotate663->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate664->rotateX(-34.78*deg); Rotate664->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate665->rotateX(-34.78*deg); Rotate665->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate666->rotateX(-34.78*deg); Rotate666->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotate667->rotateX(-34.78*deg); Rotate667->rotateZ(Rotz*deg); Rotz = Rotz + 22.5 ;
  Rotz = -6.;
  Rotate668->rotateX(-34.78*deg); Rotate668->rotateZ(Rotz*deg); Rotz = -354 ;
  Rotate669->rotateX(-34.78*deg); Rotate669->rotateZ(Rotz*deg); Rotz = Rotz + 48 ;
  Rotate670->rotateX(-34.78*deg); Rotate670->rotateZ(Rotz*deg); Rotz = Rotz + 12 ; 
  Rotate671->rotateX(-34.78*deg); Rotate671->rotateZ(Rotz*deg); Rotz = Rotz + 48 ; 
  Rotate672->rotateX(-34.78*deg); Rotate672->rotateZ(Rotz*deg); Rotz = Rotz + 12 ;   
  Rotate673->rotateX(-34.78*deg); Rotate673->rotateZ(Rotz*deg); Rotz = Rotz + 48 ; 
  Rotate674->rotateX(-34.78*deg); Rotate674->rotateZ(Rotz*deg); Rotz = Rotz + 12 ;  
  Rotate675->rotateX(-34.78*deg); Rotate675->rotateZ(Rotz*deg); Rotz = Rotz + 48 ;  
  Rotate676->rotateX(-34.78*deg); Rotate676->rotateZ(Rotz*deg); Rotz = Rotz + 12 ;   
  Rotate677->rotateX(-34.78*deg); Rotate677->rotateZ(Rotz*deg); Rotz = Rotz + 48 ; 
  Rotate678->rotateX(-34.78*deg); Rotate678->rotateZ(Rotz*deg); Rotz = Rotz + 12 ;   
  Rotate679->rotateX(-34.78*deg); Rotate679->rotateZ(Rotz*deg); 
  Rotate680->rotateX(-34.78*deg); Rotate680->rotateZ(0.*deg); 
  Rotate681->rotateZ(-300.*deg); Rotate681->rotateX(-34.78*deg); 
  Rotate682->rotateZ(-240.*deg); Rotate682->rotateX(-34.78*deg);
  Rotate683->rotateZ(-180.*deg); Rotate683->rotateX(-34.78*deg);
  Rotate684->rotateZ(-120.*deg); Rotate684->rotateX(-34.78*deg);
  Rotate685->rotateZ(-60.*deg); Rotate685->rotateX(-34.78*deg);

  G4double ZPOS ;
  // Now place a shit load of them ...
  
  ZPOS = 33.3975 ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,55,10.2113,26.2663,ZPOS, Rotate608) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,57,27.8528,4.2899,ZPOS, Rotate609) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,59,17.6415,-21.9764,ZPOS, Rotate610) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,61,-10.2113,-26.2663,ZPOS, Rotate611) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,63,-27.8528,-4.2899,ZPOS, Rotate612) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,65,-17.6415,21.9764,ZPOS, Rotate613) ;
  
  ZPOS = 28.9975 ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,56,10.2113,28.2663,ZPOS, Rotate608) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,58,29.585,5.2899,ZPOS, Rotate609) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,60,19.3737,-22.9764,ZPOS, Rotate610) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,62,-10.2113,-28.2663,ZPOS, Rotate611) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,64,-29.585,-5.2899,ZPOS, Rotate612) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,66,-19.3737,22.9764,ZPOS, Rotate613) ;
  
  ZPOS = 32.1975 ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,28,1.7113,26.2663,ZPOS, Rotate646) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,29,23.6028,11.6512,ZPOS, Rotate647) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,30,21.8915,-14.6151,ZPOS, Rotate648) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,31,-1.7113,-26.2663,ZPOS, Rotate649) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,32,-23.6028,-11.6512,ZPOS, Rotate650) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,33,-21.8915,14.6151,ZPOS, Rotate651) ;

  
  //    side part.
  ZPOS = 21.9445 ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,67,1.0153,30.0,ZPOS, Rotate614) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,68,7.0153,30.0,ZPOS, Rotate614) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,69,26.4883,14.1207,ZPOS, Rotate615) ;  
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,70,29.4883,8.9245,ZPOS, Rotate615) ;  
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,71,25.473,-15.8793,ZPOS, Rotate616) ;  
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,72,22.473,-21.0755,ZPOS, Rotate616) ;  
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,73,-1.0153,-30.0,ZPOS, Rotate617) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,74,-7.0153,-30.0,ZPOS, Rotate617) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,75,-26.4883,-14.1207,ZPOS, Rotate618) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,76,-29.4883,-8.9245,ZPOS, Rotate618) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,77,-25.473,15.8793,ZPOS, Rotate619) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,78,-22.473,21.0755,ZPOS, Rotate619) ;

  
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,79,-7.386,30.0,ZPOS, Rotate614) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,80,-13.386,30.0,ZPOS, Rotate614) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,81,19.2876,26.5926,ZPOS, Rotate615) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,82,22.2876,21.3964,ZPOS, Rotate615) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,83,32.6736,-3.4074,ZPOS, Rotate616) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,84,29.6736,-8.6036,ZPOS, Rotate616) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,85,7.386,-30.0,ZPOS, Rotate617) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,86,13.386,-30.0,ZPOS, Rotate617) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,87,-19.2876,-26.5926,ZPOS, Rotate618) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,88,-22.2876,-21.3964,ZPOS, Rotate618) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,89,-32.6736,3.4074,ZPOS, Rotate619) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,90,-29.6736,8.6036,ZPOS, Rotate619) ;
  
  
  ZPOS = 15.9445 ;
 
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,34,4.0153,31.0,ZPOS, Rotate614) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,35,29.2203,11.6566,ZPOS, Rotate615) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,36,25.205,-18.6114,ZPOS, Rotate616) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,37,-4.0153,-31.0,ZPOS, Rotate617) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,38,-29.2203,-11.6566,ZPOS, Rotate618) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,39,-25.205,18.6114,ZPOS, Rotate619) ;
  
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,40,-10.386,31.0,ZPOS, Rotate614) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,41,21.6538,24.4945,ZPOS, Rotate615) ; 
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,42,32.0398,-6.5055,ZPOS, Rotate616) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,43,10.386,-31.0,ZPOS, Rotate617) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,44,-21.6538,-24.4945,ZPOS, Rotate618) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,45,-32.0398,6.5055,ZPOS, Rotate619) ;  
   
  
  ZPOS = -33.18 ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,46,0.,41.2939,ZPOS, Rotate652) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,47,15.8025,38.1506,ZPOS, Rotate653) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,48,29.1992,29.1992,ZPOS, Rotate654) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,49,37.5416,17.2032,ZPOS, Rotate655) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,50,41.2939,0.,ZPOS, Rotate656) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,51,37.5416,-17.2032,ZPOS, Rotate657) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,52,29.1992,-29.1992,ZPOS, Rotate658) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,53,15.8025,-38.1506,ZPOS, Rotate659) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,54,0.,-41.2939,ZPOS, Rotate660) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,55,-15.8025,-38.1506,ZPOS, Rotate661) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,56,-29.1992,-29.1992,ZPOS, Rotate662) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,57,-37.5416,-17.2032,ZPOS, Rotate663) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,58,-41.2939,0.,ZPOS, Rotate664) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,59,-37.5416,17.2032,ZPOS, Rotate665) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,60,-29.1992,29.1992,ZPOS, Rotate666) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,61,-15.8025,38.1506,ZPOS, Rotate667) ;
  
    
    ZPOS = -27.3722 ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,62,-4.5739,43.5182,ZPOS, Rotate668) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,63,4.5739,43.5182,ZPOS, Rotate669) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,64,35.4009,25.7202,ZPOS, Rotate670) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,65,39.9748,17.7979,ZPOS, Rotate671) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,66,39.9748,-17.7979,ZPOS, Rotate672) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,67,35.4009,-25.7202,ZPOS, Rotate673) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,68,4.5739,-43.5182,ZPOS, Rotate674) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,69,-4.5739,-43.5182,ZPOS, Rotate675) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,70,-35.4009,-25.7202,ZPOS, Rotate676) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,71,-39.9748,-17.7979,ZPOS, Rotate677) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,72,-39.9748,17.7979,ZPOS, Rotate678) ;
  PlaceElec(l_SPILowVetoSmallElec, l_SPILowVETO,73,-35.4009,25.7202,ZPOS, Rotate679) ;
  

    ZPOS = -18.1679 ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,91,-6.5451,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,92,6.5451,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,93,-1.5725,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,94,1.5725,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,95,29.9446,24.846,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,96,34.456,18.0774,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,97,32.8834,20.801,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,98,36.4896,13.5096,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,99,36.4896,-13.5096,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,100,32.8834,-20.801,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,101,34.456,-18.0774,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,102,29.9446,-24.846,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,103,1.5725,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,104,-1.5725,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,105,6.5451,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,106,-6.5451,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,107,-29.9446,-24.846,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,108,-34.456,-18.0774,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,109,-32.8834,-20.801,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,110,-36.4896,-13.5096,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,111,-36.4896,13.5096,ZPOS, Rotate685) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,112,-32.8834,20.801,ZPOS, Rotate685) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,113,-34.456,18.0774,ZPOS, Rotate685) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,114,-29.9446,24.846,ZPOS, Rotate685) ;
  
  
    ZPOS = -24.1679 ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,115,-6.5451,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,116,6.5451,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,117,-1.5725,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,118,1.5725,38.3558,ZPOS, Rotate680) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,119,29.9446,24.846,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,120,34.456,18.0774,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,121,32.8834,20.801,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,122,36.4896,13.5096,ZPOS, Rotate681) ; 
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,123,36.4896,-13.5096,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,124,32.8834,-20.801,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,125,34.456,-18.0774,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,126,29.9446,-24.846,ZPOS, Rotate682) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,127,1.5725,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,128,-1.5725,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,129,6.5451,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,130,-6.5451,-38.3558,ZPOS, Rotate683) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,131,-29.9446,-24.846,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,132,-34.456,-18.0774,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,133,-32.8834,-20.801,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,134,-36.4896,-13.5096,ZPOS, Rotate684) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,135,-36.4896,13.5096,ZPOS, Rotate685) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,136,-32.8834,20.801,ZPOS, Rotate685) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,137,-34.456,18.0774,ZPOS, Rotate685) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO,138,-29.9446,24.846,ZPOS, Rotate685) ;
  
    // Not my words ...
    //      Now try to put about 24 PMT's in the gap at the top of SBCM.
	  //     again guesswork.

  ZPOS=-20.0555 ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 139, -17.0,4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 140, -17.0,-4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 141, -12.0,12.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 142, -12.0,4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 143, -12.0,-4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 144, -12.0,-12.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 145, -6.0,10.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 146, -6.0,2.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 147, -6.0,-6.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 148, -6.0,-14.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 149, 0.0,14.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 150, 0.0,6.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 151, 0.0,-2.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 152, 0.0,-10.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 153, 6.0,10.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 154, 6.0,2.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 155, 6.0,-6.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 156, 6.0,-14.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 157, 12.0,12.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 158, 12.0,4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 159, 12.0,-4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 160, 12.0,-12.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 161, 17.0,4.0,ZPOS, NoRotation) ;
  PlacePMT(l_SPILowVetoPMT, l_SPILowVETO, 162, 17.0,-4.0,ZPOS, NoRotation) ;


  //----------------------------------------------------------------------------------------------------//
  //					The SPIDetectorUnit						//
  //----------------------------------------------------------------------------------------------------//
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
  //			WARNING! The "SPIDetMothCone" mother volume was remove				//
  //			because it overwrited the entire precedent LowVeto geometry			//
  //			so the LowVeto didn't work............	(M. Chauvin 01/2012)			//
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //

  // Mother volume for the detector system
  const G4String SPIDetectorUnitName = "SPIDetectorUnit"; // SDET
  const G4double DetZ[2] = {-2.224*cm,24.95*cm} ;//{-2.224*cm,23.75*cm} +1.2*cm for the "nipple" (M. Chauvin 13/03/2013)
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
							   l_SPILowVETO,
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
      
  // Alignment structure "nipple" on the cryostat top - 13/03/2013 M.Chauvin from top to bottom
  // !  Add indentations in cryostat top for nipple -->
  const G4String SPIDetN1Name = "SPIDetN1"; // SMN1 & SMN2
  const G4double zPlaneN1[4] = {0.*cm,0.2*cm,0.2*cm,0.25*cm};
  const G4double rInnerN1[4] = {0.*cm,0.*cm,0.*cm,0.*cm};
  const G4double rOuterN1[4] = {0.3*cm,0.3*cm,1.3*cm,1.3*cm};
  G4Polycone* s_SPIDetN1 = new G4Polycone(SPIDetN1Name,
					     0.*deg,360.*deg,
					     4,
					     zPlaneN1,rInnerN1,rOuterN1);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIDetN1 = new G4LogicalVolume(s_SPIDetN1,
							Material,
							SPIDetN1Name);
  G4VPhysicalVolume* p_SPIDetN1 = new G4PVPlacement(0,
							G4ThreeVector(0.*cm,0.*cm,23.35*cm),
							l_SPIDetN1,
							SPIDetN1Name,
							l_SPIDetectorUnit,
							false,
							0);  
  const G4String SPIDetN3Name = "SPIDetN3"; // SMN3
  G4Tubs* s_SPIDetN3 = new G4Tubs(SPIDetN3Name,
				  0.7*cm, 0.85*cm,
				  0.025*cm,
				  0.*deg, 360.*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIDetN3 = new G4LogicalVolume(s_SPIDetN3,
							Material,
							SPIDetN3Name);
  G4VPhysicalVolume* p_SPIDetN3 = new G4PVPlacement(0,
							G4ThreeVector(0.*cm,0.*cm,23.525*cm),
							l_SPIDetN3,
							SPIDetN3Name,
							l_SPIDetectorUnit,
							false,
							0);  
  const G4String SPIDetNNName = "SPIDetNN"; // SMNN
  const G4double zPlaneNN[6] = {0.*cm,0.15*cm,0.15*cm,0.35*cm,0.35*cm,1.35*cm};
  const G4double rInnerNN[6] = {0.*cm,0.*cm,0.*cm,0.*cm,0.*cm,0.*cm};
  const G4double rOuterNN[6] = {0.3*cm,0.3*cm,1.2*cm,1.2*cm,0.3*cm,0.3*cm};
  G4Polycone* s_SPIDetNN = new G4Polycone(SPIDetNNName,
					     0.*deg,360.*deg,
					     6,
					     zPlaneNN,rInnerNN,rOuterNN);
  Material =  PIMPSelectMaterial("Beryllium", Materials) ;
  G4LogicalVolume* l_SPIDetNN = new G4LogicalVolume(s_SPIDetNN,
							Material,
							SPIDetNNName);
  G4VPhysicalVolume* p_SPIDetNN = new G4PVPlacement(0,
							G4ThreeVector(0.*cm,0.*cm,23.4*cm),
							l_SPIDetNN,
							SPIDetNNName,
							l_SPIDetectorUnit,
							false,
							0);  
  const G4String SPIDetNHName = "SPIDetNH"; // SMNH
  G4Tubs* s_SPIDetNH = new G4Tubs(SPIDetNHName,
				  0.*cm, 0.2*cm,
				  0.5*cm,
				  0.*deg, 360.*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SPIDetNH = new G4LogicalVolume(s_SPIDetNH,
							Material,
							SPIDetNHName);
  G4VPhysicalVolume* p_SPIDetNH = new G4PVPlacement(0,
							G4ThreeVector(0.*cm,0.*cm,0.5*cm),
							l_SPIDetNH,
							SPIDetNHName,
							l_SPIDetNN,
							false,
							0);  

 
  // Place the 19 SPIDetectorPixel
  PIMPGeomSPIPixel* SPIPixel = new PIMPGeomSPIPixel(Materials, Sens) ; // creates object
  G4ThreeVector* SPIDetectorUnitPosition = new G4ThreeVector;
  G4RotationMatrix* RotateDetPix  = new  G4RotationMatrix ;
  RotateDetPix->rotateZ(30*deg);

  SPIDetectorUnitPosition->set(0.*cm,      0.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 0);
  SPIDetectorUnitPosition->set(0.*cm,      6.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 1);
  SPIDetectorUnitPosition->set(-5.196153*cm,  3.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 2);
  SPIDetectorUnitPosition->set(-5.196153*cm, -3.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 3);
  SPIDetectorUnitPosition->set(0.*cm,     -6.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 4);
  SPIDetectorUnitPosition->set(5.196153*cm,  -3.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 5);
  SPIDetectorUnitPosition->set(5.196153*cm,   3.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 6);
  //changed djc 23-5-05 outer ring of pixels moved 1 spave round numbering wrong   7=8 now
  SPIDetectorUnitPosition->set(5.196153*cm,   9.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 7);
  SPIDetectorUnitPosition->set(0.*cm,     12.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 8);
  SPIDetectorUnitPosition->set(-5.196153*cm,  9.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 9);
  SPIDetectorUnitPosition->set(-10.392305*cm,  6.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 10);
  SPIDetectorUnitPosition->set(-10.392305*cm,  0.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 11);
  SPIDetectorUnitPosition->set(-10.392305*cm, -6.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 12);
  SPIDetectorUnitPosition->set(-5.196153*cm, -9.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 13);
  SPIDetectorUnitPosition->set(0.*cm,    -12.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 14);
  SPIDetectorUnitPosition->set(5.196153*cm,  -9.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 15);
  SPIDetectorUnitPosition->set(10.392305*cm,  -6.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 16);
  SPIDetectorUnitPosition->set(10.392305*cm,   0.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 17);
  SPIDetectorUnitPosition->set(10.392305*cm,   6.*cm,0.*cm);
  SPIPixel->Create(l_SPIDetectorUnit,SPIDetectorUnitPosition,RotateDetPix, 18);


  //----------------------------------------------------------------------------------------------------//
  //					The SPICryoSupp							//
  //----------------------------------------------------------------------------------------------------//
  // SL01
  const G4String SPICryoSupp1Name = "SPICryoSupp1"; 
  G4Trap* s_SPICryoSupp1 = new G4Trap(SPICryoSupp1Name,
				      11.6999*cm,
				      0.*deg,0.*deg,
				      7.5*cm,0.4*cm,0.4*cm,0*deg,
				      9.0*cm,0.4*cm,0.4*cm,0*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp1 = new G4LogicalVolume(s_SPICryoSupp1,
							Material,
							SPICryoSupp1Name);
  
  G4RotationMatrix* RotateSupp1A = new G4RotationMatrix ;
  RotateSupp1A->rotateZ(330*deg);
  RotateSupp1A->rotateY(45*deg);
  G4RotationMatrix* RotateSupp1B = new G4RotationMatrix ;
  RotateSupp1B->rotateZ(210*deg);
  RotateSupp1B->rotateY(45*deg);
  G4RotationMatrix* RotateSupp1C = new G4RotationMatrix ;
  RotateSupp1C->rotateZ(90*deg);
  RotateSupp1C->rotateY(45*deg);
  
  G4VPhysicalVolume* p_SPICryoSupp1 = new G4PVPlacement(RotateSupp1A,
							G4ThreeVector(-22.8998*cm,
								      -13.2212*cm,
								      0.1112*cm),
							l_SPICryoSupp1,
							SPICryoSupp1Name,
							l_SPILowVETO,
							false,
							0);
  p_SPICryoSupp1 = new G4PVPlacement(RotateSupp1B,
				     G4ThreeVector(22.8747*cm,
						   -13.2067*cm,
						   0.1383*cm),
				     l_SPICryoSupp1,
				     SPICryoSupp1Name,
				     l_SPILowVETO,
				     false,
				     1);
  p_SPICryoSupp1 = new G4PVPlacement(RotateSupp1C,
				     G4ThreeVector(0.*cm,
						   26.4239*cm,
						   0.1073*cm),
				     l_SPICryoSupp1,
				     SPICryoSupp1Name,
				     l_SPILowVETO,
				     false,
				     2);
  
  // SL02
  const G4String SPICryoSupp2Name = "SPICryoSupp2"; 
  G4Trap* s_SPICryoSupp2 = new G4Trap(SPICryoSupp2Name,
				      1.9998*cm,
				      0.*deg,0.*deg,
				      8.7436*cm,0.125*cm,0.125*cm,0*deg,
				      9.0*cm,0.125*cm,0.125*cm,0*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp2 = new G4LogicalVolume(s_SPICryoSupp2,
							Material,
							SPICryoSupp2Name);
  
  G4RotationMatrix* RotateSupp2A = new G4RotationMatrix ;
  RotateSupp2A->rotateZ(330*deg);
  RotateSupp2A->rotateY(45*deg);
  G4RotationMatrix* RotateSupp2B = new G4RotationMatrix ;
  RotateSupp2B->rotateZ(210*deg);
  RotateSupp2B->rotateY(45*deg);
  G4RotationMatrix* RotateSupp2C = new G4RotationMatrix ;
  RotateSupp2C->rotateZ(90*deg);
  RotateSupp2C->rotateY(45*deg);
  
  G4VPhysicalVolume* p_SPICryoSupp2 = new G4PVPlacement(RotateSupp2A,
							G4ThreeVector(-28.5183*cm,
								      -16.8337*cm,
								      7.3414*cm),
							l_SPICryoSupp2,
							SPICryoSupp2Name,
							l_SPILowVETO,
							false,
							0);
  p_SPICryoSupp2 = new G4PVPlacement(RotateSupp2A,
				     G4ThreeVector(-29.1568*cm,
						   -16.8337*cm,
						   6.6034*cm),
				     l_SPICryoSupp2,
				     SPICryoSupp2Name,
				     l_SPILowVETO,
				     false,
				     1);
  p_SPICryoSupp2 = new G4PVPlacement(RotateSupp2C,
				     G4ThreeVector(0.*cm,
						   32.9251*cm,
						   7.3459*cm),
				     l_SPICryoSupp2,
				     SPICryoSupp2Name,
				     l_SPILowVETO,
				     false,
				     2);
  p_SPICryoSupp2 = new G4PVPlacement(RotateSupp2C,
				     G4ThreeVector(0.*cm,
						   33.6619*cm,
						   6.598*cm),
				     l_SPICryoSupp2,
				     SPICryoSupp2Name,
				     l_SPILowVETO,
				     false,
				     3);
  p_SPICryoSupp2 = new G4PVPlacement(RotateSupp2B,
				     G4ThreeVector(29.1614*cm,
						   -16.8363*cm,
						   6.5986*cm),
				     l_SPICryoSupp2,
				     SPICryoSupp2Name,
				     l_SPILowVETO,
				     false,
				     4);
  p_SPICryoSupp2 = new G4PVPlacement(RotateSupp2B,
				     G4ThreeVector(28.5078*cm,
						   -16.4594*cm,
						   7.3454*cm),
				     l_SPICryoSupp2,
				     SPICryoSupp2Name,
				     l_SPILowVETO,
				     false,
				     5);

 // SL03
  const G4String SPICryoSupp3Name = "SPICryoSupp3"; 
  G4Trap* s_SPICryoSupp3 = new G4Trap(SPICryoSupp3Name,
				      2.0001*cm,
				      0.*deg,0.*deg,
				      7.5*cm,0.1251*cm,0.1251*cm,0*deg,
				      7.7564*cm,0.1251*cm,0.1251*cm,0*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp3 = new G4LogicalVolume(s_SPICryoSupp3,
							Material,
							SPICryoSupp3Name);
  
  G4VPhysicalVolume* p_SPICryoSupp3 = new G4PVPlacement(RotateSupp2A,
							G4ThreeVector(-16.6384*cm,
								      -9.9652*cm,
								      -6.3764*cm),
							l_SPICryoSupp3,
							SPICryoSupp3Name,
							l_SPILowVETO,
							false,
							0);
  p_SPICryoSupp3 = new G4PVPlacement(RotateSupp2A,
				     G4ThreeVector(-17.2577*cm,
						   -9.9652*cm,
						   -7.0894*cm),
				     l_SPICryoSupp3,
				     SPICryoSupp3Name,
				     l_SPILowVETO,
				     false,
				     1);
  p_SPICryoSupp3 = new G4PVPlacement(RotateSupp2C,
				     G4ThreeVector(-0.0131*cm,
						   19.2079*cm,
						   -6.3719*cm),
				     l_SPICryoSupp3,
				     SPICryoSupp3Name,
				     l_SPILowVETO,
				     false,
				     2);
  p_SPICryoSupp3 = new G4PVPlacement(RotateSupp2C,
				     G4ThreeVector(-0.0386*cm,
						   19.9601*cm,
						   -7.1235*cm),
				     l_SPICryoSupp3,
				     SPICryoSupp3Name,
				     l_SPILowVETO,
				     false,
				     3);
  p_SPICryoSupp3 = new G4PVPlacement(RotateSupp2B,
				     G4ThreeVector(16.634*cm,
						   -9.6036*cm,
						   -6.3719*cm),
				     l_SPICryoSupp3,
				     SPICryoSupp3Name,
				     l_SPILowVETO,
				     false,
				     4);
  p_SPICryoSupp3 = new G4PVPlacement(RotateSupp2B,
				     G4ThreeVector(17.4115*cm,
						   -10.0526*cm,
						   -7.2662*cm),
				     l_SPICryoSupp3,
				     SPICryoSupp3Name,
				     l_SPILowVETO,
				     false,
				     5);

 // SL04
  const G4String SPICryoSupp4Name = "SPICryoSupp4"; 
  G4Trap* s_SPICryoSupp4 = new G4Trap(SPICryoSupp4Name,
				      0.7088*cm,
				      0.*deg,0.*deg,
				      11.1*cm,0.4*cm,0.4*cm,0*deg,
				      3.7451*cm,0.4*cm,0.4*cm,0*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp4 = new G4LogicalVolume(s_SPICryoSupp4,
							Material,
							SPICryoSupp4Name);
  G4RotationMatrix* RotateSupp4A = new G4RotationMatrix ;
  RotateSupp4A->rotateZ(150*deg);
  RotateSupp4A->rotateY(-90*deg);
  G4RotationMatrix* RotateSupp4B = new G4RotationMatrix ;
  RotateSupp4B->rotateZ(90*deg);
  RotateSupp4B->rotateY(90*deg);
  G4RotationMatrix* RotateSupp4C = new G4RotationMatrix ;
  RotateSupp4C->rotateZ(30*deg);
  RotateSupp4C->rotateY(-90*deg);

  G4VPhysicalVolume* p_SPICryoSupp4 = new G4PVPlacement(RotateSupp4A,
							G4ThreeVector(-33.4397*cm,
								      -19.3064*cm,
								      -6.4075*cm),
							l_SPICryoSupp4,
							SPICryoSupp4Name,
							l_SPILowVETO,
							false,
							0);
  
  p_SPICryoSupp4 = new G4PVPlacement(RotateSupp4B,
				     G4ThreeVector(0.*cm,
						   38.6129*cm,
						   6.4075*cm),
				     l_SPICryoSupp4,
				     SPICryoSupp4Name,
				     l_SPILowVETO,
				     false,
				     1);
  
  p_SPICryoSupp4 = new G4PVPlacement(RotateSupp4C,
				     G4ThreeVector(33.4397*cm,
						   -19.3064*cm,
						   6.4075*cm),
				     l_SPICryoSupp4,
				     SPICryoSupp4Name,
				     l_SPILowVETO,
				     false,
				     2);
  
 // SL05
  const G4String SPICryoSupp5Name = "SPICryoSupp5"; 
  G4Trap* s_SPICryoSupp5 = new G4Trap(SPICryoSupp5Name,
				      0.4066*cm,
				      26.56*deg,180.*deg,
				      9.*cm,2.0229*cm,2.0229*cm,0*deg,
				      9.*cm,1.6163*cm,1.6163*cm,0*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp5 = new G4LogicalVolume(s_SPICryoSupp5,
							Material,
							SPICryoSupp5Name);
  G4RotationMatrix* RotateSupp5A = new G4RotationMatrix ;
  RotateSupp5A->rotateZ(-30*deg);
  RotateSupp5A->rotateY(135*deg);
  G4RotationMatrix* RotateSupp5B = new G4RotationMatrix ;
  RotateSupp5B->rotateZ(90*deg);
  RotateSupp5B->rotateY(135*deg);
  G4RotationMatrix* RotateSupp5C = new G4RotationMatrix ;
  RotateSupp5C->rotateZ(210*deg);
  RotateSupp5C->rotateY(135*deg);

  G4VPhysicalVolume* p_SPICryoSupp5 = new G4PVPlacement(RotateSupp5A,
							G4ThreeVector(-29.3763*cm,
								      -16.9604*cm,
								      6.0959*cm),
							l_SPICryoSupp5,
							SPICryoSupp5Name,
							l_SPILowVETO,
							false,
							0);
  
  p_SPICryoSupp5 = new G4PVPlacement(RotateSupp5B,
				     G4ThreeVector(0.*cm,
						   33.9209*cm,
						   6.0959*cm),
				     l_SPICryoSupp5,
				     SPICryoSupp5Name,
				     l_SPILowVETO,
				     false,
				     1);
  
  p_SPICryoSupp5 = new G4PVPlacement(RotateSupp5C,
				     G4ThreeVector(29.3682*cm,
						   -16.9557*cm,
						   6.1052*cm),
				     l_SPICryoSupp5,
				     SPICryoSupp5Name,
				     l_SPILowVETO,
				     false,
				     2);

  // SL06
  const G4String SPICryoSupp6Name = "SPICryoSupp6"; 
  G4Trap* s_SPICryoSupp6 = new G4Trap(SPICryoSupp6Name,
				      1.3462*cm,
				      0.*deg,0.*deg,
				      5.7912*cm,0.575*cm,0.575*cm,0*deg,
				      9.*cm,0.575*cm,0.575*cm,0*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp6 = new G4LogicalVolume(s_SPICryoSupp6,
							Material,
							SPICryoSupp6Name);
  G4RotationMatrix* RotateSupp6A = new G4RotationMatrix ;
  RotateSupp6A->rotateY(90*deg);
  RotateSupp6A->rotateX(30*deg);
  G4RotationMatrix* RotateSupp6B = new G4RotationMatrix ;
  RotateSupp6B->rotateY(90*deg);
  RotateSupp6B->rotateX(270*deg);
  G4RotationMatrix* RotateSupp6C = new G4RotationMatrix ;
  RotateSupp6C->rotateY(90*deg);
  RotateSupp6C->rotateX(150*deg);

  G4VPhysicalVolume* p_SPICryoSupp6 = new G4PVPlacement(RotateSupp6C,
							G4ThreeVector(-31.6565*cm,
								      -18.2769*cm,
								      7.3825*cm),
							l_SPICryoSupp6,
							SPICryoSupp6Name,
							l_SPILowVETO,
							false,
							0);
  
  p_SPICryoSupp6 = new G4PVPlacement(RotateSupp6B,
				     G4ThreeVector(0.*cm,
						   36.5537*cm,
						   7.3825*cm),
				     l_SPICryoSupp6,
				     SPICryoSupp6Name,
				     l_SPILowVETO,
				     false,
				     1);
  
  p_SPICryoSupp6 = new G4PVPlacement(RotateSupp6A,
				     G4ThreeVector(31.6565*cm,
						   -18.2769*cm,
						   7.3825*cm),
				     l_SPICryoSupp6,
				     SPICryoSupp6Name,
				     l_SPILowVETO,
				     false,
				     2);

  // SL07
  const G4String SPICryoSupp7Name = "SPICryoSupp7"; 
  G4Box* s_SPICryoSupp7 = new G4Box(SPICryoSupp7Name,
				    0.4*cm, 1.6021*cm, 1.05*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp7 = new G4LogicalVolume(s_SPICryoSupp7,
							Material,
							SPICryoSupp7Name);
  G4RotationMatrix* RotateSupp7A = new G4RotationMatrix ;
  RotateSupp7A->rotateY(90*deg);
  RotateSupp7A->rotateX(-120*deg);
  G4RotationMatrix* RotateSupp7B = new G4RotationMatrix ;
  RotateSupp7B->rotateY(90*deg);
  RotateSupp7B->rotateX(0*deg);
  G4RotationMatrix* RotateSupp7C = new G4RotationMatrix ;
  RotateSupp7C->rotateY(90*deg);
  RotateSupp7C->rotateX(-240*deg);

  G4VPhysicalVolume* p_SPICryoSupp7 = new G4PVPlacement(RotateSupp7A,
							G4ThreeVector(-36.4635*cm,
								      -9.4475*cm,
								      6.4075*cm),
							l_SPICryoSupp7,
							SPICryoSupp7Name,
							l_SPILowVETO,
							false,
							0);
  p_SPICryoSupp7 = new G4PVPlacement(RotateSupp7A,
				     G4ThreeVector(-26.4135*cm,
						   -26.8546*cm,
						   6.4075*cm),
				     l_SPICryoSupp7,
				     SPICryoSupp7Name,
				     l_SPILowVETO,
				     false,
				     1);
  
  p_SPICryoSupp7 = new G4PVPlacement(RotateSupp7B,
				     G4ThreeVector(-10.05*cm,
						   36.3021*cm,
						   6.4075*cm),
				     l_SPICryoSupp7,
				     SPICryoSupp7Name,
				     l_SPILowVETO,
				     false,
				     2);
  p_SPICryoSupp7 = new G4PVPlacement(RotateSupp7B,
				     G4ThreeVector(10.05*cm,
						   36.3021*cm,
						   6.4075*cm),
				     l_SPICryoSupp7,
				     SPICryoSupp7Name,
				     l_SPILowVETO,
				     false,
				     3);
 p_SPICryoSupp7 = new G4PVPlacement(RotateSupp7C,
				     G4ThreeVector(26.4135*cm,
						   -26.8546*cm,
						   6.4075*cm),
				     l_SPICryoSupp7,
				     SPICryoSupp7Name,
				     l_SPILowVETO,
				     false,
				     4);
 p_SPICryoSupp7 = new G4PVPlacement(RotateSupp7C,
				    G4ThreeVector(36.4635*cm,
						  -9.4475*cm,
						  6.4075*cm),
				    l_SPICryoSupp7,
				    SPICryoSupp7Name,
				    l_SPILowVETO,
				    false,
				    5);

  // SL08
  const G4String SPICryoSupp8Name = "SPICryoSupp8"; 
  G4Box* s_SPICryoSupp8 = new G4Box(SPICryoSupp8Name,
				    0.4*cm, 9.0*cm, 1.3483*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_SPICryoSupp8 = new G4LogicalVolume(s_SPICryoSupp8,
							Material,
							SPICryoSupp8Name);
  G4RotationMatrix* RotateSupp8A = new G4RotationMatrix ;
  RotateSupp8A->rotateY(90*deg);
  RotateSupp8A->rotateX(-120*deg);
  G4RotationMatrix* RotateSupp8B = new G4RotationMatrix ;
  RotateSupp8B->rotateY(90*deg);
  RotateSupp8B->rotateX(0*deg);
  G4RotationMatrix* RotateSupp8C = new G4RotationMatrix ;
  RotateSupp8C->rotateY(90*deg);
  RotateSupp8C->rotateX(-240*deg);

  G4VPhysicalVolume* p_SPICryoSupp8 = new G4PVPlacement(RotateSupp4A,
							G4ThreeVector(-31.6583*cm,
								      -18.2779*cm,
								      6.4075*cm),
							l_SPICryoSupp8,
							SPICryoSupp8Name,
							l_SPILowVETO,
							false,
							0);
  p_SPICryoSupp8 = new G4PVPlacement(RotateSupp4B,
				     G4ThreeVector(0.*cm,
						   36.5558*cm,
						   6.4075*cm),
				     l_SPICryoSupp8,
				     SPICryoSupp8Name,
				     l_SPILowVETO,
				     false,
				     1);
  
  p_SPICryoSupp8 = new G4PVPlacement(RotateSupp4C,
				     G4ThreeVector(31.2188*cm,
						   -18.0241*cm,
						   6.4075*cm),
				     l_SPICryoSupp8,
				     SPICryoSupp8Name,
				     l_SPILowVETO,
				     false,
				     2);


  // SP01
  const G4String SPIPompage1Name = "SPIPompage1"; 
  G4Box* s_SPIPompage1 = new G4Box(SPIPompage1Name,
				   1.95*cm, 3.12*cm, 6.37*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage1 = new G4LogicalVolume(s_SPIPompage1,
						       Material,
						       SPIPompage1Name);
  G4RotationMatrix* RotatePom1 = new G4RotationMatrix ;
  RotatePom1->rotateY(90*deg);
  RotatePom1->rotateX(60*deg);
  
  G4VPhysicalVolume* p_SPIPompage1 = new G4PVPlacement(RotatePom1,
						       G4ThreeVector(-0.5871*cm,
								     5.3768*cm,
								     -6.9225*cm),
						       l_SPIPompage1,
						       SPIPompage1Name,
						       l_SPILowVETO,
						       false,
						       0);
 
  // SP07
  const G4String SPIPompage7Name = "SPIPompage7"; 
  G4Trap* s_SPIPompage7 = new G4Trap(SPIPompage7Name,
				   0.2*cm,
				   0.*deg,0.*deg,
				   1.8*cm, 0.15*cm, 0.15*cm, 0.*deg,
				   1.4*cm, 0.15*cm, 0.15*cm, 0.*deg);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage7 = new G4LogicalVolume(s_SPIPompage7,
						       Material,
						       SPIPompage7Name);
  G4RotationMatrix* RotatePom7a = new G4RotationMatrix ;
  RotatePom7a->rotateX(-90*deg);
  RotatePom7a->rotateY(-30*deg);
  G4RotationMatrix* RotatePom7b = new G4RotationMatrix ;
  RotatePom7b->rotateX(-90*deg);
  RotatePom7b->rotateY(-210*deg);
  
  G4VPhysicalVolume* p_SPIPompage7 = new G4PVPlacement(RotatePom7a,
						       G4ThreeVector(4.6699*cm,
								     2.8115*cm,
								     -7.0925*cm),
						       l_SPIPompage7,
						       SPIPompage7Name,
						       l_SPILowVETO,
						       false,
						       0);
  p_SPIPompage7 = new G4PVPlacement(RotatePom7b,
				    G4ThreeVector(-0.1802*cm,
						  11.2121*cm,
						  -7.0925*cm),
				    l_SPIPompage7,
				    SPIPompage7Name,
				    l_SPILowVETO,
				    false,
				    1);


 // SP06
  const G4String SPIPompage6Name = "SPIPompage6"; 
  G4Box* s_SPIPompage6 = new G4Box(SPIPompage6Name,
				   1.8*cm, 0.15*cm, 4.65*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage6 = new G4LogicalVolume(s_SPIPompage6,
						       Material,
						       SPIPompage6Name);
  G4VPhysicalVolume* p_SPIPompage6 = new G4PVPlacement(RotatePom1,
						       G4ThreeVector(2.2448*cm,
								     7.0118*cm,
								     -7.0925*cm),
						       l_SPIPompage6,
						       SPIPompage6Name,
						       l_SPILowVETO,
						       false,
						       0);

 // SP08
  const G4String SPIPompage8Name = "SPIPompage8"; 
  G4Box* s_SPIPompage8 = new G4Box(SPIPompage8Name,
				   0.04*cm, 1.12*cm, 5.8894*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage8 = new G4LogicalVolume(s_SPIPompage8,
						       Material,
						       SPIPompage8Name);
  G4RotationMatrix* RotatePom8 = new G4RotationMatrix ;
  RotatePom8->rotateX(-90*deg);
  RotatePom8->rotateY(60*deg);
  G4VPhysicalVolume* p_SPIPompage8 = new G4PVPlacement(RotatePom8,
						       G4ThreeVector(9.2653*cm,
								     6.3309*cm,
								     -7.0921*cm),
						       l_SPIPompage8,
						       SPIPompage8Name,
						       l_SPILowVETO,
						       false,
						       0);
  p_SPIPompage8 = new G4PVPlacement(RotatePom8,
				    G4ThreeVector(7.2153*cm,
						  9.8816*cm,
						  -7.0921*cm),
				    l_SPIPompage8,
				    SPIPompage8Name,
				    l_SPILowVETO,
				    false,
				    1);
  p_SPIPompage8 = new G4PVPlacement(RotatePom8,
				    G4ThreeVector(5.1753*cm,
						  13.4149*cm,
						  -7.0921*cm),
				    l_SPIPompage8,
				    SPIPompage8Name,
				    l_SPILowVETO,
				    false,
				    2);
  
  // SP09
  const G4String SPIPompage9Name = "SPIPompage9"; 
  G4Trap* s_SPIPompage9 = new G4Trap(SPIPompage9Name,
				     1.1104*cm,
				     0.*deg,0.*deg,
				     1.0599*cm, 0.04*cm, 0.04*cm, 0.*deg,
				     0.7675*cm, 0.04*cm, 0.04*cm, 0.*deg);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage9 = new G4LogicalVolume(s_SPIPompage9,
						       Material,
						       SPIPompage9Name);
  G4RotationMatrix* RotatePom9a = new G4RotationMatrix ;
  RotatePom9a->rotateZ(60*deg);
  RotatePom9a->rotateX(-7.5*deg);
  G4RotationMatrix* RotatePom9b = new G4RotationMatrix ;
  RotatePom9b->rotateZ(60*deg);
  RotatePom9b->rotateX(-22.50*deg);
  G4RotationMatrix* RotatePom9c = new G4RotationMatrix ;
  RotatePom9c->rotateZ(60*deg);
  RotatePom9c->rotateX(-37.50*deg);

  G4VPhysicalVolume* p_SPIPompage9 = new G4PVPlacement(RotatePom9a,
						       G4ThreeVector(15.1485*cm,
								     9.7295*cm,
								     -6.9723*cm),
						       l_SPIPompage9,
						       SPIPompage9Name,
						       l_SPILowVETO,
						       false,
						       0);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9a,
				    G4ThreeVector(13.1002*cm,13.2792*cm,
						  -6.9732*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    1);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9a,
				    G4ThreeVector(11.0598*cm,16.8134*cm,
						  -6.9737*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    2);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9b,
				    G4ThreeVector(14.6158*cm,14.1542*cm,
						  -6.5043*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    3);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9b,
				    G4ThreeVector(12.5681*cm,17.6842*cm,
						  -6.5071*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    4);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9b,
				    G4ThreeVector(16.6649*cm,10.6042*cm,
						  -6.5047*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    5);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9c,
				    G4ThreeVector(15.9746*cm,14.9387*cm,
						  -5.5985*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    6);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9c,
				    G4ThreeVector(18.0147*cm,11.4048*cm,
						  -5.5979*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    7);
  p_SPIPompage9 = new G4PVPlacement(RotatePom9c,
				    G4ThreeVector(13.922*cm,18.472*cm,
						  -5.6047*cm),
				    l_SPIPompage9,
				    SPIPompage9Name,
				    l_SPILowVETO,
				    false,
				    8);


  // SP12
  const G4String SPIPompage12Name = "SPIPompage12"; 
  G4Box* s_SPIPompage12 = new G4Box(SPIPompage12Name,
				    0.04*cm, 1.12*cm, 7.5657*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage12 = new G4LogicalVolume(s_SPIPompage12,
							Material,
							SPIPompage12Name);
  G4RotationMatrix* RotatePom12 = new G4RotationMatrix ;
  RotatePom12->rotateZ(60*deg);
  RotatePom12->rotateX(-135.*deg);
  G4VPhysicalVolume* p_SPIPompage12 = new G4PVPlacement(RotatePom12,
						       G4ThreeVector(21.2354*cm,
								     17.9759*cm,
								     0.3075*cm),
						       l_SPIPompage12,
						       SPIPompage12Name,
						       l_SPILowVETO,
						       false,
						       0);
  p_SPIPompage12 = new G4PVPlacement(RotatePom12,
				    G4ThreeVector(19.1884*cm,
						  21.5285*cm,
						  0.3076*cm),
				    l_SPIPompage12,
				    SPIPompage12Name,
				    l_SPILowVETO,
				    false,
				    1);
  p_SPIPompage12 = new G4PVPlacement(RotatePom12,
				    G4ThreeVector(23.2804*cm,
						  14.434*cm,
						  0.3076*cm),
				    l_SPIPompage12,
				    SPIPompage12Name,
				    l_SPILowVETO,
				    false,
				    2);
  
  // SP13
  const G4String SPIPompage13Name = "SPIPompage13"; 
  G4Trap* s_SPIPompage13 = new G4Trap(SPIPompage13Name,
				     1.1104*cm,
				     0.*deg,0.*deg,
				     0.7675*cm, 0.04*cm, 0.04*cm, 0.*deg,
				     1.0599*cm, 0.04*cm, 0.04*cm, 0.*deg);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage13 = new G4LogicalVolume(s_SPIPompage13,
							Material,
							SPIPompage13Name);

  G4VPhysicalVolume* p_SPIPompage13 = new G4PVPlacement(RotatePom9c,
						       G4ThreeVector(26.4961*cm,
								     21.0133*cm,
								     6.2135*cm),
						       l_SPIPompage13,
						       SPIPompage13Name,
						       l_SPILowVETO,
						       false,
						       0);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9c,
				    G4ThreeVector(28.5195*cm,
						  17.5103*cm,
						  6.2136*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    1);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9c,
				    G4ThreeVector(24.4356*cm,
						  24.564*cm,
						  6.2316*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    2);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9b,
				    G4ThreeVector(27.8549*cm,
						  21.7978*cm,
						  7.1193*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    3);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9b,
				    G4ThreeVector(29.8809*cm,
						  18.2898*cm,
						  7.1194*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    4);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9b,
				    G4ThreeVector(25.8019*cm,
						  25.3745*cm,
						  7.1217*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    5);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9a,
				    G4ThreeVector(27.323*cm,
						  26.2192*cm,
						  7.5878*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    6);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9a,
				    G4ThreeVector(29.3705*cm,
						  22.6728*cm,
						  7.5883*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    7);
  p_SPIPompage13 = new G4PVPlacement(RotatePom9a,
				    G4ThreeVector(31.4042*cm,
						  19.1519*cm,
						  7.5885*cm),
				    l_SPIPompage13,
				    SPIPompage13Name,
				    l_SPILowVETO,
				    false,
				    8);

  // SP16 left out as will likly cause problems as defined as MANY
  
  //SP17
  const G4String SPIPompage17Name = "SPIPompage17"; 
  G4Box* s_SPIPompage17 = new G4Box(SPIPompage17Name,
				    5.7394*cm, 4.05*cm, 0.04*cm);
  Material =  PIMPSelectMaterial("TiAlV", Materials);
  G4LogicalVolume* l_SPIPompage17 = new G4LogicalVolume(s_SPIPompage17,
							Material,
							SPIPompage17Name);
  G4RotationMatrix* RotatePom17 = new G4RotationMatrix ;
  RotatePom17->rotateZ(-210.*deg);

  G4VPhysicalVolume* p_SPIPompage17 = new G4PVPlacement(RotatePom17,
							G4ThreeVector(7.3452*cm,
								      9.9565*cm,
								      -5.9325*cm),
							l_SPIPompage17,
							SPIPompage17Name,
							l_SPILowVETO,
							false,
							0);
  p_SPIPompage17 = new G4PVPlacement(RotatePom17,
				     G4ThreeVector(7.3552*cm,
						   9.9392*cm,
						   -8.2525*cm),
				     l_SPIPompage17,
				     SPIPompage17Name,
				     l_SPILowVETO,
				     false,
				     1);
  
  // SP04
  const G4String SPIPompage04Name = "SPIPompage04"; 
  G4Box* s_SPIPompage04 = new G4Box(SPIPompage04Name,
				    1.62*cm, 1.12*cm, 4.07*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPIPompage04 = new G4LogicalVolume(s_SPIPompage04,
							Material,
							SPIPompage04Name);
  G4VPhysicalVolume* p_SPIPompage04 = new G4PVPlacement(0,
							G4ThreeVector(0.33*cm,
								      0.*cm,
								      0.*cm),
							l_SPIPompage04,
							SPIPompage04Name,
							l_SPIPompage1,
							false,
							0);

  // SP05
  const G4String SPIPompage05Name = "SPIPompage05"; 
  G4Trap* s_SPIPompage05 = new G4Trap(SPIPompage05Name,
				      0.15*cm,
				      0.*deg, 0.*deg,
				      1.12*cm, 1.62*cm, 1.62*cm, 0.*deg,
				      0.82*cm, 1.62*cm, 1.62*cm, 0.*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPIPompage05 = new G4LogicalVolume(s_SPIPompage05,
							Material,
							SPIPompage05Name);
  G4RotationMatrix* RotatePom5 = new G4RotationMatrix ;
  RotatePom5->rotateY(180*deg);
  G4VPhysicalVolume* p_SPIPompage05 = new G4PVPlacement(RotatePom5,
							G4ThreeVector(0.33*cm,
								      0.*cm,
								      -4.22*cm),
							l_SPIPompage05,
							SPIPompage05Name,
							l_SPIPompage1,
							false,
							0);
  p_SPIPompage05 = new G4PVPlacement(0,
				     G4ThreeVector(0.33*cm,
						   0.*cm,
						   4.22*cm),
				     l_SPIPompage05,
				     SPIPompage05Name,
				     l_SPIPompage1,
				     false,
				     1);
  
 // SP02
  const G4String SPIPompage02Name = "SPIPompage02"; 
  G4Box* s_SPIPompage02 = new G4Box(SPIPompage02Name,
				    1.*cm, 1.585*cm, 1.12*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_SPIPompage02 = new G4LogicalVolume(s_SPIPompage02,
							Material,
							SPIPompage02Name);
  G4RotationMatrix* RotatePom2 = new G4RotationMatrix ;
  RotatePom2->rotateX(90*deg);
  RotatePom2->rotateY(-90*deg);
  G4VPhysicalVolume* p_SPIPompage02 = new G4PVPlacement(0,
							G4ThreeVector(-0.17*cm,
								      2.12*cm,
								      -2.485*cm),
							l_SPIPompage02,
							SPIPompage02Name,
							l_SPIPompage1,
							false,
							0);
  p_SPIPompage02 = new G4PVPlacement(0,
				     G4ThreeVector(-0.17*cm,
						   2.12*cm,
						   2.485*cm),
				     l_SPIPompage02,
				     SPIPompage02Name,
				     l_SPIPompage1,
				     false,
				     1);

  // leaving out SP03, SP28, SF 01&02

  // SB06
  const G4String SPICryoAuxB06Name = "SPICryoAuxB06"; 
  G4Box* s_SPICryoAuxB06 = new G4Box(SPICryoAuxB06Name,
				     2.15*cm, 0.8682*cm, 19.1186*cm);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPICryoAuxB06 = new G4LogicalVolume(s_SPICryoAuxB06,
							 Material,
							 SPICryoAuxB06Name);
  G4RotationMatrix* RotateAuxB06 = new G4RotationMatrix ;
  RotateAuxB06->rotateZ(180*deg);
  RotateAuxB06->rotateX(-90*deg);
  
  G4VPhysicalVolume* p_SPICryoAuxB06 = new G4PVPlacement(RotateAuxB06,
							 G4ThreeVector(0.,-37.1415*cm,
								       7.1575*cm),
							 l_SPICryoAuxB06,
							 SPICryoAuxB06Name,
							 l_SPILowVETO,
							 false,
							 0);

 // SB07
  const G4String SPICryoAux07Name = "SPICryoAux07"; 
  G4Trap* s_SPICryoAux07 = new G4Trap(SPICryoAux07Name,
				      0.1909*cm,
				      42.32*deg,180.*deg,
				      1.7681*cm, 18.7599*cm, 18.7599*cm, 0.*deg,
				      2.1559*cm, 19.1295*cm, 19.1295*cm, 0.*deg);
  Material =  PIMPSelectMaterial("Beryllium", Materials);
  G4LogicalVolume* l_SPICryoAux07 = new G4LogicalVolume(s_SPICryoAux07,
							Material,
							SPICryoAux07Name);
  
  G4RotationMatrix* RotateCA07 = new G4RotationMatrix ;
  RotateCA07->rotateZ(-90*deg);
  
  G4VPhysicalVolume* p_SPICryoAux07 = new G4PVPlacement(RotateCA07,
							G4ThreeVector(0.,-37.3263*cm,
								      8.5709*cm),
							l_SPICryoAux07,
							SPICryoAux07Name,
							l_SPILowVETO,
							false,
							0);

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
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.196153*cm ,3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 2); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.196153*cm ,-3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 3); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,-6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 4); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.196153*cm ,3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 5); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.196153*cm ,-3.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 6); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,12.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 17);
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.196153*cm ,-9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 18); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(10.392305*cm ,6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 7); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(10.392305*cm ,0.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 8); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(10.392305*cm ,-6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 9); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(5.196153*cm ,9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 10); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(0.*cm ,-12.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 11); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.196153*cm ,-9.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 12); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-10.392305*cm ,-6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 13); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-10.392305*cm ,0.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 14); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-10.392305*cm ,6.*cm, 0.5*cm),
				   l_SPITitRing, SPITitRingName,l_SPIColdPlate2,
				   false, 15); 
  p_SPITitRing = new G4PVPlacement(0, G4ThreeVector(-5.196153*cm ,9.*cm, 0.5*cm),
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
  

  /*
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
								      46.0132*cm-20.5*cm,
								      -82.3901*cm+90.075*cm),
							l_SPIPompage26,
							SPIPompage26Name,
							l_SPIDetectorUnit, // changed to 
							false,
							0);
  p_SPIPompage26 = new G4PVPlacement(RotatePom26b,
				     G4ThreeVector(39.8599*cm,
						   55.8368*cm-20.5*cm,
						   -82.39*cm+90.075*cm),
				     l_SPIPompage26,
				     SPIPompage26Name,
				     l_SPIDetectorUnit, // changed to
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
								      50.8368*cm-20.5*cm,
								      -82.39*cm+90.075*cm),
							l_SPIPompage25,
							SPIPompage25Name,
							l_SPIDetectorUnit, // changed to
							false,
							0);
  */
  // not including SPs 30, 29, 21, 23, 24, 31,33, 32, 20
  // leaving out SP03, SP28, SF 01&02

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

  // missed out a whole list of volumes that are too small to 
  // any real difference to the background.
  

  // ----------------Cryo as a seperate object-----------------------//


  // ------------------- VISUALISATION -----------------------
  l_SPIDetNN->SetVisAttributes(Purple);
  l_SPILowVetoAlRinger->SetVisAttributes(Yellow);
  
  l_SPILowVetoBeTile1->SetVisAttributes(Red);
  l_SPILowVetoBeTile2->SetVisAttributes(Red);
  l_SPILowVetoBeTile3->SetVisAttributes(Red);
  l_SPILowVetoBeTile4->SetVisAttributes(Red);
  l_SPILowVetoBeTile5->SetVisAttributes(Red);
  l_SPILowVetoBeTile6->SetVisAttributes(Red); 
  l_SPILowVetoBeTile7->SetVisAttributes(Red); 
  l_SPILowVetoBeTile8->SetVisAttributes(Red); 
  l_SPILowVetoBeTile9->SetVisAttributes(Red);
  l_SPILowVetoBeTile10->SetVisAttributes(Red);
  l_SPILowVetoBeTile11->SetVisAttributes(Red);
  //Base
  l_SPILowVetoBeTile12->SetVisAttributes(Red);
  l_SPILowVetoBeTile13->SetVisAttributes(Red);
  l_SPILowVetoBeTile14->SetVisAttributes(Red);
  l_SPILowVetoBeTile15->SetVisAttributes(Red);
  l_SPILowVetoBeTile16->SetVisAttributes(Red);
  l_SPILowVetoBeTile17->SetVisAttributes(Red);
  l_SPILowVetoBeTile18->SetVisAttributes(Red);

  l_SPILowVetoSmallElec->SetVisAttributes(RoyalBlue); 
  l_SPILowVetoPMT->SetVisAttributes(Green);

  l_SPICryoAux07->SetVisAttributes(Yellow);
  l_SPICryoAuxB06->SetVisAttributes(Green);
  l_SPIPompage1->SetVisAttributes(Green);

  // -------------------- SENSITIVITY ---------------------------.
  
  l_SPILowVetoBeTile1->SetSensitiveDetector(Sens);
  l_SPILowVetoBeTile2->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile3->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile4->SetSensitiveDetector(Sens);
  l_SPILowVetoBeTile5->SetSensitiveDetector(Sens);  
  l_SPILowVetoBeTile6->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile7->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile8->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile9->SetSensitiveDetector(Sens);  
  l_SPILowVetoBeTile10->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile11->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile12->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile13->SetSensitiveDetector(Sens);  
  l_SPILowVetoBeTile14->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile15->SetSensitiveDetector(Sens);
  l_SPILowVetoBeTile16->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile17->SetSensitiveDetector(Sens); 
  l_SPILowVetoBeTile18->SetSensitiveDetector(Sens); 

}


PIMPGeomSPILowVeto::~PIMPGeomSPILowVeto()
{;}

void PIMPGeomSPILowVeto::Create(G4LogicalVolume* Parent, 
				const G4ThreeVector* Position, 
				G4RotationMatrix* Rotation,
				G4int Copy)
{  
  const G4String SPILowVetoName = "SPILowVeto" ;
  
  G4VPhysicalVolume* p_SPILowVETO = new G4PVPlacement(Rotation,
							*Position,
							l_SPILowVETO,
							SPILowVetoName,
							Parent,
							false,
							Copy); 
  
  return ;
}

void PIMPGeomSPILowVeto::PlacePMT(G4LogicalVolume* Child,
				  G4LogicalVolume* Parent, 
				  G4int PMTNum,
				  G4double Xposition,
				  G4double Yposition,
				  G4double Zposition,
				  G4RotationMatrix* Rotation)
{
  G4ThreeVector PMTPosition = G4ThreeVector(Xposition*cm,Yposition*cm,Zposition*cm);
  p_SPILowVetoPMT= new G4PVPlacement(Rotation,
				     PMTPosition,
				     Child,
				     "LowVetoPMT",
				     Parent,
				     true,
				     PMTNum); 
  return ;
}
void PIMPGeomSPILowVeto::PlaceElec(G4LogicalVolume* EChild,
				   G4LogicalVolume* EParent, 
				   G4int ElecNum,
				   G4double EXposition,
				   G4double EYposition,
				   G4double EZposition,
				   G4RotationMatrix* ERotation)
{

  G4ThreeVector ElecPosition = G4ThreeVector(EXposition*cm,EYposition*cm,EZposition*cm);
  p_SPILowSmallElec= new G4PVPlacement(ERotation,
				       ElecPosition,
				       EChild,
				       "LowSmallElec",
				       EParent,
				       true,
				       ElecNum); 
  return ;
}
