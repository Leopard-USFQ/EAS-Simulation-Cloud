#include "CylindricalElectricFieldSetup.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4TransportationManager.hh"
#include "G4LogicalVolume.hh"

CylindricalElectricFieldSetup::CylindricalElectricFieldSetup(G4LogicalVolume* logicCylindricalVolume, 
                                                 G4ThreeVector electricFieldVector)
{
    
    // Create the electric field
    fElectricField = new G4UniformElectricField(electricFieldVector);

    // Configure the equation of motion for the electric field
    fEquation = new G4EqMagElectricField(fElectricField);

    // Create the Field Manager and Chord Finder for the combined field
    fFieldManager = new G4FieldManager();
    fFieldManager->SetDetectorField(fElectricField);

    // Create the stepper with the Runge-Kutta method 
    G4int nvar = 8;  // Numbers of variables
    auto pStepper = new G4ClassicalRK4(fEquation, nvar);

    // Configure the driver for the integration
    G4double minStep = 10 * mm; // Minimum step for the integration
    auto pIntegrationDriver = new G4IntegrationDriver<G4ClassicalRK4>(minStep, pStepper, nvar);

    fChordFinder = new G4ChordFinder(pIntegrationDriver);

    // Configure the Field Manager for the Chord Finder and the combined field
    fFieldManager->SetChordFinder(fChordFinder);

    // Create a region for the cylinder and assign the Field Manager to this region
    G4Region* cylindricalRegion = new G4Region("CylindricalRegion");
    cylindricalRegion->AddRootLogicalVolume(logicCylindricalVolume);
    cylindricalRegion->SetFieldManager(fFieldManager);
}

CylindricalElectricFieldSetup::~CylindricalElectricFieldSetup()
{
    delete fElectricField;
    delete fEquation;
    delete fFieldManager;
    delete fChordFinder;
}
