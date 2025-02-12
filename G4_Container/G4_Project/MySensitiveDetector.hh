#ifndef MYSENSITIVEDETECTOR_HH
#define MYSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *); // Must be public
    G4int GetParticleCount() const; // Method to get the particle count

private:
    G4int particleCount; // Variable to count the particles
};

#endif

