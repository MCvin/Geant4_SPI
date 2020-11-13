/*
  Primary Generator Action 
  ================================================
 
 */
#include "PIMPPrimaryGeneratorAction.hh"
#include "PIMPSpaceEnvironment.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "PIMPRandomEnergy.hh"
#include "PIMPGammaRayBurst.hh"
//#include "fitsio.h"
#include "G4Event.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4SingleParticleSource.hh"
#include "G4UImanager.hh"
#include "globals.hh"
#include "Randomize.hh"
#include <fstream>

//extern float Exposure ;
//extern G4String SpectralType ;

//G4double PrimeEnergy ;
//G4ThreeVector PrimeVector ;
//long long Count ;


#include "Events.hh"

//extern Events *DataArray;

PIMPPrimaryGeneratorAction::PIMPPrimaryGeneratorAction() {
}

PIMPPrimaryGeneratorAction::~PIMPPrimaryGeneratorAction() {
    delete particleGun;
    //  delete getParameters ;
    delete CosmicSpectra;

    // Status message
    G4cout << "============= AND I'M SPENT ===============" << G4endl;
    G4cout << ParticleCount << " Particles Processed" << G4endl;
    G4cout << "===========================================" << G4endl;


}

void PIMPPrimaryGeneratorAction::Initialize() {
    ReportEvery = 1000000;
    G4int Status = 0;
    bool Diagnose = FALSE;

    if (SpectralType == "CR" || SpectralType == "CDX") {
        //		  G4int n_particle = 1;
        //		  particleGun = new G4ParticleGun(n_particle);
        //		  getParameters = new G4GeneralParticleSource();
    } else {
        //G4int n_particle = 1;
        particleGun = new G4SingleParticleSource();
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
        particleGun->SetParticleDefinition(particle);

        if (SpectralType == "PointSource") {
            // ****************  Crab Spectrum
            //			G4double alpha = -2.12;//crab
            //G4double alpha = -2.07;//vela
            E_min = 0.1; //MeV
            E_max = 3.0; //30//MeV


            power = -alpha + 1.0;
            min = (pow(E_min, power)) / power;
            max = (pow(E_max, power)) / power;


        } else if (SpectralType == "BrokenPL") {
            E_min = 100; //keV
            E_max = 3000; //keV

            TotalIntegration = 0;
            G4double Break = Ebreak;
            G4double Ene = E_min; // lower limit is 12 keV
            G4double IntegrateUp = 0.;
            G4double UpToSegment = 0.;


            while (Ene <= Break) {
                G4double KevIntegration[5] = {0., 0., 0., 0., 0.};
                for (int i = 0; i < 5; i++) {
                    KevIntegration[i] = (norm * std::pow((Ene), -alpha)); // *
                    //   std::pow(2.71828183, (-1.0 * Ene / beta)));
                    //if (Diagnose == TRUE) G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
                    //    ( pow(((Ene+1.0)/100.),Alpha) *
                    // 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
                    Ene = Ene + 1.0;
                }
                Ene = Ene - 1.0;
                G4double TotalSegment = 1.0 * ((14. / 45.) * KevIntegration[0] +
                        (64. / 45.) * KevIntegration[1] +
                        (24. / 45.) * KevIntegration[2] +
                        (64. / 45.) * KevIntegration[3] +
                        (14. / 45.) * KevIntegration[4]);
                UpToSegment = IntegrateUp;
                IntegrateUp = IntegrateUp + TotalSegment;
                //                if (Diagnose == TRUE) G4cout << "Random:: " << Random
                //                        << " IntegrateUp: " << IntegrateUp
                //                        << " Energy: " << Ene << G4endl;
            }
            Ene = Ene - 4.0;
            G4double UpToKeV;
            if (Diagnose == TRUE) G4cout << "Before second while : " << IntegrateUp << G4endl;
            while (Ene <= Break) {
                UpToKeV = UpToSegment;
                UpToSegment = UpToSegment + (norm * (std::pow(Ene, -alpha)) +
                        (norm * std::pow((Ene + 1.0), -alpha))) / 2.0;
                //if (Diagnose == TRUE) cout  << " UpToSegment: " << UpToSegment
                //       << " Energy: " << Ene << endl;
                Ene = Ene + 1.0;
            }

            Ene = Ene - 1.0;
            //Ene = Break;




            LowE_total = UpToKeV;//UpToSegment;//IntegrateUp;
            IntegrateUp = 0;
            G4cout << "Ene afer first while = " << Ene << G4endl;
            while (Ene < E_max) {
                G4double KevIntegration[5] = {0., 0., 0., 0., 0.};
                for (int i = 0; i < 5; i++) {
                    KevIntegration[i] = (norm * std::pow((Break), beta - alpha) *
                            std::pow(Ene, -beta));
                    //if (Diagnose == TRUE) G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
                    //    ( pow(((Ene+1.0)/100.),Alpha) *
                    // 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
                    Ene = Ene + 1.0;
                }
                Ene = Ene - 1.0;
                G4double TotalSegment = 1.0 * ((14. / 45.) * KevIntegration[0] +
                        (64. / 45.) * KevIntegration[1] +
                        (24. / 45.) * KevIntegration[2] +
                        (64. / 45.) * KevIntegration[3] +
                        (14. / 45.) * KevIntegration[4]);
                UpToSegment = IntegrateUp;
                IntegrateUp = IntegrateUp + TotalSegment;
                //                if (Diagnose == TRUE) G4cout << "Random:: " << Random
                //                        << " IntegrateUp: " << IntegrateUp
                //                        << " Energy: " << Ene << G4endl;
            }
            Ene = Ene - 4.0;
            UpToKeV = 0;
            if (Diagnose == TRUE) G4cout << "Before second while : " << IntegrateUp << G4endl;
            while (Ene < E_max) {
                UpToKeV = UpToSegment;
                UpToSegment = UpToSegment + (norm * (std::pow(Break, beta - alpha) *
                        std::pow(Ene, -beta)) +
                        (norm * std::pow((Break), beta - alpha)) *
                        std::pow(Ene + 1.0, -beta)) / 2.0;
                //if (Diagnose == TRUE) cout  << " UpToSegment: " << UpToSegment
                //        << " Energy: " << Ene << endl;
                Ene = Ene + 1.0;
            }

            Ene = Ene - 1.0;


            TotalIntegration = LowE_total + UpToKeV;//UpToSegment;//IntegrateUp;




            //            for (G4double Ene = E_min; Ene < E_max; Ene++) {
            //                TotalIntegration = TotalIntegration + (((norm * std::pow(Ene, -alpha) * std::pow(2.71828183, (-1.0 * Ene / beta)))+
            //                        (norm * std::pow((Ene + 1.0), -alpha) * std::pow(2.71828183, (-1.0 * (Ene + 1.0) / beta)))) / 2.0);
            //            }
            G4cout << "Total Integration = " << TotalIntegration << "  Low E = " << LowE_total << G4endl;


        } else if (SpectralType == "CutoffPL") {
            E_min = 100; //keV
            E_max = 3000; //keV
            //power = alpha + 1.0;
            //min = (pow(E_min, power)) / power;
            //max = (pow(E_max, power)) / power;
            TotalIntegration = 0;
            G4double Break = E_max;
            G4double Ene = E_min; // lower limit is 12 keV
            G4double IntegrateUp = 0.;
            G4double UpToSegment;


            while (Ene < E_max) {
                G4double KevIntegration[5] = {0., 0., 0., 0., 0.};
                for (int i = 0; i < 5; i++) {
                    KevIntegration[i] = (norm * std::pow((Ene), -alpha) *
                            std::pow(2.71828183, (-1.0 * Ene / beta)));
                    //if (Diagnose == TRUE) G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
                    //    ( pow(((Ene+1.0)/100.),Alpha) *
                    // 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
                    Ene = Ene + 1.0;
                }
                Ene = Ene - 1.0;
                G4double TotalSegment = 1.0 * ((14. / 45.) * KevIntegration[0] +
                        (64. / 45.) * KevIntegration[1] +
                        (24. / 45.) * KevIntegration[2] +
                        (64. / 45.) * KevIntegration[3] +
                        (14. / 45.) * KevIntegration[4]);
                UpToSegment = IntegrateUp;
                IntegrateUp = IntegrateUp + TotalSegment;
                //                if (Diagnose == TRUE) G4cout << "Random:: " << Random
                //                        << " IntegrateUp: " << IntegrateUp
                //                        << " Energy: " << Ene << G4endl;
            }

            TotalIntegration = IntegrateUp;




            //            for (G4double Ene = E_min; Ene < E_max; Ene++) {
            //                TotalIntegration = TotalIntegration + (((norm * std::pow(Ene, -alpha) * std::pow(2.71828183, (-1.0 * Ene / beta)))+
            //                        (norm * std::pow((Ene + 1.0), -alpha) * std::pow(2.71828183, (-1.0 * (Ene + 1.0) / beta)))) / 2.0);
            //            }
            G4cout << "Total Integration = " << TotalIntegration << G4endl;
        } else if (SpectralType == "GRB") {
            Status = PIMPSetGammaRayBurstDetails(SpectralType);
            if (Status != 0) {
                G4cout << "----------------------------" <<
                        "- GRB details incorrect    -" <<
                        "++++++++++++++++++++++++++++" << G4endl;
            }
        } else {
            G4cout << "SpectralType Not Defined!" << G4endl;
            exit(1);
        }
        G4String PosType = "Plane"; // a surface
        G4String shapeType = "Square"; // a square
        //G4String shapeType = "Circle"; // a square
        particleGun->GetPosDist()->SetPosDisType(PosType);
        particleGun->GetPosDist()->SetPosDisShape(shapeType);
        particleGun->GetPosDist()->SetHalfX(70.0 * cm);
        particleGun->GetPosDist()->SetHalfY(70.0 * cm);
        //particleGun->GetPosDist()->SetHalfX(22.15 * cm);
        //particleGun->GetPosDist()->SetHalfY(22.15 * cm);
        //particleGun->GetPosDist()->SetRadius(25.0 * cm);
        DataArray->Set_RASource(RASource);
        DataArray->Set_DECSource(DECSource);


        G4cout << "Yeah Baby, I'm initialised! Polarisation of " << PolarAngle << G4endl;
    }

    last_seconds = time(NULL);

    ParticleCount = 0;

    // Parameters to the box surrounding INTEGRAL
    HalfX = 215.0 * cm;
    HalfY = 215.0 * cm;
    HalfZ = 241.65 * cm;
    SideArea = HalfY * 2 * HalfZ * 2; // both sides the same
    EndArea = HalfX * 2 * HalfY * 2;

    CosmicSpectra = new PIMPRandomEnergy;


}

void PIMPPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    bool Diagnose = FALSE;
    //if (ParticleCount > 399990) Diagnose = TRUE;
    if (SpectralType == "CR" || SpectralType == "CDX") {
        //     G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        //     G4ParticleDefinition* particle = particleTable->FindParticle(PrimaryParticleType);
        //     particleGun->SetParticleDefinition(particle);
        //     G4double RandomEnergy = CosmicSpectra->GenerateRandomEnergy(&Breaks,
        //     								&Boundry[0],
        //     								&Index[0],
        //     								&Norm[0]) ;
        //     particleGun->SetParticleEnergy(RandomEnergy*MeV);

        //     //++++++++++++ A PLANE ++++++++++++++++++++++++++++++++++++++++++++++
        //     //G4String PosType = "Plane"; // a surface
        //     //G4String shapeType = "Square"; // a square
        //     //getParameters->SetPosDisType(PosType);
        //     //getParameters->SetCentreCoords(G4ThreeVector(-93.8*cm,0., 400.0 * cm));
        //     //getParameters->SetPosDisShape(shapeType);
        //     //getParameters->SetHalfX(50.0 * mm);
        //     //getParameters->SetHalfY(50.0 * mm);
        //     //getParameters->GeneratePointsInPlane();
        //     //particle_position = getParameters->GetParticlePosition();
        //     //G4ThreeVector Direction = G4ThreeVector(0., 0., -1.);
        //     //particleGun->SetParticleMomentumDirection(Direction);
        //     //particleGun->SetParticlePosition(particle_position);
        //     //PrimeEnergy = particleGun->GetParticleEnergy();
        //     //PrimeVector = Direction ;

        //     //+++++++ ISOTROPIC AND HOMOGENIUS +++++++++++++++++++++++++++++++++++

        //     SetIsotropicParameters();
        //     particleGun->SetParticleMomentumDirection(RandomDirection);
        //     particleGun->SetParticlePosition(RandomPosition);
        //     PrimeEnergy = particleGun->GetParticleEnergy();
        //     PrimeVector = RandomDirection ;

        //     // Set the Vertex
        //     particleGun->GeneratePrimaryVertex(anEvent);
    } else {

        // G4cout << " Event " << Count << G4endl;

        G4double Epos = 0.0;
        if (SpectralType == "PointSource") {
            G4double rand = G4UniformRand();
            Epos = pow((((rand * (max - min)) + min) * power), 1 / power);
	    //Debug
	    //Epos=0.6617; //137Cs
	    //Epos=0.06; //
	    //Epos=2.223;
	    //G4cout << "E_fired= " << Epos << G4endl;

        } else if (SpectralType == "BrokenPL") {

            if (Diagnose == TRUE) G4cout << "Starting Energy Calculation" << G4endl;
            G4double rand = G4UniformRand();
            if (Diagnose == TRUE) G4cout << "TotalIntegration : " << TotalIntegration << "  " << rand << G4endl;
            G4double Random = rand * TotalIntegration;
            // The idea is to integrate up, using Bode's Law, in increments until the
            // 5kev segments total greater than "Random". Then to go back and find out which
            // kev bin "Random" lies in and interpolate linearly.
            if (Diagnose == TRUE) G4cout << "Random : " << Random << G4endl;

            G4double Break = Ebreak;
            G4double Ene = E_min; // lower limit is 12 keV
            G4double IntegrateUp = 0.;
            G4double UpToSegment;
            if (Random <= LowE_total) {

                if (Diagnose == TRUE) G4cout << "Before first while : " << IntegrateUp << " " << Random << G4endl;
                while (IntegrateUp < Random) {
                    G4double KevIntegration[5] = {0., 0., 0., 0., 0.};
                    for (int i = 0; i < 5; i++) {
                        KevIntegration[i] = norm * (std::pow((Ene), -alpha));
                        //if (Diagnose == TRUE) G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
                        //    ( pow(((Ene+1.0)/100.),Alpha) *
                        // 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
                        Ene = Ene + 1.0;
                    }
                    Ene = Ene - 1.0;
                    G4double TotalSegment = 1.0 * ((14. / 45.) * KevIntegration[0] +
                            (64. / 45.) * KevIntegration[1] +
                            (24. / 45.) * KevIntegration[2] +
                            (64. / 45.) * KevIntegration[3] +
                            (14. / 45.) * KevIntegration[4]);
                    UpToSegment = IntegrateUp;
                    IntegrateUp = IntegrateUp + TotalSegment;
                    if (Diagnose == TRUE) G4cout << "Random:: " << Random
                            << " IntegrateUp: " << IntegrateUp
                            << " Energy: " << Ene << G4endl;
                }
                // Random is inside this segment
                Ene = Ene - 4.0;
                G4double UpToKeV;
                if (Diagnose == TRUE) G4cout << "Before second while : " << IntegrateUp << " " << Random << G4endl;
                while (UpToSegment < Random) {
                    UpToKeV = UpToSegment;
                    UpToSegment = UpToSegment + (norm * (std::pow(Ene, -alpha)) +
                            (norm * std::pow((Ene + 1.0), -alpha))) / 2.0;
                    if (Diagnose == TRUE) cout << "Random:: " << Random
                            << " UpToSegment: " << UpToSegment
                            << " Energy: " << Ene << endl;
                    Ene = Ene + 1.0;
                }

                Ene = Ene - 1.0;
                // Find the parameters for the linear interpolation
                G4double Slope = (norm * (std::pow((Ene + 1.0), -alpha)) -
                        (norm * std::pow((Ene), -alpha))) / (1.0);
                G4double Intercept = (norm * std::pow(Ene, -alpha)) - (Slope * Ene);
                Random = Random - UpToKeV;

                if (Diagnose == TRUE) G4cout << "Energy: " << Ene << " Random: " << Random
                        << " Slope: " << Slope
                        << " Intercept: " << Intercept << " Y at Ene: " << (norm * std::pow(Ene, -alpha)) << G4endl;
                // ---- Now interpolate ----
                G4double A = Slope / 2.0;
                G4double B = Intercept; //Slope*Ene + Intercept ;
                G4double C = -1.0 * Random;

                if (Diagnose == TRUE) G4cout << "A: " << A << " B: " << B
                        << " C: " << C << G4endl;
                // ---- Now interpolate ----

                Epos = (((-1.0 * B + std::pow((std::pow(B, 2) - 4 * A * C), 0.5)) / (2.0 * A)) + Ene)* 0.001;
                //Epos = ((Random - Intercept) / Slope)*0.001;
                //if (Diagnose == TRUE) cout << "Returns ... " << Epos << endl;
            } else {
                //Second Section
                Ene = Break;
                Random = Random - LowE_total;
                if (Diagnose == TRUE) G4cout << "Before first while : " << IntegrateUp << " " << Random << G4endl;
                while (IntegrateUp < Random && Ene < E_max) {
                    G4double KevIntegration[5] = {0., 0., 0., 0., 0.};
                    for (int i = 0; i < 5; i++) {
                        KevIntegration[i] = (norm * std::pow((Break), beta - alpha) *
                                std::pow(Ene, -beta));
                        //if (Diagnose == TRUE) G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
                        //    ( pow(((Ene+1.0)/100.),Alpha) *
                        // 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
                        Ene = Ene + 1.0;
                    }
                    Ene = Ene - 1.0;
                    G4double TotalSegment = 1.0 * ((14. / 45.) * KevIntegration[0] +
                            (64. / 45.) * KevIntegration[1] +
                            (24. / 45.) * KevIntegration[2] +
                            (64. / 45.) * KevIntegration[3] +
                            (14. / 45.) * KevIntegration[4]);
                    UpToSegment = IntegrateUp;
                    IntegrateUp = IntegrateUp + TotalSegment;
                    if (Diagnose == TRUE) G4cout << "Random:: " << Random
                            << " IntegrateUp: " << IntegrateUp
                            << " Energy: " << Ene << G4endl;
                }
                // Random is inside this segment
                Ene = Ene - 4.0;
                G4double UpToKeV;
                if (Diagnose == TRUE) G4cout << "Before second while : " << IntegrateUp << " " << Random << G4endl;
                while (UpToSegment < Random && Ene < E_max) {
                    UpToKeV = UpToSegment;
                    UpToSegment = UpToSegment + ((norm * std::pow((Break), beta - alpha) *
                            std::pow(Ene, -beta))+
                            (norm * std::pow((Break), beta - alpha) *
                            std::pow(Ene + 1.0, -beta))) / 2.0;
                    if (Diagnose == TRUE) cout << "Random:: " << Random
                            << " UpToSegment: " << UpToSegment
                            << " Energy: " << Ene << endl;
                    Ene = Ene + 1.0;
                }

                Ene = Ene - 1.0;
                // Find the parameters for the linear interpolation
                G4double Slope = ((norm * (std::pow((Break), beta - alpha) *
                        std::pow((Ene + 1.0), -beta))) -
                        (norm * std::pow((Break), beta - alpha) *
                        std::pow((Ene), -beta))) / (1.0);
                G4double Intercept = (norm * std::pow(Break, beta - alpha) *
                        std::pow(Ene, -beta)) - (Slope * Ene);
                Random = Random - UpToKeV;

                if (Diagnose == TRUE) G4cout << "Energy: " << Ene << " Random: " << Random
                        << " Slope: " << Slope
                        << " Intercept: " << Intercept << " Y at Ene: " << (norm * std::pow(Break, beta - alpha) *
                        std::pow(Ene, -beta)) << G4endl;
                // ---- Now interpolate ----
                G4double A = Slope / 2.0;
                G4double B = Intercept; //Slope*Ene + Intercept ;
                G4double C = -1.0 * Random;

                if (Diagnose == TRUE) G4cout << "A: " << A << " B: " << B
                        << " C: " << C << G4endl;
                // ---- Now interpolate ----

                Epos = (((-1.0 * B + std::pow((std::pow(B, 2) - 4 * A * C), 0.5)) / (2.0 * A)) + Ene)* 0.001;
                //Epos = ((Random - Intercept) / Slope)*0.001;





            }

            if (Diagnose == TRUE) G4cout << "Returns ... " << Epos << " For Event " << ParticleCount << G4endl;

	    //G4cout << "E_fired= " << Epos << G4endl;


        } else if (SpectralType == "CutoffPL") {
            if (Diagnose == TRUE) G4cout << "Starting Energy Calculation" << G4endl;

            G4double Random = G4UniformRand() * TotalIntegration;
            // The idea is to integrate up, using Bode's Law, in increments until the
            // 5kev segments total greater than "Random". Then to go back and find out which
            // kev bin "Random" lies in and interpolate linearly.

            G4double Break = E_max;
            G4double Ene = E_min; // lower limit is 12 keV
            G4double IntegrateUp = 0.;
            G4double UpToSegment;

            if (Diagnose == TRUE) G4cout << "Before first while : " << IntegrateUp << " " << Random << G4endl;
            while (IntegrateUp < Random) {
                G4double KevIntegration[5] = {0., 0., 0., 0., 0.};
                for (int i = 0; i < 5; i++) {
                    KevIntegration[i] = norm * (std::pow((Ene), -alpha) *
                            std::pow(2.71828183, (-1.0 * Ene / beta)));
                    //if (Diagnose == TRUE) G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
                    //    ( pow(((Ene+1.0)/100.),Alpha) *
                    // 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
                    Ene = Ene + 1.0;
                }
                Ene = Ene - 1.0;
                G4double TotalSegment = 1.0 * ((14. / 45.) * KevIntegration[0] +
                        (64. / 45.) * KevIntegration[1] +
                        (24. / 45.) * KevIntegration[2] +
                        (64. / 45.) * KevIntegration[3] +
                        (14. / 45.) * KevIntegration[4]);
                UpToSegment = IntegrateUp;
                IntegrateUp = IntegrateUp + TotalSegment;
                if (Diagnose == TRUE) G4cout << "Random:: " << Random
                        << " IntegrateUp: " << IntegrateUp
                        << " Energy: " << Ene << G4endl;
            }
            // Random is inside this segment
            Ene = Ene - 4.0;
            G4double UpToKeV;
            if (Diagnose == TRUE) G4cout << "Before second while : " << IntegrateUp << " " << Random << G4endl;
            while (UpToSegment < Random) {
                UpToKeV = UpToSegment;
                UpToSegment = UpToSegment + (norm * (std::pow(Ene, -alpha) *
                        std::pow(2.71828183, (-1.0 * Ene / beta))) +
                        (norm * std::pow((Ene + 1.0), -alpha) *
                        std::pow(2.71828183, (-1.0 * (Ene + 1.0) / beta)))) / 2.0;
                if (Diagnose == TRUE) cout << "Random:: " << Random
                        << " UpToSegment: " << UpToSegment
                        << " Energy: " << Ene << endl;
                Ene = Ene + 1.0;
            }

            Ene = Ene - 2.0;
            // Find the parameters for the linear interpolation
            G4double Slope = (norm * (std::pow((Ene + 1.0), -alpha) *
                    std::pow(2.71828183, (-1.0 * (Ene + 1.0) / beta))) -
                    (norm * std::pow((Ene), -alpha) *
                    std::pow(2.71828183, (-1.0 * (Ene) / beta)))) / (1.0);
            G4double Intercept = (norm * std::pow(Ene, -alpha) *
                    std::pow(2.71828183, (-1.0 * Ene / beta))) - (Slope * Ene);
            Random = Random - UpToKeV;

            if (Diagnose == TRUE) G4cout << "Energy: " << Ene << " Random: " << Random
                    << " Slope: " << Slope
                    << " Intercept: " << Intercept << " Y at Ene: " << (norm * std::pow(Ene, -alpha) *
                    std::pow(2.71828183, (-1.0 * Ene / beta))) << G4endl;
            // ---- Now interpolate ----
            G4double A = Slope / 2.0;
            G4double B = Intercept; //Slope*Ene + Intercept ;
            G4double C = -1.0 * Random;

            if (Diagnose == TRUE) G4cout << "A: " << A << " B: " << B
                    << " C: " << C << G4endl;
            // ---- Now interpolate ----

            Epos = (((-1.0 * B + std::pow((std::pow(B, 2) - 4 * A * C), 0.5)) / (2.0 * A)) + Ene)* 0.001;
            //Epos = ((Random - Intercept) / Slope)*0.001;
            if (Diagnose == TRUE) cout << "Returns ... " << Epos << endl;


            //            G4double A = Slope / 2.0;
            //            G4double B = Slope * Ene + Intercept;
            //            G4double C = -1.0 * Random;
            //            Random = (((-1.0 * B + std::pow((std::pow(B, 2) - 4 * A * C), 0.5)) / (2.0 * A)) + Ene)* 0.001;
            //
            //         cout << "Returns ... " << Random << endl ;
            //
            //        Epos = Random;
            //       exit(1);

	    //G4cout << "E_fired= " << Epos << G4endl;


        } else if (SpectralType == "GRB") {
            //**************  grb spectrum
            Epos = CosmicSpectra->GenerateRandomEnergy(Alpha,
                    Beta,
                    Ebreak,
                    LowEnergyTotal,
                    HighEnergyTotal);
        } else {
            G4cout << "SpectralType Not Defined!" << G4endl;
            exit(1);
        }




        //Set Particle Energy
        //PrimeEnergy = Epos ;
        DataArray->Set_PrimeEnergy(Epos);
        particleGun->GetEneDist()->SetMonoEnergy(Epos);

        //Set Particle Time
        particle_time = 0.0;
        particleGun->SetParticleTime(particle_time);

        //Set Source Position
        if (Diagnose == TRUE) G4cout << particle_position << endl;
        particleGun->GetPosDist()->SetCentreCoords(particle_position);
        //Set Source Direction
        if (Diagnose == TRUE) G4cout << particle_position << endl;
        particleGun->GetAngDist()->SetParticleMomentumDirection(Direction);
        if (Diagnose == TRUE) G4cout << particle_position << endl;

        //Set Source Polarisation
        particleGun->SetParticlePolarization(Polarisation);
        if (Diagnose == TRUE) G4cout << particle_position << endl;

        //Set Primary Vertex
        particleGun->GeneratePrimaryVertex(anEvent);

        if (Diagnose == TRUE) G4cout << particle_position << endl;


    }


    //************************** EVENT FLAG ****************************************
    //******************************************************************************

    if (ParticleCount % ReportEvery == 0 && ParticleCount > 0) {

        G4int status = 0;
        const G4Run* aRun = G4RunManager::GetRunManager()->GetCurrentRun();
        double Exposure = aRun->GetNumberOfEventToBeProcessed();

        time_t seconds;
        seconds = time(NULL);
        double dif = difftime(seconds, last_seconds);
        double TimeToFinish = (((Exposure - ParticleCount) / ReportEvery) * dif) / 60;
        last_seconds = seconds;

        double Done = (ParticleCount) / 1000000.0;
        G4cout << " " << Machine << "\t   has completed   " << Done << "\t Million events of " << Exposure << G4endl;
        G4cout << "   " << dif << " seconds since last report.  Due to finish in " << TimeToFinish << " minutes." << G4endl;

        status = DataArray->Write_To_File();
        if (Diagnose == TRUE) G4cout << " File Written " << G4endl;
        ofstream fout("Percentage"); //create output
        fout << (ParticleCount / Exposure)*100 << "  " << TimeToFinish << endl;
        fout.close();
        if (Diagnose == TRUE) G4cout << " File Written " << G4endl;
    }
    ParticleCount++;
}

