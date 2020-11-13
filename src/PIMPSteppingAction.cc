/*
Stepping Action
=========================================================================

 */

#include "PIMPSteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
//extern long long Count ;
PIMPSteppingAction::PIMPSteppingAction()  
{

}

PIMPSteppingAction::~PIMPSteppingAction()
{

}

void PIMPSteppingAction::UserSteppingAction(const G4Step* Step)
{
  // G4cout << Step->GetTrack()->GetDefinition()->GetParticleName() << G4endl ;
  /*
  if( Step->GetTrack()->GetDefinition()->GetParticleName() == "Be7[0.0]" )
    {
      G4cout << "Ooops, Beryllium-7 !" << G4endl ;
      Step->GetTrack()->SetTrackStatus(fStopAndKill);      
    }
  */
  if(  Step->GetTrack()->GetCurrentStepNumber() > 1000 ) 
    {
	const G4Run* aRun = G4RunManager::GetRunManager()->GetCurrentRun();
	double Count = aRun->GetNumberOfEvent();

      G4cout << "Killing event too many steps! Greater than 1000 steps for event " << Count << G4endl ;
      Step->GetTrack()->SetTrackStatus(fStopAndKill);     
    }
  /*
  if( Step->GetTrack()->GetDefinition()->GetParticleName() == "Ho163[0.0]" )
    {
      G4cout << "Ooops, Holmium-163 !" << G4endl ;
      Step->GetTrack()->SetTrackStatus(fStopAndKill);
    }

  if( Step->GetTrack()->GetDefinition()->GetParticleName() == "Tl194[0.0]" )
    {
      G4cout << "Ooops, Thallium-194 !" << G4endl ;
      Step->GetTrack()->SetTrackStatus(fStopAndKill);      
    }

  if( Step->GetTrack()->GetDefinition()->GetParticleName() == "Pb201[628.9]" )
    {
      G4cout << "Ooops, Lead-201m !" << G4endl ;
      Step->GetTrack()->SetTrackStatus(fStopAndKill);      
    }

    G4cout << Step->GetTrack()->GetDefinition()->GetParticleName() << G4endl ;
  */
  /*
  
  if (Step->GetTrack()->GetParentID() < 0 ||
      Step->GetTrack()->GetTrackID() < 0 ) 
    {
      Step->GetTrack()->SetWeight(0.1) ;
    }
  */

  //G4cout << "Weight: " << Step->GetTrack()->GetWeight() << G4endl ;
  //  G4ThreeVector Pol = Step->GetTrack()->GetPolarization();
  //  G4cout << Step->GetTrack()->GetCurrentStepNumber()<<"    "<< Pol << G4endl;

}



