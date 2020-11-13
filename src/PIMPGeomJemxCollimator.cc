// ------------------------------------------------------------------
// PIMPGeometry - JemxCollimator
// ------------------------------------------------------------------

#include "PIMPGeomJemxCollimator.hh"

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
// #include "G4VPhysicalVolume.hh"

PIMPGeomJemxCollimator::PIMPGeomJemxCollimator(const G4MaterialTable* Materials)
{
  // ----------- Collimator above detector plane --------------
  const G4String JemxCollimatorName = "JemxCollimator"; // JCOL
  G4Tubs* s_JemxCollimator = new G4Tubs(JemxCollimatorName,
					0.*cm,22.1*cm,
					2.85*cm,
					0.*deg,360*deg) ;
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials);
  l_JemxCollimator = new G4LogicalVolume(s_JemxCollimator,
					 Material,
					 JemxCollimatorName);
  // --- Molybedenum ring
  const G4String JCollMoBracketName = "JCollMoBracket"; // JCGR
  G4Tubs* s_JCollMoBracket = new G4Tubs(JCollMoBracketName,
					13.0*cm,13.3*cm,
					2.85*cm,
					0.*deg,360*deg) ;
  Material =  PIMPSelectMaterial("Molybdenum", Materials);
  G4LogicalVolume* l_JCollMoBracket = new G4LogicalVolume(s_JCollMoBracket,
							  Material,
							  JCollMoBracketName);
  G4VPhysicalVolume* p_JCollMoBracket = new G4PVPlacement(0,
							  G4ThreeVector(0., 0., 0.),
							  l_JCollMoBracket,
							  JCollMoBracketName,
							  l_JemxCollimator,
							  false,
							  0); 
  // --- Collimator box ---
  // The collimators are graded (Mo:Cu:Al) and are in a grid. 
  // Easiest way is to construct square tubes 

  const G4String CollTubeName = "CollTube"; // new structure to G4 (JCSM,JCSC,JCSA)
  G4Box* s_CollTube = new G4Box(CollTubeName,0.3525*cm,0.3525*cm,2.85*cm) ;
  Material =  PIMPSelectMaterial("Molybdenum", Materials);
  G4LogicalVolume* l_CollTube = new G4LogicalVolume(s_CollTube,
						    Material,
						    CollTubeName);
  G4VPhysicalVolume* p_CollTube ;
  G4int TubeNum = 0 ;
  G4double TubeX; G4double TubeY ; G4double Hyp ;
  for (int i=0 ; i<18 ; i++)
    {
        for (int j=0 ; j<18 ; j++)
	  {
	    //-----+ place tubes
	    TubeX = i*0.705 + 0.3525 ;
	    TubeY = j*0.705 + 0.3525 ;
	    Hyp = std::pow((std::pow(TubeX,2.0)+std::pow(TubeY,2.0)),0.5) ;
	    if(Hyp < 12.502) 
	      {
		p_CollTube = new G4PVPlacement(0,
					       G4ThreeVector(TubeX*cm, TubeY*cm, 0.),
					       l_CollTube,
					       CollTubeName,
					       l_JCollMoBracket,
					       false,
					       TubeNum);
		TubeNum++ ;
		p_CollTube = new G4PVPlacement(0,
					       G4ThreeVector(-1.0*TubeX*cm, TubeY*cm, 0.),
					       l_CollTube,
					       CollTubeName,
					       l_JCollMoBracket,
					       false,
					       TubeNum);
		TubeNum++ ;
		p_CollTube = new G4PVPlacement(0,
					       G4ThreeVector(TubeX*cm, -1.0*TubeY*cm, 0.),
					       l_CollTube,
					       CollTubeName,
					       l_JCollMoBracket,
					       false,
					       TubeNum);
		TubeNum++ ;
		p_CollTube = new G4PVPlacement(0,
					       G4ThreeVector(-1.0*TubeX*cm, -1.0*TubeY*cm, 0.),
					       l_CollTube,
					       CollTubeName,
					       l_JCollMoBracket,
					       false,
					       TubeNum);
		TubeNum++ ;
	      }
	  }
    }

  // Graded material and vacuum
  const G4String CollTubeCuName = "CollTubeCu"; 
  G4Box* s_CollTubeCu = new G4Box(CollTubeCuName,0.3435*cm,0.3435*cm,2.85*cm) ;
  Material =  PIMPSelectMaterial("Copper", Materials);
  G4LogicalVolume* l_CollTubeCu = new G4LogicalVolume(s_CollTubeCu,
						    Material,
						    CollTubeCuName);
  G4VPhysicalVolume* p_CollTubeCu = new G4PVPlacement(0,
						    G4ThreeVector(0., 0., 0.),
						    l_CollTubeCu,
						    CollTubeCuName,
						    l_CollTube,
						    false,
						    0); 
  const G4String CollTubeAlName = "CollTubeAl"; 
  G4Box* s_CollTubeAl = new G4Box(CollTubeAlName,0.3415*cm,0.3415*cm,2.85*cm) ;
  Material =  PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_CollTubeAl = new G4LogicalVolume(s_CollTubeAl,
						    Material,
						    CollTubeAlName);
  G4VPhysicalVolume* p_CollTubeAl = new G4PVPlacement(0,
						    G4ThreeVector(0., 0., 0.),
						    l_CollTubeAl,
						    CollTubeAlName,
						    l_CollTubeCu,
						    false,
						    0); 
  const G4String CollTubeVacName = "CollTubeVac"; 
  G4Box* s_CollTubeVac = new G4Box(CollTubeVacName,0.3365*cm,0.3365*cm,2.85*cm) ;
  Material =  PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_CollTubeVac = new G4LogicalVolume(s_CollTubeVac,
						    Material,
						    CollTubeVacName);
  G4VPhysicalVolume* p_CollTubeVac = new G4PVPlacement(0,
						    G4ThreeVector(0., 0., 0.),
						    l_CollTubeVac,
						    CollTubeVacName,
						    l_CollTubeAl,
						    false,
						    0); 

  // ---------------- VISUALISATION ---------------------------------------
  // l_JemxCollimator->SetVisAttributes(Green);

}

PIMPGeomJemxCollimator::~PIMPGeomJemxCollimator()
{;}

void PIMPGeomJemxCollimator::Create(const G4MaterialTable* Materials, 
				    G4LogicalVolume* Parent, 
				    const G4ThreeVector* Position, 
				    G4RotationMatrix* Rotation)
{  

  
  // Create JemxCollimator Mother volume 
  const G4String Name = "JemxCollimator" ;
  G4VPhysicalVolume* p_JemxCollimator = new G4PVPlacement(Rotation,
							  *Position,
							  l_JemxCollimator,
							  Name,
							  Parent,
							  false,
							  0);	
  // ------------------- VISUALISATION -----------------------

  // l_JemxCollimator->SetVisAttributes(Green);
  // l_JemxCollimator->SetVisAttributes (G4VisAttributes::Invisible);
  
  return ;
}













