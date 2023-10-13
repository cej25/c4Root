#ifndef BplasAnalysis_hh
#define BplasAnalysis_hh

#include "BplasAnalysisStructs.hh"
#include "ext_h101.h"

#include <TH1.h>
#include <vector>

struct EXT_STR_h101_onion_t;

class BplasAnalysis
{
public:
  BplasAnalysis();
  void CreateHistograms();
  void LoadCalibrationFiles();
  void Process(struct EXT_STR_h101_onion_t* event);

private:
  void ProcessCard(decltype(&EXT_STR_h101_onion_t::plastic_crate[0].card[0]), size_t);
  void UnpackFillHistos();
  bool UseHistos;

  std::vector<TH1F*> hToTs;
};

#endif /* BplasAnalysis_hh */
