#include "HBHERecHit.h"

HBHERecHit::HBHERecHit():
  HcalRecHit(){}

HBHERecHit::HBHERecHit(Collection& c, unsigned short i, short j ):
  HcalRecHit(c,i){}

float HBHERecHit::energy       () {return m_collection -> GetData() -> HBHERecHitEnergy     -> at(m_raw_index);}
float HBHERecHit::recHitTime   () {return m_collection -> GetData() -> HBHERecHitTime       -> at(m_raw_index);}
int   HBHERecHit::ieta         () {return m_collection -> GetData() -> HBHERecHitIEta          -> at(m_raw_index);}
int   HBHERecHit::iphi         () {return m_collection -> GetData() -> HBHERecHitIPhi          -> at(m_raw_index);}
float HBHERecHit::eta          () {return m_collection -> GetData() -> HBHERecHitEta           -> at(m_raw_index);}
float HBHERecHit::phi          () {return m_collection -> GetData() -> HBHERecHitPhi           -> at(m_raw_index);}
int   HBHERecHit::aux          () {return m_collection -> GetData() -> HBHERecHitAux           -> at(m_raw_index);}
int   HBHERecHit::depth        () {return m_collection -> GetData() -> HBHERecHitDepth         -> at(m_raw_index);}
int   HBHERecHit::flags        () {return m_collection -> GetData() -> HBHERecHitFlags         -> at(m_raw_index);}
int   HBHERecHit::hpdid        () {return m_collection -> GetData() -> HBHERecHitHPDid         -> at(m_raw_index);}
int   HBHERecHit::rbxid        () {return m_collection -> GetData() -> HBHERecHitRBXid         -> at(m_raw_index);}
