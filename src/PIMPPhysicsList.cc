//
//  PIMPPhysicsList.cc 2020-11-05  Maxime Chauvin
//

#include "PIMPPhysicsList.hh"

PIMPPhysicsList::PIMPPhysicsList() : G4VModularPhysicsList()
{
    G4int verb = 0;
    SetVerboseLevel(verb);

    // EM physics
    RegisterPhysics(new G4EmLivermorePolarizedPhysics());

    // Decay
    RegisterPhysics(new G4DecayPhysics());

    // Radioactive decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PIMPPhysicsList::~PIMPPhysicsList()
{
}

void PIMPPhysicsList::SetCuts()
{
    SetCutsWithDefault();
}
