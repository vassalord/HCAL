#ifndef QIE10_H
#define QIE10_H

#include "HcalQIE.h"

class QIE10 : public HcalQIE {

 public:
  QIE10();
  QIE10(Collection& c, unsigned short i, short j = 0);
  
  int   ieta  () ;
  int   iphi  () ;
  int   subdet () ;
  int   depth  () ;
  int   rawid  () ;
  int   linkerror  () ;
  int   flags  () ;
  int soi (int i);
  int ok (int i);
  int adc (int i);
  double fc (int i);
  int letdc (int i);
  int tetdc (int i);
  int capid (int i);
  
  int getRawIndex () { return m_raw_index; }

  //HBHESample operator[] ( int i ){
  //  return HBHESample( *m_collection, m_raw_index, i );
  //}
  
};

#endif 
