/* I will use this file to define all the parameters of my
.shw.bz2 file, which is provided by CORSIKA within the ARTI platform */

#ifndef PrimarySpectrum_HH
#define PrimarySpectrum_HH

// Geant4 Libraries
#include "globals.hh"
#include "G4ThreeVector.hh"

// C++ Libraries
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <iomanip>

class PrimarySpectrumMessenger;

class PrimarySpectrum
{
public:
    PrimarySpectrum();
    ~PrimarySpectrum();

    void primaryMomento();
    int openFile(std::string name);
    
    G4ThreeVector getPosition() const;
    G4ThreeVector getDirection() const;
    G4String getParticleId() const; 
    G4double getEnergy() const;

    G4ThreeVector particlePosition;
    G4ThreeVector particleDirection;
    G4String parId;
    std::string inputFile; //[] = "tmpMachin24h.shw.bz2"
    
private:
    G4double pi;
    float r;
    float theta;

    G4int crkId;
    G4double px;
    G4double py;
    G4double pz;
    G4double x;// This would be the X position of the particle from the .shw.bz2 file
    G4double y;// This would be the Y position of the particle from the .shw.bz2 file
    G4double z;// This would be the Z position of the particle from the .shw.bz2 file
    G4int shwId;
    G4int prmId;
    G4double prmEner;
    G4double prmThe;
    G4double prmPhi;

    FILE *inFile = NULL;
    PrimarySpectrumMessenger* fSpectMessenger;

    G4int lineNumber;
};

#endif
