
#ifndef PIMPHit_h
#define PIMPHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
// #include "globals.hh"
#include "G4ThreeVector.hh"
// #include "fitsio.h"

class PIMPHit : public G4VHit
{
public:
  PIMPHit();
  ~PIMPHit();
  PIMPHit(const PIMPHit&);
  const PIMPHit& operator=(const PIMPHit&);
  G4int operator==(const PIMPHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();
  //void WriteOut(G4int NumberOfHits);
      

public:  
  
  void RecordHitNo(G4int HitNo);
  void RecordPosition(G4ThreeVector Position);
  void RecordEnergyDeposit(G4double EnergyDeposit);
  void RecordDeltaTime(G4double dTime);
  void RecordVolumeName(G4String VolumeName);
  void RecordVolumeNumber(G4int VolumeNumber);
  void RecordCopyNumber(G4int CopyNumber);  
  void RecordPrimeEnergy(G4double PrimeEnergy);
  void RecordPrimeVector(G4ThreeVector PrimeVector);
  void RecordWeight(G4double Weight);

  G4int ReturnHitNo() { return i_HitNo;}
  G4ThreeVector ReturnPosition() { return i_Position;};
  G4double ReturnEnergyDeposit() { return i_EnergyDeposit;};
  G4double ReturnDeltaTime() { return i_dTime;};
  G4String ReturnVolumeName() { return i_VolumeName;};
  G4int ReturnVolumeNumber() { return i_VolumeNumber;};
  G4int ReturnCopyNumber() { return i_CopyNumber;};  
  G4double ReturnPrimeEnergy() { return i_PrimeEnergy;};
  G4ThreeVector ReturnPrimeVector() { return i_PrimeVector;};
  G4double ReturnDepth() { return i_Position.z();};
  G4double ReturnWeight() { return i_Weight;};

private:
  
  G4int i_HitNo;
  G4ThreeVector i_Position;
  G4double i_EnergyDeposit;
  G4double i_dTime;
  G4String i_VolumeName;
  G4int i_VolumeNumber;
  G4int i_CopyNumber;  
  G4double i_PrimeEnergy;
  G4ThreeVector i_PrimeVector;
  G4double i_Depth;
  G4double i_Weight;

};

typedef G4THitsCollection<PIMPHit> PIMPHitsCollection;

extern G4Allocator<PIMPHit> PIMPHitAllocator ;

inline void* PIMPHit::operator new(size_t)
{
    void* aHit;
  aHit = (void*) PIMPHitAllocator.MallocSingle();
  return aHit;
}

inline void PIMPHit::operator delete(void* aHit)
{ 
    PIMPHitAllocator.FreeSingle((PIMPHit*) aHit);
}

#endif


