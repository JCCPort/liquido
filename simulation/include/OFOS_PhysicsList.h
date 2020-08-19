#ifndef OFOS_PhysicsList_h
#define OFOS_PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class OFOS_PhysicsList: public G4VUserPhysicsList {
public:
    OFOS_PhysicsList();
    ~OFOS_PhysicsList() override;
    
    void SetSecondaryHad(G4String hadval);
    
private:
    //PhysicsMessenger* physicsMessenger;
    
    G4String SecondaryHadModel;
    
    G4bool gheishahad;
    G4bool bertinihad;
    G4bool binaryhad;
    
    G4double       electronCutValue ;
    G4double       gammaCutValue ;
    
    
protected:
    // Construct particle and physics process
    void ConstructParticle() override;
    void ConstructProcess() override;
    void SetCuts() override;
    
protected:
    // these methods Construct particles
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();
    
protected:
    // these methods Construct physics processes and register them
    void ConstructEM();
    void ConstructOp();
    static void ConstructHadEl();//MBA 4/12/15
    static void ConstructHad_QSGP_BIC_HP();//MBA 4/12/15
    void ConstructDecay(); //MBA 4/12/15
    static void ConstructHad_NuBeam();

    static void ConstructHad_FTFP_BERT();

    static void ConstructHad_QGSP_BERT_HP();
};

#endif
