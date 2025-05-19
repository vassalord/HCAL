#include "HcalQIE.h"

HcalQIE::HcalQIE():
  Object(){}

HcalQIE::HcalQIE(Collection& c, unsigned short i, short j):
  Object(c,i,"HcalQIE"){}

bool HcalQIE::PassUserID (ID id, bool verbose){ return false; }
