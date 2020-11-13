
#ifndef PIMPSensitive_h
#define PIMPSensitive_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include "PIMPHit.hh"
#include "Events.hh"

class G4Step;
class G4HCofThisEvent;


class PIMPSensitive : public G4VSensitiveDetector
{
public:
  PIMPSensitive(G4String, Events *InDataArray);
  ~PIMPSensitive();

  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  G4int ReturnVolumeNumber(G4String VolumeName);
  G4int AdjustInteractions(G4int NbHits);
  G4int AdjustInteractions_old(G4int NbHits);
  void Set_SpectralType(G4String Val) {
        SpectralType = Val;
    }

private:  
struct Data{
  double EnergyIn;
  double Edep;
  int    Pixel;
  double Event;
  int    Volume;
};
  PIMPHitsCollection *Collection;    
  G4int HitNumber  ;
  G4int Level;

  G4double Time[300000] ;
  G4double Energy[300000] ; 
  G4double Depth[300000] ;
  G4int Volume[300000] ;   
  G4int Replica[300000] ; 
  G4double Weight[300000] ;
  G4ThreeVector Position[300000] ;
  G4double tempenergy[300000];
  G4ThreeVector tempvect[300000];
  G4int outputWeight[300000] ;
  G4int EventTime ;
  //long long Count;
  G4bool GeHit;
  G4String SpectralType ;
  Events *DataArray;
};

#endif

 
