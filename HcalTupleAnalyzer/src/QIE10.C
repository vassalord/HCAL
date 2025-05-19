#include "QIE10.h"

QIE10::QIE10():
  HcalQIE(){}

QIE10::QIE10(Collection& c, unsigned short i, short j ):
  HcalQIE(c,i){}

int    QIE10::ieta         () {return m_collection -> GetData() -> QIE10DigiIEta        -> at(m_raw_index);}
int    QIE10::iphi         () {return m_collection -> GetData() -> QIE10DigiIPhi        -> at(m_raw_index);}
int    QIE10::subdet       () {return m_collection -> GetData() -> QIE10DigiSubdet      -> at(m_raw_index);}
int    QIE10::depth        () {return m_collection -> GetData() -> QIE10DigiDepth       -> at(m_raw_index);}
int    QIE10::rawid        () {return m_collection -> GetData() -> QIE10DigiRawID       -> at(m_raw_index);}
int    QIE10::linkerror    () {return m_collection -> GetData() -> QIE10DigiLinkError   -> at(m_raw_index);}
int    QIE10::flags        () {return m_collection -> GetData() -> QIE10DigiFlags       -> at(m_raw_index);}
int    QIE10::soi     (int i) {return m_collection -> GetData() -> QIE10DigiSOI         -> at(m_raw_index)[i];}
int    QIE10::ok      (int i) {return m_collection -> GetData() -> QIE10DigiOK          -> at(m_raw_index)[i];}
int    QIE10::adc     (int i) {return m_collection -> GetData() -> QIE10DigiADC         -> at(m_raw_index)[i];}
double QIE10::fc      (int i) {return m_collection -> GetData() -> QIE10DigiFC          -> at(m_raw_index)[i];}
int    QIE10::letdc   (int i) {return m_collection -> GetData() -> QIE10DigiLETDC       -> at(m_raw_index)[i];}
int    QIE10::tetdc   (int i) {return m_collection -> GetData() -> QIE10DigiTETDC       -> at(m_raw_index)[i];}
int    QIE10::capid   (int i) {return m_collection -> GetData() -> QIE10DigiCapID       -> at(m_raw_index)[i];}
