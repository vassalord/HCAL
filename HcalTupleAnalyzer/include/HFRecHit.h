#ifndef HF_RECHIT_H
#define HF_RECHIT_H

#include "HcalRecHit.h"
#include "HFSample.h"

class HFRecHit : public HcalRecHit {

 public:
  HFRecHit();
  HFRecHit(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  float eta  () ;
  float phi  () ;
  int   aux  () ;
  int   depth () ;
  int   flags () ;
  int   hpdid () ;
  int   rbxid () ;
  
  int getRawIndex () { return m_raw_index; }

  HFSample operator[] ( int i ){
    return HFSample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
