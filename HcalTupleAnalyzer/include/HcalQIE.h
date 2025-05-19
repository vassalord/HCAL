#ifndef HCAL_QIE_H
#define HCAL_QIE_H

#include "Object.h"
#include "HcalSample.h"

class HcalQIE : public Object { 
  
 public:
  HcalQIE();
  HcalQIE(Collection& c, unsigned short i, short j = 0);
  
  virtual int   ieta  () = 0;
  virtual int   iphi  () = 0;
  virtual int   subdet() = 0;
  virtual int   depth () = 0;
  virtual int   rawid () = 0;
  virtual int   linkerror () = 0;
  //virtual int   capiderror () = 0;
  virtual int   flags () = 0;
  //virtual int   ntdc  () = 0;
  //virtual float timefc () = 0;
  //virtual float timetdc () = 0;
  //virtual float totalfc () = 0;
  virtual int   soi   (int i) = 0;
  //virtual int   ok    (int i) = 0;
  virtual int   adc   (int i) = 0;
  virtual double fc    (int i) = 0;
  //virtual int   tdc   (int i) = 0;
  //virtual int   tetdc (int i) = 0;
  //virtual int   letdc (int i) = 0;
  virtual int   capid (int i) = 0;

  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!

  bool PassUserID (ID id, bool verbose = false);

 protected:
  double m_null_value;

};

#endif
