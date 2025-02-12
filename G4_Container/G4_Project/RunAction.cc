#include "RunAction.hh"
#include "MySensitiveDetector.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(MyDetectorConstruction* detectorConstruction)
    : G4UserRunAction(), fDetectorConstruction(detectorConstruction)
{
    // Constructor: Initialize variables or perform initial configurations

    // Open the output file
    outFile.open("simulation_results.txt", std::ios::app);  // Append mode

    if (!outFile.is_open()) {
        G4cerr << "Error: Could not open output file." << G4endl;
    }

    startTime = 0;
    endTime = 0;
}

RunAction::~RunAction()
{
    // Destructor: Free any resources if necessary
    // Close the output file if it's open
    if (outFile.is_open()) {
        outFile.close();
    }
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    // This method is executed at the beginning of each run
    
    G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

    // Here, you can initialize variables, open output files, etc.
    // For example, you could reset the particle counter if needed

    // Record the start time of the simulation
    startTime = std::clock();
}


void RunAction::EndOfRunAction(const G4Run* run)
{
    // This method is executed at the end of each run

    // Measure end time
    endTime = std::clock();
    
    // Calculate simulation time
    double simulationTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    
    MySensitiveDetector* sensitiveDetector = fDetectorConstruction->GetSensitiveDetector();

    // Print the total number of detected particles
    if (sensitiveDetector)
    {
        G4cout << "Sensitive detector successfully initialized in RunAction." << G4endl;
        G4cout << "Total number of detected particles: "
               << sensitiveDetector->GetParticleCount() << G4endl;
    }
    else
    {
        G4cout << "No particles detected." << G4endl;
    }

    // Here, you can also save results to a file, close files, etc.

    // Get magnetic field values from the mother world
    G4ThreeVector worldmagneticField = fDetectorConstruction->GetMagneticFieldValue();
    G4double MworldSizeX = fDetectorConstruction->GetWorldSizeX();
    G4double MworldSizeY = fDetectorConstruction->GetWorldSizeY();
    G4double MworldSizeZ = fDetectorConstruction->GetWorldSizeZ();


    // Get the values of electric and magnetic fields from the cylinder
    G4ThreeVector cylindermagneticField = fDetectorConstruction->GetCylinderMagneticField();
    G4ThreeVector cylinderelectricField = fDetectorConstruction->GetCylinderElectricField();
    G4double cylinderRadius = fDetectorConstruction->GetCylinderRadius();
    G4double cylinderHeight = fDetectorConstruction->GetCylinderHeight();
    G4double cylinderPosX = fDetectorConstruction->GetCylinderPosX();
    G4double cylinderPosY = fDetectorConstruction->GetCylinderPosY();
    G4double cylinderPosZ = fDetectorConstruction->GetCylinderPosZ();

    // Get detector size and position values
    G4double DetectorSizeX = fDetectorConstruction->GetDetectorSizeX();
    G4double DetectorSizeY = fDetectorConstruction->GetDetectorSizeY();
    G4double DetectorSizeZ = fDetectorConstruction->GetDetectorSizeZ();
    G4double DetectorPosX = fDetectorConstruction->GetDetectorPosX();
    G4double DetectorPosY = fDetectorConstruction->GetDetectorPosY();
    G4double DetectorPosZ = fDetectorConstruction->GetDetectorPosZ();

    G4cout << "### Run " << run->GetRunID() << " end." << G4endl;

    // Write values to the output file
    if (outFile.is_open())
    {
        outFile << "### Run " << run->GetRunID() << " ###\n";
        outFile << "Mother world size (X): " << MworldSizeX << "mm\n";
        outFile << "Mother world size (Y): " << MworldSizeY << "mm\n";
        outFile << "Mother world size (Z): " << MworldSizeZ << "mm\n";
        outFile << "Magnetic Field in mother world (X): " << worldmagneticField.x() / tesla << " T\n";
        outFile << "Magnetic Field in mother world(Y): " << worldmagneticField.y() / tesla << " T\n";
        outFile << "Magnetic Field in mother world (Z): " << worldmagneticField.z() / tesla << " T\n";
        outFile << "Cylinder world Radius: " << cylinderRadius << "mm\n";
        outFile << "Cylinder world Height: " << cylinderHeight << "mm\n";
        outFile << "Cylinder world Position (X): " << cylinderPosX << "mm\n";
        outFile << "Cylinder world Position (Y): " << cylinderPosY << "mm\n";
        outFile << "Cylinder world Position (Z): " << cylinderPosZ << "mm\n";
        outFile << "Magnetic Field in cylinder (X): " << cylindermagneticField.x() / tesla << " T\n";
        outFile << "Magnetic Field in cylinder (Y): " << cylindermagneticField.y() / tesla << " T\n";
        outFile << "Magnetic Field in cylinder (Z): " << cylindermagneticField.z() / tesla << " T\n";
        outFile << "Electric Field in cylinder (X): " << cylinderelectricField.x() / volt/m << " V/m\n";
        outFile << "Electric Field in cylinder (Y): " << cylinderelectricField.y() / volt/m << " V/m\n";
        outFile << "Electric Field in cylinder (Z): " << cylinderelectricField.z() / volt/m << " V/m\n";
        outFile << "Detector Size (X): " << DetectorSizeX << "mm\n";
        outFile << "Detector Size (Y): " << DetectorSizeY << "mm\n";
        outFile << "Detector Size (Z): " << DetectorSizeZ << "mm\n";
        outFile << "Detector Position (X): " << DetectorPosX << "mm\n";
        outFile << "Detector Position (Y): " << DetectorPosY << "mm\n";
        outFile << "Detector Position (Z): " << DetectorPosZ << "mm\n";
        outFile << "Simulation time: " << simulationTime << " seconds\n";
        outFile << "Particles detected: " << sensitiveDetector->GetParticleCount() << "\n";
        outFile << "Particles simulated: " << run->GetNumberOfEventToBeProcessed() << "\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile.close();
    } else {
        G4cerr << "Error: Could not open output file." << G4endl;
    }
}
