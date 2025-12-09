#include "EventGenerator.h"
#include "JetAnalyzer.h"
#include <iostream>
#include "ArgumentParser.h"

void printEventInfo(const JetCollection& jetCollection) {
    for (size_t i = 0; i < jetCollection.size(); ++i) {
        std::cout << " *************\n";
        std::cout << " Event " << i << " has " << jetCollection[i].size() << " jets." << std::endl;
        for (size_t j = 0; j < jetCollection[i].size(); ++j) {
            const auto& jet = jetCollection[i][j];
            std::cout << "  Jet " << j + 1 << ": pt = " << jet.pt() 
                      << ", eta = " << jet.eta() 
                      << ", phi = " << jet.phi() << std::endl;
            for (int k = 0; k < jet.constituents().size(); ++k) {
                const auto& constituent = jet.constituents()[k];
                std::cout << "    Constituent " << k + 1 << ": pt = " << constituent.pt() 
                          << ", eta = " << constituent.eta() 
                          << ", phi = " << constituent.phi() << std::endl;
            }
        }
        std::cout << " *************\n";
    }
}

int main(int argc, char** argv) {

    ArgumentParser argParser;
    if (!argParser.parse(argc, argv)) {
        return 1;
    } 
    argParser.parse(argc, argv);
    bool debug = argParser.isDebug();
    size_t nEvents = argParser.getNEvents();
    std::string outputFilename = argParser.getFilename();

    EventGenerator eventGen;
    eventGen.initialize();
    eventGen.generateEvents(nEvents);
    const JetCollection& jets = eventGen.getJetCollection();
    if (debug) {
        printEventInfo(jets);
    }
    JetAnalyzer jetAnalyzer(outputFilename);
    jetAnalyzer.analyze(jets);
    return 0;
}