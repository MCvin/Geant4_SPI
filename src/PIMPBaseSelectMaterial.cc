// Material Selection Base Class

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "PIMPBaseSelectMaterial.hh"
//#include "G4ios.hh"
#include <iostream>
#include <vector>
using namespace std;

PIMPBaseSelectMaterial::PIMPBaseSelectMaterial()
{;}

PIMPBaseSelectMaterial::~PIMPBaseSelectMaterial()
{;}

G4Material* PIMPBaseSelectMaterial::PIMPSelectMaterial(G4String MatName, 
						       const G4MaterialTable* MaterialTable)
{
  G4bool Found = false ;
  G4Material* Material ;
  //  vector<G4Material* >::iterator iter = MaterialTable->begin();
  //  for( ; iter != MaterialTable->end(); ++iter )
  vector<G4Material*>::const_iterator iter;
//   for(vector<G4Material* const>::const_iterator iter = MaterialTable->begin();iter != MaterialTable->end(); ++iter )
  for(iter = MaterialTable->begin() ; iter != MaterialTable->end(); ++iter )
    {
      Material = *iter ;	
      if(Material->GetName() == MatName)
	{
	  iter = (MaterialTable->end())-1;
	  Found = true ;
	}
    };

  if(Found == true)
    {  
      G4cout << " Material: " << MatName << " selected" << G4endl ;
    }
  else
    {
      G4cout << " Material: " << MatName << " NOT FOUND, better check out your geometry files..." << G4endl; 
    }
  return Material ;

}

