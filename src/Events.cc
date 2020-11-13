#include "Events.hh"

Events::Events() {
    //Create File
    FileNumber = 0;
    status = 0;
    //status = Create_New_File(FileName);

}

Events::~Events() {
    //  cout << " Destructor Called" << endl;
}


int Events::Write_To_File() {
    bool Diagnose = FALSE;
    int j = EnergyIn.size();
    int jm = mEnergyIn.size();

    if (Diagnose == TRUE) cout<<j<<"  "<<jm<<endl;

    double* aEnergyIn;
    double* aEdep;
    int* aPixel;
    long* aEvent;
    double* aEventX;
    double* aEventY;
    double* aEventZ;

    double* amEnergyIn;
    double* amEdep;
    int* amPixel;
    long* amEvent;
    double* amEventX;
    double* amEventY;
    double* amEventZ;

    aEnergyIn = new double[j];
    aEdep = new double[j];
    aPixel = new int[j];
    aEvent = new long[j];
    aEventX = new double[j];
    aEventY = new double[j];
    aEventZ = new double[j];

    amEnergyIn = new double[jm];
    amEdep = new double[jm];
    amPixel = new int[jm];
    amEvent = new long[jm];
    amEventX = new double[jm];
    amEventY = new double[jm];
    amEventZ = new double[jm];

    for (int i = 0; i < j; i++) {
        aEnergyIn[i] = EnergyIn.at(i);
        aEdep[i] = Edep.at(i);
        aPixel[i] = Pixel.at(i);
        aEvent[i] = Event.at(i);
        aEventX[i] = EventX.at(i);
        aEventY[i] = EventY.at(i);
        aEventZ[i] = EventZ.at(i);
    }
    for (int i = 0; i < jm; i++) {
        amEnergyIn[i] = mEnergyIn.at(i);
        amEdep[i] = mEdep.at(i);
        amPixel[i] = mPixel.at(i);
        amEvent[i] = mEvent.at(i);
        amEventX[i] = mEventX.at(i);
        amEventY[i] = mEventY.at(i);
        amEventZ[i] = mEventZ.at(i);
    }

    if (Diagnose == TRUE)   cout << " Arrays Assigned" << endl;

    fitsfile *fptr;

    fits_open_file(&fptr, CurrentFileName.c_str(), 1, &status); //open out single events
    if (Diagnose == TRUE)  cout << "->"<<CurrentFileName<<"<-" << endl;
    fits_report_error(stdout, status);

    //Singles
    fits_movabs_hdu(fptr, 2, NULL, &status); //move out single events
    fits_report_error(stdout, status);
    long RowNumSingle;
    fits_get_num_rows(fptr, &RowNumSingle, &status);
    fits_report_error(stderr, status);
    RowNumSingle++;
    fits_write_col(fptr, TDOUBLE, 1, RowNumSingle, 1, j, aEnergyIn, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TDOUBLE, 2, RowNumSingle, 1, j, aEdep, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TINT, 3, RowNumSingle, 1, j, aPixel, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TLONG, 4, RowNumSingle, 1, j, aEvent, &status);
    fits_report_error(stdout, status);
    /*
    fits_write_col(fptr, TDOUBLE, 5, RowNumSingle, 1, j, aEventX, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TDOUBLE, 6, RowNumSingle, 1, j, aEventY, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TDOUBLE, 7, RowNumSingle, 1, j, aEventZ, &status);
    fits_report_error(stdout, status);
    */
    if (Diagnose == TRUE) cout << " Singles Written " << endl;

    //Multiples
    fits_movabs_hdu(fptr, 3, NULL, &status); //move out single events
    fits_report_error(stdout, status);
    long RowNumMultiple;
    fits_get_num_rows(fptr, &RowNumMultiple, &status);
    fits_report_error(stderr, status);
    RowNumMultiple++;
    fits_write_col(fptr, TDOUBLE, 1, RowNumMultiple, 1, jm, amEnergyIn, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TDOUBLE, 2, RowNumMultiple, 1, jm, amEdep, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TINT, 3, RowNumMultiple, 1, jm, amPixel, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TLONG, 4, RowNumMultiple, 1, jm, amEvent, &status);
    fits_report_error(stdout, status);
    /*
    fits_write_col(fptr, TDOUBLE, 5, RowNumMultiple, 1, jm, amEventX, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TDOUBLE, 6, RowNumMultiple, 1, jm, amEventY, &status);
    fits_report_error(stdout, status);
    fits_write_col(fptr, TDOUBLE, 7, RowNumMultiple, 1, jm, amEventZ, &status);
    fits_report_error(stdout, status);
    */
    if (Diagnose == TRUE)  cout << " Multiples Written" << endl;


    fits_close_file(fptr, &status);
    fits_report_error(stdout, status);
    fptr = 0;

    EnergyIn.clear();
    Edep.clear();
    Pixel.clear();
    Event.clear();
    EventX.clear();
    EventY.clear();
    EventZ.clear();

    mEnergyIn.clear();
    mEdep.clear();
    mPixel.clear();
    mEvent.clear();
    mEventX.clear();
    mEventY.clear();
    mEventZ.clear();


    delete [] aEnergyIn;
    delete [] aEdep;
    delete [] aPixel;
    delete [] aEvent;
    delete [] aEventX;
    delete [] aEventY;
    delete [] aEventZ;

    delete [] amEnergyIn;
    delete [] amEdep;
    delete [] amPixel;
    delete [] amEvent;
    delete [] amEventX;
    delete [] amEventY;
    delete [] amEventZ;


    return 0;
}

