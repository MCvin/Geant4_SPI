// Geometry

#include "PIMPGeometry.hh"
#include "PIMPMaterials.hh"
#include "PIMPSensitive.hh"

#include "PIMPGeomSpacecraft.hh"
#include "PIMPGeomIBIS.hh"
#include "PIMPGeomSPI.hh"
#include "PIMPGeomJEMX.hh"
#include "PIMPGeomSideStructures.hh"


#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4SDManager.hh"
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

// extern G4LogicalVolume* Sensitive ;
 
PIMPGeometry::PIMPGeometry(PIMPSensitive* SensIn)// :SensGe(NULL)
{
    Sens = SensIn;
}

PIMPGeometry::~PIMPGeometry()
{;}

G4VPhysicalVolume* PIMPGeometry::Construct()//PIMPSensitive* Sens)
{
  
  // SensitiveLogical = Sensitive;
  //G4cout << SensitiveLogical->GetName() << G4endl ;

//   G4SDManager *SDman = G4SDManager::GetSDMpointer();
//   PIMPSensitive* Sens = new PIMPSensitive("Sensitive"); 
//   SDman->AddNewDetector(Sens);
  //SensitiveLogical->SetSensitiveDetector(Sens);
  


  //-------------------- Initialise -----------------------------------------
  G4RotationMatrix* NullRotation = new G4RotationMatrix;

  //-------------------- Construct the Materials Table ----------------------------
  PIMPMaterials* Materials = new PIMPMaterials ;
  const G4MaterialTable* theMaterials = Materials->CreateMaterialTable();
 
  //-------------------- Create the World Volume ----------------------------------
  G4Material* Temp = PIMPSelectMaterial("Galactic", theMaterials) ;
  G4Box* s_World = new G4Box("World",1000.0*cm,1000.0*cm,1000.0*cm);  
  G4LogicalVolume* l_World = new G4LogicalVolume(s_World,Temp,"World");		
  G4VPhysicalVolume* World = new G4PVPlacement(0,G4ThreeVector(),"World",l_World,
  					    0,false,0);		

  
  //-------------------- Create a sample block  ----------------------------------
//   Temp = PIMPSelectMaterial("Germanium", theMaterials) ;
//   G4Box* s_TestBlock = new G4Box("TestBlock",1.0*cm,1.0*cm,1.0*cm);  
//   G4LogicalVolume* l_TestBlock = new G4LogicalVolume(s_TestBlock,Temp,"TestBlock");		
//   G4VPhysicalVolume* TestBlock = new G4PVPlacement(0,
// 						   G4ThreeVector(),
// 						   l_TestBlock,
// 						   "TestBlock",
// 						   l_World,
// 						   false,
// 						   0);	
//   l_TestBlock->SetVisAttributes(Yellow);
//   l_TestBlock->SetSensitiveDetector(Sens);
//******************************************************************************************************************************  

  Temp = PIMPSelectMaterial("Galactic", theMaterials) ;
  G4Box* s_INTEGRAL = new G4Box("INTEGRAL",215.0*cm,215.0*cm,241.65*cm);  
  G4LogicalVolume* l_INTEGRAL = new G4LogicalVolume(s_INTEGRAL,Temp,"INTEGRAL");		
	G4VPhysicalVolume* p_INTEGRAL;
	//Centre Spi at 0,0
	 p_INTEGRAL = new G4PVPlacement(0,
						  G4ThreeVector(70.*cm, 0., 0.), 
						  l_INTEGRAL,
						  "INTEGRAL",
						  l_World,
						  false,
						  0);		
  
  //------------------- Now include Spacecraft --------------------------------
  PIMPGeomSpacecraft* Spacecraft = new PIMPGeomSpacecraft(theMaterials) ; // creates object
  const G4ThreeVector* SpacecraftPosition = new G4ThreeVector(0.,0.,(-128.3+64.15)*cm); 
  Spacecraft->Create(theMaterials, 
		     l_INTEGRAL, 
		     SpacecraftPosition, 
		     NullRotation);
  /*		     
  PIMPGeomSideStructures* SideStructures = new PIMPGeomSideStructures(theMaterials);
  const G4ThreeVector* PlusYPosition = new G4ThreeVector(13.1*cm,
							 -1.0*(118.2/2 + 49.65/2)*cm,
							 (350/2)*cm); 
  const G4ThreeVector* MinusYPosition = new G4ThreeVector(13.1*cm,
							 (118.2/2 + 49.65/2)*cm,
							 (350/2)*cm); 
  SideStructures->CreatePlusY(theMaterials, 
			      l_INTEGRAL, 
			      PlusYPosition, 
			      NullRotation);
  SideStructures->CreateMinusY(theMaterials, 
			       l_INTEGRAL, 
			       MinusYPosition, 
			       NullRotation);
    REMEMBER TO INCLUDE THE STRUCTURES NEXT TO IBIS AND THE ELECTRONICS ON THE BASE */

  
  //------------------- Now include IBIS --------------------------------
  PIMPGeomIBIS* IBIS = new PIMPGeomIBIS(theMaterials) ; // creates object
  const G4ThreeVector* IBISPosition = new G4ThreeVector(100.4*cm,0.,175.*cm); 
  IBIS->Create(theMaterials, 
	       l_INTEGRAL, 
	       IBISPosition, 
	       NullRotation);

  
  //------------------- Now include SPI --------------------------------
  PIMPGeomSPI* SPI = new PIMPGeomSPI(theMaterials, Sens) ; // creates object
  const G4ThreeVector* SPIPosition = new G4ThreeVector(-93.8*cm,0.,(117.6+10.5)*cm); 
  G4RotationMatrix* RotateSPI = new G4RotationMatrix ;
  RotateSPI->rotateZ(90*deg);
  SPI->Create(theMaterials, 
	      l_INTEGRAL, 
	      SPIPosition, 
	      RotateSPI);
  


  
  //------------------- Now include JEMX --------------------------------
  PIMPGeomJEMX* JEMX = new PIMPGeomJEMX(theMaterials) ; // creates object
  const G4ThreeVector* JEMXPosition = new G4ThreeVector(13.1*cm,0.,(355-355/2)*cm); 
  JEMX->Create(theMaterials, 
	      l_INTEGRAL, 
	      JEMXPosition, 
	      NullRotation);
  
  

  //------------------- Now include periferal structures and electronics ---
  // CPZ1
  const G4String SSTrianglesName = "SSTriangles";
  G4Trap* s_SSTriangles = new G4Trap(SSTrianglesName,
				     (237/2)*cm,
				     5.98*deg, 90*deg,
				     (49.65/2)*cm, 2.*cm, 2.*cm, 0.*deg,
				     0.001*cm, 2.*cm,2.*cm, 0.*deg);
  G4Material* Material =  PIMPSelectMaterial("PLMHoney", theMaterials) ;
  G4LogicalVolume* l_SSTriangles = new G4LogicalVolume(s_SSTriangles,
				      Material,
				      SSTrianglesName);
  G4VPhysicalVolume* p_SSTriangles = new G4PVPlacement(0,
						       G4ThreeVector(-14.7*cm,
								     -71.513*cm,
								     118.5*cm),
						       l_SSTriangles,
						       SSTrianglesName,
						       l_INTEGRAL,
						       false,
						       0);
  G4RotationMatrix* Rotate1 = new G4RotationMatrix ;
  Rotate1->rotateZ(180*deg);
  p_SSTriangles = new G4PVPlacement(Rotate1,
				    G4ThreeVector(-14.7*cm,
						  71.513*cm,
						  118.5*cm),
				    l_SSTriangles,
				    SSTrianglesName,
				    l_INTEGRAL,
				    false,
				    1);
  
  // CDPM - external electronics inside mother
  const G4String INTEGRALExtElec1Name = "INTEGRALExtElec1"; 
  G4Box* s_INTEGRALExtElec1 = new G4Box(INTEGRALExtElec1Name,
					11.6*cm, 12.5*cm,8.75*cm);
  Material =  PIMPSelectMaterial("ElectroMix", theMaterials);
  G4LogicalVolume* l_INTEGRALExtElec1 = new G4LogicalVolume(s_INTEGRALExtElec1,
							    Material,
							    INTEGRALExtElec1Name);
  G4VPhysicalVolume* p_INTEGRALExtElec1 = new G4PVPlacement(0,
							    G4ThreeVector(3.6*cm,
									  93.25*cm,
									  8.75*cm),
							    l_INTEGRALExtElec1,
							    INTEGRALExtElec1Name,
							    l_INTEGRAL,
							    false,
							    0);
  p_INTEGRALExtElec1 = new G4PVPlacement(0,
					 G4ThreeVector(3.6*cm,
						       -93.25*cm,
						       8.75*cm),
					 l_INTEGRALExtElec1,
					 INTEGRALExtElec1Name,
					 l_INTEGRAL,
					 false,
					 1);

  // CIEM - external electronics inside mother
  const G4String INTEGRALExtElec2Name = "INTEGRALExtElec2"; 
  G4Box* s_INTEGRALExtElec2 = new G4Box(INTEGRALExtElec2Name,
					15.75*cm, 15.15*cm,12.85*cm);
  Material =  PIMPSelectMaterial("ElectroMix", theMaterials);
  G4LogicalVolume* l_INTEGRALExtElec2 = new G4LogicalVolume(s_INTEGRALExtElec2,
							    Material,
							    INTEGRALExtElec2Name);
  G4VPhysicalVolume* p_INTEGRALExtElec2 = new G4PVPlacement(0,
							    G4ThreeVector(48.15*cm,
									  91.6*cm,
									  12.85*cm),
							    l_INTEGRALExtElec2,
							    INTEGRALExtElec2Name,
							    l_INTEGRAL,
							    false,
							    0);
  p_INTEGRALExtElec2 = new G4PVPlacement(0,
					 G4ThreeVector(48.15*cm,
						       -91.6*cm,
						       12.85*cm),
					 l_INTEGRALExtElec2,
					 INTEGRALExtElec2Name,
					 l_INTEGRAL,
					 false,
					 1);

  // CPEM - external electronics inside mother
  const G4String INTEGRALExtElec3Name = "INTEGRALExtElec3"; 
  G4Box* s_INTEGRALExtElec3 = new G4Box(INTEGRALExtElec3Name,
					11.9*cm, 10.5*cm,12.3*cm);
  Material =  PIMPSelectMaterial("ElectroMix", theMaterials);
  G4LogicalVolume* l_INTEGRALExtElec3 = new G4LogicalVolume(s_INTEGRALExtElec3,
							    Material,
							    INTEGRALExtElec3Name);
  G4VPhysicalVolume* p_INTEGRALExtElec3 = new G4PVPlacement(0,
							    G4ThreeVector(93.9*cm,
									  91.65*cm,
									  12.3*cm),
							    l_INTEGRALExtElec3,
							    INTEGRALExtElec3Name,
							    l_INTEGRAL,
							    false,
							    0);
  p_INTEGRALExtElec3 = new G4PVPlacement(0,
					 G4ThreeVector(93.9*cm,
						       -91.65*cm,
						       12.3*cm),
					 l_INTEGRALExtElec3,
					 INTEGRALExtElec3Name,
					 l_INTEGRAL,
					 false,
					 1);
  p_INTEGRALExtElec3 = new G4PVPlacement(0,
					 G4ThreeVector(122.9*cm,
						       91.65*cm,
						       12.3*cm),
					 l_INTEGRALExtElec3,
					 INTEGRALExtElec3Name,
					 l_INTEGRAL,
					 false,
					 1);
  p_INTEGRALExtElec3 = new G4PVPlacement(0,
					 G4ThreeVector(122.9*cm,
						       -91.65*cm,
						       12.3*cm),
					 l_INTEGRALExtElec3,
					 INTEGRALExtElec3Name,
					 l_INTEGRAL,
					 false,
					 1);

  
  
  /*  
  SensitiveLogical = Sensitive;
  G4cout << SensitiveLogical->GetName() << G4endl ;

  G4SDManager *SDman = G4SDManager::GetSDMpointer();
  PIMPSensitive* Sens = new PIMPSensitive("Sensitive"); 
  SDman->AddNewDetector(Sens);
  SensitiveLogical->SetSensitiveDetector(Sens);
  */




  //**************************************************************************************************************************************


//   G4cout << "builting detector" << G4endl;

//   G4double a, z;
//   G4double density;
//   G4int nel;

//   //Air
//   G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
//   G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
//   G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
   
//   //    G4Material* Air = new G4Material("Air", density= 0.00000001*mg/cm3, nel=2);
//   Air->AddElement(N, 70*perCent);
//   Air->AddElement(O, 30*perCent);

    
//   //Germanium
//   G4VisAttributes* yellow= new G4VisAttributes(G4Colour(1.,1.,0.));
//   yellow->SetVisibility(TRUE);
//   yellow->SetForceSolid(TRUE);

//   G4Material* Ge = 
//   new G4Material("Germanium", z=32., a=72.5899963*g/mole, density=  5.32299995*g/cm3);


//   G4VisAttributes* red= new G4VisAttributes(G4Colour(1.,0.,0.));
//   red->SetVisibility(TRUE);
//   red->SetForceSolid(TRUE);

//   // Print all the materials defined.
//   //
//   G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
//   G4cout << *(G4Material::GetMaterialTable()) << G4endl;

// //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  

// //world
// //      G4Box*             solidWorld;    // pointer to the solid envelope 
// //      G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
// //      G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope



//   //------------------------------ 
//   // World
//   //------------------------------ 


//    G4double HalfWorldLength = 100.*cm ;
  
// //   solidWorld= new G4Box("world",HalfWorldLength,HalfWorldLength,HalfWorldLength);
// //   logicWorld= new G4LogicalVolume( solidWorld, Air, "World", 0, 0, 0);
  
// //   //  Must place the World Physical volume unrotated at (0,0,0).
// //   // 
// //   physiWorld = new G4PVPlacement(0,               // no rotation
// //                                  G4ThreeVector(), // at (0,0,0)
// //                                  logicWorld,      // its logical volume
// // 				 "World",         // its name
// //                                  0,               // its mother  volume
// //                                  false,           // no boolean operations
// //                                  0);              // no field specific to volume

//  G4Box* soliddet= new G4Box("world",HalfWorldLength,HalfWorldLength,HalfWorldLength);
//  G4LogicalVolume*  logicdet= new G4LogicalVolume( soliddet, Air, "det", 0, 0, 0);
  
//   //  Must place the World Physical volume unrotated at (0,0,0).
//   // 
// G4VPhysicalVolume*    physidet = new G4PVPlacement(0,               // no rotation
//                                  G4ThreeVector(-70.0*cm,-10.0*cm,0.), // at (0,0,0)
//                                  logicdet,      // its logical volume
// 				 "det",         // its name
//                                  l_World,               // its mother  volume
//                                  false,           // no boolean operations
//                                  0);              // no field specific to volume


//   G4cout << "built world" << G4endl;
//   //**********************  Target **********************************

				 
//   G4double Ge_In_dia  = 0.*cm ;
//   G4double Ge_Out_dia = 2.*cm ;
//   G4double Ge_Half_z      = 2.24*cm ;
//   G4double Ge_Start_theta = 0.*deg;
//   G4double Ge_Delta_theta = 360.*deg;

//   G4Tubs* solidGeHit= new G4Tubs("Germanium_block", Ge_In_dia, Ge_Out_dia, Ge_Half_z, Ge_Start_theta, Ge_Delta_theta);
//   G4LogicalVolume* logicGeHit= new G4LogicalVolume( solidGeHit, Ge, "Germanium_block", 0, 0, 0);
//   logicGeHit->SetVisAttributes(yellow);
//   G4VPhysicalVolume*  physiGeHit= new G4PVPlacement(0,               // no rotation
// 						    G4ThreeVector(0.,0.,0.), // at (0,0,0)
// 						    logicGeHit,      // its logical volume
// 						    "Germanium_block",         // its name
// 						    //         l_World,      // its logical volume
//       						    logicdet,               // its mother  volume
// 						    false,           // no boolean operations
// 						    0);              // no field specific to volume

//   G4cout << "built target" << G4endl;
//   //**********************  Detector **********************************

//   const G4String GeDetName = "GeDet";
//   G4float Radius_ring = 20.0*cm;
//   G4int Number_det = 1;
//   G4VSolid * s_GeDet = new G4Box(GeDetName, ((Radius_ring-5.0*cm)*(std::tan(10.0*deg)))/2, 10.0*cm, 10.0*cm);
//   G4LogicalVolume * l_GeDet = new G4LogicalVolume(s_GeDet, Ge, GeDetName, 0, 0, 0);

//   G4VPhysicalVolume *p_GeDet ;
//   for(int i=0; i<Number_det ; i++)
//   {
//     G4double phi, x, y, z;
//     phi = 360.*deg/Number_det*i;
//     x = Radius_ring*std::sin(phi);
//     y = Radius_ring*std::cos(phi);
//     z = 0.*cm;
//     G4RotationMatrix rm;
//     rm.rotateZ(-phi);
//     p_GeDet
//       = new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(x,y,z)),
//                           l_GeDet, 
// 			  GeDetName,
//                           //       l_World,      // its logical volume
//                           logicdet,
// 			  false,
// 			  i);
//   G4cout << "built pixel" << G4endl;
//   }



//   l_GeDet->SetSensitiveDetector(Sens );
// logicGeHit->SetSensitiveDetector(Sens );
  // --------------- SET VISUALISATION PARAMETERS -------------------
  
  l_World->SetVisAttributes (G4VisAttributes::Invisible);
  // l_INTEGRAL->SetVisAttributes (G4VisAttributes::Invisible);
  // l_SSTriangles->SetVisAttributes(SkyBlue);
  // l_INTEGRALExtElec3->SetVisAttributes(Yellow);

  // ----------------------------------------------------------------

  return World;
  
}
















