#include <vector>
#include <TSystem.h>
#include <TString.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>


std::vector<int> GetSubrunsWrapper(int runNumber)
{
    std::vector<int> subruns;

    TString inputpath = "/home/lisa/data/server/experiments/staging/2026_IKP_LISA_test/lmd/";

    void* dir = gSystem->OpenDirectory(inputpath);
    const char* f;

    TString prefix = Form("run_%04d_", runNumber);

    while ((f = gSystem->GetDirEntry(dir)))
    {
        TString name = f;

        if (!name.BeginsWith(prefix)) continue;
        if (!name.EndsWith(".lmd")) continue;

        TString sub = name;
        sub.ReplaceAll(prefix, "");
        sub.ReplaceAll(".lmd", "");

        subruns.push_back(sub.Atoi());
    }

    gSystem->FreeDirectory(dir);

    std::sort(subruns.begin(), subruns.end());
    
    std::cout << "Found " << subruns.size() << " subruns:\n";
    for (int subrunNumber : subruns)
    {
        std::cout << "  " << subrunNumber << '\n';
    }

    

    return subruns;
}


void trees_wrapper(int runNumber, const char *configFilename =
        "lisa_config_0-180deg_v0.C")
{

    TString config_path = "/home/lisa/programs/c4/julia_c4Root/config/lisaext/general/";
    TString newConfig = config_path + configFilename;

    FILE *in = fopen("/home/lisa/programs/c4/julia_c4Root/macros/lisa/versoek_make_trees_dev.C", "r");
    FILE *out = fopen("/home/lisa/programs/c4/julia_c4Root/macros/lisa/versoek_make_trees_dev_tmp.C", "w");
    
    if (!in || !out) {
    std::cerr << "Could not open macro files." << std::endl;
    return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), in)) {

        if (strstr(line, "#define LISA_CONFIG_FILE")) {
            fprintf(out,
                "#define LISA_CONFIG_FILE \"%s\"\n",
                newConfig.Data());
        } else {
            fputs(line, out);
        }
    }

    fclose(in);
    fclose(out);


    std::vector<int> subruns = GetSubrunsWrapper(runNumber);

    for (int subrunNumber : subruns)
    {
        std::cout << "\n=================================\n";
        std::cout << "Running subrun " << subrunNumber << std::endl;
        std::cout << "=================================\n";

        // IMPORTANT: new ROOT process per run
       TString cmd = Form(
    "root -l -q -e '.L versoek_make_trees_dev_tmp.C' -e 'versoek_make_trees_dev(%d,%d)'",
    runNumber, subrunNumber);

        gSystem->Exec(cmd);
    }
     remove("versoek_make_trees_dev_tmp.C");
}
