#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHERecHit.h"
#include "HFRecHit.h"
#include "QIE11.h"
#include "QIE10.h"
#include "HODigi.h"

void analysisClass::loop(){
  
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
  tuple_tree -> fChain -> SetBranchStatus("bx"              , kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitTime" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHERecHitDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitTime" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFRecHitDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecTime" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiGain" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRCGain" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiAllFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiPedFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiTotFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiADC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiTDC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiCapID" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiCapIDError" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE11DigiSOI" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiIPhi" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiIEta" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiDepth" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiFC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiLETDC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiTETDC" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiCapID" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("QIE10DigiSOI" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTKey" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerDecisions" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerNames" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerPrescales" , kTRUE);

  //--------------------------------------------------------------------------------
  // Histograms
  //--------------------------------------------------------------------------------

  TH1F * h_bx = makeTH1F("h_bx", " Bunch crossing ; BX ; Events ", 364, -40, 3600); // Max should be 3564 (Physics <= 3445, Abort gap >= 3446)

  // HBHE RecHit

  TH1F * h_HBHErecHitEnergy = makeTH1F("h_HBHERecHitEnergy", " HBHE RecHit Energy ; RecHit Energy [GeV] ; Entries ", 100, -1, 2);
  TH1F * h_HBHErecHitTime = makeTH1F("h_HBHERecHitTime", " HBHE RecHit Time ; RecHit Time [ns] ; Entries ", 100, -15000, 5000);

  char histName[100];
  char titleName[100];
  std::map <int,TH2F*> h_HBHErecHitEnergyPerDepth;
  std::map <int,TH2F*> h_HBHErecHitChargePerDepth;
  //std::map <int,TH2F*> h_HBHErecHitTDCPerDepth;
  std::map <int,TH2F*> h_HBHEDigiHitsPerDepth;
  for (int depth = 1; depth <= 7; depth++){
    sprintf(histName,"h_HBHErecHitEnergyPerDepth%d",depth);
    sprintf(titleName," HBHE energy over i#eta / i#phi for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHErecHitEnergyPerDepth[depth] = makeTH2F(histName, titleName, 83, -41.5, 41.5, 72, 0.5, 72.5);

    sprintf(histName,"h_HBHErecHitChargePerDepth%d",depth);
    sprintf(titleName," HBHE total charge over i#eta / i#phi for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHErecHitChargePerDepth[depth] = makeTH2F(histName, titleName, 83, -41.5, 41.5, 72, 0.5, 72.5);

    /*sprintf(histName,"h_HBHErecHitTDCPerDepth%d",depth);
    sprintf(titleName," HBHE TDC over i#eta / i#phi for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHErecHitTDCPerDepth[depth] = makeTH2F(histName, titleName, 83, -41.5, 41.5, 72, 0.5, 72.5);*/

    sprintf(histName,"h_HBHEDigiHitsPerDepth%d",depth);
    sprintf(titleName," HBHE Digi hits for Depth %d ; i#eta ; i#phi ",depth);
    h_HBHEDigiHitsPerDepth[depth] = makeTH2F(histName, titleName, 83, -41.5, 41.5, 72, 0.5, 72.5);
  }

  // HF RecHit

  TH1F * h_HFrecHitEnergy = makeTH1F("h_HFRecHitEnergy", " HF RecHit Energy ; RecHit Energy [GeV] ; Entries ", 100, -5, 5);
  TH1F * h_HFrecHitTime = makeTH1F("h_HFRecHitTime", " HF RecHit Time ; RecHit Time [ns] ; Entries ", 100, -120, -80);
  TH2F * h_HFDigiHits = makeTH2F("h_HFDigiHits", " HF Digi hits ; i#eta ; i#phi ", 83, -41.5, 41.5, 72, 0.5, 72.5);

  std::map <int,TH2F*> h_HFrecHitEnergyPerDepth;
  std::map <int,TH2F*> h_HFrecHitChargePerDepth;
  for (int depth = 1; depth <= 2; depth++){
    sprintf(histName,"h_HFrecHitEnergyPerDepth%d",depth);
    sprintf(titleName," HF energy over i#eta / i#phi for Depth %d ; i#eta ; i#phi ",depth);
    h_HFrecHitEnergyPerDepth[depth] = makeTH2F(histName, titleName, 83, -41.5, 41.5, 72, 0.5, 72.5);
  }
  for (int depth = 1; depth <= 4; depth++){
    sprintf(histName,"h_HFrecHitChargePerDepth%d",depth);
    sprintf(titleName," HF total charge over i#eta / i#phi for Depth %d ; i#eta ; i#phi ",depth);
    h_HFrecHitChargePerDepth[depth] = makeTH2F(histName, titleName, 83, -41.5, 41.5, 72, 0.5, 72.5);
  }

  // HO Digi & RecHit

  TH1F * h_HOrecHitEnergy = makeTH1F("h_HORecHitEnergy", " HO RecHit Energy ; RecHit Energy [GeV] ; Entries ", 100, 0, 200);
  TH1F * h_HOrecHitTime = makeTH1F("h_HORecHitTime", " HO RecHit Time ; RecHit Time [ns] ; Entries ", 140, -70, 70);
  TH2F * h_HOrecHitEnergyPerEtaPhi = makeTH2F("h_HOrecHitEnergyPerEtaPhi", " HO RecHit energy over i#eta / i#phi ; i#eta ; i#phi ; i#eta ; i#phi ", 31, -15.5, 15.5, 72, 0.5, 72.5);
  TH2F * h_HOrecHitChargePerEtaPhi = makeTH2F("h_HOrecHitChargePerEtaPhi", " HO total charge (sum over all TS) over i#eta / i#phi ; i#eta ; i#phi ; i#eta ; i#phi ", 31, -15.5, 15.5, 72, 0.5, 72.5);
  TH2F * h_HOChargeTS = makeTH2F("h_HOChargeTS", " HO charge over TS ; TS ; TS Charge [fC] ", 10, 0, 10, 128, 0, 12800); //QIE8 in HO: Max charge is 10k-11k fC.
  TH2F * h_HOEnergyTS = makeTH2F("h_HOEnergyTS", " HO energy over TS ; TS ; TS Energy [GeV] ", 10, 0, 10, 70, 0, 350);
  TH2F * h_HOGainPerEtaPhi = makeTH2F("h_HOGainPerEtaPhi", " HO gain over i#eta / i#phi ; i#eta ; i#phi ", 31, -15.5, 15.5, 72, 0.5, 72.5);
  TH2F * h_HORCGainPerEtaPhi = makeTH2F("h_HORCGainPerEtaPhi", " HO RCgain over i#eta / i#phi ; i#eta ; i#phi ", 31, -15.5, 15.5, 72, 0.5, 72.5);

  std::map <int,TH2F*> h_HOrecHitEnergyPerEtaPhiTS;
  std::map <int,TH2F*> h_HOChargePerEtaPhiTS;
  std::map <int,TH2F*> h_HORawChargePerEtaPhiTS;
  std::map <int,TH2F*> h_HOPedestalPerEtaPhiTS;
  for (int TS = 1; TS <= 10; TS++){
    sprintf(histName,"h_HOrecHitEnergyPerEtaPhiTS%d",TS);
    sprintf(titleName," HO energy over i#eta / i#phi for TS %d ; i#eta ; i#phi ",TS);
    h_HOrecHitEnergyPerEtaPhiTS[TS] = makeTH2F(histName, titleName, 31, -15.5, 15.5, 72, 0.5, 72.5);

    sprintf(histName,"h_HOChargePerEtaPhiTS%d",TS);
    sprintf(titleName," HO total charge over i#eta / i#phi for TS %d ; i#eta ; i#phi ",TS);
    h_HOChargePerEtaPhiTS[TS] = makeTH2F(histName, titleName, 31, -15.5, 15.5, 72, 0.5, 72.5);

    sprintf(histName,"h_HORawChargePerEtaPhiTS%d",TS);
    sprintf(titleName," HO raw charge over i#eta / i#phi for TS %d ; i#eta ; i#phi ",TS);
    h_HORawChargePerEtaPhiTS[TS] = makeTH2F(histName, titleName, 31, -15.5, 15.5, 72, 0.5, 72.5);

    sprintf(histName,"h_HOPedestalPerEtaPhiTS%d",TS);
    sprintf(titleName," HO pedestal charge over i#eta / i#phi for TS %d ; i#eta ; i#phi ",TS);
    h_HOPedestalPerEtaPhiTS[TS] = makeTH2F(histName, titleName, 31, -15.5, 15.5, 72, 0.5, 72.5);
  }

  // QIE11 Digi ( = HBHE Digi )

  TH1F * h_QIE11DigiFC = makeTH1F("h_QIE11DigifC", " QIE11 Digi Charge ; Charge [fC] ; Entries ", 100, 0, 100000);
  TH1F * h_QIE11DigiFCSum = makeTH1F("h_QIE11DigifCSum", " QIE11 Digi Charge, Sum per Event ; Charge [fC] ; Entries ", 100, 0, 1000000);
  TH1F * h_QIE11DigiFCHBSum = makeTH1F("h_QIE11DigifCHBSum", " QIE11 Digi Charge, HB Sum per Event ; Charge [fC] ; Entries ", 100, 0, 1000000);
  TH1F * h_QIE11DigiFCHESum = makeTH1F("h_QIE11DigifCHESum", " QIE11 Digi Charge, HE Sum per Event ; Charge [fC] ; Entries ", 100, 0, 1000000);
  TH1F * h_QIE11DigiTDC = makeTH1F("h_QIE11DigiTDC", " QIE11 Digi TDC ; TDC ; Entries ", 64, 0, 64);
  TH2F * h_QIE11ADCvsTDC = makeTH2F("h_QIE11ADCvsTDC", " QIE11 over ADC / TDC ; ADC ; TDC ", 256, 0, 256, 64, 0, 64);
  TH2F * h_QIE11ADCvsTDCinHB = makeTH2F("h_QIE11ADCvsTDCinHB", " QIE11 over ADC / TDC in HB ; ADC ; TDC ", 256, 0, 256, 4, 0, 4);
  TH2F * h_QIE11ADCvsTDCinHE = makeTH2F("h_QIE11ADCvsTDCinHE", " QIE11 over ADC / TDC in HE ; ADC ; TDC ", 256, 0, 256, 64, 0, 64);
  TH2F * h_QIE11ChargeTS = makeTH2F("h_QIE11ChargeTS", " QIE11 Charge over TS ; TS ; TS Charge [fC] ", 8, 0, 8, 200, 0, 100000);
  TH2F * h_QIE11ADCvsCharge = makeTH2F("h_QIE11ADCvsCharge", " QIE11 Charge over ADC ; ADC ; Charge in TS [fC] ", 256, 0, 256, 60, 0, 30000);
  TH2F * h_QIE11TDCvsCharge = makeTH2F("h_QIE11TDCvsCharge", " QIE11 Charge over TDC ; TDC ; Charge in TS [fC] ", 64, 0, 64, 60, 0, 30000);
  TH2F * h_QIE11HBDigiNHitOverFC = makeTH2F("h_QIE11HBDigiNHitOverFC", " QIE11 HB Digi hits over charge ; Event total charge [fC] ; Number of hits >60fC", 160, 0, 4000000, 100, 0, 10000);
  TH2F * h_QIE11HEDigiNHitOverFC = makeTH2F("h_QIE11HEDigiNHitOverFC", " QIE11 HE Digi hits over charge ; Event total charge [fC] ; Number of hits >60fC", 160, 0, 4000000, 100, 0, 10000);

  std::map <int,TH2F*> h_QIE11ADCvsTDCinHBPerTS;
  std::map <int,TH2F*> h_QIE11ADCvsTDCinHEPerTS;
  for (int TS = 1; TS <= 8; TS++){
    sprintf(histName,"h_QIE11ADCvsTDCinHBPerTS%d",TS);
    sprintf(titleName," QIE11 over ADC / TDC in HB TS %d ; ADC ; TDC ",TS);
    h_QIE11ADCvsTDCinHBPerTS[TS] = makeTH2F(histName, titleName, 256, 0, 256, 4, 0, 4);

    sprintf(histName,"h_QIE11ADCvsTDCinHEPerTS%d",TS);
    sprintf(titleName," QIE11 over ADC / TDC in HE TS %d ; ADC ; TDC ",TS);
    h_QIE11ADCvsTDCinHEPerTS[TS] = makeTH2F(histName, titleName, 256, 0, 256, 64, 0, 64);
  }
  /*std::map <int,TH2F*> h_QIE11ChargeTSPerDepth;
  std::map <int,TH2F*> h_QIE11ADCvsTDCinHEPerTSDepth;
  for (int depth = 1; depth <= 7; depth++){
    sprintf(histName,"h_QIE11ChargeTSPerDepth%d",depth);
    sprintf(titleName," QIE11 Charge over TS for Depth %d ; TS ; TS Charge [fC] ",depth);
    h_QIE11ChargeTSPerDepth[depth] = makeTH2F(histName, titleName, 8, 0, 8, 200, 0, 100000);
  
    for (int TS = 1; TS <= 8; TS++){
      sprintf(histName,"h_QIE11ADCvsTDCinHEPerTSDepth%d",TS+depth*10);
      sprintf(titleName," QIE11 over ADC / TDC in HE TS %d Depth %d; ADC ; TDC ",TS,depth);
      h_QIE11ADCvsTDCinHEPerTSDepth[TS+depth*10] = makeTH2F(histName, titleName, 256, 0, 256, 64, 0, 64);
    }
  }*/

  TH2F * h_QIE11ChargeEtaPhi = makeTH2F("h_QIE11ChargeEtaPhi", " QIE11 charge over all TS ; i#eta ; i#phi ", 83, -41.5, 41.5, 72, 0.5, 72.5);
  TH2F * h_QIE11ChargeEtaPhiSOI = makeTH2F("h_QIE11ChargeEtaPhiSOI", " QIE11 charge over all TS at SOI ; i#eta ; i#phi ", 83, -41.5, 41.5, 72, 0.5, 72.5);

  // QIE10 Digi ( = HF Digi )

  TH1F * h_QIE10DigiFC = makeTH1F("h_QIE10DigifC", " QIE10 Digi Charge ; Charge [fC] ; Entries ", 200, 0, 200000);
  TH1F * h_QIE10DigiFCSum = makeTH1F("h_QIE10DigifCSum", " QIE10 Digi Charge, Sum per Event ; Charge [fC] ; Entries ", 100, 0, 1000000);
  TH2F * h_QIE10DigiFCoverBX = makeTH2F("h_QIE10DigiFCoverBX", " QIE10 Digi Charge over BX ; BX ; Charge [fC]", 360, 0, 3600, 35, 0, 350);
  TH2F * h_QIE10DigiFCSumoverBX = makeTH2F("h_QIE10DigiFCSumoverBX", " QIE10 Digi Charge Sum over BX ; BX ; Charge [fC] ", 360, 0, 3600, 100, 100000, 1000000);
  TH1F * h_QIE10DigiLETDC = makeTH1F("h_QIE10DigiLETDC", " QIE10 Digi LETDC ; TDC ; Entries ", 64, 0, 64);
  TH1F * h_QIE10DigiTETDC = makeTH1F("h_QIE10DigiTETDC", " QIE10 Digi TETDC ; TDC ; Entries ", 64, 0, 64);
  TH2F * h_QIE10DigiNHitOverFC = makeTH2F("h_QIE10DigiNHitOverFC", " QIE10 Digi hits over charge ; Event total charge [fC] ; Number of hits >60fC", 100, 0, 200000, 173, 0, 1728);

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  int logstep = n_events/20;
  if (logstep==0) logstep=1;
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( i % logstep == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheRechits (new Collection(*tuple_tree, tuple_tree -> HBHERecHitIEta -> size()));
    int nHBHERechits = hbheRechits -> GetSize();
    CollectionPtr hfRechits (new Collection(*tuple_tree, tuple_tree -> HFRecHitIEta -> size()));
    int nHFRechits = hfRechits -> GetSize();
    CollectionPtr hodigis (new Collection(*tuple_tree, tuple_tree -> HODigiIEta -> size()));
    int nHODigis = hodigis -> GetSize();
    CollectionPtr qie11s (new Collection(*tuple_tree, tuple_tree -> QIE11DigiIEta -> size()));
    int nQIE11s = qie11s -> GetSize();
    CollectionPtr qie10s (new Collection(*tuple_tree, tuple_tree -> QIE10DigiIEta -> size()));
    int nQIE10s = qie10s -> GetSize();

    getTriggers(tuple_tree->HLTKey, tuple_tree->HLTInsideDatasetTriggerNames, tuple_tree->HLTInsideDatasetTriggerDecisions, tuple_tree->HLTInsideDatasetTriggerPrescales);
    if (i==0) printTriggers();
    // Example for looking at triggers:
    //std::cout << "Trigger: " << triggerFired("HLT_ZeroBias_split_v1") << std::endl;

    h_bx -> Fill( tuple_tree->bx );

  // HBHE RecHit
    for (int iHBHERechit = 0; iHBHERechit < nHBHERechits; ++iHBHERechit){
      HBHERecHit hbheRechit = hbheRechits -> GetConstituent<HBHERecHit>(iHBHERechit);

      int ieta = hbheRechit.ieta();
      int iphi = hbheRechit.iphi();
      int depth = hbheRechit.depth();
      bool isHE = ((abs(ieta) > 16) || (abs(ieta) == 16 && depth == 4));

      h_HBHErecHitEnergy -> Fill( hbheRechit.energy() );
      h_HBHErecHitTime -> Fill( hbheRechit.recHitTime() );
      h_HBHErecHitEnergyPerDepth[depth] -> Fill( ieta , iphi , hbheRechit.energy() );
    };

  // HF RecHit
    for (int iHFRechit = 0; iHFRechit < nHFRechits; ++iHFRechit){
      HFRecHit hfRechit = hfRechits -> GetConstituent<HFRecHit>(iHFRechit);

      int ieta = hfRechit.ieta();
      int iphi = hfRechit.iphi();
      int depth = hfRechit.depth();

      h_HFrecHitEnergy -> Fill( hfRechit.energy() );
      h_HFrecHitTime -> Fill( hfRechit.recHitTime() );
      h_HFrecHitEnergyPerDepth[depth] -> Fill( ieta , iphi , hfRechit.energy() );
    };

  // HO Digi & RecHit
    for (int iHODigi = 0; iHODigi < nHODigis; ++iHODigi){
      HODigi hodigi = hodigis -> GetConstituent<HODigi>(iHODigi);

      int ieta = hodigi.ieta();
      int iphi = hodigi.iphi();

      h_HOrecHitEnergy -> Fill( hodigi.recenergy() );
      h_HOrecHitTime -> Fill( hodigi.recHitTime() );
      h_HOrecHitEnergyPerEtaPhi -> Fill( ieta , iphi , hodigi.recenergy() );
      h_HOGainPerEtaPhi -> Fill( ieta , iphi , hodigi.gain(0) );
      h_HORCGainPerEtaPhi -> Fill( ieta , iphi , hodigi.rcGain(0) );

      for (int j = 0; j < 10; ++j){ // Loop over 10 TSs
        h_HOrecHitChargePerEtaPhi -> Fill( ieta , iphi , hodigi.fc(j) );
        h_HOChargeTS -> Fill( j, hodigi.fc(j) );
        h_HOEnergyTS -> Fill( j, hodigi.energy(j) );
        h_HOrecHitEnergyPerEtaPhiTS[j+1] -> Fill( ieta , iphi , hodigi.energy(j) );
        h_HOChargePerEtaPhiTS[j+1] -> Fill( ieta , iphi , hodigi.fc(j) );
        h_HORawChargePerEtaPhiTS[j+1] -> Fill( ieta , iphi , hodigi.allFC(j) );
        h_HOPedestalPerEtaPhiTS[j+1] -> Fill( ieta , iphi , hodigi.pedFC(j) );
      }
    };

  // QIE11 Digi ( = HBHE Digi )
    float fCHBSum = 0.0;
    float fCHESum = 0.0;
    int Nhits60fcHB = 0;
    int Nhits60fcHE = 0;
    for (int iQIE11 = 0; iQIE11 < nQIE11s; ++iQIE11){
      QIE11 qie11 = qie11s -> GetConstituent<QIE11>(iQIE11);

      int ieta = qie11.ieta();
      int iphi = qie11.iphi();
      int depth = qie11.depth();
      float totalfc = qie11.totalfc();
      bool isHE = ((abs(ieta) > 16) || (abs(ieta) == 16 && depth == 4));

      h_HBHEDigiHitsPerDepth[depth] -> Fill( ieta , iphi , 1 );
      h_HBHErecHitChargePerDepth[depth] -> Fill( ieta , iphi , totalfc );
      h_QIE11DigiFC -> Fill( totalfc );
      if (isHE){
        fCHESum += totalfc;
        if (totalfc > 60) Nhits60fcHE += 1;
      }else{
        fCHBSum += totalfc;
        if (totalfc > 60) Nhits60fcHB += 1;
      }

      for (int j = 0; j < 8; ++j){ // Loop over 8 TSs
        h_QIE11DigiTDC -> Fill( qie11.tdc(j) );
        h_QIE11ADCvsTDC -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
        //h_HBHErecHitTDCPerDepth[depth] -> Fill( ieta , iphi , qie11.tdc(j) );
        h_QIE11ChargeTS -> Fill( j, qie11.fc(j) );
        //h_QIE11ChargeTSPerDepth[depth] -> Fill( j, qie11.fc(j) );
        h_QIE11ADCvsCharge -> Fill( qie11.adc(j) , qie11.fc(j) , 1 );
        h_QIE11TDCvsCharge -> Fill( qie11.tdc(j) , qie11.fc(j) , 1 );
        if (isHE){
          h_QIE11ADCvsTDCinHEPerTS[j+1] -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
          //h_QIE11ADCvsTDCinHEPerTSDepth[j+1+depth*10] -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
          h_QIE11ADCvsTDCinHE -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
        }else{
          h_QIE11ADCvsTDCinHBPerTS[j+1] -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
          h_QIE11ADCvsTDCinHB -> Fill( qie11.adc(j) , qie11.tdc(j) , 1 );
        }
        h_QIE11ChargeEtaPhi -> Fill( ieta , iphi , qie11.fc(j) );
        if (qie11.soi(j)) h_QIE11ChargeEtaPhiSOI -> Fill( ieta , iphi , qie11.fc(j) );
      }
    };
    h_QIE11DigiFCHBSum -> Fill( fCHBSum );
    h_QIE11DigiFCHESum -> Fill( fCHESum );
    h_QIE11DigiFCSum -> Fill( fCHBSum+fCHESum );
    h_QIE11HBDigiNHitOverFC -> Fill( fCHBSum , Nhits60fcHB , 1);
    h_QIE11HEDigiNHitOverFC -> Fill( fCHESum , Nhits60fcHE , 1);


  // QIE10 Digi ( = HF Digi )
    float fCSum = 0.0;
    float Nhits60fc = 0;
    for (int iQIE10 = 0; iQIE10 < nQIE10s; ++iQIE10){
      QIE10 qie10 = qie10s -> GetConstituent<QIE10>(iQIE10);

      int ieta = qie10.ieta();
      int iphi = qie10.iphi();
      int depth = qie10.depth();
      double fc;
      h_HFDigiHits -> Fill( ieta , iphi , qie10.depth() );

      for (int j = 0; j < 3; ++j){ // Loop over 3 TSs
        fc = qie10.fc(j);
        h_QIE10DigiFC -> Fill( fc );
        h_QIE10DigiLETDC -> Fill( qie10.letdc(j) );
        h_QIE10DigiTETDC -> Fill( qie10.tetdc(j) );
        h_HFrecHitChargePerDepth[depth] -> Fill( ieta , iphi , fc );
        if(qie10.soi(j)) fCSum += fc;
        if(fc>60 && qie10.soi(j)) Nhits60fc += 1;
        h_QIE10DigiFCoverBX -> Fill( tuple_tree->bx , fc , 1);
      }
    };
    h_QIE10DigiFCSum -> Fill( fCSum );
    h_QIE10DigiFCSumoverBX -> Fill( tuple_tree->bx , fCSum , 1);
    h_QIE10DigiNHitOverFC -> Fill( fCSum , Nhits60fc , 1);

  };  
}

