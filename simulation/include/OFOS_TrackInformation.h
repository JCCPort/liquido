#ifndef OFOS_TrackInformation_h
#define OFOS_TrackInformation_h 1


#include "globals.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

//use code from G4 extended optical LXe example for Track Status


enum TrackStatus { active=1, hitPMT=2, absorbed=4, boundaryAbsorbed=8,
		   inactive=28, wcReflected = 32, GlassRebound=40 };

/*TrackStatus:
  active: still being tracked
  hitPMT: stopped by being detected in a PMT
  absorbed: stopped by being absorbed with G4OpAbsorbtion
  boundaryAbsorbed: stopped by being aborbed with G4OpAbsorbtion
  hitSphere: track hit the sphere at some point
  inactive: track is stopped for some reason
  GlassRebound: Optical Photons having touched more than once a PMTGlass before being detected  //MBA 3/12/15
   -This is the sum of all stopped flags so can be used to remove stopped flags
 */

class OFOS_TrackInformation : public G4VUserTrackInformation {

public:
  OFOS_TrackInformation(): saveit(false), drawit(false), status(active) {}

  //  TrackInformation(const TrackInformation* aninfo) 
  // { saveit = aninfo->saveit;}

  explicit OFOS_TrackInformation(const G4Track*);

  ~OFOS_TrackInformation() override = default;
  
  inline void *operator new(size_t);

  inline void operator delete(void *aTrackInfo);

  inline int operator ==(const OFOS_TrackInformation& right) const
  {return (this==&right);}
  
  // Sets the track status to s (does not check validity of flags)
  void SetTrackStatusFlags(G4int s){status=s;}

  // Does a smart add of track status flags (disabling old flags that conflict)
  // If s conflicts with itself it will not be detected
  void AddTrackStatusFlag(G4int s);
  int GetTrackStatus()  {return status;}

  void SetDrawOption(G4bool b) {drawit = b;}
  G4bool GetDrawOption() {return drawit;}

  void SetSaveOption(G4bool b) {saveit = b;}
  G4bool GetSaveOption() {return saveit;}

  void Print() const override;


private:
  G4bool saveit; 
  G4bool drawit;
  G4int  status; 

};


extern G4Allocator<OFOS_TrackInformation> aTrackInfoAllocator;


inline void* OFOS_TrackInformation::operator new(size_t) { 
  void* aTrackInfo;
  aTrackInfo = (void*)aTrackInfoAllocator.MallocSingle();
  return aTrackInfo;
}

inline void OFOS_TrackInformation::operator delete(void *aTrackInfo){ 
  aTrackInfoAllocator.FreeSingle((OFOS_TrackInformation*)aTrackInfo);
}


#endif