// void PIMPPrimaryGeneratorAction::Set_DirectionParameters(G4int SourcePos) {
//     //double RASource;
//     // double DECSource;
// 
//     //int SourcePos=2;
//     switch (SourcePos) {
//         case 0:
//             //Calibration
//             RASource = 0.0;
//             DECSource = 0.0;
//             break;
//         case 1:
//             //Crab
//             RASource = 83.63320833;
//             DECSource = 22.01447222;
//             //RASource += 0.53224;
//             //DECSource += 2.259709;
//             break;
//         case 2:
//             //Vela
//             RASource = 128.836064;
//             DECSource = -45.176432;
//             break;
//         case 3:
//             RASource = 303.83266666667;
//             DECSource = 15.517361111111;
//             break;
//         case 4:
//             RASource = 287.1579167;
//             DECSource = -6.635388889;
//             break;
//         case 5:
//             //GRB041219a
//             RASource = 6.11533333;
//             DECSource = 62.84263917;
//             break;
//         case 6:
//             RASource = 267.1579167;
//             DECSource = -6.635388889;
//             break;
//         case 7:
//             //Cyg X-1
//             RASource = 299.5903165;
//             DECSource = 35.20160508;
//             break;
//         case 8:
//             //Solar Flare 28-10-2003 around 11h10
//             RASource = 212.355;
//             DECSource = -13.062;
//             break;
//         case 9:
//             //Solar Flare 7-3-2012 around 0h20
//             RASource = 347.9;
//             DECSource = -5.2;
//             break;
//         case 10:
//             //Transient
//             RASource = 266.294166667;
//             DECSource = -26.404083333;
//             break;
//         case 11:
//             //GRB120711
//             RASource = 94.67830;
//             DECSource = -70.99905;
//             break;
//         default:
//             G4cout << "No Position Found" << G4endl;
//             exit(1);
//     }
// 
//     G4cout << RASource << "     " << DECSource << "     " << RAPointing << "     " << DECPointing << "     " << ROLL << G4endl;
//     Theta = Separation(DegreesToHours(RASource), DECSource, DegreesToHours(RAPointing), DECPointing);
//     Phi = -PositionAngle(DegreesToHours(RASource), DECSource, DegreesToHours(RAPointing), DECPointing) - ROLL;
//     Psi = 0.0; //ROLL * deg ;
//     G4cout << Theta << "    " << Phi << G4endl;
// 
//     //particle_position = G4ThreeVector(0.0 * cm, 0.0 * cm, 500.0 * cm);
//     particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 500.0 * cm);
//     //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 229.8 * cm); //upon the mask pixels
//     //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 226.8 * cm); //under the mask pixels
//     //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 65.0 * cm); //10 cm upon the camera
//     //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 57.0 * cm); //2 cm upon the camera
//     //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 55.0 * cm); //0.8 cm inside the camera
//     //particle_position = G4ThreeVector(3.25 * cm, 6.0 * cm, 55.8 * cm); //mask hole on the camera
//     particle_position = particle_position.rotateY(DegreesToRadians(Theta) * rad);
//     particle_position = particle_position.rotateZ(DegreesToRadians(Phi) * rad);
// 
//     Direction = G4ThreeVector(0., 0., -1.);
//     Direction = Direction.rotateY(DegreesToRadians(Theta));
//     Direction = Direction.rotateZ(DegreesToRadians(Phi));
// 
// 
//     G4double PolarAng;
//     PolarAng = PolarAngle;
// 
//     //G4PolarisedCompton uses stokes and not 3-vector
//     if (PolarAngle < 999) {
//         G4double AngleRad = DegreesToRadians(PolarAng + ROLL);
//         //        Polarisation = G4ThreeVector(cos(AngleRad), sin(AngleRad), 0.);
// 
// 
// 
//         G4ThreeVector normal(1., 0., 0.);
//         //  G4cout <<normal<< G4endl;
//         G4ThreeVector kphoton = Direction; //particleGun->GetParticleMomentumDirection();
//         //G4cout <<kphoton<< G4endl;
//         G4ThreeVector product = normal.cross(kphoton);
//         //G4cout <<product<< G4endl;
//         G4double modul2 = product*product;
//         //G4cout <<modul2<< G4endl;
//         G4ThreeVector e_perpend(0., 0., 1.);
//         //G4cout <<e_perpend<< G4endl;
//         if (modul2 > 0.) e_perpend = (1. / std::sqrt(modul2)) * product;
//         // G4cout <<e_perpend<< G4endl;
//         G4ThreeVector e_paralle = e_perpend.cross(kphoton);
//         //G4cout <<e_paralle<< G4endl;
//         Polarisation = cos(AngleRad) * e_paralle + sin(AngleRad) * e_perpend;
//         //G4cout <<Polarisation<< G4endl;
// 
// 
//         //        Polarisation = G4ThreeVector(cos(DegreesToRadians(PolarAng)), sin(DegreesToRadians(PolarAng)), 0.);
//         //	Polarisation = Polarisation.rotateY(DegreesToRadians(Theta));
//         //	Polarisation = Polarisation.rotateZ(DegreesToRadians(Phi));
//         //	Polarisation = Polarisation.rotate(DegreesToRadians(-(Phi+ROLL)),particle_position);
//     } else { // unpolarised
// 
//         Polarisation = G4ThreeVector(0., 0., 0.);
//     }
// 
// 
//     //     Polarisation = Polarisation.rotateY(DegreesToRadians(Theta));
//     //     Polarisation = Polarisation.rotateZ(DegreesToRadians(Phi));
//     //     Polarisation = Polarisation.rotate(DegreesToRadians((Phi + ROLL)-90.0), particle_position);
// 
//     ////////    G4double AngleRad = DegreesToRadians(PolarAng - (Phi + ROLL));
//     //     G4double AngleRad = DegreesToRadians(PolarAng + Phi + ROLL);
//     //   G4ThreeVector StokesPolarisation = G4ThreeVector(
//     //            ((std::cos(AngleRad)*std::cos(AngleRad))-(std::sin(AngleRad)*std::sin(AngleRad))),
//     //            (2.0 * std::sin(AngleRad)* std::cos(AngleRad)), 0.0);
//     //   G4cout << "Degree = " << std::sqrt((StokesPolarisation.x()*StokesPolarisation.x())+
//     //   (StokesPolarisation.y()*StokesPolarisation.y())+
//     //   (StokesPolarisation.z()*StokesPolarisation.z())) << G4endl;
//     ////////   G4ThreeVector StokesPolarisation = G4ThreeVector(
//     ////////            std::cos(2.0*AngleRad),
//     ////////            std::sin(2.0*AngleRad), 0.0);
//     //    if (PolarAngle < 999) {
//     //        Polarisation = StokesPolarisation;
//     //    } else { // unpolarised
//     //        Polarisation = G4ThreeVector(0., 0., 0.);
//     //    }
// 
// 
// }

