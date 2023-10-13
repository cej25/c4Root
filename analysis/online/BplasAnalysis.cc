#include "BplasAnalysis.hh"
#include "BplasAnalysisStructs.hh"

#include "ext_h101.h"

#include <TDirectory.h>
#include <TH1.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

static constexpr size_t UCESB_CRATES = (sizeof(EXT_STR_h101_onion_t::plastic_crate) / sizeof(EXT_STR_h101_onion_t::plastic_crate[0]));
static constexpr size_t UCESB_CARDS = (sizeof(EXT_STR_h101_onion_t::plastic_crate[0].card) / sizeof(EXT_STR_h101_onion_t::plastic_crate[0].card[0]));

static_assert(UCESB_CRATES == 1, "Unpacker Only Tested on one Crate");

static constexpr size_t MAX_CARDS = UCESB_CARDS;
// Ch0 (Trigger) + 32 time channels
static constexpr size_t TDC_CHANNELS = 33;

std::ostream dout{nullptr};
//std::ostream dout{std::cout.rdbuf()};

struct fineTimeCalib
{
  int min;
  int max;
  double lookup[600];
};

fineTimeCalib calibrations[MAX_CARDS][TDC_CHANNELS];

double getFine(int card, int channel, int fine, double scale = 5000.)
{
  if (fine < calibrations[card][channel].min)
    return 0;
  if (fine > calibrations[card][channel].max)
    return scale;
  return (calibrations[card][channel].lookup[fine]) * scale;
}

BplasAnalysis::BplasAnalysis() : UseHistos(false)
{
  for (size_t card = 0; card < MAX_CARDS; card++)
  {
    for (size_t i = 0; i < TDC_CHANNELS; i++)
    {
      calibrations[card][i].min = 0;
      calibrations[card][i].max = 0;
      std::fill(std::begin(calibrations[card][i].lookup),
	  std::end(calibrations[card][i].lookup), 0);
    }
  }
}

void BplasAnalysis::LoadCalibrationFiles()
{
  for (size_t card = 0; card < MAX_CARDS; card++)
  {
    std::cout << "Reading calibration parameters for bPlas card " << card << "..." << std::endl;
    for (size_t i = 0; i < TDC_CHANNELS; i++)
    {
      std::stringstream fpath;
      fpath << "./bPlasCalib/Calib_" << card << "_" << i << ".dat";
      std::ifstream calib;
      calib.open(fpath.str());
      if (calib.fail()) continue;
      calib.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      calib.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      int min = 1024, max = 0;
      while (calib)
      {
	int bin;
	double value;
	calib >> bin >> value;
	if (bin < min) min = bin;
	if (bin > max) max = bin;
	if (value > 1) {
	  throw std::runtime_error("Calibration value seems invalid");
	}
	calibrations[card][i].lookup[bin - 1] = value;
      }
      calibrations[card][i].min = min;
      calibrations[card][i].max = max;
      if (min > max) {
	std::stringstream errbuf;
	errbuf << "Calibration made no sense";
	errbuf << " min=" << min;
	errbuf << " max=" << max;
	throw std::runtime_error(errbuf.str());
      }
    }
  }
}

void BplasAnalysis::ProcessCard(decltype(&EXT_STR_h101_onion_t::plastic_crate[0].card[0]) card, size_t cardidx)
{
  // This test should be redundant because it shouldn't be possible
  // But it's a basic sanity test that ucesb spec file wasn't broken
  if (card->time_coarse != card->time_fine
      || card->time_fine != card->time_edge
      || card->time_edge != card->time_channel
      || card->time_channel != card->time_epoch)
  {
    throw std::runtime_error("bPlas time entries misasligned");
  }

  std::array<double, TDC_CHANNELS> leads = {0};
  std::array<int32_t, TDC_CHANNELS> epoch = {0};
  int32_t epoch_base = 0;
  int32_t last_epoch = 0;

  for (uint32_t i = 0; i < card->time_coarse; ++i)
  {
    if (card->time_epochv[i] != 0)
    {
      last_epoch = card->time_epochv[i];
    }
    else
    {
      if (card->time_finev[i] == 0x3ff) continue;
      int channel = card->time_channelv[i];
      if (channel >= TDC_CHANNELS) continue;

      if (last_epoch != 0)
      {
	if (epoch_base == 0 && channel == 0) {
	  epoch_base = last_epoch;
	}
	else if (epoch_base == 0) {
	  throw std::runtime_error("Unexpected TDC epoch before trigger");
	}
	epoch[channel] = last_epoch - epoch_base;
	dout << "epoch[" << cardidx << "][" << channel << "] = " << (last_epoch - epoch_base) << std::endl;
	last_epoch = 0;
      }

      double time = (epoch[channel] * 1024e4) + card->time_coarsev[i] * 5000
	- getFine(cardidx, channel, card->time_finev[i]);

      // 1 = Leading edge
      if (card->time_edgev[i] == 1) {
	dout << "TDC Card=" << cardidx << ", Ch=" << channel << ", Lead, Time=" << time << std::endl;
	leads[channel] = time;
      }
      // 0 = Trailing edge
      else {
	if (leads[channel]) {
	  double tot = time - leads[channel];
	  dout << "TDC Card=" << cardidx << ", Ch=" << channel << ", Trail, Time=" << time << ", ToT=" << tot << std::endl;
	  if (UseHistos)
	    hToTs[(cardidx * TDC_CHANNELS) + channel]->Fill(tot);
	}
	else {
	  dout << "TDC Card=" << cardidx << ", Ch=" << channel << ", Trail, Time=" << time << std::endl;
	}
	leads[channel] = 0;
      }
    }
  }
}

void BplasAnalysis::Process(struct EXT_STR_h101_onion_t* event)
{
  // Process event to std::vector<BplasAdicItem> and/or fill histos
  for (size_t c = 0; c < MAX_CARDS; c++)
  {
    ProcessCard(&event->plastic_crate[0].card[c], c);
  }
}

void BplasAnalysis::UnpackFillHistos()
{
}

void BplasAnalysis::CreateHistograms()
{
  const char* orig_cd = gDirectory->GetPath();
  TDirectory* bplas_tot_folder = new TDirectory("BplasTot", "Bplas Tots");
  bplas_tot_folder->cd();
  hToTs.clear();
  hToTs.resize(MAX_CARDS * TDC_CHANNELS);
  for (size_t c = 0; c < MAX_CARDS; ++c)
  {
    for (size_t i = 0; i < TDC_CHANNELS; ++i)
    {
      size_t idx = (c * TDC_CHANNELS) + i;
      std::stringstream hname, htitle;

      hname << "hToT_" << c << "_" << i;
      htitle << "ToT Card " << c << ", Channel " << i;

      hToTs[idx] = new TH1F(hname.str().c_str(), htitle.str().c_str(),
	  50000, 0, 30000000);
    }
  }
  UseHistos = true;
  gDirectory->Cd(orig_cd);
}
