/*
  Sensitive Detector Event
  ================================================================
 
 */

#include "PIMPSensitive.hh"
#include "PIMPGeometry.hh"
//#include "PIMPPrimaryGeneratorAction.hh"

#include "G4HCofThisEvent.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
// cfitsio
//#include "fitsio.h"
//#include <time.h>
//#include <gaussians.hh>
#include "Events.hh"
#include <string>

//extern G4double PrimeEnergy;

PIMPSensitive::PIMPSensitive(G4String name, Events *InDataArray)
: G4VSensitiveDetector(name) {
    collectionName.insert("Collection");
    DataArray = InDataArray;
    HitNumber = 0;
}

PIMPSensitive::~PIMPSensitive() {
    ;
}

void PIMPSensitive::Initialize(G4HCofThisEvent *HCE) {

    Collection = new PIMPHitsCollection(SensitiveDetectorName, collectionName[0]);
    static G4int HCID = -1;
    if (HCID < 0) {
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    HCE->AddHitsCollection(HCID, Collection);

  
  //SpectralType = DataArray->Get_SpectralType();

  //EventTime = clock() ;

}

G4bool PIMPSensitive::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {

    // o Event Parameters
    //   (Prime energy, Prime vector)
    // o Interaction Parameters
    //   (E deposit, time increment, volume, depth)
    G4double Edep = aStep->GetTotalEnergyDeposit();
    // Check the energy deposit
    if ((Edep == 0.)) return false;

    G4double dTime = aStep->GetTrack()->GetGlobalTime();

    G4String VolumeName = aStep->GetTrack()->GetVolume()->GetName();

    G4int VolNum = ReturnVolumeNumber(VolumeName);
    if (VolNum == 0) {	//Volume not registered
    G4cout << "Sensitive Volume: " << VolumeName
	   << " NOT registered" << G4endl;
    }

    // Process the rest of the information given that we know the volume
    G4TouchableHistory *theTouchable
            = (G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable());

    G4int CopyNumber = theTouchable->GetReplicaNumber(Level); // Get correct level. Ge=1

    G4ThreeVector EdepPosition = aStep->GetTrack()->GetPosition();
    ////if (CopyNumber == 5) G4cout << "Position = " << EdepPosition << G4endl;
    //G4ThreeVector Pol = aStep->GetTrack()->GetPolarization();

    //G4double Weight = aStep->GetTrack()->GetWeight() ;
    //// G4double InitEnergy = aStep->GetTrack()->GetVertexKineticEnergy();//GetTotalEnergy();
    ////G4ThreeVector InitPosition = aStep->GetTrack()->GetPosition();
    //G4cout << PrimeEnergy << "    " << InitEnergy <<G4endl;


    // Create a PIMP Hit object
    PIMPHit* newHit = new PIMPHit();

    // Include this Hit in the Hits Collection and record the number
    HitNumber = Collection->insert(newHit);

    // Set the relevant parameters to record
    newHit->RecordHitNo(HitNumber);
    newHit->RecordPosition(EdepPosition);
    newHit->RecordEnergyDeposit(Edep);
    newHit->RecordDeltaTime(dTime);
    newHit->RecordVolumeName(VolumeName);
    newHit->RecordVolumeNumber(VolNum);
    newHit->RecordCopyNumber(CopyNumber);
    //  newHit->RecordPrimeEnergy(InitEnergy);
    //  newHit->RecordPrimeVector(InitPosition);
    //  newHit->RecordWeight(Weight);

    // Debug
    //G4cout << VolumeName << " " << CopyNumber  << " " << Edep  << G4endl;


    return true;
}

void PIMPSensitive::EndOfEvent(G4HCofThisEvent* HCE) {
    const G4Run* aRun = G4RunManager::GetRunManager()->GetCurrentRun();
    long Count = aRun->GetNumberOfEvent();

    //  const G4Event* aEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
    // G4ThreeVector InitPosition = aEvent->GetPrimaryVertex()->GetPosition();

    G4double InitEnergy = DataArray->Get_PrimeEnergy();
    //aEvent->GetPrimaryVertex()->GetVertexKineticEnergy();//GetTotalEnergy(); 

    //  G4cout << PrimeEnergy << "    " << InitEnergy <<G4endl;

    G4int NbHits = Collection->entries();
    //  G4double InitEnergy = (*Collection)[NbHits-1]->ReturnPrimeEnergy() ;
    //  G4ThreeVector InitPosition = (*Collection)[NbHits-1]->ReturnPrimeVector() ;
    //  G4double InitEnergy = 0.0;
    //  G4ThreeVector InitPosition;

    //G4cout << "New Event!" << G4endl;

    if (NbHits > 300000) {
        G4cout << "Skipped, due to interaction excess " << NbHits << G4endl;
    }
    if (NbHits != 0 && NbHits <= 300000) {
        for (G4int i = 0; i < NbHits; i++) {
            Time[i] = (*Collection)[i]->ReturnDeltaTime();
            Energy[i] = (*Collection)[i]->ReturnEnergyDeposit();
            Depth[i] = (*Collection)[i]->ReturnDepth() ;
            Volume[i] = (*Collection)[i]->ReturnVolumeNumber();
            Replica[i] = (*Collection)[i]->ReturnCopyNumber();
            Position[i] = (*Collection)[i]->ReturnPosition();
            //Weight[i] = (*Collection)[i]->ReturnWeight() ;
            //if(Weight[i] == 1.) {outputWeight[i] = 1 ;} // so as to save memory in the FITS
            //if(Weight[i] == 0.1) {outputWeight[i] = 2 ;}
            // 1 = prompt, 2 = delayed
            /////InitEnergy =(*Collection)[0]->ReturnPrimeEnergy() ;
            //InitPosition = (*Collection)[0]->ReturnPrimeVector() ;

            if (Volume[i] == 1) {
                GeHit = true;
            }
	    //G4cout << "Hit[i] = " << Volume[i] <<"  "<<Replica[i]<< " " << Energy[i] << G4endl;

        }

	// rearrange the array so that we add up all deposits inside any sensitive volume
	G4int AdjustedNbHits = AdjustInteractions(NbHits);

	//for (G4int i = 0; i < AdjustedNbHits; i++) {
	//    G4cout << "AdjustedHit[i] = " << Volume[i] <<"  "<<Replica[i]<< " " << Energy[i] << G4endl;
	//}


        if (GeHit == true) {
            // 	  G4cout << "Hit " << Count << G4endl;
            if (SpectralType == "CR" || SpectralType == "CDX") {

                // Event details
                //	    fits_write_col(fptr,TDOUBLE,1,RowNum,1,1,&PrimeEnergy,&status) ;
                //	    fits_write_col(fptr,TDOUBLE,2,RowNum,1,3,&PrimeVecXYZ,&status) ;
                //	    // Interaction details
                //	    fits_write_col(fptr,TDOUBLE,3,RowNum,1,AdjustedNbHits,&Time,&status) ;
                //	    fits_write_col(fptr,TDOUBLE,4,RowNum,1,AdjustedNbHits,&Energy,&status) ;
                //	    fits_write_col(fptr,TDOUBLE,5,RowNum,1,AdjustedNbHits,&Depth,&status) ;
                //	    fits_write_col(fptr,TINT,6,RowNum,1,AdjustedNbHits,&Volume,&status) ;
                //	    fits_write_col(fptr,TINT,7,RowNum,1,AdjustedNbHits,&Replica,&status) ;
                //	    fits_write_col(fptr,TINT,8,RowNum,1,1,&AdjustedNbHits,&status) ;
                //	    //fits_write_col(fptr,TINT,9,RowNum,1,AdjustedNbHits,&outputWeight,&status) ;
                //	    fits_report_error(stderr, status);
            }

            if (SpectralType == "PointSource" || SpectralType == "GRB" || SpectralType == "CutoffPL" || SpectralType == "BrokenPL") {

	        //(M. Chauvin 01/2012)
	        //GeHit veto'd?
                G4bool VetoEvent = FALSE;
                //for (G4int i = 0; i < NbHits; i++) {
		for (G4int i = 0; i < AdjustedNbHits; i++) {

		    if (Volume[i] == 2) {  //Plastic scintillator
		        if ((Energy[i] > 0.500)) {  //threshold = 500keV
			    VetoEvent = TRUE;
			    //G4cout << "VetoHit[i] = " << Volume[i] <<"  "<<Replica[i]<< " " << Energy[i] << G4endl;
			}
		    }
		    if (Volume[i] > 2) {  //ACS
		        if ((Energy[i] > 0.100)) {  //threshold = 100keV
			    VetoEvent = TRUE;
			    //G4cout << "VetoHit[i] = " << Volume[i] <<"  "<<Replica[i]<< " " << Energy[i] << G4endl;
			}
		    }
                }

                if (VetoEvent == FALSE) {  //GeHit not veto'd

                    G4double Pixels[19];
                    G4double EdepPosX[19];
                    G4double EdepPosY[19];
                    G4double EdepPosZ[19];
                    for (G4int i = 0; i < 19; i++) {
                        Pixels[i] = 0;
                        EdepPosX[i] = 0;
                        EdepPosY[i] = 0;
                        EdepPosZ[i] = 0;
                    }
                    //for (G4int i = 0; i < NbHits; i++) {
		    for (G4int i = 0; i < AdjustedNbHits; i++) {

                        if (Volume[i] == 1) {
			    //Pixels[Replica[i]] += Energy[i]; //add the Ge energy if not done by AdjustInteractions
                            Pixels[Replica[i]] = Energy[i];
                            EdepPosX[Replica[i]] = Position[i].x();
                            EdepPosY[Replica[i]] = Position[i].y();
                            EdepPosZ[Replica[i]] = Position[i].z();
                        }

                    }

		    //number of pixel hit
                    G4int PixelsHit = 0;
                    for (G4int i = 0; i < 19; i++) {
                        if (Pixels[i] > 0) {
                            PixelsHit++;
                        }
                    }

                    if (PixelsHit != 1) {
		        //Multiple
                        for (int i = 0; i < 19; i++) {
                            if (Pixels[i] > 0) {
                                //save table to multiple
                                //G4cout << "Saving Multiple" << G4endl;
                                DataArray->Put_mEnergyIn(InitEnergy);
                                DataArray->Put_mEdep(Pixels[i]);
                                DataArray->Put_mPixel(i);
                                DataArray->Put_mEvent(Count);
                                DataArray->Put_mEventX(EdepPosX[i]);
                                DataArray->Put_mEventY(EdepPosY[i]);
                                DataArray->Put_mEventZ(EdepPosZ[i]);
                          //// G4cout << "Position Stored = " << i << " " << EdepPosX[i] << "  " << EdepPosY[i] << "  " <<EdepPosZ[i] << G4endl;
                            }
                        }
                    } else {
		        //Single
                        for (int i = 0; i < 19; i++) {
                            if (Pixels[i] > 0) {
                                //save table to Single
                                //G4cout << "Saving Single" << G4endl;
                                DataArray->Put_EnergyIn(InitEnergy);
                                DataArray->Put_Edep(Pixels[i]);
                                DataArray->Put_Pixel(i);
                                DataArray->Put_Event(Count);
                                DataArray->Put_EventX(EdepPosX[i]);
                                DataArray->Put_EventY(EdepPosY[i]);
                                DataArray->Put_EventZ(EdepPosZ[i]);
                            }
                        }
                    }


                }
            }
        }
    }

}

void PIMPSensitive::clear() {
}

void PIMPSensitive::DrawAll() {
}

void PIMPSensitive::PrintAll() {
}

G4int PIMPSensitive::ReturnVolumeNumber(G4String VolumeName) {
    G4int VolumeNumber = 0;

    // Set the volume number but also set the level that the volume is at within
    // the object.
    // The "Level" is also set and this is a parameter of the replica number
    // If Level is not zero then you are looking at the copy of the volume higher up
    // in the heirarchy e.g: Germanium inside the SPI pixel, there's only one Ge but
    // 19 copies of the pixel units.
    if (VolumeName ==
            "SPIDetGermanium") {
        VolumeNumber = 1;
        Level = 1;
    }
    if (VolumeName ==
            "SPIMaskVetoScint") {
        VolumeNumber = 2;
        Level = 0;
    }
    if (VolumeName ==
            "SPIUpVetoBGO") {
        VolumeNumber = 3;
        Level = 0;
    }
    if (VolumeName ==
            "SPIMidVetoBGOa") {
        VolumeNumber = 4;
        Level = 0;
    }
    if (VolumeName ==
            "SPIMidVetoBGOb") {
        VolumeNumber = 5;
        Level = 0;
    }
    if (VolumeName ==
            "SPIMidVetoBGOc") {
        VolumeNumber = 6;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile1") {
        VolumeNumber = 7;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile2") {
        VolumeNumber = 8;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile3") {
        VolumeNumber = 9;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile4") {
        VolumeNumber = 10;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile5") {
        VolumeNumber = 11;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile6") {
        VolumeNumber = 12;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile7") {
        VolumeNumber = 13;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile8") {
        VolumeNumber = 14;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile9") {
        VolumeNumber = 15;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile10") {
        VolumeNumber = 16;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile11") {
        VolumeNumber = 17;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile12") {
        VolumeNumber = 18;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile13") {
        VolumeNumber = 19;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile14") {
        VolumeNumber = 20;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile15") {
        VolumeNumber = 21;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile16") {
        VolumeNumber = 22;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile17") {
        VolumeNumber = 23;
        Level = 0;
    }
    if (VolumeName ==
            "SPILowVetoBeTile18") {
        VolumeNumber = 24;
        Level = 0;
    }
    if (VolumeName ==
            "GeDet") {
        VolumeNumber = 1;
        Level = 0;
    }
    if (VolumeName ==
            "Germanium_block") {
        VolumeNumber = 88;
        Level = 0;
    }
    if (VolumeName ==
            "TestBlock") {
        VolumeNumber = 99;
        Level = 0;
    }

    return VolumeNumber;

}


G4int PIMPSensitive::AdjustInteractions(G4int NbHits) {  //(M. Chauvin 01/2012)
    // now to rearrange the array so that we add up all deposits inside any
    // veto of ACS tile. The problem being, that the hits collection can have
    // 200,000 interactions and if we let the events list record every interaction
    // then the file sizes go mental.

    G4int AdjustedNbHits = 0;
    G4double Read[300000] ;

    for (G4int i = 0; i < NbHits; i++) {
        Read[i] = 0;
    }

    for (G4int i = 0; i < NbHits; i++) {
        if (Read[i] == 0) {  // new sensitive volume
	    Time[AdjustedNbHits] = Time[i];
	    Energy[AdjustedNbHits] = Energy[i];
	    Depth[AdjustedNbHits] = Depth[i];
	    Volume[AdjustedNbHits] = Volume[i];
	    Replica[AdjustedNbHits] = Replica[i];
            Position[AdjustedNbHits] = Position[i];

	    for (G4int j = i+1; j < NbHits; j++) {
	        if (Volume[i] == Volume[j] && Replica[i] == Replica[j]) {
		    Energy[AdjustedNbHits] += Energy[j];  // add up deposit

		    Read[j] = 1;  // not to be read
		}
	    }

	    AdjustedNbHits++;
	}
    }

    return AdjustedNbHits;

}

G4int PIMPSensitive::AdjustInteractions_old(G4int NbHits) {
    // now to rearrange the array so that we add up all deposits inside any
    // veto of ACS tile. The problem being, that the hits collection can have
    // 200,000 interactions and if we let the events list record every interaction
    // then the file sizes go mental.

    GeHit = false;
    G4int AdjustedNbHits = 0;
    G4int CurrentVolume = 0;
    G4int CurrentReplica = 0;
    G4double CurrentTime = 0.0;

    for (G4int i = 0; i < NbHits; i++) {
        if (Volume[i] > 1) // not in the SPI Ge detector units
        {
            if (Volume[i] == CurrentVolume && Replica[i] == CurrentReplica) {
                if ((Time[i] - CurrentTime) < 1000.) // interactions < 1 micro sec apart
                {
                    Energy[AdjustedNbHits] = Energy[AdjustedNbHits] + Energy[i];
                    CurrentTime = Time[i];
                } else {
                    Time[AdjustedNbHits] = Time[i - 1];
                    Depth[AdjustedNbHits] = Depth[i - 1];
                    Volume[AdjustedNbHits] = CurrentVolume;
                    Replica[AdjustedNbHits] = CurrentReplica;
                    AdjustedNbHits++;

                    CurrentVolume = Volume[i];
                    CurrentReplica = Replica[i];
                    CurrentTime = Time[i];
                    Energy[AdjustedNbHits] = Energy[i];
                }
            } else {
                if (i != 0) {
                    Time[AdjustedNbHits] = Time[i - 1];
                    Depth[AdjustedNbHits] = Depth[i - 1];
                    Volume[AdjustedNbHits] = CurrentVolume;
                    Replica[AdjustedNbHits] = CurrentReplica;
                    AdjustedNbHits++;
                }
                CurrentVolume = Volume[i];
                CurrentReplica = Replica[i];
                CurrentTime = Time[i];
                Energy[AdjustedNbHits] = Energy[i];
            }
        } else // interaction in the SPI Ge
        {
            GeHit = true;
            if (CurrentVolume > 1 && i != 0) {
                Time[AdjustedNbHits] = Time[i - 1];
                Depth[AdjustedNbHits] = Depth[i - 1];
                Volume[AdjustedNbHits] = CurrentVolume;
                Replica[AdjustedNbHits] = CurrentReplica;
                AdjustedNbHits++;
            }

            Time[AdjustedNbHits] = Time[i];
            Energy[AdjustedNbHits] = Energy[i];
            Depth[AdjustedNbHits] = Depth[i];
            Volume[AdjustedNbHits] = Volume[i];
            Replica[AdjustedNbHits] = Replica[i];

            AdjustedNbHits++;
            CurrentVolume = Volume[i];
            CurrentReplica = Replica[i];
            CurrentTime = Time[i];
        }

        if (i == (NbHits - 1)) // read out last event
        {
            Time[AdjustedNbHits] = Time[i];
            Depth[AdjustedNbHits] = Depth[i];
            Volume[AdjustedNbHits] = CurrentVolume;
            Replica[AdjustedNbHits] = CurrentReplica;
            AdjustedNbHits++;
        }
    }

    return AdjustedNbHits;

}