void PIMPPrimaryGeneratorAction::Set_DirectionParameters(G4double SourceRA, G4double SourceDEC) {

    RASource = SourceRA;
    DECSource = SourceDEC;

    G4cout << RASource << "     " << DECSource << "     " << RAPointing << "     " << DECPointing << "     " << ROLL << G4endl;
    Theta = Separation(DegreesToHours(RASource), DECSource, DegreesToHours(RAPointing), DECPointing);
    Phi = -PositionAngle(DegreesToHours(RASource), DECSource, DegreesToHours(RAPointing), DECPointing) - ROLL;
    Psi = 0.0; //ROLL * deg ;
    G4cout << Theta << "    " << Phi << G4endl;

    //particle_position = G4ThreeVector(0.0 * cm, 0.0 * cm, 500.0 * cm);
    particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 500.0 * cm);
    //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 229.8 * cm); //upon the mask pixels
    //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 226.8 * cm); //under the mask pixels
    //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 65.0 * cm); //10 cm upon the camera
    //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 57.0 * cm); //2 cm upon the camera
    //particle_position = G4ThreeVector(3.25 * cm, 0.0 * cm, 55.0 * cm); //0.8 cm inside the camera
    //particle_position = G4ThreeVector(3.25 * cm, 6.0 * cm, 55.8 * cm); //mask hole on the camera
    particle_position = particle_position.rotateY(DegreesToRadians(Theta) * rad);
    particle_position = particle_position.rotateZ(DegreesToRadians(Phi) * rad);

    Direction = G4ThreeVector(0., 0., -1.);
    Direction = Direction.rotateY(DegreesToRadians(Theta));
    Direction = Direction.rotateZ(DegreesToRadians(Phi));


    G4double PolarAng;
    PolarAng = PolarAngle;

    //G4PolarisedCompton uses stokes and not 3-vector
    if (PolarAngle < 999) {
        G4double AngleRad = DegreesToRadians(PolarAng + ROLL);

        G4ThreeVector normal(1., 0., 0.);
        //  G4cout <<normal<< G4endl;
        G4ThreeVector kphoton = Direction; //particleGun->GetParticleMomentumDirection();
        //G4cout <<kphoton<< G4endl;
        G4ThreeVector product = normal.cross(kphoton);
        //G4cout <<product<< G4endl;
        G4double modul2 = product*product;
        //G4cout <<modul2<< G4endl;
        G4ThreeVector e_perpend(0., 0., 1.);
        //G4cout <<e_perpend<< G4endl;
        if (modul2 > 0.) e_perpend = (1. / std::sqrt(modul2)) * product;
        // G4cout <<e_perpend<< G4endl;
        G4ThreeVector e_paralle = e_perpend.cross(kphoton);
        //G4cout <<e_paralle<< G4endl;
        Polarisation = cos(AngleRad) * e_paralle + sin(AngleRad) * e_perpend;
        //G4cout <<Polarisation<< G4endl;

    } else { // unpolarised

        Polarisation = G4ThreeVector(0., 0., 0.);
    }


}

