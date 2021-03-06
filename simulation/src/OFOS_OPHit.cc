
#include "OFOS_OPHit.h"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"


G4ThreadLocal G4Allocator<OFOS_OPHit> *OFOS_OPHitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OFOS_OPHit::OFOS_OPHit() : G4VHit(),
                           track_id_(-1),
//                           parent_id_   (-1),  // Josh addition
                           type_(-1),
                           primary_id_(-1),
                           secondary_id_(-1),
                           time_(-1.),
                           position_(G4ThreeVector()),
                           polarization_(G4ThreeVector()) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OFOS_OPHit::~OFOS_OPHit() = default;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OFOS_OPHit::OFOS_OPHit(const OFOS_OPHit &right) : G4VHit() {
    track_id_ = right.track_id_;
//    parent_id_    = right.parent_id_   ; // Josh addition
    type_ = right.type_;
    primary_id_ = right.primary_id_;
    secondary_id_ = right.secondary_id_;
    time_ = right.time_;
    position_ = right.position_;
    polarization_ = right.polarization_;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const OFOS_OPHit &OFOS_OPHit::operator=(const OFOS_OPHit &right) {
    track_id_ = right.track_id_;
//    parent_id_    = right.parent_id_   ;  // Josh addition
    type_ = right.type_;
    primary_id_ = right.primary_id_;
    secondary_id_ = right.secondary_id_;
    time_ = right.time_;
    position_ = right.position_;
    polarization_ = right.polarization_;

    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int OFOS_OPHit::operator==(const OFOS_OPHit &right) const {
    return (this == &right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OFOS_OPHit::Draw() {
    G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager) {
        G4Circle circle(position_);
        circle.SetScreenSize(4.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1., 0., 0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OFOS_OPHit::Print() {
}

