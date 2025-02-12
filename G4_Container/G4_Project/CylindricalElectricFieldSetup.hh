#ifndef CYLINDRICAL_ELECTRIC_FIELD_SETUP_HH
#define CYLINDRICAL_ELECTRIC_FIELD_SETUP_HH

#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"



class CylindricalElectricFieldSetup {
public:
    // Constructor: Receives the logical volume of the cylinder and the field vectors
    CylindricalElectricFieldSetup(G4LogicalVolume* logicCylindricalVolume, 
                            G4ThreeVector electricFieldVector);
    
    // Destructor
    virtual ~CylindricalElectricFieldSetup();

private:
    // Combined electromagnetic field
    G4UniformElectricField* fElectricField; // uniform electric field

    // Equation of motion for combined fields
    G4EqMagElectricField* fEquation;

    // Field manager and chord finder for the cylinder region
    G4FieldManager* fFieldManager;
    G4ChordFinder* fChordFinder;
};

#endif

