#ifndef HBHE_RECHIT_H
#define HBHE_RECHIT_H

#include "HcalRecHit.h"
#include "HBHESample.h"

class HBHERecHit : public HcalRecHit {

 public:
  HBHERecHit();
  HBHERecHit(Collection& c, unsigned short i, short j = 0);
  
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

  HBHESample operator[] ( int i ){
    return HBHESample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
