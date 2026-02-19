#ifndef EventGenerator_h
#define EventGenerator_h

#include "Pythia8/Pythia.h"
#include "JetAnalysis.h"
#include "JetCollection.h"

class EventGenerator {
  public:
    EventGenerator(const std::string& configFile) : configFile_(configFile) {};
    ~EventGenerator() {};

    // intitialize with a configuration file
    // the function parsers line by line and applies the settings to the Pythia instance
    void initialize() {
      std::ifstream infile(configFile_);
      if (!infile.is_open()) {
        throw std::runtime_error("Could not open configuration file: " + configFile_);
      }
      std::string line;
      while (std::getline(infile, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;
        pythia_.readString(line);
      }
      infile.close();
      pythia_.init();
    }
    
      pythia_.readString("NewGaugeBoson:ffbar2gmZZprime = on");
      pythia_.readString("Zprime:gmZmode = 3"); // SM-like couplings
      pythia_.readString("32:m0 = 300."); // Z' mass 3 TeV
      pythia_.readString("32:onMode = off"); // turn off all Z' decays
      pythia_.readString("32:onIfAny = 1 2 3 4"); // turn on Z'->ttbar 
      ////ttbar
      //pythia_.readString("Top:gg2ttbar = on"); // gluon fusion
      //pythia_.readString("Top:qqbar2ttbar = on"); // quark-antiquark annihilation
      //// Z->tau tau
      //pythia_.readString("WeakSingleBoson:ffbar2gmZ = on");
      //pythia_.readString("WeakZ0:gmZmode = 2"); // SM-like couplings
      //pythia_.readString("23:onMode = off"); // turn off all Z decays
      //pythia_.readString("23:onIfAny = 15"); // turn on Z->tau tau
      pythia_.init();

    }*/
    
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
    std::string configFile_;
};

#endif
