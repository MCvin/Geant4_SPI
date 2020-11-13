/*
Crystal Hit
===========================================================

 */

#include "PIMPHit.hh"
//#include <stdio.h>
//#include <iostream.h>
//#include <iomanip.h>

#include "G4ios.hh"
// #include "g4std/fstream"
// #include "g4std/iomanip"
// #include "g4std/vector"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

// cfitsio
#include "fitsio.h"

//extern fitsfile *fptr ;

G4Allocator<PIMPHit> PIMPHitAllocator;

PIMPHit::PIMPHit()
{;}

PIMPHit::~PIMPHit()
{;}

PIMPHit::PIMPHit(const PIMPHit &right): G4VHit()
{;}

const PIMPHit &PIMPHit::operator=(const PIMPHit &right)
{ return *this; }

int PIMPHit::operator==(const PIMPHit& right) const
{ return (this==&right) ? 1 : 0; }


void PIMPHit::RecordHitNo(G4int HitNo) 
{i_HitNo = HitNo;
//G4cout << HitNo << " " ;
}
void PIMPHit::RecordPosition(G4ThreeVector Position) 
{i_Position = Position;}
void PIMPHit::RecordEnergyDeposit(G4double EnergyDeposit) 
{i_EnergyDeposit = EnergyDeposit;}
void PIMPHit::RecordDeltaTime(G4double dTime) 
{i_dTime = dTime;}
void PIMPHit::RecordVolumeName(G4String VolumeName) 
{i_VolumeName = VolumeName;}
void PIMPHit::RecordVolumeNumber(G4int VolumeNumber) 
{i_VolumeNumber = VolumeNumber;}
void PIMPHit::RecordCopyNumber(G4int CopyNumber) 
{i_CopyNumber = CopyNumber;}
void PIMPHit::RecordPrimeEnergy(G4double PrimeEnergy) 
{i_PrimeEnergy = PrimeEnergy;}
void PIMPHit::RecordPrimeVector(G4ThreeVector PrimeVector) 
{i_PrimeVector = PrimeVector;}
void PIMPHit::RecordWeight(G4double Weight) 
{i_Weight = Weight;}

void PIMPHit::Draw()
{;}

void PIMPHit::Print()
{;}
















