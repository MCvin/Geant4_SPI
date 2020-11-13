
#ifndef PIMPSteppingAction_h
#define PIMPSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class PIMPSteppingAction : public G4UserSteppingAction
{
public:
  PIMPSteppingAction();
  ~PIMPSteppingAction();
  
public:
 
  void UserSteppingAction(const G4Step* Step);

};

#endif

    
