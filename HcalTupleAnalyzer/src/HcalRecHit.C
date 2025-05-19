#include "HcalRecHit.h"

HcalRecHit::HcalRecHit():
  Object(){}

HcalRecHit::HcalRecHit(Collection& c, unsigned short i, short j):
  Object(c,i,"HcalRecHit"){}

bool HcalRecHit::PassUserID (ID id, bool verbose){ return false; }
