/* 
 * J. Kevin Adkins
 * University of Kentucky
 * May 30, 2013
 *
 * This code will create the reduced jet trees from the jet maker
 * trees that will be used for jet QA 
 */

#include "math.h"
#include "StJetQAMaker.h"
#include "TDataSetIter.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"

#include "StSpinPool/StJetEvent/StJetEvent.h"
#include "StSpinPool/StJetEvent/StJetCandidate.h"
#include "StSpinPool/StJetEvent/StJetParticle.h"
#include "StSpinPool/StJetEvent/StJetTrack.h"
#include "StSpinPool/StJetEvent/StJetTower.h"
#include "StSpinPool/StJetEvent/StJetVertex.h"
#include "StSpinPool/StJetSkimEvent/StJetSkimEvent.h"
#include "StSpinPool/StJetEvent/StJetTower.h"

ClassImp(StJetQAMaker)

//_____________________________________________________________________________
/// TLA constructor
  StJetQAMaker::StJetQAMaker(const char *name, const char *outputFile, TChain *jetChain, TChain *skimChain):StMaker(name), mJetChain(jetChain), mSkimChain(skimChain){
    outfile = TString(outputFile);
}

//_____________________________________________________________________________
/// This is TLA destructor
StJetQAMaker::~StJetQAMaker(){
  //
}


