#include "JetAnalyzer.h"

void JetAnalyzer::setBranches(TTree* tree) {
    tree->Branch("jetPt", &jetPt_);
    tree->Branch("jetEta", &jetEta_);
    tree->Branch("jetPhi", &jetPhi_);
    tree->Branch("jetEnergy", &jetEnergy_);
    tree->Branch("jetNConstituents", &jetNConstituents_);
    tree->Branch("jetConstituentsPx", &jetConstituentsPx_);
    tree->Branch("jetConstituentsPy", &jetConstituentsPy_);
    tree->Branch("jetConstituentsPz", &jetConstituentsPz_);
    tree->Branch("jetConstituentsPt", &jetConstituentsPt_);
    tree->Branch("jetConstituentsE", &jetConstituentsE_);
    tree->Branch("jetConsituentsEta", &jetConsituentsEta_);
    tree->Branch("jetConstituentsPhi", &jetConstituentsPhi_);
    tree->Branch("jetConstituentsPdgId", &jetConstituentsPdgId_);
}

void JetAnalyzer::analyze(const JetCollection& jetCollection) {
    TTree* tree = new TTree("JetTree", "Jet Analysis Tree");
    setBranches(tree);

    for (const auto& jets : jetCollection) {
        for (const auto& jet : jets) {
            jetPt_.push_back(jet.pt());
            jetEta_.push_back(jet.eta());
            jetPhi_.push_back(jet.phi());
            jetEnergy_.push_back(jet.e());
            jetNConstituents_.push_back(jet.constituents().size());

            double sumPt = 0.0, sumEta = 0.0, sumPhi = 0.0;
            for (const auto& constituent : jet.constituents()) {
                sumPt += constituent.pt();
                sumEta += constituent.eta();
                sumPhi += constituent.phi();

                jetConstituentsPx_.push_back(constituent.px());
                jetConstituentsPy_.push_back(constituent.py());
                jetConstituentsPz_.push_back(constituent.pz());
                jetConstituentsE_.push_back(constituent.e());
                jetConstituentsPt_.push_back(constituent.pt());
                jetConsituentsEta_.push_back(constituent.eta());
                jetConstituentsPhi_.push_back(constituent.phi());
                jetConstituentsPdgId_.push_back(constituent.user_index());
            }
        }
        tree->Fill();
        clear();
    }

    outputFile_->Write();
}