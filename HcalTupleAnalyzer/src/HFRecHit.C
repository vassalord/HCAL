#include "HFRecHit.h"

HFRecHit::HFRecHit():
  HcalRecHit(){}

HFRecHit::HFRecHit(Collection& c, unsigned short i, short j ):
  HcalRecHit(c,i){}

float HFRecHit::energy       () {return m_collection -> GetData() -> HFRecHitEnergy     -> at(m_raw_index);}
float HFRecHit::recHitTime   () {return m_collection -> GetData() -> HFRecHitTime       -> at(m_raw_index);}
int   HFRecHit::ieta         () {return m_collection -> GetData() -> HFRecHitIEta          -> at(m_raw_index);}
int   HFRecHit::iphi         () {return m_collection -> GetData() -> HFRecHitIPhi          -> at(m_raw_index);}
float HFRecHit::eta          () {return m_collection -> GetData() -> HFRecHitEta           -> at(m_raw_index);}
float HFRecHit::phi          () {return m_collection -> GetData() -> HFRecHitPhi           -> at(m_raw_index);}
int   HFRecHit::aux          () {return m_collection -> GetData() -> HFRecHitAux           -> at(m_raw_index);}
int   HFRecHit::depth        () {return m_collection -> GetData() -> HFRecHitDepth         -> at(m_raw_index);}
int   HFRecHit::flags        () {return m_collection -> GetData() -> HFRecHitFlags         -> at(m_raw_index);}
int   HFRecHit::hpdid        () {return m_collection -> GetData() -> HFRecHitHPDid         -> at(m_raw_index);}
int   HFRecHit::rbxid        () {return m_collection -> GetData() -> HFRecHitRBXid         -> at(m_raw_index);}