//_____________________________________________________________________________
/// Init - is a first method the top level StChain calls to initialize all its makers 
Int_t StJetQAMaker::Init(){
   jetRootFile = new TFile(outfile, "recreate");

   //Initialize the Jet and Skim events
   mJetEvent = 0;
   mSkimEvent = 0;

   // Set branch address of the Jet and Skim chains
   mJetChain->SetBranchAddress("AntiKtR060NHits12", &mJetEvent);
   mSkimChain->SetBranchAddress("skimEventBranch", &mSkimEvent);

   // Initialize QA histograms
   //JP2
   JP2_jetEta = new TH1F("JP2_jetEta", "Trig JP2 jetEta", 80, -2.0, 2.0);
   JP2_jetPhi = new TH1F("JP2_jetPhi", "Trig JP2 jetPhi", 70, -3.2, 3.2);
   JP2_jetPt = new TH1F("JP2_jetPt", "Trig JP2 jetPt", 100, 0.0, 100.0);
   JP2_jetRt = new TH1F("JP2_jetRt", "Trig JP2 jetRt", 30, 0.0, 1.5);
   JP2_towEt = new TH1F("JP2_towEt", "Trig JP2 towEt", 100, 0.0, 100.0);
   JP2_towPhi = new TH1F("JP2_towPhi", "Trig JP2 towPhi", 60, -3.5, 3.5);
   JP2_towEta = new TH1F("JP2_towEta", "TrigJP2 towEta", 80, -2.0, 2.0);
   JP2_trackPt = new TH1F("JP2_trackPt", "TrigJP2 trackPt", 100, 0, 100);
   JP2_trackPhi = new TH1F("JP2_trackPhi", "TrigJP2 trackPhi", 60, -3.5, 3.5);
   JP2_trackEta = new TH1F("JP2_trackEta", "TrigJP2 trackEta", 80, -3.5, 3.5);
   JP2_hadronEta = new TH1F("JP2_hadronEta", "Trig JP2 hadronEta", 80, -1.5, 1.5);
   JP2_numJets = new TH1F("JP2_numJets", "TrigJP2 numJets", 50, 0.0, 50.);
   JP2_numTracks = new TH1F("JP2_numTracks", "TrigJP2 numTracks", 50, 0., 50.);
   JP2_numTow = new TH1F("JP2_numTow", "TrigJP2 numTow", 100, 0.0, 100);
   JP2_verX = new TH1F("JP2_verX", "TrigJP2 vertexX", 200, -100, 100);
   JP2_verY = new TH1F("JP2_verY", "TrigJP2 vertexY", 200, -100, 100);
   JP2_verZ = new TH1F("JP2_verZ", "TrigJP2 vertexZ", 200, -100, 100);

   JP2_jetdetEta = new TH1F("JP2_jetdetEta", "Trig JP2 jetdetEta", 80, -2.0, 2.0);
   JP2_trackDcaZ = new TH1F("JP2_trackDcaZ", "Trig JP2 trackDcaZ", 600, -3.0,3.0);
   JP2_trackDcaD = new TH1F("JP2_trackDcaD", "Trig JP2 trackDcaD", 600, -3.0,3.0);
   JP2_trackdEdx = new TH1F("JP2_trackdEdx", "Trig JP2 trackdEdx", 100000, 0.0, 0.0001);
   JP2_towAdc = new TH1F("JP2_towAdc", "Trig JP2 towAdc", 4800, 0., 4800.);
   JP2_towPed = new TH1F("JP2_towPed", "Trig JP2 towPed", 4800, 0., 4800.);
   JP2_towPedAdc = new TH1F("JP2_towPedAdc", "Trig JP2 towPedAdc", 4800, 0., 4800.);
   JP2_PreScale = new TH1F("JP2_PreScale", "Trig JP2 PreScale", 100000000, 0., 100000000.);

   JP2_tracknSigmaPion = new TH1F("JP2_tracknSigmaPion", "Trig JP2 tracknSigmaPion", 60000, -30, 30);
   JP2_tracknSigmaKaon = new TH1F("JP2_tracknSigmaKaon", "Trig JP2 tracknSigmaKaon", 60000, -30, 30);
   JP2_tracknSigmaProton = new TH1F("JP2_tracknSigmaProton", "Trig JP2 tracknSigmaProton", 60000, -30, 30);
   JP2_tracknSigmaElectron = new TH1F("JP2_tracknSigmaElectron", "Trig JP2 tracknSigmaElectron", 60000, -30, 30);
   JP2_trackm = new TH1F("JP2_trackm", "Trig JP2 trackm", 400000, -20, 20);

   JP2_didFire = new TH1F("JP2_didFire", "", 5,0,5);
   JP2_didshouldFire = new TH1F("JP2_didshouldFire", "", 5,0,5);

   JP2_didFire0 = new TH1F("JP2_didFire0", "", 5,0,5);
   JP2_didshouldFire0 = new TH1F("JP2_didshouldFire0", "", 5,0,5);

   JP2_trackPtEtaCorr = new TH2F("JP2_trackPtEtaCorr", "Track Pt vs Eta", 100, 0., 50., 40, -2., 2.);
   JP2_trackPtPhiCorr = new TH2F("JP2_trackPtPhiCorr", "Track Pt vs Phi", 100, 0., 50., 60, -3.5, 3.5);
   JP2_trackEtaPhiCorr = new TH2F("JP2_trackEtaPhiCorr", "Track Eta vs Phi", 40, -2., 2., 60, -3.5, 3.5);
   JP2_hadronEtaPhiCorr = new TH2F("JP2_hadronEtaPhiCorr", "Hadron Eta vs Phi", 40, -2., 2., 60, -3.5, 3.5);
   JP2_jetEtaPhiCorr = new TH2F("JP2_jetEtaPhiCorr", "Jet Eta vs Phi", 40, -2., 2., 60, -3.5, 3.5);
   JP2_towerEtvsID = new TH2F("JP2_towerEtvsID","",5000,0.,5000,1000,0.,20.);

   JP2_EemcIDvsEt   = new TH2F("JP2_EemcIDvsEt", "Tower Id vs. E", 800, -50, 750, 5000, 0, 50);
   JP2_EemcIDvsAdc = new TH2F("JP2_EemcIDvsAdc", "Tower Id vs. Adc", 800, -50, 750, 5000, 0, 5000);
   JP2_EemcIDvsEne = new TH2F("JP2_EemcIDvsEne", "Tower Id vs. Ene", 800, -50, 750, 5000, 0, 100);
   JP2_EemcIDvsEta = new TH2F("JP2_EemcIDvsEta", "Tower Id vs. Eta", 800, -50, 750, 50, -2, 3);

   return StMaker::Init();
}


