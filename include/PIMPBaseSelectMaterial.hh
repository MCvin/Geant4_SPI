// Material Selection Base Class


#ifndef PIMPBaseSelectMaterial_H
#define PIMPBaseSelectMaterial_H 1

#include "G4Material.hh"
#include "G4MaterialTable.hh"

class PIMPBaseSelectMaterial
{
public:
  PIMPBaseSelectMaterial();
  ~PIMPBaseSelectMaterial();

  G4Material* PIMPSelectMaterial(G4String MatName,
				  const G4MaterialTable* MaterialTable);

};

#endif

