// ------------------------------------------------------------------
// PIMPGeometry - Spacecraft
// ------------------------------------------------------------------

#include "PIMPGeomSpacecraft.hh"

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

PIMPGeomSpacecraft::PIMPGeomSpacecraft(const G4MaterialTable* Materials)
{
  
  G4cout << "Create: Spacecraft" << G4endl ;

  // CRAF
  const G4String Name = "Spacecraft";
  G4Tubs* s_Spacecraft = new G4Tubs(Name,0.,215.0*cm,64.15*cm,0.*deg,360.0*deg);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_Spacecraft = new G4LogicalVolume(s_Spacecraft,
				     Material,
				     Name);
  // CBEN
  const G4String PayloadBenchName = "PayloadBenchName" ;
  G4Box* s_PayloadBench = new G4Box(PayloadBenchName,
				    (289/2)*cm,(281.1/2)*cm,(10.5/2)*cm);
  Material =  PIMPSelectMaterial("AluminiumHoney1", Materials) ;
  G4LogicalVolume* l_PayloadBench = new G4LogicalVolume(s_PayloadBench,
							Material,
							PayloadBenchName);
  G4VPhysicalVolume* p_PayloadBench = new G4PVPlacement(0,
							G4ThreeVector(13.1*cm,
								      0.*cm,
								      ( 64.15 - 10.5/2.)*cm),
							l_PayloadBench,
							PayloadBenchName,
							l_Spacecraft,
							false,
							0);	
  // CBHO - holes for JEM-X
  const G4String BenchJHoleName = "BenchJHoleName" ;
  G4Tubs* s_BenchJHole = new G4Tubs(BenchJHoleName,
				    0.*cm,22.5*cm,(10.5/2)*cm,0.*deg,360.0*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchJHole = new G4LogicalVolume(s_BenchJHole,
						      Material,
						      BenchJHoleName);
  G4VPhysicalVolume* p_BenchJHole = new G4PVPlacement(0,
						      G4ThreeVector(
					      (-289./2. + 124.4 + 21.3 )*cm,
					      28.35*cm,
					      0.*cm),
						      l_BenchJHole,
						      BenchJHoleName,
						      l_PayloadBench,
						      false,
						      0);
  p_BenchJHole = new G4PVPlacement(0,
				   G4ThreeVector(
						 (-289./2. + 124.4 + 21.3 )*cm,
						 -28.35*cm,
						 0.*cm),
				   l_BenchJHole,
				   BenchJHoleName,
				   l_PayloadBench,
				   false,
				   1);

  // CCU1 - holes 
  const G4String BenchHole1Name = "BenchHole1Name" ;
  G4Box* s_BenchHole1 = new G4Box(BenchHole1Name,
				  1.165*cm, 11.645*cm, (10.5/2)*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole1 = new G4LogicalVolume(s_BenchHole1,
						      Material,
						      BenchHole1Name);
  G4VPhysicalVolume* p_BenchHole1 = new G4PVPlacement(0,
						      G4ThreeVector(143.335*cm,
								    -97.405*cm,
								    0.*cm),
						      l_BenchHole1,
						      BenchHole1Name,
						      l_PayloadBench,
						      false,
						      0);
  G4RotationMatrix* Flip1 = new G4RotationMatrix ;
  Flip1->rotateX(180*deg);
  p_BenchHole1 = new G4PVPlacement(Flip1,
				   G4ThreeVector(143.335*cm,
						 97.405*cm,
						 0.*cm),
				   l_BenchHole1,
				   BenchHole1Name,
				   l_PayloadBench,
				   false,
				   1);
  // CCU2 - holes 
  const G4String BenchHole2Name = "BenchHole2Name" ;
  G4Box* s_BenchHole2 = new G4Box(BenchHole2Name,
				  53.835*cm, 5.825*cm, (10.5/2)*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole2 = new G4LogicalVolume(s_BenchHole2,
						      Material,
						      BenchHole2Name);
  G4VPhysicalVolume* p_BenchHole2 = new G4PVPlacement(0,
						      G4ThreeVector(88.335*cm,
								    -103.225*cm,
								    0.*cm),
						      l_BenchHole2,
						      BenchHole2Name,
						      l_PayloadBench,
						      false,
						      0);;
  p_BenchHole2 = new G4PVPlacement(Flip1,
				   G4ThreeVector(88.335*cm,
						 103.225*cm,
						 0.*cm),
				   l_BenchHole2,
				   BenchHole2Name,
				   l_PayloadBench,
				   false,
				   1);
  // CCU3 - holes 
  const G4String BenchHole3Name = "BenchHole3Name" ;
  G4Box* s_BenchHole3 = new G4Box(BenchHole3Name,
				  41.905*cm, 5.825*cm,(10.5/2)*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole3 = new G4LogicalVolume(s_BenchHole3,
						      Material,
						      BenchHole3Name);
  G4VPhysicalVolume* p_BenchHole3 = new G4PVPlacement(0,
						      G4ThreeVector(-102.595*cm,
								    -103.225*cm,
								    0.*cm),
						      l_BenchHole3,
						      BenchHole3Name,
						      l_PayloadBench,
						      false,
						      0);;
  p_BenchHole3 = new G4PVPlacement(Flip1,
				   G4ThreeVector(-102.595*cm,
						 103.225*cm,
						 0.*cm),
				   l_BenchHole3,
				   BenchHole3Name,
				   l_PayloadBench,
				   false,
				   1);
  // CCU4 - holes 
  const G4String BenchHole4Name = "BenchHole4Name" ;
  G4Trap* s_BenchHole4 = new G4Trap(BenchHole4Name,
				    5.25*cm,
				    0.*deg, 0.*deg,
				    13.33*cm,1.165*cm, 0.01*cm, 2.502*deg,
				    13.33*cm,1.165*cm, 0.01*cm, 2.502*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole4 = new G4LogicalVolume(s_BenchHole4,
						      Material,
						      BenchHole4Name);
  G4VPhysicalVolume* p_BenchHole4 = new G4PVPlacement(0,
						      G4ThreeVector(143.9175*cm,
								    72.43*cm,
								    0.*cm),
						      l_BenchHole4,
						      BenchHole4Name,
						      l_PayloadBench,
						      false,
						      0);;
  p_BenchHole4 = new G4PVPlacement(Flip1,
				   G4ThreeVector(143.9175*cm,
						 -72.43*cm,
						 0.*cm),
				   l_BenchHole4,
				   BenchHole4Name,
				   l_PayloadBench,
				   false,
				   1);
  // CCU5 - holes 
  const G4String BenchHole5Name = "BenchHole5Name" ;
  G4Trap* s_BenchHole5 = new G4Trap(BenchHole5Name,
				    5.25*cm,
				    0.*deg, 0.*deg,
				    5.82*cm,3.36*cm, 0.01*cm, 16.1*deg,
				    5.82*cm,3.36*cm, 0.01*cm, 16.1*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole5 = new G4LogicalVolume(s_BenchHole5,
						      Material,
						      BenchHole5Name);
  G4VPhysicalVolume* p_BenchHole5 = new G4PVPlacement(0,
						      G4ThreeVector(140.49*cm,
								    -91.58*cm,
								    0.*cm),
						      l_BenchHole5,
						      BenchHole5Name,
						      l_PayloadBench,
						      false,
						      0);;
  p_BenchHole5 = new G4PVPlacement(Flip1,
				   G4ThreeVector(140.49*cm,
						 91.58*cm,
						 0.*cm),
				   l_BenchHole5,
				   BenchHole5Name,
				   l_PayloadBench,
				   false,
				   1);

  // CCU6/7 - holes 
  const G4String BenchHole6Name = "BenchHole6Name" ;
  G4Trap* s_BenchHole6 = new G4Trap(BenchHole6Name,
				    5.25*cm,
				    0.*deg, 0.*deg,
				    5.825*cm,12.955*cm, 0.01*cm, 48.036*deg,
				    5.825*cm,12.955*cm, 0.01*cm, 48.036*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole6 = new G4LogicalVolume(s_BenchHole6,
						      Material,
						      BenchHole6Name);
  G4VPhysicalVolume* p_BenchHole6 = new G4PVPlacement(0,
						      G4ThreeVector(28.0225*cm,
								    -103.225*cm,
								    0.*cm),
						      l_BenchHole6,
						      BenchHole6Name,
						      l_PayloadBench,
						      false,
						      0);;
  p_BenchHole6 = new G4PVPlacement(Flip1,
				   G4ThreeVector(28.0225*cm,
						 103.225*cm,
						 0.*cm),
				   l_BenchHole6,
				   BenchHole6Name,
				   l_PayloadBench,
				   false,
				   1);
  G4RotationMatrix* Flip2 = new G4RotationMatrix ;
  Flip2->rotateY(180*deg);
  G4RotationMatrix* Rotate1 = new G4RotationMatrix ;
  Rotate1->rotateY(180*deg);
  Rotate1->rotateX(180*deg);
  p_BenchHole6 = new G4PVPlacement(Flip2,
				   G4ThreeVector(-54.215*cm,
						 -103.225*cm,
						 0.*cm),
				   l_BenchHole6,
				   BenchHole6Name,
				   l_PayloadBench,
				   false,
				   2);
  p_BenchHole6 = new G4PVPlacement(Rotate1,
				   G4ThreeVector(-54.215*cm,
						 103.225*cm,
						 0.*cm),
				   l_BenchHole6,
				   BenchHole6Name,
				   l_PayloadBench,
				   false,
				   3);

  // CCU8 - holes 
  const G4String BenchHole8Name = "BenchHole8Name" ;
  G4Trap* s_BenchHole8 = new G4Trap(BenchHole8Name,
				    5.25*cm,
				    0.*deg, 0.*deg,
				    21.2*cm,21.2*cm, 0.01*cm, 26.565*deg,
				    21.2*cm,21.2*cm, 0.01*cm, 26.565*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_BenchHole8 = new G4LogicalVolume(s_BenchHole8,
						      Material,
						      BenchHole8Name);
  G4VPhysicalVolume* p_BenchHole8 = new G4PVPlacement(Flip2,
						      G4ThreeVector(-133.9*cm,
								    -76.2*cm,
								    0.*cm),
						      l_BenchHole8,
						      BenchHole8Name,
						      l_PayloadBench,
						      false,
						      0);;
  p_BenchHole8 = new G4PVPlacement(Rotate1,
				   G4ThreeVector(-133.9*cm,
						 76.2*cm,
						 0.*cm),
				   l_BenchHole8,
				   BenchHole8Name,
				   l_PayloadBench,
				   false,
				   1);


  // CPUD - PDU box
  const G4String PDUBoxName = "PDUBoxName" ;
  G4Box* s_PDUBox = new G4Box(PDUBoxName,
			      15.*cm, 22.5*cm, 10.*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_PDUBox = new G4LogicalVolume(s_PDUBox,
						  Material,
						      PDUBoxName);
  G4VPhysicalVolume* p_PDUBox = new G4PVPlacement(0,
						  G4ThreeVector(64*cm,
								0.*cm,
								(64.15-10.5-10)*cm),
						  l_PDUBox,
						  PDUBoxName,
						  l_Spacecraft,
						  false,
						  0);

  // JDFE - JEMX DFEE
  const G4String JemxDFEEName = "JemxDFEEName" ;
  G4Box* s_JemxDFEE = new G4Box(JemxDFEEName,
				12.*cm, 12.*cm, 4.*cm);
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_JemxDFEE = new G4LogicalVolume(s_JemxDFEE,
						    Material,
						    JemxDFEEName);
  G4VPhysicalVolume* p_JemxDFEE = new G4PVPlacement(0,
						    G4ThreeVector(14.3*cm,
								  28.35*cm,
								  (64.15-4)*cm),
						    l_JemxDFEE,
						    JemxDFEEName,
						    l_Spacecraft,
						    false,
						    0);
  p_JemxDFEE = new G4PVPlacement(0,
				 G4ThreeVector(14.3*cm,
					       -28.35*cm,
					       (64.15-4)*cm),
				 l_JemxDFEE,
				 JemxDFEEName,
				 l_Spacecraft,
				 false,
				 1);

  // JDFE - JEMX DFEE electronics
  const G4String JemxDFEEelecName = "JemxDFEEelecName" ;
  G4Box* s_JemxDFEEelec = new G4Box(JemxDFEEelecName,
				11.6*cm, 11.6*cm, 3.6*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_JemxDFEEelec = new G4LogicalVolume(s_JemxDFEEelec,
							Material,
							JemxDFEEelecName);
  G4VPhysicalVolume* p_JemxDFEEelec = new G4PVPlacement(0,
							G4ThreeVector(0.,0.,0.),
							l_JemxDFEEelec,
							JemxDFEEelecName,
							l_JemxDFEE,
							false,
							0);

  // CSVM - The main part, the SVM 
  const G4String SpacecraftServiceModuleName = "SpacecraftServiceModuleName" ;
  G4Tubs* s_SpacecraftServiceModule = new G4Tubs(SpacecraftServiceModuleName,
						 0., 215*cm, (117.5/2)*cm, 0*deg, 360*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SpacecraftServiceModule = new G4LogicalVolume(s_SpacecraftServiceModule,
								   Material,
								   SpacecraftServiceModuleName);
  G4VPhysicalVolume* p_SpacecraftServiceModule = new G4PVPlacement(0,
								   G4ThreeVector(0.,0.,
										 (-64.15+(117.5/2))*cm),
								   l_SpacecraftServiceModule,
								   SpacecraftServiceModuleName,
								   l_Spacecraft,
								   false,
								   0);

 // CXPP - Top panel
  const G4String SVMPanel1Name = "SVMPanel1Name" ;
  G4Box* s_SVMPanel1 = new G4Box(SVMPanel1Name,
				 (312.4/2)*cm, (283.4/2)*cm, (1.5/2)*cm);
  Material =  PIMPSelectMaterial("AluminiumHoney1", Materials) ;
  G4LogicalVolume* l_SVMPanel1 = new G4LogicalVolume(s_SVMPanel1,
						     Material,
						     SVMPanel1Name);
  G4VPhysicalVolume* p_SVMPanel1 = new G4PVPlacement(0,
						     G4ThreeVector(0.,0.,
								   (-1.5/2+(117.5/2))*cm),
						     l_SVMPanel1,
						     SVMPanel1Name,
						     l_SpacecraftServiceModule,
						     false,
						     0);
  // CXPH - Hole in panel 
  const G4String SVMPanel1HoleName = "SVMPanel1HoleName" ;
  G4Tubs* s_SVMPanel1Hole = new G4Tubs(SVMPanel1HoleName,
				       0.*cm, (216.3/2)*cm, (1.5/2)*cm, 0., 360*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SVMPanel1Hole = new G4LogicalVolume(s_SVMPanel1Hole,
							 Material,
							 SVMPanel1HoleName);
  G4VPhysicalVolume* p_SVMPanel1Hole = new G4PVPlacement(0,
							 G4ThreeVector(0.,0.,0.),
							 l_SVMPanel1Hole,
							 SVMPanel1HoleName,
							 l_SVMPanel1,
							 false,
							 0);
  
  // CXMP - Bottom panel
  const G4String SVMPanel2Name = "SVMPanel2Name" ;
  G4Box* s_SVMPanel2 = new G4Box(SVMPanel2Name,
				 (312.4/2)*cm, (283.4/2)*cm, (1.5/2)*cm);
  Material =  PIMPSelectMaterial("AluminiumHoney1", Materials) ;
  G4LogicalVolume* l_SVMPanel2 = new G4LogicalVolume(s_SVMPanel2,
						     Material,
						     SVMPanel2Name);
  G4VPhysicalVolume* p_SVMPanel2 = new G4PVPlacement(0,
						     G4ThreeVector(0.,0.,
								   (117.5/2.-110.4+1.5/2.)*cm),
						     l_SVMPanel2,
						     SVMPanel2Name,
						     l_SpacecraftServiceModule,
						     false,
						     0);

  // CXMH - Hole in panel 
  const G4String SVMPanel2HoleName = "SVMPanel2HoleName" ;
  G4Tubs* s_SVMPanel2Hole = new G4Tubs(SVMPanel2HoleName,
				       0.*cm, (216.3/2)*cm, (1.5/2)*cm, 0., 360*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_SVMPanel2Hole = new G4LogicalVolume(s_SVMPanel2Hole,
							 Material,
							 SVMPanel2HoleName);
  G4VPhysicalVolume* p_SVMPanel2Hole = new G4PVPlacement(0,
							 G4ThreeVector(0.,0.,0.),
							 l_SVMPanel2Hole,
							 SVMPanel2HoleName,
							 l_SVMPanel2,
							 false,
							 0);
  
  // CCUT - triangle cut offs 
  const G4String PanelCutoffsName = "PanelCutoffsName" ;
  G4Trap* s_PanelCutoffs = new G4Trap(PanelCutoffsName,
				      0.75*cm,
				      0.*deg, 0.*deg,
				      29.5*cm,34.*cm, 0.001*cm, 29.95*deg,
				      29.5*cm,34.*cm, 0.001*cm, 29.95*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_PanelCutoffs = new G4LogicalVolume(s_PanelCutoffs,
							Material,
							PanelCutoffsName);
  G4VPhysicalVolume* p_PanelCutoffs ;
  G4RotationMatrix* Rotate2 = new G4RotationMatrix ;
  Rotate2->rotateY(180*deg);
  Rotate2->rotateZ(90*deg);
  G4RotationMatrix* Rotate3 = new G4RotationMatrix ;
  Rotate3->rotateZ(90*deg);
  G4RotationMatrix* Rotate4 = new G4RotationMatrix ;
  Rotate4->rotateZ(-90*deg);
  G4RotationMatrix* Rotate5 = new G4RotationMatrix ;
  Rotate5->rotateX(180*deg);
  Rotate5->rotateZ(90*deg);

  p_PanelCutoffs = new G4PVPlacement(Rotate2,G4ThreeVector(126.75*cm,
							   -125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel2,  false,  0);
  p_PanelCutoffs = new G4PVPlacement(Rotate2,G4ThreeVector(126.75*cm,
							   -125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel1,  false,  1);
  p_PanelCutoffs = new G4PVPlacement(Rotate3,G4ThreeVector(-126.75*cm,
							   -125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel2,  false,  2);
  p_PanelCutoffs = new G4PVPlacement(Rotate3,G4ThreeVector(-126.75*cm,
							   -125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel1,  false,  3);
  p_PanelCutoffs = new G4PVPlacement(Rotate4,G4ThreeVector(126.75*cm,
							   125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel2,  false,  4);
  p_PanelCutoffs = new G4PVPlacement(Rotate4,G4ThreeVector(126.75*cm,
							   125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel1,  false,  5);	
  p_PanelCutoffs = new G4PVPlacement(Rotate5,G4ThreeVector(-126.75*cm,
							   125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel2,  false,  6);
  p_PanelCutoffs = new G4PVPlacement(Rotate5,G4ThreeVector(-126.75*cm,
							   125.5*cm,
							   0.*cm),
				     l_PanelCutoffs, PanelCutoffsName,
				     l_SVMPanel1,  false,  7);    

  // CCPA - Corner diagonal panel
  const G4String SVMPanel3Name = "SVMPanel3Name" ;
  G4Box* s_SVMPanel3 = new G4Box(SVMPanel3Name,
				 44.695*cm, 0.5 *cm, 53.7 *cm);
  Material =  PIMPSelectMaterial("AluminiumHoney4", Materials) ;
  G4LogicalVolume* l_SVMPanel3 = new G4LogicalVolume(s_SVMPanel3,
						     Material,
						     SVMPanel3Name);

  G4RotationMatrix* Rotate6 = new G4RotationMatrix ;
  Rotate6->rotateZ(49.*deg);
  G4RotationMatrix* Rotate7 = new G4RotationMatrix ;
  Rotate7->rotateZ(311.*deg);
  G4VPhysicalVolume* p_SVMPanel3 = new G4PVPlacement(Rotate7,
						     G4ThreeVector(126.725*cm,
								   -108.1*cm,
								   3.55*cm),
						     l_SVMPanel3,
						     SVMPanel3Name,
						     l_SpacecraftServiceModule,
						     false,
						     0);
  p_SVMPanel3 = new G4PVPlacement(Rotate6,
				  G4ThreeVector(-126.725*cm,
						-108.1*cm,
						3.55*cm),
				  l_SVMPanel3,
				  SVMPanel3Name,
				  l_SpacecraftServiceModule,
				  false,
				  1);
  p_SVMPanel3 = new G4PVPlacement(Rotate7,
				  G4ThreeVector(-126.725*cm,
						108.1*cm,
						3.55*cm),
				  l_SVMPanel3,
				  SVMPanel3Name,
				  l_SpacecraftServiceModule,
				  false,
				  2);
  p_SVMPanel3 = new G4PVPlacement(Rotate6,
				  G4ThreeVector(126.725*cm,
						108.1*cm,
						3.55*cm),
				  l_SVMPanel3,
				  SVMPanel3Name,
				  l_SpacecraftServiceModule,
				  false,
				  3);
  
  // CTHR - Aluminium thrust cone
  const G4String ThrustConeName = "ThrustConeName" ;
  G4Cons* s_ThrustCone = new G4Cons(ThrustConeName,
				    (263.4/2 -1)*cm,(263.4/2)*cm,
				    (216.1/2 -1)*cm,(216.1/2)*cm,  
				    (117.5/2)*cm,
				    0*deg, 360*deg);
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_ThrustCone = new G4LogicalVolume(s_ThrustCone,
						      Material,
						      ThrustConeName);
  G4VPhysicalVolume* p_ThrustCone = new G4PVPlacement(0,
						      G4ThreeVector(0.,0.,0.),
						      l_ThrustCone,
						      ThrustConeName,
						      l_SpacecraftServiceModule,
						      false,
						      0);
  
  // CZPA - side panels
  const G4String SidePanelName = "SidePanelName" ;
  G4Box* s_SidePanel = new G4Box(SidePanelName,
				 2.*cm, (149/2)*cm, (110.4-1)/2 * cm); 
  Material =  PIMPSelectMaterial("AluminiumHoney4", Materials) ;
  G4LogicalVolume* l_SidePanel = new G4LogicalVolume(s_SidePanel,
						     Material,
						     SidePanelName);
  G4VPhysicalVolume* p_SidePanel = new G4PVPlacement(0,
						     G4ThreeVector(((312.4/2)-2)*cm,
								   0.,
								   (117.5/2 - 110.4/2)*cm),
						     l_SidePanel,
						     SidePanelName,
						     l_SpacecraftServiceModule,
						     false,
						     0);
  p_SidePanel = new G4PVPlacement(0,
				  G4ThreeVector(-1.0*((312.4/2)-2)*cm,
						0.,
						(117.5/2 - 110.4/2)*cm),
				  l_SidePanel,
				  SidePanelName,
				  l_SpacecraftServiceModule,
				  false,
				  0);
  
  // CPZE - eleccy box
  const G4String LeccyBoxName = "LeccyBox" ;
  G4Box* s_LeccyBox = new G4Box(LeccyBoxName,
				10.*cm, 74.5*cm, 53.7*cm); 
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_LeccyBox = new G4LogicalVolume(s_LeccyBox,
						    Material,
						    LeccyBoxName);
  G4VPhysicalVolume* p_LeccyBox = new G4PVPlacement(0,
						    G4ThreeVector((312.4/2-4-10)*cm,
								  0.*cm,
								  (117.5/2-55.2)*cm),
						    l_LeccyBox,
						    LeccyBoxName,
						    l_SpacecraftServiceModule,
						    false,
						    0);

  // CMZE -Electronics box that incorporates the reaction wheels
  const G4String LeccyBox1Name = "LeccyBox1" ;
  G4Trap* s_LeccyBox1 = new G4Trap(LeccyBox1Name,
				   53.7*cm,
				   5.18*deg,0*deg,
				   74.5*cm,10*cm,10*cm,0*deg,
				   74.5*cm,20*cm,20*cm,0*deg);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_LeccyBox1 = new G4LogicalVolume(s_LeccyBox1,
						     Material,
						     LeccyBox1Name);
  G4VPhysicalVolume* p_LeccyBox1 = new G4PVPlacement(0,
						     G4ThreeVector((-312.4/2+4+15)*cm,
								   0.*cm,
								   (117.5/2-55.2)*cm),
						     l_LeccyBox1,
						     LeccyBox1Name,
						     l_SpacecraftServiceModule,
						     false,
						     0);
  

  // CFSM/CFSE- Electronics
  const G4String SomeLeccy1Name = "SomeLeccy1" ;
  G4Box* s_SomeLeccy1 = new G4Box(SomeLeccy1Name,
				 3.175*cm, 6.35*cm, 8.095*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy1 = new G4LogicalVolume(s_SomeLeccy1,
						     Material,
						     SomeLeccy1Name);
  G4VPhysicalVolume* p_SomeLeccy1 = new G4PVPlacement(0,
						     G4ThreeVector(6.825*cm,
								   48.15*cm,
								   -8.945*cm),
						     l_SomeLeccy1,
						     SomeLeccy1Name,
						     l_LeccyBox,
						     false,
						     0);
  p_SomeLeccy1 = new G4PVPlacement(0,
				   G4ThreeVector(6.825*cm,
						 48.15*cm,
						 31.755*cm),
				   l_SomeLeccy1,
				   SomeLeccy1Name,
				   l_LeccyBox,
				   false,
				   1);

  // CACM / CACE - Electronics
  const G4String SomeLeccy2Name = "SomeLeccy2" ;
  G4Box* s_SomeLeccy2 = new G4Box(SomeLeccy2Name,
				  7.75*cm, 9.35*cm, 13.505*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy2 = new G4LogicalVolume(s_SomeLeccy2,
						      Material,
						      SomeLeccy2Name);
  G4VPhysicalVolume* p_SomeLeccy2 = new G4PVPlacement(0,
						      G4ThreeVector(2.25*cm,
								    -45.35*cm,
								    31.905*cm),
						      l_SomeLeccy2,
						      SomeLeccy2Name,
						      l_LeccyBox,
						      false,
						      0);
  
  // CAEM / CAEE - control and actuator electronics
  const G4String SomeLeccy3Name = "SomeLeccy3" ;
  G4Box* s_SomeLeccy3 = new G4Box(SomeLeccy3Name,
				  10*cm, 12.5*cm, 12.71*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy3 = new G4LogicalVolume(s_SomeLeccy3,
						      Material,
						      SomeLeccy3Name);
  G4VPhysicalVolume* p_SomeLeccy3 = new G4PVPlacement(0,
						      G4ThreeVector(0*cm,
								    -41.5*cm,
								    0.89*cm),
						      l_SomeLeccy3,
						      SomeLeccy3Name,
						      l_LeccyBox,
						      false,
						      0);

  // CNCB - Yet more elctronics 
  const G4String SomeLeccy4Name = "SomeLeccy4" ;
  G4Box* s_SomeLeccy4 = new G4Box(SomeLeccy4Name,
				  6.5*cm, 26.8*cm, 9.75*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy4 = new G4LogicalVolume(s_SomeLeccy4,
						      Material,
						      SomeLeccy4Name);
  G4VPhysicalVolume* p_SomeLeccy4 = new G4PVPlacement(0,
						      G4ThreeVector(3.42*cm,
								    28.875*cm,
								    -34.2*cm),
						      l_SomeLeccy4,
						      SomeLeccy4Name,
						      l_LeccyBox,
						      false,
						      0);
  p_SomeLeccy4 = new G4PVPlacement(0,
				   G4ThreeVector(3.42*cm,
						 -28.875*cm,
						 -34.2*cm),
				   l_SomeLeccy4,
				   SomeLeccy4Name,
				   l_LeccyBox,
				   false,
				   1);

  G4RotationMatrix* Rotate8 = new G4RotationMatrix ;
  Rotate8->rotateX(90*deg);
  Rotate8->rotateY(45*deg);

  // CRWM 
  const G4String ReactionTubeName = "ReactionTube" ;
  G4Tubs* s_ReactionTube = new G4Tubs(ReactionTubeName,
				  0.*cm, 18.25*cm, 5.25*cm, 0.*deg, 360*deg);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_ReactionTube = new G4LogicalVolume(s_ReactionTube,
						      Material,
						      ReactionTubeName);
  G4VPhysicalVolume* p_ReactionTube = new G4PVPlacement(Rotate8,
							  G4ThreeVector((3.75)*cm,
									(17.216)*cm,
									32.876*cm),
							  l_ReactionTube,
							  ReactionTubeName,
							  l_LeccyBox1,
							  false,
							  0);
  p_ReactionTube = new G4PVPlacement(Rotate8,
				       G4ThreeVector((3.)*cm,
						     (-52.857)*cm,
						     32.7*cm),
				       l_ReactionTube,
				       ReactionTubeName,
				       l_LeccyBox1,
				       false,
				       1);
   p_ReactionTube = new G4PVPlacement(Rotate8,
				       G4ThreeVector((3.75)*cm,
						     (-21.369)*cm,
						     32.523*cm),
				       l_ReactionTube,
				       ReactionTubeName,
				       l_LeccyBox1,
				       false,
				       2);
   p_ReactionTube = new G4PVPlacement(Rotate8,
					G4ThreeVector((3.)*cm,
						      (52.857)*cm,
						      32.7*cm),
					l_ReactionTube,
					ReactionTubeName,
					l_LeccyBox1,
					false,
					3);


  // CRWS - The Reaction Wheel
  const G4String ReactionSphereName = "ReactionSphere" ;
  G4Sphere* s_ReactionSphere = new G4Sphere(ReactionSphereName,
					    0,17.55*cm,
					    0,180.*deg,
					    0,360*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_ReactionSphere = new G4LogicalVolume(s_ReactionSphere,
							  Material,
							  ReactionSphereName);
   G4RotationMatrix* Rotate9 = new G4RotationMatrix ;
  Rotate9->rotateX(90*deg);
  Rotate9->rotateY(-45*deg);

  G4VPhysicalVolume* p_ReactionSphere = new G4PVPlacement(Rotate9,
							  G4ThreeVector((3.75+3)*cm,
									(17.216-3)*cm,
									32.876*cm),
							  l_ReactionSphere,
							  ReactionSphereName,
							  l_LeccyBox1,
							  false,
							  0);
  p_ReactionSphere = new G4PVPlacement(Rotate9,
				       G4ThreeVector((3.+3)*cm,
						     (-52.857-3)*cm,
						     32.7*cm),
				       l_ReactionSphere,
				       ReactionSphereName,
				       l_LeccyBox1,
				       false,
				       1);
   p_ReactionSphere = new G4PVPlacement(Rotate9,
				       G4ThreeVector((3.75+3)*cm,
						     (-21.369-3)*cm,
						     32.523*cm),
				       l_ReactionSphere,
				       ReactionSphereName,
				       l_LeccyBox1,
				       false,
				       2);
   p_ReactionSphere = new G4PVPlacement(Rotate9,
					G4ThreeVector((3.+3)*cm,
						      (52.857-3)*cm,
						      32.7*cm),
					l_ReactionSphere,
					ReactionSphereName,
					l_LeccyBox1,
					false,
					3);

  // CWDM / CWDE - Electronics
  const G4String SomeLeccy5Name = "SomeLeccy5" ;
  G4Box* s_SomeLeccy5 = new G4Box(SomeLeccy5Name,
				  6.25*cm, 11.2*cm, 16.3*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy5 = new G4LogicalVolume(s_SomeLeccy5,
						      Material,
						      SomeLeccy5Name);
  G4VPhysicalVolume* p_SomeLeccy5 = new G4PVPlacement(0,
						      G4ThreeVector(-8.75*cm,
								    43.9*cm,
								    -29.05*cm),
						      l_SomeLeccy5,
						      SomeLeccy5Name,
						      l_LeccyBox1,
						      false,
						      0);
  // CDMU - Electronics
  const G4String SomeLeccy6Name = "SomeLeccy6" ;
  G4Box* s_SomeLeccy6 = new G4Box(SomeLeccy6Name,
				  10.35*cm, 14.*cm, 17.3*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy6 = new G4LogicalVolume(s_SomeLeccy6,
						      Material,
						      SomeLeccy6Name);
  G4VPhysicalVolume* p_SomeLeccy6 = new G4PVPlacement(0,
						      G4ThreeVector(-4.57*cm,
								    -49.6*cm,
								    -32.7*cm),
						      l_SomeLeccy6,
						      SomeLeccy6Name,
						      l_LeccyBox1,
						      false,
						      0);

  // CYPA - Side panels
  const G4String SidePanel1Name = "SidePanel1" ;
  G4Box* s_SidePanel1 = new G4Box(SidePanel1Name,
				  (194.5/2)*cm, 2*cm, ((110.4-3)/2.)*cm);
  Material =  PIMPSelectMaterial("AluminiumHoney4", Materials) ;
  G4LogicalVolume* l_SidePanel1 = new G4LogicalVolume(s_SidePanel1,
						      Material,
						      SidePanel1Name);
  G4VPhysicalVolume* p_SidePanel1 = new G4PVPlacement(0,
						      G4ThreeVector(0.*cm,
								    (283.4/2-2)*cm,
								    (117.5/2 - 110.4/2)*cm),
						      l_SidePanel1,
						      SidePanel1Name,
						      l_SpacecraftServiceModule,
						      false,
						      0);
  p_SidePanel1 = new G4PVPlacement(0,
				   G4ThreeVector(0.*cm,(-283.4/2+2)*cm,
						 (117.5/2 - 110.4/2)*cm),
				   l_SidePanel1,
				   SidePanel1Name,
				   l_SpacecraftServiceModule,
				   false,
				   1);


  // CPYE and CMYE - More electronics boxes
  const G4String LeccyBox3Name = "LeccyBox3" ;
  G4Box* s_LeccyBox3 = new G4Box(LeccyBox3Name,
				 85.*cm, 15.*cm, 53.5*cm);
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_LeccyBox3 = new G4LogicalVolume(s_LeccyBox3,
						     Material,
						     LeccyBox3Name);
  G4LogicalVolume* l_LeccyBox4 = new G4LogicalVolume(s_LeccyBox3,
						     Material,
						     LeccyBox3Name);

  G4VPhysicalVolume* p_LeccyBox3 = new G4PVPlacement(0,
						     G4ThreeVector(0.*cm,
								   (283.4/2-4-15)*cm,
								   (117.5/2 - 55.2)*cm),
						     l_LeccyBox3,
						     LeccyBox3Name,
						     l_SpacecraftServiceModule,
						     false,
						     0);
 
  G4VPhysicalVolume* p_LeccyBox4 = new G4PVPlacement(0,
						     G4ThreeVector(0.*cm,
								   -1.0*(283.4/2-4-15)*cm,
								   (117.5/2 - 55.2)*cm),
						     l_LeccyBox4,
						     LeccyBox3Name,
						     l_SpacecraftServiceModule,
						     false,
						     0);

  // CFDM / CFDE
  const G4String SomeLeccy7Name = "SomeLeccy7" ;
  G4Box* s_SomeLeccy7 = new G4Box(SomeLeccy7Name,
				  12.35*cm, 10.45*cm, 12.8*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy7 = new G4LogicalVolume(s_SomeLeccy7,
						      Material,
						      SomeLeccy7Name);
  G4VPhysicalVolume* p_SomeLeccy7 = new G4PVPlacement(0,
						      G4ThreeVector(-64.825*cm,
								    -4.55*cm,
								    30.4*cm),
						      l_SomeLeccy7,
						      SomeLeccy7Name,
						      l_LeccyBox3,
						      false,
						      0);

  // CRTM / CRTE - more leccy
  const G4String SomeLeccy8Name = "SomeLeccy8" ;
  G4Box* s_SomeLeccy8 = new G4Box(SomeLeccy8Name,
				  13.*cm, 10.5*cm, 12.5*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy8 = new G4LogicalVolume(s_SomeLeccy8,
						      Material,
						      SomeLeccy8Name);
  G4VPhysicalVolume* p_SomeLeccy8 = new G4PVPlacement(0,
						      G4ThreeVector(61.5*cm,
								    -4.5*cm,
								    29.4*cm),
						      l_SomeLeccy8,
						      SomeLeccy8Name,
						      l_LeccyBox3,
						      false,
						      0);
 
  // CSTM / CSTE - more leccy
  const G4String SomeLeccy9Name = "SomeLeccy9" ;
  G4Box* s_SomeLeccy9 = new G4Box(SomeLeccy9Name,
				  10.5*cm, 6.475*cm, 12.2*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy9 = new G4LogicalVolume(s_SomeLeccy9,
						      Material,
						      SomeLeccy9Name);
  G4VPhysicalVolume* p_SomeLeccy9 = new G4PVPlacement(0,
						      G4ThreeVector(-66.6*cm,
								    -8.525*cm,
								    -33.35*cm),
						      l_SomeLeccy9,
						      SomeLeccy9Name,
						      l_LeccyBox3,
						      false,
						      0);
  p_SomeLeccy9 = new G4PVPlacement(0,
				   G4ThreeVector(-66.6*cm,
						 -8.525*cm,
						 0.35*cm),
				   l_SomeLeccy9,
				   SomeLeccy9Name,
				   l_LeccyBox3,
				   false,
				   1);

  // CIMM and the rest ...
  const G4String SomeLeccy10Name = "SomeLeccy10" ;
  G4Box* s_SomeLeccy10 = new G4Box(SomeLeccy10Name,
				   14.05*cm, 5.655*cm, 16.55*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy10 = new G4LogicalVolume(s_SomeLeccy10,
						       Material,
						       SomeLeccy10Name);
  G4VPhysicalVolume* p_SomeLeccy10 = new G4PVPlacement(0,
						       G4ThreeVector(22.25*cm,
								     -9.265*cm,
								     -19.75*cm),
						       l_SomeLeccy10,
						       SomeLeccy10Name,
						       l_LeccyBox3,
						       false,
						       0);
  // CPRU and the rest ...
  const G4String SomeLeccy11Name = "SomeLeccy11" ;
  G4Box* s_SomeLeccy11 = new G4Box(SomeLeccy11Name,
				   13.8*cm, 6.5*cm, 12.2*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy11 = new G4LogicalVolume(s_SomeLeccy11,
						       Material,
						       SomeLeccy11Name);
  G4VPhysicalVolume* p_SomeLeccy11 = new G4PVPlacement(0,
						       G4ThreeVector(59.3*cm,
								     -8.42*cm,
								     -7.5*cm),
						       l_SomeLeccy11,
						       SomeLeccy11Name,
						       l_LeccyBox3,
						       false,
						       0);

  // CPDS
  const G4String SomeLeccy12Name = "SomeLeccy12" ;
  G4Box* s_SomeLeccy12 = new G4Box(SomeLeccy12Name,
				   15.435*cm,9.749*cm,22.748*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy12 = new G4LogicalVolume(s_SomeLeccy12,
						       Material,
						       SomeLeccy12Name);
  G4VPhysicalVolume* p_SomeLeccy12 = new G4PVPlacement(0,
						       G4ThreeVector(-63.565*cm,
								     5.171*cm,
								     -15.552*cm),
						       l_SomeLeccy12,
						       SomeLeccy12Name,
						       l_LeccyBox4,
						       false,
						       0);

  // CMRS
  const G4String SomeLeccy13Name = "SomeLeccy13" ;
  G4Box* s_SomeLeccy13 = new G4Box(SomeLeccy13Name,
				   28.435*cm, 7.312*cm, 25.9975*cm);
  Material =  PIMPSelectMaterial("ElectroMix", Materials) ;
  G4LogicalVolume* l_SomeLeccy13 = new G4LogicalVolume(s_SomeLeccy13,
						       Material,
						       SomeLeccy13Name);
  G4VPhysicalVolume* p_SomeLeccy13 = new G4PVPlacement(0,
						       G4ThreeVector(52.435*cm,
								     7.608*cm,
								     19.9975*cm),
						       l_SomeLeccy13,
						       SomeLeccy13Name,
						       l_LeccyBox4,
						       false,
						       0);
  /*
  // CFT1
  const G4String FuelTankStrapName = "FuelTankStrap" ;
  G4Tubs* s_FuelTankStrap = new G4Tubs(FuelTankStrapName,
				  31.131*cm, 32.131*cm, 6.8*cm, 49., 180*deg);
  Material =  PIMPSelectMaterial("Titanium", Materials) ;
  G4LogicalVolume* l_FuelTankStrap = new G4LogicalVolume(s_FuelTankStrap,
						    Material,
						    FuelTankStrapName);
  G4VPhysicalVolume* p_FuelTankStrap = new G4PVPlacement(0,
						    G4ThreeVector(127.075*cm,
								  108.45*cm,
								  19.19*cm),
						    l_FuelTankStrap,
						    FuelTankStrapName,
						    l_SpacecraftServiceModule,
						    false,
						    0);
  */
  
  // CFT2
  const G4String FuelTankName = "FuelTank" ;
  G4Sphere* s_FuelTank = new G4Sphere(FuelTankName,
				      0.*cm, 32.131*cm,
				      311*deg, 180*deg, 0., 360*deg);
  Material =  PIMPSelectMaterial("Titanium", Materials) ;
  G4LogicalVolume* l_FuelTank = new G4LogicalVolume(s_FuelTank,
						    Material,
						    FuelTankName);
  
  G4RotationMatrix* FlipFuel1 = new G4RotationMatrix ;
  FlipFuel1->rotateY(180*deg);
  G4RotationMatrix* FlipFuel2 = new G4RotationMatrix ;
  FlipFuel2->rotateX(180*deg);
  G4RotationMatrix* FlipFuel3 = new G4RotationMatrix ;
  FlipFuel3->rotateY(180*deg);
  FlipFuel3->rotateX(180*deg);


  G4VPhysicalVolume* p_FuelTank = new G4PVPlacement(0,
						    G4ThreeVector(127.075*cm,
								  108.45*cm,
								  19.19*cm),
						    l_FuelTank,
						    FuelTankName,
						    l_SpacecraftServiceModule,
						    false,
						    0);
  p_FuelTank = new G4PVPlacement(FlipFuel1,
				 G4ThreeVector(-127.075*cm,
					       108.45*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 1);
  p_FuelTank = new G4PVPlacement(FlipFuel2,
				 G4ThreeVector(127.075*cm,
					       -108.45*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 2);
  p_FuelTank = new G4PVPlacement(FlipFuel3,
				 G4ThreeVector(-127.075*cm,
					       -108.45*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 3);
  
  p_FuelTank = new G4PVPlacement(FlipFuel3,
				 G4ThreeVector(126.415*cm,
					       107.79*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 0);
  p_FuelTank = new G4PVPlacement(FlipFuel2,
				 G4ThreeVector(-126.415*cm,
					       107.79*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 1);
  p_FuelTank = new G4PVPlacement(FlipFuel1,
				 G4ThreeVector(126.415*cm,
					       -107.79*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 2);
  p_FuelTank = new G4PVPlacement(0,
				 G4ThreeVector(-126.415*cm,
					       -107.79*cm,
					       19.19*cm),
				 l_FuelTank,
				 FuelTankName,
				 l_SpacecraftServiceModule,
				 false,
				 3);




  // CFT2 - fuel
  const G4String FuelName = "Fuel" ;
  G4Sphere* s_Fuel = new G4Sphere(FuelName,
				  0.*cm, 31.131*cm,
				  311*deg, 180*deg, 0., 360*deg);
  Material =  PIMPSelectMaterial("Fuel", Materials) ;
  G4LogicalVolume* l_Fuel = new G4LogicalVolume(s_Fuel,
						Material,
						FuelName);
  G4VPhysicalVolume* p_Fuel = new G4PVPlacement(0,
						G4ThreeVector(0.,0.,0.),
						l_Fuel,
						FuelName,
						l_FuelTank,
						false,
						0);
  
  
  

  // ------------------- VISUALISATION -----------------------

  // l_PayloadBench->SetVisAttributes(Purple);


}

PIMPGeomSpacecraft::~PIMPGeomSpacecraft()
{;}

void PIMPGeomSpacecraft::Create(const G4MaterialTable* Materials, 
			    G4LogicalVolume* Parent, 
			    const G4ThreeVector* Position, 
			    G4RotationMatrix* Rotation)
{  

  // Create Spacecraft Mother volume 
  
  const G4String Name = "Spacecraft" ;
  G4VPhysicalVolume* p_Spacecraft = new G4PVPlacement(Rotation,
						      *Position,
						      l_Spacecraft,
						      Name,
						      Parent,
						      false,
						      0);	

  
  // ------------------- VISUALISATION -----------------------
  
  /// l_Spacecraft->SetVisAttributes(Purple);
  // l_Spacecraft->SetVisAttributes (G4VisAttributes::Invisible);
  
  return ;
}