//_____________________________________________________________________________
/// Make - this method is called in loop for each event
Int_t StJetQAMaker::Make(){

  // Reset all values to zero for each event
  jetPt = jetEt = jetPhi = jetEta = jetRt = numJets = trackPhi = trackPt = trackEta = numTracks = 0.;
  towEt = towEta = towPhi = numTowers = verX = verY = verZ = 0.;

  // This is called for each event, so there is no event loop as in the macro.
  // So we start with getting information directly from the event
  assert(mJetEvent && mSkimEvent);
  assert(mJetEvent->runId() == mSkimEvent->runId() && mJetEvent->eventId() == mSkimEvent->eventId());
  runNum = mJetEvent->runId();
  // initialize the triggers

  mJP2 = mSkimEvent->trigger(500411);
  if(!mJP2) mJP2 = mSkimEvent->trigger(500401);

  if(mJP2 && mJP2->didFire()){
    JP2_didFire0->Fill(1);
    if(mJP2->shouldFire()==1) JP2_didshouldFire0->Fill(1);
  }
  // Start vertex loop
  numVertices = mJetEvent->numberOfVertices();
  //cout << "Number of Vertices: " << numVertices << endl;
  for (Int_t iVertex = 0; iVertex < numVertices; ++iVertex){
    mJetVertex = mJetEvent->vertex(iVertex);   
    numJets = mJetVertex->numberOfJets();
    //cout << "Number of Jets: " << numJets << endl;
    if(mJP2 && mJP2->didFire()){
      JP2_didFire->Fill(1);
      if(mJP2->shouldFire()) JP2_didshouldFire->Fill(1);
    }

    // Loop through jets at the vertex
    for (Int_t iJet = 0; iJet < numJets; ++iJet){
      mJet = mJetVertex->jet(iJet);
      jetPt = mJet->pt();
      jetEta = mJet->eta();
      jetPhi = mJet->phi();
      jetRt = mJet->neutralFraction();
      numTracks = mJet->numberOfTracks();
      numTowers = mJet->numberOfTowers();
      verX = mJetVertex->position().x();
      verY = mJetVertex->position().y();
      verZ = mJetVertex->position().z();

      jetdetEta = mJet->detEta();

      // Now check to see if trigger fired. If it did fill it with the above information
      // JP2
      if(mJP2){
	if (mJP2->didFire() && mJP2->shouldFire() == 1){
	  JP2_jetPt->Fill(jetPt);
	  JP2_jetEta->Fill(jetEta);
	  JP2_jetPhi->Fill(jetPhi);
	  JP2_jetRt->Fill(jetRt);
	  JP2_numJets->Fill(numJets);
	  JP2_verX->Fill(verX);
	  JP2_verY->Fill(verY);
	  JP2_verZ->Fill(verZ);
	  JP2_jetEtaPhiCorr->Fill(jetEta, jetPhi);

          JP2_jetdetEta->Fill(jetdetEta);
	}
      }
      // Loop through the tracks in the jet
      numTracks = mJet->numberOfTracks();
      //cout <<"Number of Tracks: " <<  numTracks << endl;
      for (Int_t iTrack = 0; iTrack < numTracks; ++iTrack){
	mJetTrack = mJet->track(iTrack);
	trackPt = mJetTrack->pt();
	trackEta = mJetTrack->eta();
	trackPhi = mJetTrack->phi();
	trackDcaZ = mJetTrack->dcaZ();
        trackDcaD = mJetTrack->dcaD();
        trackdEdx = mJetTrack->dEdx();
        tracknSigmaPion = mJetTrack->nSigmaPion();
        tracknSigmaKaon = mJetTrack->nSigmaKaon();
        tracknSigmaProton = mJetTrack->nSigmaProton();
        tracknSigmaElectron = mJetTrack->nSigmaElectron();
        trackm = mJetTrack->m();

	// Fill HIstograms
	// JP2
	if(mJP2){
	  if (mJP2->didFire() && mJP2->shouldFire() == 1){
	    JP2_trackPt->Fill(trackPt);
	    JP2_trackEta->Fill(trackEta);
	    JP2_trackPhi->Fill(trackPhi);
	    JP2_numTracks->Fill(numTracks);
	    JP2_trackPtEtaCorr->Fill(trackPt,trackEta);
	    JP2_trackPtPhiCorr->Fill(trackPt,trackPhi);
	    JP2_trackEtaPhiCorr->Fill(trackEta,trackPhi);

            JP2_trackDcaZ->Fill(trackDcaZ);
            JP2_trackDcaD->Fill(trackDcaD);
            JP2_trackdEdx->Fill(trackdEdx);

            JP2_tracknSigmaPion->Fill(tracknSigmaPion);
            JP2_tracknSigmaKaon->Fill(tracknSigmaKaon);
            JP2_tracknSigmaProton->Fill(tracknSigmaProton);
            JP2_tracknSigmaElectron->Fill(tracknSigmaElectron);
            JP2_trackm->Fill(trackm);
	  }
	}
      } // Tracks Loop

      ParticleCuts(mJet);

      //Loop through towers
      numTowers = mJet->numberOfTowers();
      //cout << "Number of Towers: " <<  numTowers << endl;
      for (Int_t iTower = 0; iTower < numTowers; ++iTower){
	mJetTower = mJet->tower(iTower);
	towEta = mJetTower->eta();
	towEt = mJetTower->energy()/cosh(towEta);
	towPhi = mJetTower->phi();

        towAdc = mJetTower->adc();
        towPed = mJetTower->pedestal();
        towPedAdc = mJetTower->adc() - mJetTower->pedestal();
	// Fill Histograms -- JP0
	// JP2
	if (mJP2){
	  if (mJP2->didFire() && mJP2->shouldFire() == 1){
	    JP2_towEt->Fill(towEt);
	    JP2_towPhi->Fill(towPhi);
	    JP2_towEta->Fill(towEta);
	    JP2_numTow->Fill(numTowers);
            JP2_towerEtvsID->Fill(mJetTower->id(),towEt);

            JP2_towAdc->Fill(towAdc);
            JP2_towPed->Fill(towPed);
            JP2_towPedAdc->Fill(towPedAdc);

            if(mJetTower->detectorId() == 13) JP2_EemcIDvsEt->Fill(mJetTower->id(),towEt);
            if(mJetTower->detectorId() == 13) JP2_EemcIDvsEne->Fill(mJetTower->id(),mJetTower->energy());
            if(mJetTower->detectorId() == 13) JP2_EemcIDvsAdc->Fill(mJetTower->id(),mJetTower->adc());
            if(mJetTower->detectorId() == 13) JP2_EemcIDvsEta->Fill(mJetTower->id(),mJetTower->eta());
	  }
	}
      }// Towers Loop
    }// Jet Loop
  }// Vertex Loop
  return kStOK;
}

