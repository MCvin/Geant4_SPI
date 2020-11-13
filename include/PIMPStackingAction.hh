
#ifndef PIMPStackingAction_h
#define PIMPStackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

class G4Track;

#include "PIMPHit.hh"

class PIMPStackingAction : public G4UserStackingAction
{
public:
  PIMPStackingAction();
  ~PIMPStackingAction();
  
public:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void PrepareNewEvent();


};

#endif

    
