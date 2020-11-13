
#ifndef Events_h
#define Events_h
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <stdio.h>
//#include "fitsio.h"
//#include "math.h"
//#include "Events.hh"
//
//using namespace std;
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include "fitsio.h"
#include "Events.hh"
#include <vector>
#include <sstream>

using namespace std;

class Events {
    vector <double> EnergyIn;
    vector <double> Edep;
    vector <int> Pixel;
    vector <long> Event;
    vector <double> EventX;
    vector <double> EventY;
    vector <double> EventZ;

    vector <double> mEnergyIn;
    vector <double> mEdep;
    vector <int> mPixel;
    vector <long> mEvent;
    vector <double> mEventX;
    vector <double> mEventY;
    vector <double> mEventZ;

    int FileNumber;
    string CurrentFileName;
    int status;
    string SpectralType;
    double PrimeEnergy;

    double RAPointing;
    double DECPointing;
    double ROLL;
    double RASource;
    double DECSource;
    double alpha;
    double beta;
    double Ebreak;
    double PolarAngle;
    long Exposure;
    int seed;


public:
    Events();
    ~Events();

    //************ Singles ************************
    void Put_EnergyIn(double Value) {
        EnergyIn.push_back(Value);
    }
    void Put_Edep(double Value) {
        Edep.push_back(Value);
    }
    void Put_Pixel(int Value) {
        Pixel.push_back(Value);
    }
    void Put_Event(long Value) {
        Event.push_back(Value);
    }
    void Put_EventX(double Value) {
        EventX.push_back(Value);
    }
    void Put_EventY(double Value) {
        EventY.push_back(Value);
    }
    void Put_EventZ(double Value) {
        EventZ.push_back(Value);
    }

    //************ Multiples ***********************
    void Put_mEnergyIn(double Value) {
        mEnergyIn.push_back(Value);
    }
    void Put_mEdep(double Value) {
        mEdep.push_back(Value);
    }
    void Put_mPixel(int Value) {
        mPixel.push_back(Value);
    }
    void Put_mEvent(long Value) {
        mEvent.push_back(Value);
    }
    void Put_mEventX(double Value) {
        mEventX.push_back(Value);
    }
    void Put_mEventY(double Value) {
        mEventY.push_back(Value);
    }
    void Put_mEventZ(double Value) {
        mEventZ.push_back(Value);
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

    void Set_RASource(double Value) {
        RASource = Value;
    }
    void Set_DECSource(double Value) {
        DECSource = Value;
    }
    void Set_SpectralType(string Val) {
        SpectralType = Val;
    }
    void Set_Alpha(double Value) {
        alpha = Value;
    }
    void Set_Beta(double Value) {
        beta = Value;
    }
    void Set_Ebreak(double Value) {
        Ebreak = Value;
    }
    void Set_PolarAngle(double Value) {
        PolarAngle = Value;
    }

    void Set_Exposure(long Value) {
        Exposure = Value;
    }
    void Set_Seed(int Value) {
        seed = Value;
    }

    void Set_PrimeEnergy(double Value) {
        PrimeEnergy = Value;
    }
    double Get_PrimeEnergy() {
        return PrimeEnergy;
    }

    int Write_To_File();
    int Create_New_File(string FileName);

};

#endif



