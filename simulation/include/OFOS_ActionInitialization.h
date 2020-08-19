
#ifndef OFOS_ActionInitialization_h
#define OFOS_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "OFOS_DetectorConstruction.h"

//class B4DetectorConstruction;

/// Action initialization class.
///

class OFOS_ActionInitialization : public G4VUserActionInitialization
{
  public:
    explicit OFOS_ActionInitialization( OFOS_DetectorConstruction* det );
    ~OFOS_ActionInitialization() override;

    void BuildForMaster() const override;
    void Build() const override;

  private :
    OFOS_DetectorConstruction* fDetector;
};

#endif

    
