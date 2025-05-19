#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHERecHit.h"
#include "HFRecHit.h"
#include "QIE11.h"
#include "QIE10.h"

void analysisClass::loop(){

  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  
  //const double recHitEnergyCut = 0.;
  const int nSample = 10;
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;
  
  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event"           , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls"              , kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitTime" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitTime" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiTotFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiADC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiTDC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiCapID" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiLETDC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiCapID" , kTRUE);

  //--------------------------------------------------------------------------------
  // Histograms
  //--------------------------------------------------------------------------------

  TH1F * h_HBHErecHitEnergy = makeTH1F("HBHE RecHit Energy", 100, -1, 2);
  h_HBHErecHitEnergy -> SetTitle(" HBHE RecHit Energy ; Rechit Energy [GeV] ; ");

  TH1F * h_HFrecHitEnergy = makeTH1F("HF RecHit Energy", 100, -5, 5);
  h_HFrecHitEnergy -> SetTitle(" HF RecHit Energy ; Rechit Energy [GeV] ; ");

  TH1F * h_HBHErecHitTime = makeTH1F("HBHE RecHit Time", 100, -15000, 5000);
  h_HBHErecHitTime -> SetTitle(" HBHE RecHit Time ; Rechit Time [ns] ; ");

  TH1F * h_HFrecHitTime = makeTH1F("HF RecHit Time", 100, -120, -80);
  h_HFrecHitTime -> SetTitle(" HF RecHit Time ; Rechit Time [ns] ; ");

  char histName[100];
  char titleName[100];
  std::map <int,TH2F*> h_HBHErecHitEnergyPerDepth;
  std::map <int,TH2F*> h_HBHErecHitChargePerDepth;
  std::map <int,TH2F*> h_HBHErecHitTDCPerDepth;
  std::map <int,TH2F*> h_HBHEDigiDepthPerDepth;
  for (int depth = 1; depth <= 7; depth++){
    sprintf(histName,"h_HBHErecHitEnergyPerDepth%d",depth);
    h_HBHErecHitEnergyPerDepth[depth] = makeTH2F(histName, 83, -41.5, 41.5, 72, 0.5, 72.5);
    sprintf(titleName," HBHE i#eta versus i#phi weighted by energy for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHErecHitEnergyPerDepth[depth] -> SetTitle(titleName);

    sprintf(histName,"h_HBHErecHitChargePerDepth%d",depth);
    h_HBHErecHitChargePerDepth[depth] = makeTH2F(histName, 83, -41.5, 41.5, 72, 0.5, 72.5);
    sprintf(titleName," HBHE i#eta versus i#phi weighted by total charge for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHErecHitChargePerDepth[depth] -> SetTitle(titleName);

    sprintf(histName,"h_HBHErecHitTDCPerDepth%d",depth);
    h_HBHErecHitTDCPerDepth[depth] = makeTH2F(histName, 83, -41.5, 41.5, 72, 0.5, 72.5);
    sprintf(titleName," HBHE i#eta versus i#phi weighted by TDC for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHErecHitTDCPerDepth[depth] -> SetTitle(titleName);

    sprintf(histName,"h_HBHEDigiDepthPerDepth%d",depth);
    h_HBHEDigiDepthPerDepth[depth] = makeTH2F(histName, 83, -41.5, 41.5, 72, 0.5, 72.5);
    sprintf(titleName," HBHE Digi Depth %d ; i#eta ; i#phi ",depth);
    h_HBHEDigiDepthPerDepth[depth] -> SetTitle(titleName);
  }

  TH2F * h_HFDigiDepth = makeTH2F("HF Digi Depth", 83, -41.5, 41.5, 72, 0.5, 72.5);
  h_HFDigiDepth -> SetTitle(" HF Digi Depth ; i#eta ; i#phi ");

  TH1F * h_QIE11DigiFC = makeTH1F("QIE11 Digi fC", 100, 0, 2000);
  h_QIE11DigiFC -> SetTitle(" QIE11 Digi Charge ; Charge [fC] ; ");

  TH1F * h_QIE10DigiFC = makeTH1F("QIE10 Digi fC", 100, 0, 100);
  h_QIE10DigiFC -> SetTitle(" QIE10 Digi Charge ; Charge [fC] ; ");

  TH1F * h_QIE11DigiTDC = makeTH1F("QIE11 Digi TDC", 100, -10, 80);
  h_QIE11DigiTDC -> SetTitle(" QIE11 Digi TDC ; TDC ; ");

  TH1F * h_QIE10DigiLETDC = makeTH1F("QIE10 Digi LETDC", 100, 40, 80);
  h_QIE10DigiLETDC -> SetTitle(" QIE10 Digi LETDC ; TDC ; ");

  TH1F * h_QIE11DigiCapID = makeTH1F("QIE11 Digi CapID", 1, -2, 4);
  h_QIE11DigiCapID -> SetTitle(" QIE11 Digi CapID ; QIE11 CapID ; ");

  TH1F * h_QIE10DigiCapID = makeTH1F("QIE10 Digi CapID", 1, 0, 6);
  h_QIE10DigiCapID -> SetTitle(" QIE10 Digi CapID ; QIE10 CapID ; ");

  TH2F * h_QIE11TDCvsADC = makeTH2F("QIE11 TDC vs ADC", 70, 0, 70, 100, 0, 100);
  h_QIE11TDCvsADC -> SetTitle(" QIE11 TDC vs ADC ; ADC ; TDC ");

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 0) % 10 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheRechits (new Collection(*tuple_tree, tuple_tree -> HBHERecHitIEta -> size()));
    int nHBHERechits = hbheRechits -> GetSize();
    for (int iHBHERechit = 0; iHBHERechit < nHBHERechits; ++iHBHERechit){
      HBHERecHit hbheRechit = hbheRechits -> GetConstituent<HBHERecHit>(iHBHERechit);

      h_HBHErecHitEnergy -> Fill( hbheRechit.energy() );
      h_HBHErecHitTime -> Fill( hbheRechit.recHitTime() );

      double ieta = hbheRechit.ieta();
      double iphi = hbheRechit.iphi();
      double depth = hbheRechit.depth();
      h_HBHErecHitEnergyPerDepth[depth] -> Fill( ieta , iphi , hbheRechit.energy() );
    };

    CollectionPtr hfRechits (new Collection(*tuple_tree, tuple_tree -> HFRecHitIEta -> size()));
    int nHFRechits = hfRechits -> GetSize();
    for (int iHFRechit = 0; iHFRechit < nHFRechits; ++iHFRechit){
      HFRecHit hfRechit = hfRechits -> GetConstituent<HFRecHit>(iHFRechit);

      h_HFrecHitEnergy -> Fill( hfRechit.energy() );
      h_HFrecHitTime -> Fill( hfRechit.recHitTime() );
    };

    CollectionPtr qie11s (new Collection(*tuple_tree, tuple_tree -> QIE11DigiIEta -> size()));
    int nQIE11s = qie11s -> GetSize();
    for (int iQIE11 = 0; iQIE11 < nQIE11s; ++iQIE11){
      QIE11 qie11 = qie11s -> GetConstituent<QIE11>(iQIE11);

      double ieta = qie11.ieta();
      double iphi = qie11.iphi();
      double depth = qie11.depth();
      h_HBHEDigiDepthPerDepth[depth] -> Fill( ieta , iphi , 1 );
      h_HBHErecHitChargePerDepth[depth] -> Fill( ieta , iphi , qie11.totalfc() );
      h_QIE11DigiFC -> Fill( qie11.totalfc() );

      for (int j = 0; j < nSample; ++j){
        h_QIE11DigiTDC -> Fill( qie11.tdc(j) );
        h_QIE11DigiCapID -> Fill( qie11.capid(j) );
        h_QIE11TDCvsADC -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
        h_HBHErecHitTDCPerDepth[depth] -> Fill( ieta , iphi , qie11.tdc(j) );
      }
    };

    CollectionPtr qie10s (new Collection(*tuple_tree, tuple_tree -> QIE10DigiIEta -> size()));
    int nQIE10s = qie10s -> GetSize();
    for (int iQIE10 = 0; iQIE10 < nQIE10s; ++iQIE10){
      QIE10 qie10 = qie10s -> GetConstituent<QIE10>(iQIE10);

      h_HFDigiDepth -> Fill( qie10.ieta() , qie10.iphi() , qie10.depth() );
      for (int j = 0; j < nSample; ++j){
        h_QIE10DigiFC -> Fill( qie10.fc(j) );
        h_QIE10DigiLETDC -> Fill( qie10.letdc(j) );
        h_QIE10DigiCapID -> Fill( qie10.capid(j) );
      }
    };

  };  
}
  
