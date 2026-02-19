<img src="https://github.com/brusale/jetlib/blob/master/docs/jetlib.png" height="125">

Generate a sample of particles inside a jet. Jetlib generates events through the Pythia8 event generator and clusters particles with FastJet, producing a ROOT file containing information about jets and their constituents.

To run jetlib, clone the repo and follow these steps

```bash
cd jetlib
mkdir build && cd build
cmake ..
make -jN
./jetlib -f output.root --nEvents 5
```
Jetlib uses `fastjet-3.5.0` and `pythia8.306`
