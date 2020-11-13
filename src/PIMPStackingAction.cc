/*
Stacking Action
=========================================================================

 */

#include "PIMPStackingAction.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ios.hh"

//G4ThreeVector cPosition ;
//G4ThreeVector cMomentum ;
//G4ParticleDefinition* cDefinition ;
//G4double cTime ;

PIMPStackingAction::PIMPStackingAction()  
{

}

PIMPStackingAction::~PIMPStackingAction()
{

}

G4ClassificationOfNewTrack PIMPStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  
  // G4cout << "Stacking Action " << G4endl ;
  G4ClassificationOfNewTrack classification = fWaiting;

  const G4String  particleName = aTrack->GetDefinition()->GetParticleName();
  //G4cout << "Stacking Name: "<< particleName << G4endl ;
 
  if(particleName.substr(0,5) == "Pb201" || // Pb201[628.9] or Pb201[629.4] or Pb201[629.1]
     particleName == "Be7[0.0]"     ||
     particleName == "Ho163[0.0]"   ||  // now have patches for the data
     particleName == "Tl194[0.0]"   ||  // now have patches for the data
     particleName.substr(0,5) == "Ir191" ||
     particleName.substr(0,5) == "Ta177" || // Ta177[185.9]
     particleName == "C11[0.0]" )  
    { 
      G4cout << "Track killed due to the unwelcome presence of " << particleName << G4endl ;
      classification = fKill;
    }

  //  G4cout << particleName << ": " << aTrack->GetDefinition()->GetBaryonNumber() << 
  //  " Track: " << aTrack->GetTrackID() << " wgt: " << aTrack->GetWeight() << G4endl ;

  /*   
  if( aTrack->GetDefinition()->GetBaryonNumber() > 4 &&
      aTrack->GetTrackID() > 0 )
    {
      // Add a lot more tracks
      
      classification = fPostpone;
      //  G4cout << " POST " << particleName << ": " << aTrack->GetDefinition()->GetBaryonNumber() << 
      // " Track: " << aTrack->GetTrackID() << G4endl ;
  
      // Copy vertex info ...
      //cPosition =  aTrack->GetPosition() ;
      //cMomentum =  aTrack->GetMomentumDirection() ;
      //cDefinition = aTrack->GetDefinition() ;
      //cTime = aTrack->GetGlobalTime() ;
	
    }
  */
  
 return classification;
}

void  PIMPStackingAction::PrepareNewEvent()
{
  
  
  //    This method is called by G4StackManager at the begining of
  //  each event.
  //    Be careful that the urgentStack and the waitingStack of 
  //  G4StackManager are empty at this moment, because this method
  //  is called before accepting primary particles. Also, note that
  //  the postponeStack of G4StackManager may have some postponed
  //  tracks.
  

  //  G4cout << "Prepare new event is called" << G4endl ;
  
  //stackManager->TransferOneStackedTrack( origin, destination);
  // stackManager->PushOneTrack(aTrack,G4VTrajectory *newTrajectory)
  

  // Rip out some code from StackManger and use it to make
  // mulitple copies in my postponed stack
  /*

  G4StackedTrack * aStackedTrack;
  G4TrackStack tmpStack;
  // get number of postponed tracks
  G4TrackStack * postponeStack = stackManager->GetPostponedTrackStack();
  postponeStack->TransferTo(&tmpStack);

  G4int PostponedTracks = tmpStack.GetNTrack() ;  
  for(G4int j=0 ; j < PostponedTracks ; j++)
    
    {
      aStackedTrack=tmpStack.PopFromStack();
     
      G4Track* aTrack = aStackedTrack->GetTrack();
      aTrack->SetTrackID(-1 - 2*j);
      postponeStack->PushToStack(aStackedTrack);

      // Add a extra particle 
      G4ParticleDefinition* cParticleDef = aTrack->GetDynamicParticle()->GetDefinition();
      //const G4ThreeVector cParticleMom = aTrack->GetDynamicParticle()->GetMomentumDirection();
      //G4double cParticleKinetic = aTrack->GetDynamicParticle()->GetKineticEnergy();
      //G4DynamicParticle* cParticle = new G4DynamicParticle( cParticleDef,
      //							    cParticleMom,
      //						    cParticleKinetic) ;
      G4double cTime = aTrack->GetGlobalTime();
      const G4ThreeVector cPosition = aTrack->GetPosition();
      
      //G4Track* cTrack = new G4Track(cParticle,
      //				    cTime,
      //				    cPosition); 
      //G4VTrajectory * cTraj = aStackedTrack->GetTrajectory() ;  
      //G4StackedTrack * cStackedTrack = new G4StackedTrack(cTrack,
      //						  cTraj);
//      postponeStack->PushToStack(cStackedTrack);

      for(int i=0 ; i <4 ; i++)
	{
	  const G4ThreeVector dParticleMom = aTrack->GetDynamicParticle()->GetMomentumDirection();
	  G4double dParticleKinetic = aTrack->GetDynamicParticle()->GetKineticEnergy();
	  G4DynamicParticle* dParticle = new G4DynamicParticle( cParticleDef,
								dParticleMom,
								dParticleKinetic) ;
	  G4Track* dTrack = new G4Track(dParticle,
					cTime,
					cPosition); 
	  G4VTrajectory * dTraj = aStackedTrack->GetTrajectory() ;  
	  G4StackedTrack * dStackedTrack = new G4StackedTrack(dTrack,
							      dTraj);
	  postponeStack->PushToStack(dStackedTrack);
	}
      
    }

  */  
  
}
 
