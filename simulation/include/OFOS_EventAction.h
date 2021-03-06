#ifndef OFOS_EventAction_h
#define OFOS_EventAction_h 1

#include <vector>

#include "G4UserEventAction.hh"

#include "globals.hh"

//#include "OFOS_SiPmtHit.h"
//#include "OFOS_FiberHit.h"



class OFOS_EventAction : public G4UserEventAction {

public:
    OFOS_EventAction();

    ~OFOS_EventAction() override;


    // data members
    G4int vert_fiber_hit_collection_id_;
    G4int hori_fiber_hit_collection_id_;
    G4int vert_sipmt_hit_collection_id_;
    G4int hori_sipmt_hit_collection_id_;
    G4int vessel_hit_collection_id_;

    void BeginOfEventAction(const G4Event *) override;

    void EndOfEventAction(const G4Event *) override;


private:

    G4int process_hit_collections(const G4Event *evt) const;

    static void fetch_event_info(const G4Event *evt);

};


#endif
