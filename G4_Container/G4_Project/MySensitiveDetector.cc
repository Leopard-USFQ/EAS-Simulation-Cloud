#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


#include "MySensitiveDetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) 
    : G4VSensitiveDetector(name), particleCount(0)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4cout << "Direction in ProcessHits: " << this << G4endl;

    // Get the particle track
    G4Track *track = aStep->GetTrack();

    // Get the particle step points
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
    
    
    G4ThreeVector posParticulainicial = preStepPoint->GetPosition(); // The values are in mm. Remember that Geant4 provides values in mm by default.
    G4ThreeVector posParticulafinal = postStepPoint->GetPosition();


    G4cout << "The initial position of the particle is: " << posParticulainicial << G4endl;
    G4cout << "The final position of the particle is: " << posParticulafinal << G4endl;


    // Increment the particle counter
    particleCount++;

    // Print the particle counter at the end of the event or whenever needed
    G4cout << "Total number of particles that entered the detector: " << particleCount << G4endl;
    
    // Stop and delete the particle track
    track->SetTrackStatus(fStopAndKill);

    return true;
}

G4int MySensitiveDetector::GetParticleCount() const
{
    //G4cout << "Particle count is: " << particleCount << G4endl;
    //G4cout << "Direction in GetParticleCount: " << this << G4endl;
    return particleCount;
}
