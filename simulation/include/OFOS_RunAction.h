
#ifndef OFOS_RunAction_h
#define OFOS_RunAction_h 1

#include <string>
#include <utility>

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4String.hh"
//#include "TFile.h"
//#include "LIMbuSRunActionMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class TFile;
//class LIMbuSRunActionMessenger;

/// Run action class

class OFOS_DetectorConstruction;

class OFOS_PrimaryGeneratorAction;

class OFOS_RunAction : public G4UserRunAction {


    G4String out_filename;
    G4String log_filename;
    G4String geom_filename;

private:
//  LIMbuSRunActionMessenger* messenger; 
    OFOS_DetectorConstruction *detector_;

public:
    explicit OFOS_RunAction(OFOS_DetectorConstruction *det);

    ~OFOS_RunAction() override;

    void BeginOfRunAction(const G4Run *run) override;

    void EndOfRunAction(const G4Run *run) override;

//
    void SetOutputFileName(G4String val) { out_filename = std::move(val); }

    static std::string get_current_time();

    void ComputeElectronCriticalEnergy();

    TFile *output_hit_file_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
