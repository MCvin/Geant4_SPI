// Materials

#include "PIMPMaterials.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "globals.hh"
#include "G4ios.hh"

PIMPMaterials::PIMPMaterials()
{;}

PIMPMaterials::~PIMPMaterials()
{;}

const G4MaterialTable* PIMPMaterials::CreateMaterialTable()
{
  //------------- Materials Used -----------
  G4String name, symbol;    
  G4double a, z, density;              
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;
  G4double temperature, pressure;

  // Elements used for definition of materials
  a = 207.19 * g/mole;
  G4Element *PbE = new G4Element(name="Lead", symbol="Pb", z = 82., a);
  a = 180.95 * g/mole;   
  G4Element *TaE = new G4Element(name="Tantalum", symbol="Ta", z = 73., a);
  a = 118.69 * g/mole;
  G4Element *SnE = new G4Element(name="Tin", symbol="Sn", z = 50., a);
  a = 63.55 * g/mole;
  G4Element *CuE = new G4Element(name="Copper", symbol="Cu", z = 29., a);
  a = 112.4 * g/mole;
  G4Element *CdE = new G4Element(name="Cadmium", symbol="Cd", z = 48., a);
  a = 65.38 * g/mole;
  G4Element *ZnE = new G4Element(name="Zinc", symbol="Zn", z = 30., a);
  a = 127.6 * g/mole;
  G4Element *TeE = new G4Element(name="Tellurium", symbol="Te", z=52., a);
  a = 12.011 * g/mole;
  G4Element *CE = new G4Element(name="Carbon", symbol="C", z=6., a);
  a = 28.09 * g/mole;
  G4Element *SiE = new G4Element(name="Silicon", symbol="Si", z=14., a);
  a = 26.98 * g/mole;
  G4Element *AlE = new G4Element(name="Aluminium", symbol="Al", z=13., a);
  a = 1.008 * g/mole;
  G4Element *HE = new G4Element(name="Hydrogen", symbol="H", z=1., a);
  a = 15.999 * g/mole;
  G4Element *OE = new G4Element(name="Oxygen", symbol="O", z=8., a);
  a = 58.693 * g/mole;
  G4Element *NiE = new G4Element(name="Nickel", symbol="Ni", z=28., a);
  a = 55.845 * g/mole;
  G4Element *FeE = new G4Element(name="Iron", symbol="Fe", z=26., a);
  a = 196.97 * g/mole;
  G4Element *AuE = new G4Element(name="Gold", symbol="Au", z=79., a);
  a = 107.8682 * g/mole;
  G4Element *AgE = new G4Element(name="Silver", symbol="Ag", z=47., a);
  a = 40.08 * g/mole;
  G4Element *CaE = new G4Element(name="Calcium", symbol="Ca", z=20., a);
  a = 14.007 * g/mole;
  G4Element *NE = new G4Element(name="Nitrogen", symbol="N", z=7., a);
  a = 39.948 * g/mole;
  G4Element *ArE = new G4Element(name="Argon", symbol="Ar", z=18., a);
  a = 183.85 * g/mole;
  G4Element *WE = new G4Element(name="Tungsten", symbol="W", z=74., a);
  a = 9.012 * g/mole;
  G4Element *BeE = new G4Element(name="Beryllium", symbol="Be", z=4., a);
  a = 95.94 * g/mole;
  G4Element *MoE = new G4Element(name="Molybdenum", symbol="Mo", z=42., a);
  a = 131.29 * g/mole;
  G4Element *XeE = new G4Element(name="Xenon", symbol="Xe", z=54., a); 
  a = 51.996 * g/mole;
  G4Element *CrE = new G4Element(name="Chromium", symbol="Cr", z=24., a); 
  a = 208.98038 * g/mole;
  G4Element *BiE = new G4Element(name="Bismuth", symbol="Bi", z=83., a); 
  a = 72.64 * g/mole;
  G4Element *GeE = new G4Element(name="Germanium", symbol="Ge", z=32., a); 
  a = 47.88 * g/mole;
  G4Element *TiE = new G4Element(name="Titanium", symbol="Ti", z=22., a); 
  a = 50.942 * g/mole;
  G4Element *VE = new G4Element(name="Vanadium", symbol="V", z=23., a); 
  a = 133.0 * g/mole;
  G4Element *CsE = new G4Element(name="Caesium", symbol="Cs", z=55., a); 
  a = 127.0 * g/mole;
  G4Element *IE = new G4Element(name="Iodine", symbol="I", z=53., a); 



  // Define simple materials used in PIMP
  density = 2.700*g/cm3;  
  a = 26.98*g/mole;
  z = 13.;
  G4Material* Al = new G4Material(name="Aluminium", z, a, density);
  density = 0.2*g/cm3;  
  G4Material* AlHoney1 = new G4Material(name="AluminiumHoney1", z, a, density);  
  density = 0.091*g/cm3;  
  G4Material* AlHoney2 = new G4Material(name="AluminiumHoney2", z, a, density); 
  density = 0.055*g/cm3;  
  G4Material* AlHoney3 = new G4Material(name="AluminiumHoney3", z, a, density); 
  density = 0.16*g/cm3;  
  G4Material* AlHoney4 = new G4Material(name="AluminiumHoney4", z, a, density); 

  density = 11.34*g/cm3;
  a = 207.19*g/mole;
  z = 82.;
  G4Material* Pb = new G4Material(name="Lead", z, a, density);

  density = 19.30*g/cm3;
  a = 196.97*g/mole;
  z = 79.;
  G4Material* Au = new G4Material(name="Gold", z, a, density);

  density = 16.6*g/cm3;
  a = 180.95*g/mole;
  z = 73.;
  G4Material* Ta = new G4Material(name="Tantulum", z, a, density);  

  density = 7.29*g/cm3;
  a = 118.71*g/mole;
  z = 50.;
  G4Material* Sn = new G4Material(name="Tin", z, a, density);

  density = 8.93*g/cm3;
  a = 63.55*g/mole;
  z = 29.;
  G4Material* Cu = new G4Material(name="Copper", z, a, density);

  density = 1.65 * g/cm3;
  a = 12.011 * g/mole;
  z = 6.;
  G4Material* CarbonFibre = new G4Material(name="CarbonFibre", z, a, density);
  density = 0.032 * g/cm3;
  G4Material* Korex = new G4Material(name="Korex", z, a, density);
  density = 0.5 * g/cm3;
  G4Material* Wood = new G4Material(name="Wood", z, a, density);
  


  density = 2.33 * g/cm3;
  a = 28.09 * g/mole;
  z = 14.;
  G4Material* Si = new G4Material(name="Silicon", z, a, density);

  density = 4.507 * g/cm3;
  a = 47.867 * g/mole;
  z = 22.;
  G4Material* Ti = new G4Material(name="Titanium", z, a, density);

  density = 10.490 * g/cm3;
  a = 107.8682 * g/mole;
  z = 47.;
  G4Material* Ag = new G4Material(name="Silver", z, a, density);
 
  density = 19.32 * g/cm3;
  a = 183.85 * g/mole;
  z = 74.;
  G4Material* W = new G4Material(name="Tungsten", z, a, density);

  density = 10.28 * g/cm3;
  a = 95.94 * g/mole;
  z = 42.;
  G4Material* Mo = new G4Material(name="Molybdenum", z, a, density);

  density = 1.5 * 5.5e-3 * g/cm3;
  a = 131.29 * g/mole;
  z = 54.;
  G4Material* Xe = new G4Material(name="Xenon", z, a, density);

  density = 1.848 * g/cm3;
  a = 9.012 * g/mole;
  z = 4.;
  G4Material* Be = new G4Material(name="Beryllium", z, a, density);

  density = 5.323 * g/cm3;
  a = 72.64 * g/mole;
  z = 32.;
  G4Material* Ge = new G4Material(name="Germanium", z, a, density);  


  // Define more complex materials

  // Electronics mixture (Carbon/Copper/Silicon/Aluminium)- LITE
  density = 0.4 * g/cm3;
  G4Material* ElectroMixLite = new G4Material(name="ElectroMixLite", density, ncomponents = 4);
  ElectroMixLite->AddElement(CE, fractionmass = 0.05);
  ElectroMixLite->AddElement(CuE, fractionmass = 0.1);
  ElectroMixLite->AddElement(SiE, fractionmass = 0.05); 
  ElectroMixLite->AddElement(AlE, fractionmass = 0.8);

  // Electronics mixture (Carbon/Copper/Silicon/Aluminium)
  density = 1.0 * g/cm3;
  G4Material* ElectroMix = new G4Material(name="ElectroMix", density, ncomponents = 4);
  ElectroMix->AddElement(CE, fractionmass = 0.05);
  ElectroMix->AddElement(CuE, fractionmass = 0.1);
  ElectroMix->AddElement(SiE, fractionmass = 0.05); 
  ElectroMix->AddElement(AlE, fractionmass = 0.8);

  // Dense Electronics mixture (Carbon/Copper/Silicon/Aluminium)
  density = 4.0 * g/cm3;
  G4Material* ElectroMixDense = new G4Material(name="ElectroMixDense", density, ncomponents = 4);
  ElectroMixDense->AddElement(CE, fractionmass = 0.05);
  ElectroMixDense->AddElement(CuE, fractionmass = 0.1);
  ElectroMixDense->AddElement(SiE, fractionmass = 0.05); 
  ElectroMixDense->AddElement(AlE, fractionmass = 0.8);

  // PCB material
  density = 1.8 * g/cm3;
  G4Material* PCB = new G4Material(name="PCB", density, ncomponents = 2);
  PCB->AddElement(CE, fractionmass = 0.99);
  PCB->AddElement(HE, fractionmass = 0.01);

  // Silicon Carbide
  density = 2.2985 * g/cm3;
  G4Material* SiC = new G4Material(name="SiC", density, ncomponents = 2);
  SiC->AddElement(SiE, natoms = 4);
  SiC->AddElement(CE, natoms = 4);
 
  // UVOT mixed materials
  density = 1.5 * g/cm3;
  G4Material* SMMix = new G4Material(name="SMMix", density, ncomponents = 7);
  SMMix->AddElement(CE, fractionmass = 0.27);
  SMMix->AddElement(HE, fractionmass = 0.02);
  SMMix->AddElement(OE, fractionmass = 0.25); 
  SMMix->AddElement(NiE, fractionmass = 0.1); 
  SMMix->AddElement(CdE, fractionmass = 0.1); 
  SMMix->AddElement(FeE, fractionmass = 0.05); 
  SMMix->AddElement(CuE, fractionmass = 0.21); 

  // Material CZT
  density = 6.06 * g/cm3;
  G4Material* CZT = new G4Material(name="CZT", density, ncomponents = 3);
  CZT->AddElement(CdE, natoms = 9);
  CZT->AddElement(ZnE, natoms = 1);
  CZT->AddElement(TeE, natoms = 10);

  // Shield alloy
  density = 11.98 *g/cm3;
  G4Material* Shield = new G4Material(name="Shield", density, ncomponents = 4);
  Shield->AddElement(PbE, fractionmass = 0.34);
  Shield->AddElement(TaE, fractionmass = 0.33);
  Shield->AddElement(SnE, fractionmass = 0.20);
  Shield->AddElement(CuE, fractionmass = 0.13);
   
  // Vacuum  
  density     = universe_mean_density;    //from G4PhysicalConstants.hh
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* Vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole,
				      density,kStateGas,temperature,pressure);

  // Glue Dots
  density = 8.8 *g/cm3;
  G4Material* GlueDot = new G4Material(name="GlueDot", density, ncomponents = 2);
  GlueDot->AddElement(AgE, fractionmass = 0.8);
  GlueDot->AddElement(CE, fractionmass = 0.2);

  // Cement
  density = 3.12 *g/cm3;
  G4Material* Cement = new G4Material(name="Cement", density, ncomponents = 6);
  Cement->AddElement(SiE, fractionmass = 0.701);
  Cement->AddElement(CE, fractionmass = 0.004);
  Cement->AddElement(CaE, fractionmass = 0.172);
  Cement->AddElement(AlE, fractionmass = 0.039);
  Cement->AddElement(FeE, fractionmass = 0.067);
  Cement->AddElement(OE, fractionmass = 0.017);

  // Air
  density = 0.0012 *g/cm3;
  G4Material* Air = new G4Material(name="Air", density, ncomponents = 4);
  Air->AddElement(NE, fractionmass = 0.781);
  Air->AddElement(OE, fractionmass = 0.2078);
  Air->AddElement(ArE, fractionmass = 0.0093);
  Air->AddElement(CE, fractionmass = 0.0019);

  // Standard Plastic
  density = 0.9 * g/cm3;
  G4Material* Plastic = new G4Material(name="Plastic", density, ncomponents = 2);
  Plastic->AddElement(CE, fractionmass = 0.99);
  Plastic->AddElement(HE, fractionmass = 0.01);

  // Plastic Scintillator
  density = 1.05 * g/cm3;
  G4Material* PlasticScint = new G4Material(name="PlasticScint", density, ncomponents = 2);
  PlasticScint->AddElement(CE, fractionmass = 0.9231);
  PlasticScint->AddElement(HE, fractionmass = 0.0769); 

  // CuBe
  density = 6.791 * g/cm3;
  G4Material* CuBe = new G4Material(name="CuBe", density, ncomponents = 2);
  CuBe->AddElement(BeE, fractionmass = 0.7);
  CuBe->AddElement(CuE, fractionmass = 0.3);  

  // Stainless Steel - 18% Cr, 8% Ni, 74% Fe
  density = 7.93 * g/cm3;
  G4Material* Stainless = new G4Material(name="Stainless", density, ncomponents = 3);
  Stainless->AddElement(CrE, fractionmass = 0.18);
  Stainless->AddElement(NiE, fractionmass = 0.08);
  Stainless->AddElement(FeE, fractionmass = 0.74);  
  
  // Glass
  density = 2.650 * g/cm3;
  G4Material* Glass = new G4Material(name="Glass", density, ncomponents = 2);
  Glass->AddElement(SiE, fractionmass = 0.334);
  Glass->AddElement(OE, fractionmass = 0.666);

  // Carbon Fibre honeycomb
  density = 0.16 * g/cm3;
  G4Material* PLMHoney = new G4Material(name="PLMHoney", density, ncomponents = 3);
  PLMHoney->AddElement(CE, fractionmass = 0.90);  
  PLMHoney->AddElement(HE, fractionmass = 0.09);
  PLMHoney->AddElement(OE, fractionmass = 0.01);
  
  //  Carbon Fibre honeycomb
  density = 0.144 * g/cm3;
  G4Material* SPIHoney = new G4Material(name="SPIHoney", density, ncomponents = 3);
  SPIHoney->AddElement(CE, fractionmass = 0.90);  
  SPIHoney->AddElement(HE, fractionmass = 0.09);
  SPIHoney->AddElement(OE, fractionmass = 0.01);  

  // Epoxy Resin
  density = 1.1 * g/cm3;
  G4Material* Epoxy = new G4Material(name="Epoxy", density, ncomponents = 3);
  Epoxy->AddElement(CE, natoms = 2);  
  Epoxy->AddElement(HE, natoms = 4);
  Epoxy->AddElement(OE, natoms = 1);

  density = 0.968 * g/cm3;
  G4Material* Potting = new G4Material(name="Potting", density, ncomponents = 3);
  Potting->AddElement(CE, natoms = 2);
  Potting->AddElement(HE, natoms = 4);
  Potting->AddElement(OE, natoms = 1);
  
  // BGO - Bismuth, Germanium, Oxygen
  density = 7.1 * g/cm3;
  G4Material* BGO = new G4Material(name="BGO", density, ncomponents = 3);
  BGO->AddElement(BiE, natoms = 4);  
  BGO->AddElement(GeE, natoms = 3);
  BGO->AddElement(OE, natoms = 12);  


  // CsI - Caesium Iodide - from G3 umatgen
  density = 4.51 * g/cm3;
  G4Material* CsI = new G4Material(name="CsI", density, ncomponents = 2);
  CsI->AddElement(CsE, fractionmass = 0.5115);  
  CsI->AddElement(IE, fractionmass = 0.4885);

  // PICSIT general - made up blend of CsI, Al and electronics for PiCsIT
  density = 2.92 * g/cm3;
  G4Material* PICSIT = new G4Material(name="PICSIT", density, ncomponents = 7);
  PICSIT->AddElement(AlE, fractionmass = 0.82);
  //PICSIT->AddElement(ElectroMix, fractionmass = 0.03);
  PICSIT->AddElement(CE, fractionmass = 0.05*0.03);
  PICSIT->AddElement(CuE, fractionmass = 0.1*0.03);
  PICSIT->AddElement(SiE, fractionmass = 0.05*0.03); 
  PICSIT->AddElement(AlE, fractionmass = 0.8*0.03);
  //PICSIT->AddElement(CsI, fractionmass = 0.15);
  PICSIT->AddElement(CsE, fractionmass = 0.5115*0.15);  
  PICSIT->AddElement(IE, fractionmass = 0.4885*0.15);


