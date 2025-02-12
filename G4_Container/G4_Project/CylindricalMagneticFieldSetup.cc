#include "CylindricalMagneticFieldSetup.hh"
#include "G4Region.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"

// Constructor: Initializes the magnetic field in the logical volume of the cylinder
CylindricalMagneticFieldSetup::CylindricalMagneticFieldSetup(G4LogicalVolume* logicCylindricalVolume, 
                                                             G4ThreeVector magneticFieldVector)
{
    // Create the magnetic field
    fMagneticField = new G4UniformMagField(magneticFieldVector);

    // Create a Field Manager for the cylinder region
    fFieldManager = new G4FieldManager();
    fFieldManager->SetDetectorField(fMagneticField);

    // Create a Chord Finder for the Field Manager of the cylinder
    fFieldManager->CreateChordFinder(fMagneticField);

    // Assign the Field Manager to the logic volume of the cylinder
    G4Region* cylindricalRegion = new G4Region("CylindricalRegion");
    cylindricalRegion->AddRootLogicalVolume(logicCylindricalVolume);
    cylindricalRegion->SetFieldManager(fFieldManager);
}

// Destructor: Free allocated memory

CylindricalMagneticFieldSetup::~CylindricalMagneticFieldSetup()
{
    delete fMagneticField;
    delete fFieldManager;
}
