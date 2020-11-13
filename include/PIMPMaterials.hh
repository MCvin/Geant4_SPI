#ifndef PIMPMaterials_H
#define PIMPMaterials_H 1

// class G4Material ;

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

class PIMPMaterials // : public G4Material
{
public:
  PIMPMaterials();
  ~PIMPMaterials();

  const G4MaterialTable* CreateMaterialTable();
  //*G4MaterialTable CreateMaterialTable();
  G4Material* GetMaterial(G4String MatName);  

  //private:
  // G4Material Vac;

};

#endif
