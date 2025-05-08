/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                              N.J. Hubbard                                  *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "TAidaConfiguration.h"

#include "c4Logger.h"

#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <locale>
#include <limits>
#include <sstream>
#include <string>

TAidaConfiguration* TAidaConfiguration::instance = nullptr;
std::string TAidaConfiguration::base_path = "Configuration_Files/AIDA";

TAidaConfiguration::TAidaConfiguration() :
    fees(0), dssds(0), wide(false), adjustadc(false), useucesb(false),
    ignorembsts(false), stats(false), ucesbshift(0), eventwindow(2000),
    tm_undelayed(-1), tm_delayed(-1), sc41l_d(-1), sc41r_d(-1)
{
  ReadConfiguration();
  DSSDtoFEE();
}

inline DSSDSide ParseSide(std::string arg)
{
  std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
  if (arg == "junction") return DSSDSide::Junction;
  return DSSDSide::Ohmic;
}

void TAidaConfiguration::ReadConfiguration()
{
  fbwindow = std::numeric_limits<double>::max();
  fbenergyh = std::numeric_limits<double>::max();
  fbenergyl = std::numeric_limits<double>::max();

  std::ifstream cfg(base_path + "/AIDA.txt");

  if (!cfg.good())
  {
    c4LOG(fatal, "Unable to read AIDA configuration file");
    return;
  }
  constexpr auto ignore = std::numeric_limits<std::streamsize>::max();
  int sub_DSSD = -1;
  bool sub_Scaler = false;
  bool sub_Analysis = false;
  while (cfg)
  {
    if (cfg.peek() == '#')
    {
      cfg.ignore(ignore, '\n');
      continue;
    }

    std::string line_s;
    std::getline(cfg, line_s);
    std::istringstream line(line_s);

    bool sub = false;
    if (line.peek() == '-')
    {
      sub = true;
      line.get();
    }

    std::string option;
    std::getline(line, option, ':');
    line.get();

    std::transform(option.begin(), option.end(), option.begin(), ::tolower);
    option.erase(option.find_last_not_of(" \n\r\t") + 1);
    option.erase(0, option.find_first_not_of(" \n\r\t"));

    if (option == "fees")
    {
      line >> fees;
      fee.resize(fees);
      for (FEEConfiguration& f: fee)
      {
        f.DSSD = -1;
      }
    }
    else if (option == "dssds")
    {
      line >> dssds;
      dssd.resize(dssds);
      for (DSSDConfiguration& d : dssd)
      {
        d.DSSD = -1;
      }
    }
    else if (option == "wide")
    {
      line >> std::boolalpha >> wide;
    }
    else if (option == "ignorembsts")
    {
      line >> std::boolalpha >> ignorembsts;
    }
    else if (option == "ucesb")
    {
      line >> std::boolalpha >> useucesb;
    }
    else if (option == "stats")
    {
      line >> std::boolalpha >> stats;
    }
    else if (option == "ucesbshift")
    {
      line >> ucesbshift;
    }
    else if (option == "eventwindow")
    {
      line >> eventwindow;
    }
    else if (option == "frontbackwindow")
    {
      line >> fbwindow;
    }
    else if (option == "frontbackenergyh")
    {
      line >> fbenergyh;
    }
    else if (option == "frontbackenergyl")
    {
      line >> fbenergyl;
    }
    else if (option == "dssd")
    {
      line >> sub_DSSD;
      if (sub_DSSD > dssds) {
        c4LOG(fatal, "DSSD value " << sub_DSSD << " exceeds number of DSSDs: " << dssds);
        sub_DSSD = 0;
      }
      else {
        dssd[sub_DSSD - 1].DSSD = sub_DSSD;
        dssd[sub_DSSD - 1].Type = 1; // set to regular AIDA by default
      }
    }
    else if (option == "top" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Top;
    }
    else if (option == "bottom" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Bottom;
    }
    else if (option == "left" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Left;
    }
    else if (option == "right" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Right;
    }
    else if (option == "leftleft" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Left;
    }
    else if (option == "leftright" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].LeftRight;
    }
    else if (option == "centreleft" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].CentreLeft;
    }
    else if (option == "centreright" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].CentreRight;
    }
    else if (option == "rightleft" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].RightLeft;
    }
    else if (option == "rightright" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Right;
    }
    else if (option == "x" && sub && sub_DSSD > 0)
    {
      std::string arg;
      line >> arg;
      dssd[sub_DSSD - 1].XSide = ParseSide(arg);
    }
    else if (option == "y" && sub && sub_DSSD > 0)
    {
      std::string arg;
      line >> arg;
      dssd[sub_DSSD - 1].YSide = ParseSide(arg);
    }
    else if (option == "full" && sub && sub_DSSD > 0)
    {
      // 1 FEE covers full BB7 layer (32 x 2 channels)
      line >> dssd[sub_DSSD - 1].Full;
      dssd[sub_DSSD - 1].Type = 2; // change to BB7 type if encountered
    }

    else if (option == "scalers")
    {
      sub_Scaler = true;
      sub_Analysis = false;
    }
    else if (sub && sub_Scaler)
    {
      std::string arg;
      std::getline(line, arg);
      int idx = std::strtol(option.c_str(), NULL, 0);
      scalers[idx] = arg;
      if (arg == "TimeMachineU")
        tm_undelayed = idx;
      else if (arg == "TimeMachineD")
        tm_delayed = idx;
      else if (arg == "SCI41L_D")
        sc41l_d = idx;
      else if (arg == "SCI41R_D")
        sc41r_d = idx;
    }
    else if (option == "analysis")
    {
      sub_Analysis = true;
      sub_Scaler= false;
    }
    else if (option == "reducenoise" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> reducenoise;
    }
    else if (option == "clusterimplants" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> clusterimplants;
    }
    else if (option == "clusterdecays" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> clusterdecays;
    }
    else if (option == "calibrate" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> calibrate;
    }
    else if (option == "parallelcalibrate" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> parallelcalibrate;
    }
    else if (option == "hugethreshold" && sub && sub_Analysis)
    {
      line >> hugethreshold;
    }
    else if (option == "pulserthreshold" && sub && sub_Analysis)
    {
      line >> pulserthreshold;
    }
  }

  if (!cfg.eof() && (cfg.bad() || cfg.fail()))
  {
    c4LOG(error, "Error parsing AIDA configuration");
    return;
  }

  adcOffsets.resize(fees);
  dssdGains.resize(dssds);
  feeTimeOffsets.resize(fees);
  stripThresholds.resize(dssds);

  for (auto& c : adcOffsets)
  {
    std::fill(c.begin(), c.end(), 0);
  }
  for (auto& d : dssdGains)
  {
    d[0].resize(wide ? 386 : 128);
    d[1].resize(128);
    std::fill(d[0].begin(), d[0].end(), 0.7);
    std::fill(d[1].begin(), d[1].end(), 0.7);
  }
  std::fill(feeTimeOffsets.begin(), feeTimeOffsets.end(), 0);
  for (auto& d : stripThresholds)
  {
    d[0].resize(wide ? 386 : 128);
    d[1].resize(128);
    std::fill(d[0].begin(), d[0].end(), 0);
    std::fill(d[1].begin(), d[1].end(), 0);
  }

  bool warning = false;
  bool loaded = false;
  std::ifstream fs(base_path + "/AIDA_offsets.txt");
  loaded = fs.good();
  fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (fs)
  {
    if (fs.peek() == '#')
    {
      fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int fs_fee, fs_channel;
    double offset;
    fs >> fs_fee >> fs_channel >> offset;
    if (!fs) break;
    if (!warning && (fs_fee > fees || fs_channel > 64)) {
      c4LOG(warning, "Invalid FEE/Channel number in AIDA_offsets.txt");
      warning = true;
    }
    if (fs_fee <= fees && fs_channel <= 64) {
      adcOffsets[fs_fee-1][fs_channel-1] = offset;
    }
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  fs.close();
  if (loaded && !cfg.eof() && (cfg.bad() || cfg.fail()))
  {
    c4LOG(error, "Error reading AIDA_offsets.txt");
  }
  else if (loaded && cfg.eof())
  {
    c4LOG(info, "Loaded AIDA ADC offsets");
  }

  fs.open(base_path + "/AIDA_times.txt");
  loaded = fs.good();
  warning = false;

  while (fs)
  {
    if (fs.peek() == '#')
    {
      fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int fs_fee, fs_offset;
    fs >> fs_fee >> fs_offset;
    if (!fs) break;
    if (!warning && (fs_fee > fees)) {
      c4LOG(warning, "Invalid FEE in AIDA_times.txt");
    }
    feeTimeOffsets[fs_fee] = fs_offset;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  if (loaded && !cfg.eof() && (cfg.bad() || cfg.fail()))
  {
    c4LOG(error, "Error reading AIDA_times.txt");
  }
  else if (loaded && cfg.eof())
  {
    c4LOG(info, "Loaded AIDA FEE clock correction");
  }
  fs.close();

  fs.open(base_path + "/AIDA_gains.txt");
  loaded = fs.good();
  warning = false;

  fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (fs)
  {
    if (fs.peek() == '#')
    {
      fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int fs_dssd, strip;
    char side;
    double offset;
    fs >> fs_dssd >> side >> strip >> offset;
    if (!fs) break;
    int sideidx = 0;
    if (side == 'Y') sideidx = 1;
    dssdGains[fs_dssd][sideidx][strip] = offset;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  if (loaded && !cfg.eof() && (cfg.bad() || cfg.fail()))
  {
    c4LOG(error, "Error reading AIDA_gains.txt");
  }
  else if (loaded && cfg.eof())
  {
    c4LOG(info, "Loaded AIDA DSSD gains");
  }

  std::ifstream stripConfig(base_path + "/AIDA_strips.txt");
  loaded = stripConfig.good();
  warning = false;

  while (stripConfig)
  {
    if (stripConfig.peek() == '#' || stripConfig.peek() == '\n')
    {
      stripConfig.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int fs_dssd, strip;
    char side;
    double threshold;
    stripConfig >> fs_dssd >> side >> strip >> threshold;
    if (!stripConfig) {
        break;
    }
    int sideidx = (side == 'Y') ? 1 : 0;
    if (fs_dssd == -1)
    {
      for (int i = 0; i < dssds; i++)
      {
        if (strip == -1)
        {
          for (size_t j = 0; j < stripThresholds[i][sideidx].size(); j++)
          {
            stripThresholds[i][sideidx][j] = threshold;
          }
        }
        else
        {
          stripThresholds[i][sideidx][strip] = threshold;
        }
      }
    }
    else
    {
      if (strip == -1)
      {
        for (size_t j = 0; j < stripThresholds[fs_dssd - 1][sideidx].size(); j++)
        {
          stripThresholds[fs_dssd - 1][sideidx][j] = threshold;
        }
      }
      else
      {
        stripThresholds[fs_dssd - 1][sideidx][strip] = threshold;
      }
    }
    stripConfig.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  if (loaded && !cfg.eof() && (cfg.bad() || cfg.fail()))
  {
    c4LOG(error, "Error reading AIDA_strips.txt");
  }
  else if (loaded && cfg.eof())
  {
    c4LOG(info, "Loaded AIDA DSSD strip thresholds");
  }

  if (useucesb && ignorembsts)
  {
    c4LOG(warning, "Not ignoring MBS timestamps when ucesb is used");
    ignorembsts = false;
  }

  LOG(info) << "AIDA Configuration: " << fees << " FEEs, " << dssds << " DSSDs, "
    << scalers.size() << " Scalers";

  std::stringstream opt;
  if (ignorembsts) opt << "NoMBS ";
  else opt << "MBS ";
  if (wide) opt << "wide ";
  if (useucesb) opt << "ucesb ";
  if (stats) opt << "stats ";
  LOG(info) << "  Options: " << opt.str();
  if (useucesb && ucesbshift) LOG(info) << "  ucesb Timestamps are shifted by " << ucesbshift << " ns";

  LOG(info) << "  Windows: Event: " << eventwindow << " ns, Front/Back: " << fbwindow << " ns";
  LOG(info) << "  Gates: Front/Back High: " << fbenergyh << " MeV, Low: " << fbenergyl << " keV";

  std::stringstream anlopt;
  if (reducenoise) anlopt << "ReduceNoise ";
  if (clusterimplants && clusterdecays) anlopt << "ClusterImplantsDecays ";
  if (clusterimplants && !clusterdecays) anlopt << "ClusterImplants";
  if (!clusterimplants && clusterdecays) anlopt << "ClusterDecays ";
  if (calibrate && parallelcalibrate) anlopt << "ParallelCalibrate ";
  if (calibrate && !parallelcalibrate) anlopt << "Calibrate ";
  LOG(info) << "  Analysis Options: " << anlopt.str();
  LOG(info) << "  Analysis Thresholds: Nonsense: " << hugethreshold << ", Pulser: " << pulserthreshold;
}

void TAidaConfiguration::DSSDtoFEE()
{
  for (DSSDConfiguration& d : dssd)
  {
    if (d.DSSD == -1) {
      c4LOG(fatal, "At least one DSSD was not mapped to any FEEs in AIDA configuration");
      continue;
    }
    if (d.Top > FEEs()) {
      c4LOG(fatal, "DSSD top maps to invalid FEE: " << d.Top << " (Max fees: " << FEEs() << ")");
    }
    if (d.Right > FEEs()) {
      c4LOG(fatal, "DSSD right maps to invalid FEE: " << d.Right << " (Max fees: " << FEEs() << ")");
    }
    if (d.Bottom > FEEs()) {
      c4LOG(fatal, "DSSD bottom maps to invalid FEE: " << d.Bottom << " (Max fees: " << FEEs() << ")");
    }
    if (d.Left > FEEs()) {
      c4LOG(fatal, "DSSD left maps to invalid FEE: " << d.Left << " (Max fees: " << FEEs() << ")");
    }

    if (d.Type == 2)
    {
      fee[d.Full - 1].DSSD = d.DSSD;
      fee[d.Full - 1].Type = d.Type;
      continue;
    }


    fee[d.Top-1].DSSD = d.DSSD;
    fee[d.Top-1].High = true;
    fee[d.Top-1].Side = d.YSide;

    fee[d.Right-1].DSSD = d.DSSD;
    fee[d.Right-1].High = true;
    fee[d.Right-1].Side = d.XSide;

    fee[d.Bottom-1].DSSD = d.DSSD;
    fee[d.Bottom-1].High = false;
    fee[d.Bottom-1].Side = d.YSide;

    fee[d.Left-1].DSSD = d.DSSD;
    fee[d.Left-1].High = false;
    fee[d.Left-1].Side = d.XSide;

    if (!wide) continue;

    if (d.LeftRight > FEEs()) {
      c4LOG(fatal, "DSSD left-right maps to invalid FEE: " << d.LeftRight << " (Max fees: " << FEEs() << ")");
    }
    if (d.CentreLeft > FEEs()) {
      c4LOG(fatal, "DSSD centre-left maps to invalid FEE: " << d.CentreLeft << " (Max fees: " << FEEs() << ")");
    }
    if (d.CentreRight > FEEs()) {
      c4LOG(fatal, "DSSD centre-right maps to invalid FEE: " << d.CentreRight << " (Max fees: " << FEEs() << ")");
    }
    if (d.RightLeft > FEEs()) {
      c4LOG(fatal, "DSSD right-left maps to invalid FEE: " << d.RightLeft << " (Max fees: " << FEEs() << ")");
    }
    fee[d.Left-1].Segment = WideAIDASegment::Left;

    fee[d.LeftRight-1].DSSD = d.DSSD;
    fee[d.LeftRight-1].High = true;
    fee[d.LeftRight-1].Side = d.XSide;
    fee[d.LeftRight-1].Segment = WideAIDASegment::Left;

    fee[d.CentreLeft-1].DSSD = d.DSSD;
    fee[d.CentreLeft-1].High = false;
    fee[d.CentreLeft-1].Side = d.XSide;
    fee[d.CentreLeft-1].Segment = WideAIDASegment::Centre;

    fee[d.CentreRight-1].DSSD = d.DSSD;
    fee[d.CentreRight-1].High = true;
    fee[d.CentreRight-1].Side = d.XSide;
    fee[d.CentreRight-1].Segment = WideAIDASegment::Centre;

    fee[d.RightLeft-1].DSSD = d.DSSD;
    fee[d.RightLeft-1].High = false;
    fee[d.RightLeft-1].Side = d.XSide;
    fee[d.RightLeft-1].Segment = WideAIDASegment::Right;

    fee[d.Right-1].Segment = WideAIDASegment::Right;
  }
}
