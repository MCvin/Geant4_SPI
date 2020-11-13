/*
Event Action
=========================================================================

 */

#include "PIMPEventAction.hh"
// #include "PIMPHit.hh"

//Removed due to G4.4.0.p01 upgrade
//#include "g4rw/tvordvec.h"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include "G4StackManager.hh"

PIMPEventAction::PIMPEventAction()  //:collectionID(-1)
{
  // Create a Stack Manager
  //G4StackManager* Stack = new G4StackManager ;

}

PIMPEventAction::~PIMPEventAction()
{

}

void PIMPEventAction::BeginOfEventAction(const G4Event* evt)
{

  //G4cout << "Begin Of Event Action" << G4endl ;
  
  // Get event number
  //////G4int evtNb = evt->GetEventID();

  /*
  G4TrajectoryContainer *TCofEvent = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (TCofEvent) n_trajectories = TCofEvent->entries();  
  G4cout << "Entries: " << n_trajectories << G4endl ;
  for(G4int i=0; i<n_trajectories; i++) 
    { 
      G4Trajectory* trj = (G4Trajectory*)
	((*(evt->GetTrajectoryContainer()))[i]);
      
      G4cout << "Track: " << trj->GetTrackID() << 
	" Particle: " <<  trj->GetParticleName() << G4endl ; 
    }

  */
  /*
  // Create a Sensitive Detector Manager class
  if(collectionID == -1)
    {
      G4SDManager *SDman = G4SDManager::GetSDMpointer();
      collectionID = SDman->GetCollectionID("hitsColl");
    }
  */

}

void PIMPEventAction::EndOfEventAction(const G4Event* evt)
{
  /*
  G4cout << "End Of Event Action" << G4endl ;
  G4TrajectoryContainer *TCofEvent = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (TCofEvent) n_trajectories = TCofEvent->entries();  
  G4cout << "Entries: " << n_trajectories << G4endl ;
  for(G4int i=0; i<n_trajectories; i++) 
    { 
      G4Trajectory* trj = (G4Trajectory*)
	((*(evt->GetTrajectoryContainer()))[i]);
      
      G4cout << "Track: " << trj->GetTrackID() << 
	" Particle: " <<  trj->GetParticleName() << G4endl ; 
    }

  */

  /*  G4cout << "Begin Of Event Action" << G4endl ;

  G4int evtNb = evt->GetEventID();

  // Get the Hit Collection of the event
  G4HCofThisEvent *HCofEvent = evt->GetHCofThisEvent();
  PIMPHC *PIMPHitsColl = (PIMPHC*)(HCofEvent->GetHC(collectionID));

  G4int numhits = PIMPHitsColl->entries();
  
  PIMPHitsColl->PrintAllHits();
  */
}