//  ! HOSTAFORM - PSAC central hub: polyoxymethylene (POMC) CH2O
//mixt  40  hosta       -3  1.41
//                     1.00000  1.00  0.50
//                    12.01115  6.00  0.25
//                    15.99940  8.00  0.25
  density = 1.41 * g/cm3;
  G4Material* Hosta = new G4Material(name="Hosta", density, ncomponents = 3);
  Hosta->AddElement(CE, natoms = 1);
  Hosta->AddElement(HE, natoms = 2);
  Hosta->AddElement(OE, natoms = 1);


  // TiAlV - Titanium, Aluminium, Vanadium
  density = 4.492 * g/cm3;
  G4Material* TAV = new G4Material(name="TiAlV", density, ncomponents = 3);
  TAV->AddElement(TiE, natoms = 6);  //WTF?!
  TAV->AddElement(AlE, natoms = 4);  //WTF?!
  TAV->AddElement(VE, natoms = 1);    //WTF?!

  // Fuel
  density = 1.0 * g/cm3;
  G4Material* Fuel = new G4Material(name="Fuel", density, ncomponents = 2);
  Fuel->AddElement(HE, natoms = 4);  
  Fuel->AddElement(NE, natoms = 1);

  // Test volume - NA 23
  density = 0.968*g/cm3;  
  a = 23*g/mole;
  z = 11.;
  G4Material* Na23 = new G4Material(name="Sodium23", z, a, density);

  // Test volume - Au 197
  density = 19.3*g/cm3;  
  a = 197.*g/mole;
  z = 79.;
  G4Material* Au197= new G4Material(name="Gold197", z, a, density);


  /*
  G4cout << "--------------###------------------" << G4endl ;  
  G4cout << *Vacuum << G4endl ;
  G4cout << Vacuum->GetName() << G4endl ;
  G4cout << Vacuum << G4endl ;
  G4cout << &Vacuum << G4endl ;
  G4cout << "--------------###------------------" << G4endl ;

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  G4cout << "buh " << G4cout ;
  G4cout << G4Material::GetMaterialTable() << G4endl;
  */

  const G4MaterialTable* MaterialTable = (G4Material::GetMaterialTable());
  // G4cout << *MaterialTable << G4endl;
  // G4cout << "ubuh" << G4endl;


  /* vector<G4Material* const>::iterator iter = MaterialTable->begin();  
  int MatCount = -1 ;
  for( ; iter != MaterialTable->end(); ++iter )
    {MatCount++;}
  */

  // G4cout << MaterailTable << G4endl ;

  // G4cout << "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" << G4endl ;
  // G4cout << MatCount << G4endl ;

  /* 
  G4Material* MaterialArray[] = 
  {
    Al,
    AlHoney1,
    AlHoney2,
    AlHoney3,
    Pb,
    Sn,
    Ta,
    Cu,
    CarbonFibre,
    Korex,
    Si,
    Ti,
    Ag,
    ElectroMix,
    SiC,
    SMMix,
    CZT,
    Shield,
    Vacuum,
  } ;

  G4cout << MaterialArray[18]->GetName() << G4endl ; 
  G4cout << MaterialArray[18] << G4endl ;
  G4Material* temp = MaterialArray[18] ;
  G4cout << temp->GetName() << G4endl ;
  

  return &MaterialArray[0]; 
  */ 

  return MaterialTable ;
}

/*
const G4MaterialTable* PIMPMaterials::GetMaterialTable()
{
  // const G4MaterialTable* Table = G4Material::GetMaterialTable() ;
  // G4cout << "Table: " << Table << endl ; 
  // return &Table ;
  return;
}
*/ 

/*
G4Material* PIMPMaterials::GetMaterial(G4String MatName) 
{
  G4Material* ReturnMaterial = GetMaterial(MatName);
  return ReturnMaterial ;
}
*/














