#ifndef HCAL_SAMPLE_H
#define HCAL_SAMPLE_H

#include "Object.h"

class HcalSample : public Object {
  
 public:
  
  HcalSample();
  HcalSample(Collection& c, unsigned short i, short j);
  
  virtual double allFC()     = 0;
  virtual double energy()    = 0;
  virtual double gain()      = 0;
  virtual double fc()        = 0;
  virtual double nomFC()     = 0;
  virtual double pedFC()     = 0;
  virtual double rcGain()    = 0;

  virtual int   adc()       = 0;
  virtual int   capid()     = 0;
  virtual int   dv()        = 0;
  virtual int   er()        = 0;
  virtual int   fiber()     = 0;
  virtual int   fiberChan() = 0;
  virtual int   raw()       = 0;

  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!
  
  bool PassUserID (ID, bool) { return false; }

 protected:
  int m_timeslice;
  double m_null_value;
};

#endif 