Int_t StJetQAMaker::Finish()
{
  jetRootFile->Write();
  jetRootFile->Close();
  delete jetRootFile;
  return kStOk;
}


void StJetQAMaker::ParticleCuts(StJetCandidate *jet)
{
  Int_t leadPosition = 0;
  pMomentum.clear();
  pMomentum.resize(jet->numberOfTracks());
  for (Int_t iTrack = 0; iTrack < jet->numberOfTracks(); ++iTrack){
    StJetTrack *particle = jet->track(iTrack);
    pMomentum.at(iTrack) = particle->momentum().Mag();
  }
  
  if (pMomentum.size() > 1){ // Otherwise the leading particle is in the zeroth position
    double leadParticle = 0.0;
    for (UInt_t pos = 0; pos < pMomentum.size(); pos++){
      if(pMomentum.at(pos) > leadParticle){
	leadParticle = pMomentum.at(pos);
	leadPosition = pos;
      }
    }
  }
  
  if (jet->numberOfTracks() > 0){
    //cout << leadPosition << endl;
    StJetTrack *mLeadTrack = jet->track(leadPosition);
    //Double_t charge = mLeadTrack->charge();
    if (mLeadTrack->dca().Mag()<1.0 && mLeadTrack->nHitsFit()>12){ // cuts on the leading track
      FillParticlePlots(mLeadTrack);
    }
  }
}
  

void StJetQAMaker::FillParticlePlots(StJetTrack* track)
{
  // JP2
  if (mJP2){
    if (mJP2->didFire() && mJP2->shouldFire() == 1){
      JP2_hadronEta->Fill(track->eta());
      JP2_hadronEtaPhiCorr->Fill(track->eta(),track->phi());
    }
  }  
}
