#ifndef QIE11_H
#define QIE11_H

#include "HcalQIE.h"

class QIE11 : public HcalQIE {

 public:
  QIE11();
  QIE11(Collection& c, unsigned short i, short j = 0);
  
  int   ieta  () ;
  int   iphi  () ;
  int   subdet () ;
  int   depth  () ;
  int   rawid  () ;
  int   linkerror  () ;
  int   capiderror () ;
  int   flags  () ;
  int   ntdc   () ;
  double timefc () ;
  float timetdc  () ;
  double totalfc  () ;
  int soi (int i);
  int adc (int i);
  double fc (int i);
  int tdc (int i);
  int capid (int i);
  
  int getRawIndex () { return m_raw_index; }

  //HBHESample operator[] ( int i ){
  //  return HBHESample( *m_collection, m_raw_index, i );
  //}
  
};

#endif 