void PIMPPrimaryGeneratorAction::Set_IsotropicParameters() {
    Phi;
    Theta;
    G4double rndm;
    rndm = G4UniformRand();
    rndm = rndm * (SideArea * 4 + EndArea * 2);
    Phi = 2 * pi * G4UniformRand();
    Theta = (acos(1 - 2 * G4UniformRand())) / 2;
    if (Theta > (pi / 2)) {

        G4cout << "Firing Particles the wrong way!" << G4endl;
    }


    // Straight down SPI
    RandomPosition.setX(-93 * cm + G4UniformRand()*40 * cm);
    RandomPosition.setY(-20.0 * cm + G4UniformRand()*40 * cm);
    RandomPosition.setZ(HalfZ);
    RandomDirection.setX(0);
    RandomDirection.setY(0);
    RandomDirection.setZ(-1);

}

G4double PIMPPrimaryGeneratorAction::Separation(G4double Alpha1, G4double Delta1, G4double Alpha2, G4double Delta2) {
    Delta1 = DegreesToRadians(Delta1);
    Delta2 = DegreesToRadians(Delta2);

    Alpha1 = HoursToRadians(Alpha1);
    Alpha2 = HoursToRadians(Alpha2);

    G4double x = cos(Delta1) * sin(Delta2) - sin(Delta1) * cos(Delta2) * cos(Alpha2 - Alpha1);
    G4double y = cos(Delta2) * sin(Alpha2 - Alpha1);
    G4double z = sin(Delta1) * sin(Delta2) + cos(Delta1) * cos(Delta2) * cos(Alpha2 - Alpha1);

    G4double value = atan2(sqrt(x * x + y * y), z);
    value = RadiansToDegrees(value);
    //	if (value < 0)
    //		value += 180;

    return value;
}

G4double PIMPPrimaryGeneratorAction::PositionAngle(G4double Alpha1, G4double Delta1, G4double Alpha2, G4double Delta2) {
    Delta1 = DegreesToRadians(Delta1);
    Delta2 = DegreesToRadians(Delta2);

    Alpha1 = HoursToRadians(Alpha1);
    Alpha2 = HoursToRadians(Alpha2);

    G4double DeltaAlpha = Alpha1 - Alpha2;
    G4double value = atan2(sin(DeltaAlpha), cos(Delta2) * tan(Delta1) - sin(Delta2) * cos(DeltaAlpha));
    value = RadiansToDegrees(value);
    //	if (value < 0)
    //		value += 180;

    return value;
}
