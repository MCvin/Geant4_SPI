// ------------------------------------------------------------------
// PIMPGeometry - JEMX
// ------------------------------------------------------------------

#include "PIMPGeomJEMX.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trap.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
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

#include "PIMPGeomJemxCollimator.hh" 
// #include "G4VPhysicalVolume.hh"
#include <stdio.h>
using namespace std;

PIMPGeomJEMX::PIMPGeomJEMX(const G4MaterialTable* Materials)
{
  const G4String Name = "JEMX";
  G4Box* s_JEMX = new G4Box(Name,29.9*cm,59.1*cm,177.5*cm);  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_JEMX = new G4LogicalVolume(s_JEMX,
			       Material,
			       Name);
  
  // -------  Mask ----------
  const G4String JMaskName = "JMask"; // JMSK
  G4Box* s_JMask = new G4Box(JMaskName,28.25*cm,28.25*cm,5.5*cm);  
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_JMask = new G4LogicalVolume(s_JMask,
						 Material,
						 JMaskName);
  G4VPhysicalVolume* p_JMask = new G4PVPlacement(0,
						 G4ThreeVector(1.*cm,28.35*cm,172.*cm),
						 l_JMask,
						 JMaskName,
						 l_JEMX,
						 false,
						 0);
  p_JMask = new G4PVPlacement(0,
			      G4ThreeVector(1.*cm,-28.35*cm,172.*cm),
			      l_JMask,
			      JMaskName,
			      l_JEMX,
			      false,
			      1);
  const G4String JMaskSuppStructName = "JMaskSuppStruct"; // JMRG
  G4Tubs* s_JMaskSuppStruct = new G4Tubs(JMaskSuppStructName,12.9*cm,13.1*cm,1.975*cm, 0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Tungsten", Materials) ;
  G4LogicalVolume* l_JMaskSuppStruct = new G4LogicalVolume(s_JMaskSuppStruct,
							   Material,
							   JMaskSuppStructName);
  G4VPhysicalVolume* p_JMaskSuppStruct = new G4PVPlacement(0,
							   G4ThreeVector(0.,0.,-2.025*cm),
							   l_JMaskSuppStruct,
							   JMaskSuppStructName,
							   l_JMask,
							   false,
							   0); 
  p_JMaskSuppStruct = new G4PVPlacement(0,
					G4ThreeVector(0.,0.,2.025*cm),
					l_JMaskSuppStruct,
					JMaskSuppStructName,
					l_JMask,
					false,
					0);

  const G4String JMaskSuppStrutName = "JMaskSuppStrut"; // JMSU
  G4Trap* s_JMaskSuppStrut = new G4Trap(JMaskSuppStrutName,
					0.1*cm,
					0.*deg, 0.*deg,
					6.825*cm, 1.975*cm, 1.325*cm,
					2.720161*deg,
					6.825*cm, 1.975*cm, 1.325*cm,
					2.720161*deg) ;
  Material =  PIMPSelectMaterial("Tungsten", Materials) ;
  G4LogicalVolume* l_JMaskSuppStrut = new G4LogicalVolume(s_JMaskSuppStrut,
							  Material,
							  JMaskSuppStrutName);
  G4RotationMatrix* RotateStrut0 = new G4RotationMatrix ;
  RotateStrut0->rotateY(90.*deg) ;
  G4VPhysicalVolume* p_JMaskSuppStrut = new G4PVPlacement(RotateStrut0,
							  G4ThreeVector(0., 19.925*cm, -1.675*cm),
							  l_JMaskSuppStrut,
							  JMaskSuppStrutName,
							  l_JMask,
							  false,
							  0);  
  G4RotationMatrix* RotateStrut1 = new G4RotationMatrix ;
  RotateStrut1->rotateY(90.*deg) ;
  RotateStrut1->rotateX(60.*deg) ;
  p_JMaskSuppStrut = new G4PVPlacement(RotateStrut1,
				       G4ThreeVector(sin(pi/3.)*19.925*cm, 
						     cos(pi/3.)*19.925*cm, -1.675*cm),
				       l_JMaskSuppStrut,
				       JMaskSuppStrutName,
				       l_JMask,
				       false,
				       1);  
  G4RotationMatrix* RotateStrut2 = new G4RotationMatrix ;
  RotateStrut2->rotateY(90.*deg) ;
  RotateStrut2->rotateX(120.*deg) ;
  p_JMaskSuppStrut = new G4PVPlacement(RotateStrut2,
				       G4ThreeVector(sin(pi/3.)*19.925*cm, 
						     -1.0*cos(pi/3.)*19.925*cm, -1.675*cm),
				       l_JMaskSuppStrut,
				       JMaskSuppStrutName,
				       l_JMask,
				       false,
				       2);  
  G4RotationMatrix* RotateStrut3 = new G4RotationMatrix ;
  RotateStrut3->rotateY(90.*deg) ;
  RotateStrut3->rotateX(180.*deg) ;  
  p_JMaskSuppStrut = new G4PVPlacement(RotateStrut3,
				       G4ThreeVector(0., 
						     -19.925*cm, -1.675*cm),
				       l_JMaskSuppStrut,
				       JMaskSuppStrutName,
				       l_JMask,
				       false,
				       3);  
  G4RotationMatrix* RotateStrut4 = new G4RotationMatrix ;
  RotateStrut4->rotateY(90.*deg) ;
  RotateStrut4->rotateX(-120.*deg) ;
  p_JMaskSuppStrut = new G4PVPlacement(RotateStrut4,
				       G4ThreeVector(-1.*sin(pi/3.)*19.925*cm, 
						     -1.*cos(pi/3.)*19.925*cm, -1.675*cm),
				       l_JMaskSuppStrut,
				       JMaskSuppStrutName,
				       l_JMask,
				       false,
				       4);  
  G4RotationMatrix* RotateStrut5 = new G4RotationMatrix ;
  RotateStrut5->rotateY(90.*deg) ;
  RotateStrut5->rotateX(-60.*deg) ;
  p_JMaskSuppStrut = new G4PVPlacement(RotateStrut5,
				       G4ThreeVector(-1.*sin(pi/3.)*19.925*cm, 
						     cos(pi/3.)*19.925*cm, -1.675*cm),
				       l_JMaskSuppStrut,
				       JMaskSuppStrutName,
				       l_JMask,
				       false,
				       5);  
  const G4String JMaskSuppStrutAName = "JMaskSuppStrutA"; // JMSL
  G4Trap* s_JMaskSuppStrutA = new G4Trap(JMaskSuppStrutAName,
					 0.1*cm,
					 0.*deg, 0.*deg,
					 6.825*cm,1.975*cm,1.325*cm,
					 2.720161*deg,
					 6.825*cm,1.975*cm,1.325*cm,
					 2.720161*deg) ;
  Material =  PIMPSelectMaterial("Tungsten", Materials) ;
  G4LogicalVolume* l_JMaskSuppStrutA = new G4LogicalVolume(s_JMaskSuppStrutA,
							   Material,
							   JMaskSuppStrutAName);
  G4RotationMatrix* RotateStrutA0 = new G4RotationMatrix ;
  RotateStrutA0->rotateY(-90.*deg) ;
  G4VPhysicalVolume* p_JMaskSuppStrutA = new G4PVPlacement(RotateStrutA0,
							   G4ThreeVector(0., 19.925*cm, 1.675*cm),
							   l_JMaskSuppStrutA,
							   JMaskSuppStrutAName,
							   l_JMask,
							   false,
							   0);
  G4RotationMatrix* RotateStrutA1 = new G4RotationMatrix ;
  RotateStrutA1->rotateY(-90.*deg) ; 
  RotateStrutA1->rotateX(-60.*deg) ;   
  p_JMaskSuppStrutA = new G4PVPlacement(RotateStrutA1,
					G4ThreeVector(sin(pi/3.)*19.925*cm, 
						      cos(pi/3.)*19.925*cm, 1.675*cm),
					l_JMaskSuppStrutA,
					JMaskSuppStrutAName,
					l_JMask,
					false,
					1);
  G4RotationMatrix* RotateStrutA2 = new G4RotationMatrix ;
  RotateStrutA2->rotateY(-90.*deg) ; 
  RotateStrutA2->rotateX(-120.*deg) ;   
  p_JMaskSuppStrutA = new G4PVPlacement(RotateStrutA2,
					G4ThreeVector(sin(pi/3.)*19.925*cm, 
						      -1.*cos(pi/3.)*19.925*cm, 1.675*cm),
					l_JMaskSuppStrutA,
					JMaskSuppStrutAName,
					l_JMask,
					false,
					2);
  G4RotationMatrix* RotateStrutA3 = new G4RotationMatrix ;
  RotateStrutA3->rotateY(-90.*deg) ; 
  RotateStrutA3->rotateX(180.*deg) ;   
  p_JMaskSuppStrutA = new G4PVPlacement(RotateStrutA3,
					G4ThreeVector(0., 
						      -19.925*cm, 1.675*cm),
					l_JMaskSuppStrutA,
					JMaskSuppStrutAName,
					l_JMask,
					false,
					3);
  G4RotationMatrix* RotateStrutA4 = new G4RotationMatrix ;
  RotateStrutA4->rotateY(-90.*deg) ; 
  RotateStrutA4->rotateX(120.*deg) ;   
  p_JMaskSuppStrutA = new G4PVPlacement(RotateStrutA4,
					G4ThreeVector(-1.*sin(pi/3.)*19.925*cm, 
						      -1.*cos(pi/3.)*19.925*cm, 1.675*cm),
					l_JMaskSuppStrutA,
					JMaskSuppStrutAName,
					l_JMask,
					false,
					4);
  G4RotationMatrix* RotateStrutA5 = new G4RotationMatrix ;
  RotateStrutA5->rotateY(-90.*deg) ; 
  RotateStrutA5->rotateX(60.*deg) ;   
  p_JMaskSuppStrutA = new G4PVPlacement(RotateStrutA5,
					G4ThreeVector(-1.*sin(pi/3.)*19.925*cm, 
						      cos(pi/3.)*19.925*cm, 1.675*cm),
					l_JMaskSuppStrutA,
					JMaskSuppStrutAName,
					l_JMask,
					false,
					5);
  // ----- Mask Support Structure Ring Piece around outside.
  const G4String JMaskRingPieceAName = "JMaskRingPieceA"; // JMPT
  const G4double AFacesZ[4] = {0.*cm,0.738*cm,0.738*cm,2.1*cm} ;
  const G4double AFacesRmin[4] = {26.75*cm,26.75*cm,26.75*cm,26.75*cm} ; 
  const G4double AFacesRmax[4] = {27.85*cm,27.85*cm,27.04*cm,27.04*cm} ;  
  G4Polycone* s_JMaskRingPieceA = new G4Polycone(JMaskRingPieceAName,
						 0.*deg,360*deg,
						 4,
						 AFacesZ, AFacesRmin, AFacesRmax) ;
  Material =  PIMPSelectMaterial("CuBe", Materials);
  G4LogicalVolume* l_JMaskRingPieceA = new G4LogicalVolume(s_JMaskRingPieceA,
							   Material,
							   JMaskRingPieceAName);
  G4VPhysicalVolume* p_JMaskRingPieceA = new G4PVPlacement(0,
							   G4ThreeVector(0., 0., -1.8*cm),
							   l_JMaskRingPieceA,
							   JMaskRingPieceAName,
							   l_JMask,
							   false,
							   0);
  const G4String JMaskRingPieceBName = "JMaskRingPieceB"; // JMPL
  const G4double BFacesZ[4] = {0.*cm,0.591*cm,0.591*cm,3.7*cm} ;
  const G4double BFacesRmin[4] = {26.75*cm,26.75*cm,26.75*cm,26.75*cm} ; 
  const G4double BFacesRmax[4] = {28.25*cm,28.25*cm,26.961*cm,26.961*cm} ;  
  G4Polycone* s_JMaskRingPieceB = new G4Polycone(JMaskRingPieceBName,
						 0.*deg,360*deg,
						 4,
						 BFacesZ, BFacesRmin, BFacesRmax) ;
  Material =  PIMPSelectMaterial("Titanium", Materials);
  G4LogicalVolume* l_JMaskRingPieceB = new G4LogicalVolume(s_JMaskRingPieceB,
							   Material,
							   JMaskRingPieceBName);
  G4VPhysicalVolume* p_JMaskRingPieceB = new G4PVPlacement(0,
							   G4ThreeVector(0., 0., -5.5*cm),
							   l_JMaskRingPieceB,
							   JMaskRingPieceBName,
							   l_JMask,
							   false,
							   0);
  // ------------ Mask Pixels ---------------
  ifstream infile("/users/clark/PIMP/JEMXopen.dat"); 
  if(!infile) 
    { 
      G4cout << "+++++++++++++++++++++++" << G4endl;
      G4cout << "ERROR: No JEMX Mask Pattern!" << G4endl;
      G4cout << "+++++++++++++++++++++++" << G4endl;
      return;
    }
  const G4String JMaskPatternName = "JMaskPattern"; // JMWS
  G4Tubs* s_JMaskPattern = new G4Tubs(JMaskPatternName,
				      0.*cm,26.770*cm,
				      0.025*cm,
				      0.*deg,360*deg) ;
  Material =  PIMPSelectMaterial("Tungsten", Materials);
  G4LogicalVolume* l_JMaskPattern = new G4LogicalVolume(s_JMaskPattern,
							Material,
							JMaskPatternName);
  G4VPhysicalVolume* p_JMaskPattern = new G4PVPlacement(0,
							G4ThreeVector(0., 0., 0.),
							l_JMaskPattern,
							JMaskPatternName,
							l_JMask,
							false,
							0);
  const G4String JMaskPixelName = "JMaskPixel"; // JMPX
  const G4double PixZ[2] = {0.*cm,0.05*cm} ;
  const G4double PixInner[2] = {0.*cm,0.*cm} ; 
  const G4double PixOuter[2] = {0.165*cm,0.165*cm} ;  
  G4Polyhedra* s_JMaskPixel = new G4Polyhedra(JMaskPixelName,
					      30.*deg,360.*deg,
					      6,2,
					      PixZ, PixInner, PixOuter) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_JMaskPixel = new G4LogicalVolume(s_JMaskPixel,
						      Material,
						      JMaskPixelName);
  G4VPhysicalVolume* p_JMaskPixel ;
  G4double Xpixel;
  G4double Ypixel;
  G4ThreeVector TilePosition;
  G4int TileNum = 0;
  
  while(infile >> Xpixel >> Ypixel)
    {
      TilePosition = G4ThreeVector(Xpixel*mm,Ypixel*mm,-0.025*cm);
      p_JMaskPixel= new G4PVPlacement(0,
				      TilePosition,
				      l_JMaskPixel,
				      JMaskPixelName,
				      l_JMaskPattern,
				      false,
				      TileNum); 
      TileNum++ ;
    }


  // ---------- Detector ----------------------------------------
  const G4String JemxDetName = "JemxDet"; // JDET
  G4Tubs* s_JemxDet = new G4Tubs(JemxDetName,0.*cm,22.1*cm,6.2*cm, 0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Tungsten", Materials) ;
  G4LogicalVolume* l_JemxDet = new G4LogicalVolume(s_JemxDet,
						   Material,
						   JemxDetName);
  // Place later on when JVOL is created ...

  const G4String JemxDetectorName = "JemxDetector"; // JDSH
  const G4double DFacesZ[15] = {-12.4*cm,
				-12.2*cm,
				-12.0*cm,
				-11.5*cm,
				-11.0*cm,
				-10.5*cm,
				-10.0*cm,
				-9.5*cm,
				-9.0*cm,
				-8.5*cm,
				-7.5*cm,
				-6.5*cm,
				-5.5*cm,
				-4.5*cm,
				-0.*cm} ;
  const G4double DFacesRmin[15] = {0.*cm,
				   0.*cm,
				   3.985*cm,
				   7.4317*cm,
				   9.6995*cm,
				   11.5078*cm,
				   13.0491*cm,
				   14.4094*cm,
				   15.635*cm,
				   16.653*cm,
				   17.747*cm,
				   18.3635*cm,
				   18.6947*cm,
				   18.8*cm,
				   18.8*cm} ; 
  const G4double DFacesRmax[15] = {0.*cm,
				   3.99499687*cm,
				   5.6427*cm,
				   8.4374*cm,
				   10.49*cm,
				   12.1815*cm,
				   13.657*cm,
				   14.9529*cm,
				   16.1382*cm,
				   17.0*cm,
				   18.0*cm,
				   18.5825*cm,
				   18.898*cm,
				   19.0*cm,
				   19.0*cm} ;  
  G4Polycone* s_JemxDetector = new G4Polycone(JemxDetectorName,
						 0.*deg,360*deg,
						 15,
						 DFacesZ, DFacesRmin, DFacesRmax) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_JemxDetector = new G4LogicalVolume(s_JemxDetector,
							Material,
							JemxDetectorName);
  G4VPhysicalVolume* p_JemxDetector = new G4PVPlacement(0,
							G4ThreeVector(0., 0., 6.2*cm),
							l_JemxDetector,
							JemxDetectorName,
							l_JemxDet,
							false,
							0);


  const G4String JemxXenonName = "JemxXenon"; // JDSH
  const G4double XeFacesRmin[15] = {0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm,
				    0.*cm} ; 
  const G4double XeFacesRmax[15] = {0.*cm,
				    0.*cm,
				    3.985*cm,
				    7.4317*cm,
				    9.6995*cm,
				    11.5078*cm,
				    13.0491*cm,
				    14.4094*cm,
				    15.635*cm,
				    16.653*cm,
				    17.747*cm,
				    18.3635*cm,
				    18.6947*cm,
				    18.8*cm,
				    18.8*cm} ; 
  
  G4Polycone* s_JemxXenon = new G4Polycone(JemxXenonName,
					   0.*deg,360*deg,
					   15,
					   DFacesZ, XeFacesRmin, XeFacesRmax) ;
  Material =  PIMPSelectMaterial("Xenon", Materials);
  G4LogicalVolume* l_JemxXenon = new G4LogicalVolume(s_JemxXenon,
						     Material,
						     JemxXenonName);
  G4VPhysicalVolume* p_JemxXenon = new G4PVPlacement(0,
						     G4ThreeVector(0., 0., 0.*cm),
						     l_JemxXenon,
						     JemxXenonName,
						     l_JemxDetector,
						     false,
						     0);

  const G4String JemxDTopPlateName = "JemxDTopPlate"; // JDPL
  G4Tubs* s_JemxDTopPlate = new G4Tubs(JemxDTopPlateName,12.5*cm,18.8*cm,0.1*cm, 0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Stainless", Materials) ;
  G4LogicalVolume* l_JemxDTopPlate = new G4LogicalVolume(s_JemxDTopPlate,
							 Material,
							 JemxDTopPlateName);
  G4VPhysicalVolume* p_JemxDTopPlate = new G4PVPlacement(0,
							 G4ThreeVector(0., 0., 6.1*cm),
							 l_JemxDTopPlate,
							 JemxDTopPlateName,
							 l_JemxDet,
							 false,
							 0);
  
  const G4String JemxDEntranceWindowName = "JemxDEntranceWindow"; // JDWI
  G4Tubs* s_JemxDEntranceWindow = new G4Tubs(JemxDEntranceWindowName,12.5*cm,18.8*cm,0.1*cm, 
					     0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Beryllium", Materials) ;
  G4LogicalVolume* l_JemxDEntranceWindow = new G4LogicalVolume(s_JemxDEntranceWindow,
							       Material,
							       JemxDEntranceWindowName);
  G4VPhysicalVolume* p_JemxDEntranceWindow = new G4PVPlacement(0,
							       G4ThreeVector(0., 0., (6.2-0.0125)*cm),
							       l_JemxDEntranceWindow,
							       JemxDEntranceWindowName,
							       l_JemxDet, 
							       false,
							       0); 
 
  const G4String JemxDSpiderPinName = "JemxDSpiderPin"; // JDPI
  G4Tubs* s_JemxDSpiderPin = new G4Tubs(JemxDSpiderPinName,0.*cm,0.75*cm,3.75*cm, 
					0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_JemxDSpiderPin = new G4LogicalVolume(s_JemxDSpiderPin,
							  Material,
							  JemxDSpiderPinName);
  G4VPhysicalVolume* p_JemxDSpiderPin = new G4PVPlacement(0,
							  G4ThreeVector(10.85*cm, 10.85*cm, 2.45*cm),
							  l_JemxDSpiderPin,
							  JemxDSpiderPinName,
							  l_JemxDet,
							  false,
							  0); 
  p_JemxDSpiderPin = new G4PVPlacement(0,
				       G4ThreeVector(-10.85*cm, 10.85*cm, 2.45*cm),
				       l_JemxDSpiderPin,
				       JemxDSpiderPinName,
				       l_JemxDet,
				       false,
				       1); 
  p_JemxDSpiderPin = new G4PVPlacement(0,
				       G4ThreeVector(-10.85*cm, -10.85*cm, 2.45*cm),
				       l_JemxDSpiderPin,
				       JemxDSpiderPinName,
				       l_JemxDet,
				       false,
				       2);    
  p_JemxDSpiderPin = new G4PVPlacement(0,
				       G4ThreeVector(10.85*cm, -10.85*cm, 2.45*cm),
				       l_JemxDSpiderPin,
				       JemxDSpiderPinName,
				       l_JemxDet,
				       false,
				       3); 

  const G4String JemxDSpiderStrutName = "JemxDSpiderStrut"; // JDST
  G4Box* s_JemxDSpiderStrut = new G4Box(JemxDSpiderStrutName,15.35*cm,0.45*cm,0.45*cm);  
  Material =  PIMPSelectMaterial("Aluminium", Materials) ;
  G4LogicalVolume* l_JemxDSpiderStrut = new G4LogicalVolume(s_JemxDSpiderStrut,
							    Material,
							    JemxDSpiderStrutName);
  G4RotationMatrix* RotateSpiderStrut0 = new G4RotationMatrix ;
  RotateSpiderStrut0->rotateZ(45.*deg) ;
  G4VPhysicalVolume* p_JemxDSpiderStrut = new G4PVPlacement(RotateSpiderStrut0,
							    G4ThreeVector(0.,0., -1.75*cm),
							    l_JemxDSpiderStrut,
							    JemxDSpiderStrutName,
							    l_JemxDet,
							    false,
							    0); 
  G4RotationMatrix* RotateSpiderStrut1 = new G4RotationMatrix ;
  RotateSpiderStrut1->rotateZ(-45.*deg) ;
  p_JemxDSpiderStrut = new G4PVPlacement(RotateSpiderStrut1,
					 G4ThreeVector(0.,0., -1.75*cm),
					 l_JemxDSpiderStrut,
					 JemxDSpiderStrutName,
					 l_JemxDet,
					 false,
					 1); 
  
  const G4String JGlassPlateName = "JGlassPlate"; // JDMP
  const G4double GlassZ[2] = {-0.15*cm,0.15*cm} ;
  const G4double GlassInner[2] = {0.*cm,0.*cm} ; 
  const G4double GlassOuter[2] = {13.49*cm,13.49*cm} ;  
  G4Polyhedra* s_JGlassPlate = new G4Polyhedra(JGlassPlateName,
					       0.*deg,360.*deg,
					       8,2,
					       GlassZ, GlassInner, GlassOuter) ;
  Material =  PIMPSelectMaterial("Glass", Materials);
  G4LogicalVolume* l_JGlassPlate = new G4LogicalVolume(s_JGlassPlate,
						       Material,
						       JGlassPlateName);
  G4VPhysicalVolume* p_JGlassPlate= new G4PVPlacement(0,
						      G4ThreeVector(0., 0., 0.2*cm),
						      l_JGlassPlate,
						      JGlassPlateName,
						      l_JemxDet,
						      false,
						      0); 

  const G4String JemxDSensitiveXeName = "JemxDSensitiveXe"; // JDXE
  G4Tubs* s_JemxDSensitiveXe = new G4Tubs(JemxDSensitiveXeName,0.*cm,12.5*cm,2.8375*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Xenon", Materials) ;
  G4LogicalVolume* l_JemxDSensitiveXe = new G4LogicalVolume(s_JemxDSensitiveXe,
							    Material,
							    JemxDSensitiveXeName);
  G4VPhysicalVolume* p_JemxDSensitiveXe = new G4PVPlacement(0,
							    G4ThreeVector(0.,0.,3.3375*cm),
							    l_JemxDSensitiveXe,
							    JemxDSensitiveXeName,
							    l_JemxDet,
							    false,
							    0); 
 
  const G4String JemxXeActiveVetoName = "JemxXeActiveVeto"; // JDVE
  G4Tubs* s_JemxXeActiveVeto = new G4Tubs(JemxXeActiveVetoName,12.5*cm,15.0*cm,2.8375*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Xenon", Materials) ;
  G4LogicalVolume* l_JemxXeActiveVeto = new G4LogicalVolume(s_JemxXeActiveVeto,
							    Material,
							    JemxXeActiveVetoName);
  G4VPhysicalVolume* p_JemxXeActiveVeto = new G4PVPlacement(0,
							    G4ThreeVector(0.*cm,0*cm,3.3375*cm),
							    l_JemxXeActiveVeto,
							    JemxXeActiveVetoName,
							    l_JemxDet,
							    false,
							    0); 
  /* This has been removed from the JEM-X model for some reason - possible
     inclusion into the spacecraft model, in which case it would have to be 
     moved to that object in PIMP. Details not added.
     The object to include is JDFE which contains JDBX (JDBB JDBT JDBS) 
     and multiple JDBR (JCT1,2,3,4,5)

  const G4String JemxDFEEName = "JemxDFEE"; // JDFE
  G4Tubs* s_JemxDFEE = new G4Tubs(JemxDFEEName,12.5*cm,15.0*cm,2.8375*cm, 
					  0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Xenon", Materials) ;
  G4LogicalVolume* l_JemxDFEE = new G4LogicalVolume(s_JemxDFEE,
							    Material,
							    JemxDFEEName);
  G4VPhysicalVolume* p_JemxDFEE = new G4PVPlacement(0,
							    G4ThreeVector(0.*cm,0*cm,3.3375*cm),
							    l_JemxDFEE,
							    JemxDFEEName,
							    l_JemxDet,
							    false,
							    0);

  */   

  
  const G4String JemxMaskFrameName = "JemxMaskFrame"; // JMFR
  G4Box* s_JemxMaskFrame = new G4Box(JemxMaskFrameName,29.9*cm,59.1*cm,2.0*cm);  
  Material =  PIMPSelectMaterial("CarbonFibre", Materials) ;
  G4LogicalVolume* l_JemxMaskFrame = new G4LogicalVolume(s_JemxMaskFrame,
							 Material,
							 JemxMaskFrameName);
  G4VPhysicalVolume* p_JemxMaskFrame = new G4PVPlacement(0,
							 G4ThreeVector(0.,0.,164.5*cm),
							 l_JemxMaskFrame,
							 JemxMaskFrameName,
							 l_JEMX,
							 false,
							 0);  

  const G4String JemxMaskFrameHoleName = "JemxMaskFrameHole"; // JDFH
  G4Tubs* s_JemxMaskFrameHole = new G4Tubs(JemxMaskFrameHoleName,
					   0.,26.75*cm,2.0*cm, 
					   0.*deg, 360.*deg);  
  Material =  PIMPSelectMaterial("Galactic", Materials) ;
  G4LogicalVolume* l_JemxMaskFrameHole = new G4LogicalVolume(s_JemxMaskFrameHole,
							     Material,
							     JemxMaskFrameHoleName);
  G4VPhysicalVolume* p_JemxMaskFrameHole = new G4PVPlacement(0,
							     G4ThreeVector(1.0*cm,
									   28.35*cm,
									   0.),
							     l_JemxMaskFrameHole,
							     JemxMaskFrameHoleName,
							     l_JemxMaskFrame,
							     false,
							     0);
  p_JemxMaskFrameHole = new G4PVPlacement(0,
					  G4ThreeVector(1.0*cm,
							-28.35*cm,
							0.),
					  l_JemxMaskFrameHole,
					  JemxMaskFrameHoleName,
					  l_JemxMaskFrame,
					  false,
					  1);

  // the walls
  const G4String JemxPLMWallzName = "JemxPLMWallz"; // JPLZ
  G4Box* s_JemxPLMWallz = new G4Box(JemxPLMWallzName,2.0*cm,59.1*cm,170.0*cm);  
  Material =  PIMPSelectMaterial("PLMHoney", Materials) ;
  G4LogicalVolume* l_JemxPLMWallz = new G4LogicalVolume(s_JemxPLMWallz,
							Material,
							JemxPLMWallzName);
  G4VPhysicalVolume* p_JemxPLMWallz = new G4PVPlacement(0,
							G4ThreeVector(-27.9*cm,0.,-7.5*cm),
							l_JemxPLMWallz,
							JemxPLMWallzName,
							l_JEMX,
							false,
							0); 
  const G4String JemxPLMWallxyName = "JemxPLMWallxy"; // JPLX
  G4Box* s_JemxPLMWallxy = new G4Box(JemxPLMWallxyName,27.9*cm,2.0*cm,170.0*cm);  
  Material =  PIMPSelectMaterial("PLMHoney", Materials) ;
  G4LogicalVolume* l_JemxPLMWallxy = new G4LogicalVolume(s_JemxPLMWallxy,
							 Material,
							 JemxPLMWallxyName);
  G4VPhysicalVolume* p_JemxPLMWallxy = new G4PVPlacement(0,
							 G4ThreeVector(2.0*cm,57.1*cm,-7.5*cm),
							 l_JemxPLMWallxy,
							 JemxPLMWallxyName,
							 l_JEMX,
							 false,
							 0);  
  p_JemxPLMWallxy = new G4PVPlacement(0,
				      G4ThreeVector(2.0*cm,-57.1*cm,-7.5*cm),
				      l_JemxPLMWallxy,
				      JemxPLMWallxyName,
				      l_JEMX,
				      false,
				      1); 
  // Virtual volume that will contain the detector....(not really necessary in G4)
  const G4String JVirtualVolName = "JVirtualVol"; // JVOL
  const G4double VVFacesZ[2] = {0.*cm,20.0*cm} ;
  const G4double VVFacesRmin[2] = {0.*cm,0.*cm} ; 
  const G4double VVFacesRmax[2] = {23*cm,23.0*cm} ;  
  G4Polycone* s_JVirtualVol = new G4Polycone(JVirtualVolName,
					     0.*deg,360*deg,
					     2,
					     VVFacesZ, VVFacesRmin, VVFacesRmax) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_JVirtualVol = new G4LogicalVolume(s_JVirtualVol,
						       Material,
						       JVirtualVolName);
  G4VPhysicalVolume* p_JVirtualVol = new G4PVPlacement(0,
						       G4ThreeVector(1.0*cm, 28.35*cm, -177.5*cm),
						       l_JVirtualVol,
						       JVirtualVolName,
						       l_JEMX,
						       false,
						       0);
  p_JVirtualVol = new G4PVPlacement(0,
				    G4ThreeVector(1.0*cm, -28.35*cm, -177.5*cm),
				    l_JVirtualVol,
				    JVirtualVolName,
				    l_JEMX,
				    false,
				    1);
  // Place Detectors inside these volumes ...
  G4VPhysicalVolume* p_JemxDet = new G4PVPlacement(0,
						   G4ThreeVector(0., 0., 6.3*cm),
						   l_JemxDet,
						   JemxDetName,
						   l_JVirtualVol,
						   false,
						   0); 

  // Now create and place the collimator inside the virtual volume ...
  PIMPGeomJemxCollimator* JemxCollimator = new PIMPGeomJemxCollimator(Materials) ; // creates object
  const G4ThreeVector* JemxCollimatorPosition = new G4ThreeVector(0.,0.,15.35*cm); 
  G4RotationMatrix* NullRotation = new G4RotationMatrix;
  JemxCollimator->Create(Materials, 
			 l_JVirtualVol, 
			 JemxCollimatorPosition, 
			 NullRotation);

  

  // ------------------- VISUALISATION ---------------
  // ----- MASK
  // l_JMaskSuppStrutA->SetVisAttributes(SkyBlue);
  // l_JMaskSuppStrut->SetVisAttributes(RoyalBlue);
  // l_JMaskSuppStruct->SetVisAttributes(Yellow);
  // l_JMaskRingPieceA->SetVisAttributes(Yellow);
  // l_JMaskRingPieceB->SetVisAttributes(RoyalBlue);
  // l_JMaskPixel->SetVisAttributes(Yellow);
  // l_JMaskPixel->SetVisAttributes(G4VisAttributes::Invisible)     ;
  // l_JemxDetector->SetVisAttributes(Yellow);
  // l_JemxXenon->SetVisAttributes(Green);
  // l_JGlassPlate->SetVisAttributes(Red);
  // l_JemxDSensitiveXe->SetVisAttributes(Yellow);
  // l_JemxDSpiderPin->SetVisAttributes(Yellow);
  // l_JemxDSpiderStrut->SetVisAttributes(Yellow);
  // l_JemxMaskFrame->SetVisAttributes(Yellow);
  // l_JMask->SetVisAttributes(Green);

}

PIMPGeomJEMX::~PIMPGeomJEMX()
{;}

void PIMPGeomJEMX::Create(const G4MaterialTable* Materials, 
			    G4LogicalVolume* Parent, 
			    const G4ThreeVector* Position, 
			    G4RotationMatrix* Rotation)
{  

  // Create JEMX Mother volume 
  const G4String Name = "JEMX" ;
  G4VPhysicalVolume* p_JEMX = new G4PVPlacement(Rotation,
						*Position,
						l_JEMX,
						Name,
						Parent,
						false,
						0);	
  
   // ------------------- VISUALISATION -----------------------

  //l_JEMX->SetVisAttributes(SkyBlue);
  /// l_JEMX->SetVisAttributes (G4VisAttributes::Invisible);
  return ;
}













