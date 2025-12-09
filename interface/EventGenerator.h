#ifndef EventGenerator_h
#define EventGenerator_h

#include "Pythia8/Pythia.h"
#include "JetAnalysis.h"
#include "JetCollection.h"

class EventGenerator {
  public:
    EventGenerator() {};
    ~EventGenerator() {};

    void initialize() {
      pythia_.readString("Random:setSeed = on");
      pythia_.readString("Random:seed = 0"); // use time-based seed
      pythia_.readString("Beams:idA = 2212"); // proton
      pythia_.readString("Beams:idB = 2212"); // proton
      pythia_.readString("Beams:eCM = 14000."); // 14 TeV
      pythia_.readString("Top:gg2ttbar = on"); // gluon fusion
      pythia_.readString("Top:qqbar2ttbar = on"); // quark-antiquark annihilation
      pythia_.init();

    }
    
    void generateEvents(size_t nEvents) {
      for (size_t iEvent = 0; iEvent < nEvents; ++iEvent) {
        if (!pythia_.next()) continue;
        const Pythia8::Event& event = pythia_.event;
        auto jetAnalysis = std::make_unique<JetAnalysis>(); 
        jetAnalysis->convertPythiaToPseudoJets(event);
        jetAnalysis->clusterJets(0.4);
        auto jets = jetAnalysis->getJets(20.0);    
        jetCollection_.push_back(jets);
        jetAnalysisCollection_.push_back(std::move(jetAnalysis));
      }
    }

    const JetCollection& getJetCollection() const {
      return jetCollection_;
    }

  private:
    Pythia8::Pythia pythia_;
    JetCollection jetCollection_;
    std::vector<std::unique_ptr<JetAnalysis>> jetAnalysisCollection_; 
};
#endif