/*
 * ==========================================================================================================
 *                              PIMP - Post-launch INTEGRAL Mass Model Package
 * ==========================================================================================================
 * 
 * Versions -
 *      10/03 - Dave Willis - Creation
 *      10/04 - Dave Clark  - Polarimetry
 *      06/10 - Dave Clark  - Version 2
 *      01/11 - Dave Clark  - Final clean up of code
 *	05/13 - Maxime Chauvin - Version 3.0 (LowVeto repair, fine detector and mask geometry, lots of other stuff...)
 * 
 * Command line -
 *      Program name - PIMP
 *      Arg[1] - Output file name
 *      Arg[2] - Random number seed (allows rerunning of exact events)
 *      Arg[3] - Source type (PointSource, GRB, CutoffPL, CDX, CR)
 *      Arg[4] - Number of events to simulate
 *      Arg[5] - Polarisation angle in degrees (999 for unpolarised)
 *      Arg[6] - Visualisation (0 = no vis, 1 = OpendGL vis)
 *      Arg[7] - RA
 *      Arg[8] - Dec
 *      Arg[9] - Roll
 *      Arg[10] - RA Source
 *      Arg[11] - DEC Source
 *      Arg[12] - Alpha (PointSource, CutoffPL only)
 *      Arg[13] - Beta (CutoffPL only)
 *      Arg[14] - Norm (CutoffPL only)
 *
 *      PIMP CygX1_Odeg.fits 1234 PointSource 50000000 0 0 83.63320833 22.01447222 0 1.36087 151.667 0.584414
 *
 *  Outputs -
 *      FileName.fits
 *          Ext 1 - Single Events (Initial Energy, Energy Deposit, Pixel Number, Event Number)
 *          Ext 2 - Multiple Events (Initial Energy, Energy Deposit, Pixel Number, Event Number, X, Y, Z)
 *              One line per deposit
 *
 *      Progress (text file)
 *          Percentage Complete, Time to finish
 *
 * ==========================================================================================================
 */


// --------------------------------------------------------------
//     This is the main()
// --------------------------------------------------------------

// Geant4
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SDManager.hh"

// User
#include "Events.hh"
#include "PIMPSensitive.hh"
#include "PIMPGeometry.hh"
#include "PIMPPhysicsList.hh"
#include "PIMPPrimaryGeneratorAction.hh"
#include "PIMPEventAction.hh"
#include "PIMPSteppingAction.hh"
#include "PIMPStackingAction.hh"

// C C++
#include <stdlib.h>
#include <stdio.h>
#include "fitsio.h"
#include <gaussians.hh>
#include "Randomize.hh"


