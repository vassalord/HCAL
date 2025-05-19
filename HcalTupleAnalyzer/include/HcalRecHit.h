#ifndef HCAL_RECHIT_H
#define HCAL_RECHIT_H

#include "Object.h"
#include "HcalSample.h"

class HcalRecHit : public Object { 
  
 public:
  HcalRecHit();
  HcalRecHit(Collection& c, unsigned short i, short j = 0);
  
  virtual float energy() = 0;
  virtual float recHitTime () = 0;
  virtual int   ieta  () = 0;
  virtual int   iphi  () = 0;
  virtual float eta   () = 0;
  virtual float phi   () = 0;
  virtual int   aux   () = 0;
  virtual int   depth () = 0;
  virtual int   flags () = 0;
  virtual int   hpdid () = 0;
  virtual int   rbxid () = 0;

  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!

  bool PassUserID (ID id, bool verbose = false);

 protected:
  double m_null_value;

};

#endif
