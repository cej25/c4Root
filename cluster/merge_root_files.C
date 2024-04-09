#include <TFile.h>
#include <TH1.h>
#include <TFolder.h>
#include <iostream>

void MergeFolder(TFolder* folder1, TFolder* folder2, TFolder* mergedFolder, const std::string& folderName) {
    if (!folder1) return;

    std::cout << "Merging folder: " << folderName << std::endl;

    // Loop over all objects in folder1
    TIter next(folder1->GetListOfFolders());
    TObject* obj;
    while ((obj = next())) {
        TString name = obj->GetName();

        // If the object is a subfolder, recursively merge its contents
        if (obj->InheritsFrom(TFolder::Class())) {
            TFolder* subfolder1 = dynamic_cast<TFolder*>(obj);
            TFolder* subfolder2 = dynamic_cast<TFolder*>(folder2->FindObjectAny(name));
            TFolder* mergedSubfolder = dynamic_cast<TFolder*>(mergedFolder->FindObjectAny(name));
            if (!mergedSubfolder)
                mergedSubfolder = mergedFolder->AddFolder(name, name);

            MergeFolder(subfolder1, subfolder2, mergedSubfolder, folderName + "/" + name.Data());
        }
        // If the object is a histogram, merge it
        else if (obj->InheritsFrom(TH1::Class())) {
            TH1* hist1 = dynamic_cast<TH1*>(obj);
            TH1* hist2 = dynamic_cast<TH1*>(folder2->FindObjectAny(name));
            if (hist1 && hist2) {
                hist1->Add(hist2);
                mergedFolder->Add(hist1);
            }
        }
    }
}

void hadd() {
    TFile* file1 = new TFile("output1.root");
    TFile* file2 = new TFile("output2.root");
    TFile* mergedFile = new TFile("merged_file.root", "RECREATE");

    // Explicitly defined folder names
    std::vector<std::string> folderNames = {"FATIMA", "Fatima VME", "DEGAS", "White Rabbit", "TimeMachines", "AIDA", "bPlast", "FRS", "Correlations"};

    // Loop over the defined folder names and merge corresponding folders
    for (const auto& folderName : folderNames) {
        TFolder* folder1 = dynamic_cast<TFolder*>(file1->Get(folderName.c_str()));
        TFolder* folder2 = dynamic_cast<TFolder*>(file2->Get(folderName.c_str()));

        // If both folders exist, merge them
        if (folder1 && folder2) {
            TFolder* mergedFolder = new TFolder(folderName.c_str(), folderName.c_str());
            MergeFolder(folder1, folder2, mergedFolder, folderName);
            mergedFolder->Write();
            delete mergedFolder;
        } else {
            std::cout << "Folder '" << folderName << "' was not found in one or more files." << std::endl;
        }
    }

    // Close the files
    file1->Close();
    file2->Close();
    mergedFile->Close();
}