int main(int argc, char** argv) {

    cout << "                 _____                          _____                      " << endl;
    cout << "                *     *   *  |*           *|   *     *                     " << endl;
    cout << "               *       |  |  | *         * |  *       *                    " << endl;
    cout << "               *       |  |  |  *       *  |  *       *                    " << endl;
    cout << "               *______*   |  |   *     *   |  *______*                     " << endl;
    cout << "               *          |  |    *   *    |  *                            " << endl;
    cout << "               *          |  |     * *     |  *                            " << endl;
    cout << "               *          *  *      *      *  *                            " << endl;
    cout << "                                                                           " << endl;
    cout << "                .---------------------------.                              " << endl;
    cout << "               |  YO, where my bitches at ?  |                             " << endl;
    cout << "                `--.  .---------------------`                              " << endl;
    cout << "                    ||    __________________                               " << endl;
    cout << "                     ` _/ ||                ~-_                            " << endl;
    cout << "                     ,/   //       /~-       /  ~-_  ________----------//  " << endl;
    cout << "    -----------------/-----------------|-------------------____________//  " << endl;
    cout << "   O--------------  /               ~~^ |                             | ~| " << endl;
    cout << "   }======{--------*____________________|_____________________________|  | " << endl;
    cout << "   '===== / /~~~'' *                   |         ____________________|-~   " << endl;
    cout << "    '----|  '___/ ||--------------------'----------|  '____/ //            " << endl;
    cout << "         `.______.'                                `._______.'             " << endl;

    //Get Machine
    //G4String Machine = getenv("HOST");
    //cout << "  Current Machine is " << Machine << endl;

    //Construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    //Setup Events Storage
    Events *DataArray = new Events();

    //Setup Sensitive Detector
    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    PIMPSensitive *Sens = new PIMPSensitive("Sensitive", DataArray);
    SDman->AddNewDetector(Sens);

    //Setup Geometry
    PIMPGeometry *Geometry = new PIMPGeometry(Sens);
    runManager->SetUserInitialization(Geometry);

    //Setup the physics
    PIMPPhysicsList* physics = new PIMPPhysicsList();
    runManager->SetUserInitialization(physics);

    //Setup the particle generator
    PIMPPrimaryGeneratorAction* PGA = new PIMPPrimaryGeneratorAction();

    //Get the pointer to the User Interface manager 
    G4UImanager* UIm = G4UImanager::GetUIpointer();

    //Set the seed
    G4Random::setTheSeed(time(0));

    if (argc==1) {// Simply observe the geometry
        G4VisManager* visManager = new G4VisExecutive;
        G4UIExecutive* UIe = new G4UIExecutive(argc, argv);
        visManager->Initialize();
        runManager->Initialize();
        UIm->ApplyCommand("/control/execute ../mac/vis.mac");
        UIe->SessionStart();
        delete visManager;
        delete UIm;
        delete UIe;
    }
    else {// batch mode
        // Define type of simulation and read in parameters
        G4String FITSfilename(argv[1]);
        long seed = atoi(argv[2]);
        G4String SpectralType(argv[3]);
        long long Exposure = atof(argv[4]);
        G4int PolarAngle = atoi(argv[5]);
        G4int visual = 0;
        visual = atoi(argv[6]);
        double RAPointing = atof(argv[7]);
        double DECPointing = atof(argv[8]);
        double ROLL = atof(argv[9]);
	    double RASource = atof(argv[10]);
        double DECSource = atof(argv[11]);
        double alpha;
        double beta;
        double Ebreak;
        double norm;
        if (SpectralType == "CutoffPL" || SpectralType == "PointSource" || SpectralType == "BrokenPL") {
	        alpha = atof(argv[12]);
	    }
        if (SpectralType == "CutoffPL" || SpectralType == "BrokenPL") {
            beta = atof(argv[13]);
            norm = atof(argv[14]);
        }
        if (SpectralType == "BrokenPL") {
            Ebreak = atof(argv[15]);
        }

        G4cout << "******************************************************" << G4endl;
        G4cout << "   File ->          " << FITSfilename << G4endl;
        G4cout << "   Seed ->          " << seed << G4endl;
        G4cout << "   Spectral Type -> " << SpectralType << G4endl;
        G4cout << "   Exposure ->      " << Exposure << G4endl;
        G4cout << "   Polarisation ->  " << PolarAngle << G4endl;
        G4cout << "   Visualisation -> " << visual << G4endl;
        G4cout << "   RAPointing ->    " << RAPointing << G4endl;
        G4cout << "   DECPointing ->   " << DECPointing << G4endl;
        G4cout << "   Roll Angle ->    " << ROLL << G4endl;
	    G4cout << "   RASource ->      " << RASource << G4endl;
        G4cout << "   DECSource ->     " << DECSource << G4endl;
        if (SpectralType == "CutoffPL" || SpectralType == "PointSource" || SpectralType == "BrokenPL") {
            G4cout << "   Alpha ->      " << alpha << G4endl;
        }
        if (SpectralType == "CutoffPL" || SpectralType == "BrokenPL") {
            G4cout << "   Beta ->       " << beta << G4endl;
            G4cout << "   Norm ->       " << norm << G4endl;
        }
        if (SpectralType == "BrokenPL") {
            G4cout << "   EBreak ->      " << Ebreak << G4endl;
        }
        G4cout << "******************************************************" << G4endl;

        G4String ParticleType;
        if (SpectralType != "CR") {
            ParticleType = "gamma";
        } else {
            ParticleType = "proton";
        }

        //PGA->Set_Machine(Machine);
        PGA->RecordPrimaryParticleType(ParticleType);
        PGA->Set_RAPointing(RAPointing);
        PGA->Set_DECPointing(DECPointing);
        PGA->Set_ROLL(ROLL);
        PGA->Set_PolarAngle(PolarAngle);
        PGA->Set_DirectionParameters(RASource,DECSource);
        PGA->Set_SpectralType(SpectralType);
        PGA->Set_DataArray(DataArray);
        if (SpectralType == "CutoffPL" || SpectralType == "PointSource" || SpectralType == "BrokenPL") {
            PGA->Set_Alpha(alpha);
            DataArray->Set_Alpha(alpha);
        }
        if (SpectralType == "CutoffPL" || SpectralType == "BrokenPL") {
            PGA->Set_Beta(beta);
            PGA->Set_Norm(norm);
            DataArray->Set_Beta(beta);
        }
        if (SpectralType == "BrokenPL") {
            PGA->Set_Ebreak(Ebreak);
            DataArray->Set_Ebreak(Ebreak);
        }
        PGA->Initialize();

        DataArray->Set_RAPointing(RAPointing);
        DataArray->Set_DECPointing(DECPointing);
        DataArray->Set_ROLL(ROLL);
        DataArray->Set_SpectralType(SpectralType);
        DataArray->Set_PolarAngle(PolarAngle);
        DataArray->Set_Exposure(Exposure);
        DataArray->Set_Seed(seed);

        Sens->Set_SpectralType(SpectralType);

        runManager->SetUserAction(PGA);
        runManager->SetUserAction(new PIMPEventAction);
        runManager->SetUserAction(new PIMPSteppingAction);
        runManager->SetUserAction(new PIMPStackingAction);

        //Initialize Geant4 kernel
        runManager->Initialize();

        // Set run parameters
        if (SpectralType == "PointSource" || SpectralType == "GRB" || SpectralType == "CutoffPL" || SpectralType == "BrokenPL") {
            DataArray->Create_New_File(FITSfilename);
            runManager->BeamOn(Exposure);
        }

        DataArray->Write_To_File();
        UIm->ApplyCommand("exit");

    }
    cout << endl;
    cout << " Now            _       " << endl;
    cout << " THAT's       /`_>      " << endl;
    cout << " what I'm    / /        " << endl;
    cout << " talking     |/         " << endl;
    cout << " about!  ____|    __    " << endl;
    cout << "        |    `.-``  )   " << endl;
    cout << "        |---``|  _.'    " << endl;
    cout << "     .-`'---``_.'       " << endl;
    cout << "   (__...--``           " << endl << endl;

    //job termination
    delete DataArray;
    delete runManager;
    return 0;
}