int Events::Create_New_File(string FileName) {


    fitsfile *fptr;
    //   string fits(".fits");
    //   size_t found;
    //   found = FileName.find(fits);
    //   if(found!=string::npos)
    //     {
    //       char Number[3];
    //       sprintf( Number, "%d", FileNumber ) ;
    //       CurrentFileName = FileName + Number;
    //       CurrentFileName += fits;
    //     }
    //   else
    //     {
    CurrentFileName = FileName;
    //     }
    // needs to be put it events file // :djc:20081125
    ifstream fin(FileName.c_str());
    if (fin) {
        cout << " File " << FileName << " exists, Overwriting!" << endl;
        CurrentFileName = "!" + FileName;
    } else {
        CurrentFileName = FileName;

    }
    fin.close();
    //

    string FITSoutputTemplate = "fits_templates/RES.TPL";

    fits_create_template(&fptr, CurrentFileName.c_str(), FITSoutputTemplate.c_str(), &status);
    fits_report_error(stderr, status);
    //add headers
    fits_write_key(fptr, TDOUBLE, "RAPOINT", &RAPointing, "RA Pointing (deg)", &status);
    fits_write_key(fptr, TDOUBLE, "DECPOINT", &DECPointing, "DEC Pointing (deg)", &status);
    fits_write_key(fptr, TDOUBLE, "ROLL", &ROLL, "ROLL Pointing (deg)", &status);
    fits_write_key(fptr, TDOUBLE, "RASRC", &RASource, "RASource (deg)", &status);
    fits_write_key(fptr, TDOUBLE, "DECSRC", &DECSource, "DECSource (deg)", &status);
    fits_write_key(fptr, TSTRING, "SPTYPE", (char*)SpectralType.c_str(), "Spectral type", &status);
    if (SpectralType == "PointSource" || SpectralType == "CutoffPL" || SpectralType == "BrokenPL") {
        fits_write_key(fptr, TDOUBLE, "ALPHA", &alpha, "Spectral index", &status);
    }
    if (SpectralType == "CutoffPL") {
        fits_write_key(fptr, TDOUBLE, "CUTOFF", &beta, "Cut off energy (keV)", &status);
    }
    if (SpectralType == "BrokenPL") {
        fits_write_key(fptr, TDOUBLE, "BETA", &beta, "Spectral index", &status);
        fits_write_key(fptr, TDOUBLE, "EBREAK", &Ebreak, "Energy break (keV)", &status);
    }
    fits_write_key(fptr, TDOUBLE, "POLARANG", &PolarAngle, "PolarAngle (deg)", &status);
    fits_write_key(fptr, TLONG, "EXPOSURE", &Exposure, "Photons fired", &status);
    fits_write_key(fptr, TINT, "SEED", &seed, "For Random Number Generator", &status);
    fits_close_file(fptr, &status);
    fits_report_error(stdout, status);
    fptr = 0;

    ofstream fout("Percentage"); //create output
    fout << 0 << "  " << 9999 << endl;
    fout.close();

    cout << "==========================================================" << endl;
    cout << "  New File Created: " << CurrentFileName << endl;
    cout << "==========================================================" << endl;
    FileNumber++;
    CurrentFileName = FileName;

    return 0;
}
