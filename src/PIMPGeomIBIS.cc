// ------------------------------------------------------------------
// PIMPGeometry - IBIS
// ------------------------------------------------------------------

#include "PIMPGeomIBIS.hh"

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

PIMPGeomIBIS::PIMPGeomIBIS(const G4MaterialTable* Materials)
{

  // Define the Mother volume 'IBIS'
  G4double IBISX = 114.2/2.0;
  G4double IBISY = 118.2/2.0; 
  const G4String Name = "IBIS";
  G4Box* s_IBIS = new G4Box(Name,IBISX*cm,(IBISY+7.1)*cm,175.0*cm);
  // note - the +7.1cm, is in the original ugeomibis.F. Calibration Unit ?  
  G4Material* Material =  PIMPSelectMaterial("Galactic", Materials) ;
  l_IBIS = new G4LogicalVolume(s_IBIS,
			       Material,
			       Name);
  
  
  // --- Mask (SES) -------------------------------------------------
  // Mother Volume
  const G4String IBISMaskName = "IBISMask";
  G4Box* s_IBISMask = new G4Box(IBISMaskName, IBISX*cm, IBISY*cm, 5.0*cm);
  Material = PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_IBISMask = new G4LogicalVolume(s_IBISMask,
						    Material,
						    IBISMaskName);
  G4VPhysicalVolume *p_IBISMask = new G4PVPlacement(0,
						    G4ThreeVector(0.,0.,(175.0-5.0)*cm),
						    l_IBISMask,
						    IBISMaskName,
						    l_IBIS,
						    false,
						    0);
  // Tungsten bit of mask (IMCV in G3)
  const G4String IBISMaskWName = "IBISMaskW";
  G4Box* s_IBISMaskW = new G4Box(IBISMaskWName, 
				 107.4/2.0*cm, 111.2/2.0*cm, (1.4/2.0 + 0.1)*cm);
  Material = PIMPSelectMaterial("Tungsten", Materials);
  G4LogicalVolume* l_IBISMaskW = new G4LogicalVolume(s_IBISMaskW,
						     Material,
						     IBISMaskWName);
  // IMCV is in IMVO (z=0). IMVO is in IMAS (G4 IBISMask) z = -5.+0.2+0.075 +0.02+ 8./2.
  G4VPhysicalVolume* p_IBISMaskW = new G4PVPlacement(0,
						     G4ThreeVector(0.,0.,-0.705*cm),
						     l_IBISMaskW,
						     IBISMaskWName,
						     l_IBISMask,
						     false,
						     0);
  
  // Mask pixel (empty pixels - solid mask is made of tungsten)
  const G4String IBISMaskPixelName = "IBISMaskPixel";
  G4Box* s_IBISMaskPixel = new G4Box(IBISMaskPixelName, 10.0*cm, 10.0*cm, (1.4/2.0 + 0.1)*cm);
  Material = PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_IBISMaskPixel = new G4LogicalVolume(s_IBISMaskPixel,
							 Material,
							 IBISMaskPixelName);
  // These arrays contain positions for pixels (test)
  G4double PixelX[8] = {-40.0, -40.0, -20.0, 0.0, 20.0, 40.0, 0.0, 40.0};
  G4double PixelY[8] = {40.0, -20.0, -40.0, -40.0, -40.0, -20.0, 0.0, 40.0};
  G4VPhysicalVolume* p_IBISMaskPixel;
  for (int i = 0; i < 8; i++)
    {
      p_IBISMaskPixel = new G4PVPlacement(0,
					  G4ThreeVector(PixelX[i]*cm,PixelY[i]*cm,0.),
					  l_IBISMaskPixel,
					  IBISMaskPixelName,
					  l_IBISMaskW,
					  false,
					  i);
    }
  
  //l_IBISMask->SetVisAttributes(G4VisAttributes::Invisible);
  //l_IBISMask->SetVisAttributes(Green);
  //
  // End of Mask ------------------------------------------------------
  
  
  

  // --- Collimator (SES) ---------------------------------------------
  // Mother volume = G3 ICOL - make it out of tungsten and hollow it out about 2mm thick
  const G4String IBISCollimatorName = "IBISCollimator";
  G4Box* s_IBISCollimator = new G4Box(IBISCollimatorName,
				      IBISX*cm, (IBISY+7.1)*cm, 155.0*cm);
  Material = PIMPSelectMaterial("Tungsten", Materials);
  G4LogicalVolume* l_IBISCollimator = new G4LogicalVolume(s_IBISCollimator,
							  Material,
							  IBISCollimatorName);
  G4VPhysicalVolume* p_IBISCollimator = new G4PVPlacement(0,
							  G4ThreeVector(0.,0.,10.0*cm),
							  l_IBISCollimator, 
							  IBISCollimatorName,
							  l_IBIS,
							  false,
							  0);
   const G4String IBISCollInName = "IBISCollIn";
   G4Box* s_IBISCollIn = new G4Box(IBISCollInName,
				   (IBISX-0.2)*cm, (IBISY+7.1-0.2)*cm, 155.0*cm);
   Material = PIMPSelectMaterial("Galactic", Materials);
   G4LogicalVolume* l_IBISCollIn = new G4LogicalVolume(s_IBISCollIn,
						       Material,
						       IBISCollInName);
   G4VPhysicalVolume* p_IBISCollIn = new G4PVPlacement(0,
						       G4ThreeVector(0.,0.,0.),
						       l_IBISCollIn, 
						       IBISCollInName,
						       l_IBISCollimator,
						       false,
							  0); 
    
   // End of Collimator / Shielding ---------------------------------------------

  
  // "Hopper" = G3 IHOT
  const G4String IBISHopperWName = "IBISHopperW";
  G4Trap* s_IBISHopperW = new G4Trap(IBISHopperWName,
				    55.0/2.0*cm, 0.9073*deg, 90*deg, 
				    (30.45+0.2)*cm, (30.82+0.2)*cm, (30.82+0.2)*cm,
				    0., 
				    (30.45+4.91+0.2)*cm, (30.82+3.846+0.2)*cm, (30.82+3.846+0.2)*cm, 
				    0.);
  Material = PIMPSelectMaterial("Tungsten", Materials);
  G4LogicalVolume* l_IBISHopperW = new G4LogicalVolume(s_IBISHopperW,
						       Material,
						       IBISHopperWName);
  G4VPhysicalVolume* p_IBISHopperW = new G4PVPlacement(0,
						       G4ThreeVector(0.,0.4355*cm,-127.5*cm),
						       l_IBISHopperW, 
						       IBISHopperWName,
						       l_IBISCollimator,
						       false,
						       0);
				  
  // Hollow out the Hopper with vacuum. Walls are 0.2cm thick = G3 IHOV
  const G4String IBISHopperVName = "IBISHopperV";
  G4Trap* s_IBISHopperV = new G4Trap(IBISHopperVName,
				    55.0/2.0*cm, 0.9073*deg, 90*deg, 
				    30.45*cm, 30.82*cm, 30.82*cm,
				    0., 
				    (30.45+4.91)*cm, (30.82+3.846)*cm, (30.82+3.846)*cm, 
				    0.);
  Material = PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_IBISHopperV = new G4LogicalVolume(s_IBISHopperV,
						       Material,
						       IBISHopperVName);
  G4VPhysicalVolume* p_IBISHopperV = new G4PVPlacement(0,
						       G4ThreeVector(0.,0.4355*cm,-127.5*cm),
						       l_IBISHopperV, 
						       IBISHopperVName,
						       l_IBISCollimator,
						       false,
						       0);
 
				  

 // End of Hopper  
  
  
  //  l_IBISCollimator->SetVisAttributes(G4VisAttributes::Invisible);
  //  l_IBISCollIn->SetVisAttributes(Green);
  
  
  
  
  
  
  
  
  
  // Veto (SES) ----------------------------------------------------------
  // Mother Volume
  const G4String IBISVetoName = "IBISVeto";
  G4Box* s_IBISVeto = new G4Box(IBISVetoName,
				57.2*cm, 59.1*cm, 15.0*cm);
  Material = PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_IBISVeto = new G4LogicalVolume(s_IBISVeto,
						    Material,
						    IBISVetoName);
  G4VPhysicalVolume* p_IBISVeto = new G4PVPlacement(0,
						    G4ThreeVector(0.,0.,(-175.0 + 15)*cm),
						    l_IBISVeto, 
						    IBISVetoName,
						    l_IBIS,
						    false,
						    0);
  
  // ISGRI  -----------------------------------------------------
  //
  // Mother Volume - goes inside IBIS Veto in G3 model
  const G4String ISGRIName = "ISGRI";
  G4Box* s_ISGRI = new G4Box(ISGRIName,
			     33.0*cm, 33.0*cm, 0.75*cm);
  Material = PIMPSelectMaterial("Galactic", Materials);
  G4LogicalVolume* l_ISGRI = new G4LogicalVolume(s_ISGRI,
						 Material,
						 ISGRIName);
  G4VPhysicalVolume* p_ISGRI = new G4PVPlacement(0,
						 G4ThreeVector(0.,0.,(15.0-0.75)*cm),
						 l_ISGRI,
						 ISGRIName,
						 l_IBISVeto,
						 false,
						 0);
  
  // ISGRI Modules = G3 ISMO - pretend they are all CZT
  const G4String ISGRIModuleName = "ISGRIModule";
  G4Box* s_ISGRIModule = new G4Box(ISGRIModuleName,
				   (15.64/2.0)*cm, (30.36/2.0)*cm, 0.75*cm);
  Material = PIMPSelectMaterial("CZT", Materials);
  G4LogicalVolume* l_ISGRIModule = new G4LogicalVolume(s_ISGRIModule,
						       Material,
						       ISGRIModuleName);
  G4VPhysicalVolume* p_ISGRIModule;
  G4double PosX, PosY;
  G4int ModuleN = 0;  
  
  for (int i = 0; i < 2 ; i++)
    {
      PosY = -30.36/2.0 + i*30.36;
      for (int j = 0; j < 4 ; j++)
	{
	  PosX = 15.64*1.5 - j*15.64;
	  p_ISGRIModule = new G4PVPlacement(0,
					    G4ThreeVector(PosX*cm, PosY*cm, 0.),
					    l_ISGRIModule,
					    ISGRIModuleName,
					    l_ISGRI,
					    false,
					    ModuleN);
	  ModuleN++;
	}
    }
  
  
  l_ISGRIModule->SetVisAttributes(Red);
  l_ISGRI->SetVisAttributes(G4VisAttributes::Invisible);
  
  
  // PiCsiT
  // Mother Volume - goes inside IBIS Veto in G3 model = IPCS, made of Aluminium
  const G4String PICSITName = "PICSIT";
  G4Box* s_PICSIT = new G4Box(PICSITName,
			     32.5*cm, 32.5*cm, 3.4*cm);
  Material = PIMPSelectMaterial("Aluminium", Materials);
  G4LogicalVolume* l_PICSIT = new G4LogicalVolume(s_PICSIT,
						 Material,
						 PICSITName);
  G4VPhysicalVolume* p_PICSIT = new G4PVPlacement(0,
						 G4ThreeVector(0.,0.,-1.6*cm),
						 l_PICSIT,
						 PICSITName,
						 l_IBISVeto,
						 false,
						 0);
  // PiCsIT modules
  // Use G3 IPMO - pretend its all CsI
  const G4String PICSITModuleName = "PICSITModule";
  G4Box* s_PICSITModule = new G4Box(PICSITModuleName,
				    (15.64/2.0)*cm, (30.36/2.0)*cm, 3.4*cm);
  Material = PIMPSelectMaterial("PICSIT", Materials);
  G4LogicalVolume* l_PICSITModule = new G4LogicalVolume(s_PICSITModule,
							Material,
							PICSITModuleName);
  G4VPhysicalVolume* p_PICSITModule;
  ModuleN = 0;  
  for (int i = 0 ; i < 2 ; i++)
    {
      PosY = -30.36/2.0 + i*30.36;
      for (int j = 0; j < 4 ; j++)
	{
	  PosX = 15.64*1.5 - j*15.64;
	  p_PICSITModule = new G4PVPlacement(0,
					     G4ThreeVector(PosX*cm,PosY*cm,0.),
					     l_PICSITModule,
					     PICSITModuleName,
					     l_PICSIT,
					     false,
					     0);
	  ModuleN++;
	}
    }
   l_PICSITModule->SetVisAttributes(SkyBlue);
}

PIMPGeomIBIS::~PIMPGeomIBIS()
{;}

void PIMPGeomIBIS::Create(const G4MaterialTable* Materials, 
			    G4LogicalVolume* Parent, 
			    const G4ThreeVector* Position, 
			    G4RotationMatrix* Rotation)
{  

  // Create IBIS Mother volume 
  
  const G4String Name = "IBIS" ;
  G4VPhysicalVolume* p_IBIS = new G4PVPlacement(Rotation,
						*Position,
						l_IBIS,
						Name,
						Parent,
						false,
						0);	
  
  // ------------------- VISUALISATION -----------------------

  
  return ;
}













