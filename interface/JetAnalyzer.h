#ifndef JetAnalyzer_h
#define JetAnalyzer_h

#include <vector>
#include "TFile.h"
#include "JetCollection.h"
#include "TTree.h"
#include <string>

class JetAnalyzer {
  public:
    JetAnalyzer(std::string outputFilename = "jet_analysis.root") {
      outputFile_ = TFile::Open(outputFilename.c_str(), "RECREATE");
    }
    ~JetAnalyzer() {
      outputFile_->Close();
    }

    void analyze(const JetCollection& jetCollection);
  private:
    TFile* outputFile_;

    std::vector<double> jetPt_;
    std::vector<double> jetEta_;
    std::vector<double> jetPhi_;
    std::vector<double> jetEnergy_;
    std::vector<int> jetNConstituents_;
    std::vector<double> jetConstituentsPx_;
    std::vector<double> jetConstituentsPy_;
    std::vector<double> jetConstituentsPz_;
    std::vector<double> jetConstituentsPt_;
    std::vector<double> jetConstituentsE_;
    std::vector<double> jetConsituentsEta_;
    std::vector<double> jetConstituentsPhi_;
    std::vector<int> jetConstituentsPdgId_;

    void setBranches(TTree* tree);

    void clear() {
      jetPt_.clear();
      jetEta_.clear();
      jetPhi_.clear();
      jetEnergy_.clear();
      jetNConstituents_.clear();
      jetConstituentsPx_.clear();
      jetConstituentsPy_.clear();
      jetConstituentsPz_.clear();
      jetConstituentsPt_.clear();
      jetConstituentsE_.clear();
      jetConsituentsEta_.clear();
      jetConstituentsPhi_.clear();
      jetConstituentsPdgId_.clear();
    }
};
#endif