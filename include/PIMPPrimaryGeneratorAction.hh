
#ifndef PIMPPrimaryGeneratorAction_h
#define PIMPPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SingleParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//#include "G4ParticleGun.hh"
#include <CLHEP/Random/Randomize.h>
#include "PIMPSpaceEnvironment.hh" 
#include "PIMPRandomEnergy.hh"
#include "PIMPGammaRayBurst.hh"
#include "Events.hh"

#define PIMPReturnSeed() HepRandom::getTheSeed()

class G4SingleParticleSource;
class G4Event;

class PIMPPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction,
public PIMPSpaceEnvironment,
public PIMPGammaRayBurst {
public:
    PIMPPrimaryGeneratorAction();
    ~PIMPPrimaryGeneratorAction();

public:
    void Initialize();
    void GeneratePrimaries(G4Event* anEvent);

    void RecordPrimaryParticleType(G4String ParticleName) {
        PrimaryParticleType = ParticleName;
        G4cout << PrimaryParticleType << G4endl;
    }
    void Set_IsotropicParameters();

    //void Set_DirectionParameters(G4int SourcePos);
    void Set_DirectionParameters(G4double SourceRA, G4double SourceDEC);

    static G4double Separation(G4double Alpha1, G4double Delta1, G4double Alpha2, G4double Delta2);
    static G4double PositionAngle(G4double Alpha1, G4double Delta1, G4double Alpha2, G4double Delta2);

    static G4double IncGamma(G4double N, G4double A, G4double X, G4double Val);

    static G4double GammaRecursive(G4double N, G4double A, G4double X, G4double Val);

    static G4double DegreesToRadians(G4double Degrees) {
        return Degrees * 0.017453292519943295769236907684886;
    }

    static G4double RadiansToDegrees(G4double Radians) {
        return Radians * 57.295779513082320876798154814105;
    }

    static G4double RadiansToHours(G4double Radians) {
        return Radians * 3.8197186342054880584532103209403;
    }

    static G4double HoursToRadians(G4double Hours) {
        return Hours * 0.26179938779914943653855361527329;
    }

    static G4double HoursToDegrees(G4double Hours) {
        return Hours * 15;
    }

    static G4double DegreesToHours(G4double Degrees) {
        return Degrees / 15;
    }

    static G4double MapTo0To360Range(G4double Degrees) {
        G4double Value = Degrees;

        //map it to the range 0 - 360
        while (Value < 0)
            Value += 360;
        while (Value > 360)
            Value -= 360;

        return Value;
    }

    static G4double MapTo0To24Range(G4double HourAngle) {
        G4double Value = HourAngle;

        //map it to the range 0 - 24
        while (Value < 0)
            Value += 24;
        while (Value > 24)
            Value -= 24;

        return Value;
    }

    void Set_RAPointing(double Value) {
        RAPointing = Value;
    }

    void Set_DECPointing(double Value) {
        DECPointing = Value;
    }

    void Set_ROLL(double Value) {
        ROLL = Value;
    }

    void Set_PolarAngle(double Value) {
        PolarAngle = Value;
    }

    void Set_Machine(G4String val) {
        Machine = val;
    }

    void Set_SpectralType(G4String Value) {
        SpectralType = Value;
    }

    void Set_DataArray(Events *Value) {
        DataArray = Value;
    }

    void Set_Alpha(G4double Value) {
        alpha = Value;
    }

    void Set_Beta(G4double Value) {
        beta = Value;
    }

    void Set_Ebreak(G4double Value) {
        Ebreak = Value;
    }

    void Set_Norm(G4double Value) {
        norm = Value;
    }

private:

    G4double E_min; //MeV
    G4double E_max; //MeV

    G4SingleParticleSource *particleGun;
    G4double alpha;
    G4double beta;
    G4double Ebreak;
    G4double norm;
    G4double LowE_total;
    G4double TotalIntegration;
    G4int NumberOfParticlesToBeGenerated;
    G4ParticleDefinition * particle_definition;
    G4ParticleMomentum particle_momentum_direction;
    G4double particle_energy;
    G4double particle_charge;
    G4ThreeVector particle_position;
    G4double particle_time;
    G4ThreeVector particle_polarization;
    G4ThreeVector Direction;
    G4ThreeVector Polarisation;
    G4String SpectralType;
    G4String Machine;
    double Theta;
    double Phi;
    double Psi;
    G4double power;
    G4double min;
    G4double max;
    long ReportEvery;
    G4double bweights[6], bweight; //record x,y,z,theta,phi,energy weights
    long long ParticleCount;
    //long long ICount;

    G4String PrimaryParticleType;
    PIMPRandomEnergy* CosmicSpectra;
    G4int Cosmic; // lable to associate calibration or cosmic flux

    G4double HalfX;
    G4double HalfY;
    G4double HalfZ;
    G4double SideArea;
    G4double EndArea;

    G4ThreeVector RandomPosition;
    G4ThreeVector RandomDirection;
    time_t last_seconds;

    double RAPointing;
    double DECPointing;
    double RASource;
    double DECSource;
    double ROLL;
    double PolarAngle;

    Events *DataArray;
};

#endif



