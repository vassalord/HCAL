#include "QIE11.h"

QIE11::QIE11():
  HcalQIE(){}

QIE11::QIE11(Collection& c, unsigned short i, short j ):
  HcalQIE(c,i){}

int    QIE11::ieta         () {return m_collection -> GetData() -> QIE11DigiIEta        -> at(m_raw_index);}
int    QIE11::iphi         () {return m_collection -> GetData() -> QIE11DigiIPhi        -> at(m_raw_index);}
int    QIE11::subdet       () {return m_collection -> GetData() -> QIE11DigiSubdet      -> at(m_raw_index);}
int    QIE11::depth        () {return m_collection -> GetData() -> QIE11DigiDepth       -> at(m_raw_index);}
int    QIE11::rawid        () {return m_collection -> GetData() -> QIE11DigiRawID       -> at(m_raw_index);}
int    QIE11::linkerror    () {return m_collection -> GetData() -> QIE11DigiLinkError   -> at(m_raw_index);}
int    QIE11::capiderror   () {return m_collection -> GetData() -> QIE11DigiCapIDError  -> at(m_raw_index);}
int    QIE11::flags        () {return m_collection -> GetData() -> QIE11DigiFlags       -> at(m_raw_index);}
int    QIE11::ntdc         () {return m_collection -> GetData() -> QIE11DigiNTDC        -> at(m_raw_index);}
double QIE11::timefc       () {return m_collection -> GetData() -> QIE11DigiTimeFC      -> at(m_raw_index);}
float  QIE11::timetdc      () {return m_collection -> GetData() -> QIE11DigiTimeTDC     -> at(m_raw_index);}
double QIE11::totalfc      () {return m_collection -> GetData() -> QIE11DigiTotFC       -> at(m_raw_index);}
int    QIE11::soi     (int i) {return m_collection -> GetData() -> QIE11DigiSOI         -> at(m_raw_index)[i];}
int    QIE11::adc     (int i) {return m_collection -> GetData() -> QIE11DigiADC         -> at(m_raw_index)[i];}
double QIE11::fc      (int i) {return m_collection -> GetData() -> QIE11DigiFC          -> at(m_raw_index)[i];}
int    QIE11::tdc     (int i) {return m_collection -> GetData() -> QIE11DigiTDC         -> at(m_raw_index)[i];}
int    QIE11::capid   (int i) {return m_collection -> GetData() -> QIE11DigiCapID       -> at(m_raw_index)[i];}
