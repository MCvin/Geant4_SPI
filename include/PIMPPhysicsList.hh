//
//  PIMPPhysicsList.cc 2020-11-05  Maxime Chauvin
//

#ifndef PIMPPhysicsList_h
#define PIMPPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

class PIMPPhysicsList: public G4VModularPhysicsList
{
public:
    PIMPPhysicsList();
    ~PIMPPhysicsList();

    virtual void SetCuts();

};

#endif
