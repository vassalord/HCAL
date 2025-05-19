#ifndef HO_SAMPLE_H
#define HO_SAMPLE_H

#include "HcalSample.h"

class HOSample : public HcalSample {
  
 public:
  
  HOSample();
  HOSample(Collection& c, unsigned short i, short j);
  
  double allFC()     ;
  double energy()    ;
  double gain()      ;
  double fc()        ;
  double nomFC()     ;
  double pedFC()     ;
  double rcGain()    ;

  int   adc()       ;
  int   capid()     ;
  int   dv()        ;
  int   er()        ;
  int   fiber()     ;
  int   fiberChan() ;
  int   raw()       ;

  int getRawIndex () { return m_raw_index; }
  int getTimeSlice() { return m_timeslice; }

};

#endif 
