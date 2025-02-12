#ifndef GEOMETRYMESSENGER_HH
#define GEOMETRYMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class MyDetectorConstruction; 
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class GeometryMessenger : public G4UImessenger
{
public:
    GeometryMessenger(MyDetectorConstruction* detectorConstruction);
    virtual ~GeometryMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    MyDetectorConstruction* fDetectorConstruction;

    G4UIdirectory* fGeometryDir;
    
    // Mother world size
    G4UIcmdWithADoubleAndUnit* worldSizeXCmd;
    G4UIcmdWithADoubleAndUnit* worldSizeYCmd;
    G4UIcmdWithADoubleAndUnit* worldSizeZCmd;
    
    // Detector size
    G4UIcmdWithADoubleAndUnit* detectorSizeXCmd;
    G4UIcmdWithADoubleAndUnit* detectorSizeYCmd;
    G4UIcmdWithADoubleAndUnit* detectorSizeZCmd;
    
    // Detector position relative to the mother world
    G4UIcmdWithADoubleAndUnit* detectorPosXCmd;
    G4UIcmdWithADoubleAndUnit* detectorPosYCmd;
    G4UIcmdWithADoubleAndUnit* detectorPosZCmd;

    // Cylinder size and position
    G4UIcmdWithADoubleAndUnit* cylinderRadiusCmd;
    G4UIcmdWithADoubleAndUnit* cylinderHeightCmd;
    G4UIcmdWithADoubleAndUnit* cylinderPosXCmd;
    G4UIcmdWithADoubleAndUnit* cylinderPosYCmd;
    G4UIcmdWithADoubleAndUnit* cylinderPosZCmd;
};

#endif
