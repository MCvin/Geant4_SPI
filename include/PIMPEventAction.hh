
#ifndef PIMPEventAction_h
#define PIMPEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//class PIMPEventActionMessenger;

class G4Event ;

class PIMPEventAction : public G4UserEventAction
{
public:
  PIMPEventAction();
  ~PIMPEventAction();
  
public:
  void   BeginOfEventAction(const G4Event*);
  void   EndOfEventAction(const G4Event*);
    
  //  void SetDrawFlag   (G4String val)  {drawFlag = val;};
  //  void SetPrintModulo(G4int    val)  {printModulo = val;};
    
private:
  //  G4int                       collectionID;                
  // G4String                    drawFlag;
  // G4int                       printModulo;                         
  //  ExN03EventActionMessenger*  eventMessenger;

};

#endif

    
