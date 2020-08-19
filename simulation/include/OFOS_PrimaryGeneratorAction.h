
#ifndef OFOS_PrimaryGeneratorAction_h
#define OFOS_PrimaryGeneratorAction_h 1

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

//class G4ParticleGun;
class G4Event;
class G4GeneralParticleSource;

/// The primary generator action class with particle gum.
///
/// It defines a single particle which hits the Tracker 
/// perpendicular to the input face. The type of the particle
/// can be changed via the G4 build-in commands of G4ParticleGun class 
/// (see the macros provided with this example).

class OFOS_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    OFOS_PrimaryGeneratorAction();    
    virtual ~OFOS_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* );

    // G4ParticleGun* GetParticleGun() {return fParticleGun;}
    G4GeneralParticleSource* GetParticleGun() {return fParticleGun;}

  private:
 // G4ParticleGun*          fParticleGun; // G4 particle gun
    G4GeneralParticleSource*          fParticleGun; // G4 particle gun
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
