/*                                                                    
 * J. Kevin Adkins
 * University of Kentucky
 * May 30, 2013
 * 
 * Header file for StJetQAMaker.cxx
 */                                                                      

#ifndef STAR_StJetQAMaker
#define STAR_StJetQAMaker

#ifndef StMaker_H
#include "StMaker.h"
#endif

#include <vector>


// You do need in such simple case to add the include file
// (and compilation is much faster).

class TTree;
class TFile;
class TChain;
class TH2F;
class TH1F;
class StJetEvent;
class StJetVertex;
class StJetCandidate;
class StJetTrack;
class StJetTower;
class StJetParticle;
class StJetSkimEvent;
class StJetSkimTrig;
class StJetTower;

class StJetQAMaker : public StMaker {
 private:
  // Private method declaration if any
 
 protected:
  // Protected method if any

 public: 
  StJetQAMaker(const char *name, const char* outputFile, TChain *jetChain, TChain* skimChain);
  virtual       ~StJetQAMaker();
  virtual Int_t Init();
  virtual Int_t  Make();
  virtual Int_t Finish();
  virtual void ParticleCuts(StJetCandidate*);
  virtual void FillParticlePlots(StJetTrack*);

  TString outfile;
  TFile *jetRootFile;
  TChain *mJetChain, *mSkimChain;
  StJetEvent *mJetEvent;
  StJetSkimEvent *mSkimEvent;
  StJetVertex *mJetVertex;
  StJetCandidate *mJet;
  StJetTrack *mJetTrack;
  StJetTower *mJetTower;
  StJetSkimTrig *mJP2;
  Int_t runNum;
  vector <double> pMomentum;

  //Histograms for QA
  //JP0 Histograms
  TH1F *JP2_jetEta, *JP2_jetPhi, *JP2_jetPt, *JP2_towEt, *JP2_towPhi, *JP2_towEta, *JP2_trackPt, *JP2_trackPhi, *JP2_trackEta, *JP2_numJets, *JP2_numTracks, *JP2_numTow, *JP2_verX, 
    *JP2_verY, *JP2_verZ, *JP2_jetRt, *JP2_hadronEta, *JP2_jetdetEta, *JP2_trackDcaZ, *JP2_trackDcaD, *JP2_trackdEdx, *JP2_towAdc, *JP2_towPedAdc, *JP2_towPed, *JP2_PreScale, *JP2_tracknSigmaPion, *JP2_tracknSigmaKaon, *JP2_tracknSigmaProton, *JP2_tracknSigmaElectron, *JP2_trackm, *JP2_didFire, *JP2_didshouldFire, *JP2_didFire0, *JP2_didshouldFire0;
  TH2F *JP2_trackPtEtaCorr, *JP2_trackPtPhiCorr, *JP2_trackEtaPhiCorr, *JP2_hadronEtaPhiCorr, *JP2_jetEtaPhiCorr, *JP2_towerEtvsID;

  TH2F *JP2_EemcIDvsEt, *JP2_EemcIDvsAdc, *JP2_EemcIDvsEne, *JP2_EemcIDvsEta;

  // Values for the histograms to store
  Double_t numVertices;
  Double_t jetPt, jetEt, jetPhi, jetEta, jetRt, numJets, jetdetEta;
  Double_t trackPhi, trackPt, trackEta, numTracks, trackDcaZ, trackDcaD, trackdEdx, tracknSigmaPion, tracknSigmaKaon, tracknSigmaProton, tracknSigmaElectron, trackm;
  Double_t towEt, towEta, towPhi, numTowers, towAdc, towPed, towPedAdc;
  Double_t verX, verY, verZ;
  
  

  /// Displayed on session exit, leave it as-is please ...
  virtual const char *GetCVS() const {
    static const char cvs[]="Tag $Name:  $ $Id: StJetQAMaker.h,v 1.15 2003/09/10 19:47:43 perev Exp $ built " __DATE__" " __TIME__ ; 
    return cvs;
  }

  ClassDef(StJetQAMaker,0)   //StAF chain virtual base class for Makers
};

#endif
