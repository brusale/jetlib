#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "EventGenerator.h"
#include "JetAnalysis.h"
#include "JetAnalyzer.h"
#include "fastjet/PseudoJet.hh"

PYBIND11_MODULE(jetlibpy, m) {
    m.doc() = "Python bindings for jetlib";

    // Bind fastjet::PseudoJet
    pybind11::class_<fastjet::PseudoJet>(m, "PseudoJet")
        .def(pybind11::init<>())
        .def("pt", &fastjet::PseudoJet::pt)
        .def("eta", &fastjet::PseudoJet::eta)
        .def("phi", &fastjet::PseudoJet::phi)
        .def("rap", &fastjet::PseudoJet::rap)
        .def("m", &fastjet::PseudoJet::m)
        .def("e", &fastjet::PseudoJet::E)
        .def("px", &fastjet::PseudoJet::px)
        .def("py", &fastjet::PseudoJet::py)
        .def("pz", &fastjet::PseudoJet::pz)
        .def("constituents", &fastjet::PseudoJet::constituents);

    pybind11::class_<EventGenerator>(m, "EventGenerator")
        .def(pybind11::init<>())
        .def("initialize", &EventGenerator::initialize)
        .def("generateEvents", &EventGenerator::generateEvents)
        .def("getJetCollection", &EventGenerator::getJetCollection);

    pybind11::class_<JetAnalysis>(m, "JetAnalysis")
        .def(pybind11::init<>())
        .def("clusterJets", &JetAnalysis::clusterJets)
        .def("getJets", &JetAnalysis::getJets)
        .def("convertPythiaToPseudoJets", &JetAnalysis::convertPythiaToPseudoJets)
        .def("clear", &JetAnalysis::clear);

    pybind11::class_<JetAnalyzer>(m, "JetAnalyzer")
        .def(pybind11::init<std::string>(), pybind11::arg("outputFilename") = "jet_analysis.root")
        .def("analyze", &JetAnalyzer::analyze)
        .def("setFilter", &JetAnalyzer::setFilter);
}