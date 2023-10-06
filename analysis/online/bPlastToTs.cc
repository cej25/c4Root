// ROOT
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include <TH1F.h>

// C based ucesb client - the CPP one is too incomplete
extern "C" {
#include "ext_data_client.h"
#include "ext_h101.h"
}

#include "BplasAnalysis.hh"

//#define DEBUG(x) x
//#define UCESB_EXTRA_ARGS "--max-events=10"
#define DEBUG(x)
#define UCESB_EXTRA_ARGS ""

void plasticToT() {

  BplasAnalysis bplas;

  bplas.LoadCalibrationFiles();
  bplas.CreateHistograms();

  struct ext_data_client* client;
  EXT_STR_h101_onion event;
  EXT_STR_h101_layout event_layout = EXT_STR_h101_LAYOUT_INIT;
  std::cout << "Spawning ucesb to unpack the file" << std::endl;
  FILE* fid;


  char const* ucesb_dir = getenv("UCESB_DIR");
  if (ucesb_dir == nullptr) {
    std::cerr << "UCESB_DIR unset, trying a hardcoded default for now" << std::endl;
    ucesb_dir = "/u/jbormans/ucesb/s452";
  }

  {
    char command[256];
    snprintf(command, sizeof(command), "%s/s452  /data.local/scanner_fn001.lmd %s --ntuple=UNPACK,RAW,STRUCT,-", ucesb_dir, UCESB_EXTRA_ARGS);

    fid = popen(command, "r");
    if (fid == NULL) {
      perror("popen");
      std::cerr << "Failed to fork unpacker" << std::endl;
      exit(1);
    }

    int fd = fileno(fid);
    client = ext_data_from_fd(fd);

    if (client == NULL) {
      perror("ext_data_connect");
      std::cerr << "Failed to connect to the unpacker" << std::endl;
    }

    std::cout << "Connected to unpacker s505" << std::endl;
  }

  if (ext_data_setup(client, &event_layout, sizeof(event_layout), NULL,
        NULL, sizeof(event), "", NULL) != 0)
  {
    perror("ext_data_setup");
    std::cerr << "Failed to setup with the unpacker: " << ext_data_last_error(client) << std::endl;
    goto disconnect;
  }

  std::cout << "ucesb bPlas Crates is: " << (sizeof(event.bplas_crate) / sizeof(event.bplas_crate[0])) << std::endl;

  // Event Loop!
  for (;;)
  {
    int fetch_rv = ext_data_fetch_event(client, &event, sizeof(event), 0 );

    if (fetch_rv == 0)
    {
      std::cout << "End from server" << std::endl;
      break;
    }

    if (fetch_rv == -1)
    {
      perror("ext_data_fetch_event");
      std::cerr << "Failed to fetch event: " << ext_data_last_error(client) << std::endl;
      break;
    }

    bplas.Process(&event);
  }

disconnect:
  {
    int rv_close = ext_data_close(client);
    if (rv_close != 0)
    {
      perror("ext_data_close");
      std::cerr << "Something went wrong when disconnecting" << std::endl;
      exit(1);
    }

    if (fid)
    {
      if (pclose(fid) == -1)
      {
        perror("pclose");
        std::cerr << "Something went wrong when closing the process" << std::endl;
        exit(1);
      }
    }

    std::cout << "Disconnected from server" << std::endl;

  }
  return;
}

