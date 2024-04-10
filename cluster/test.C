#include <iostream>
#include <vector>
#include <TFile.h>
#include <TKey.h>
#include <TList.h>
#include <TObject.h>
#include <TFolder.h>

struct DeepFolder
{
    std::vector<TFolder*> TFolderPtrVector;
    std::vector<int> TFolderDepthVector;
}

// Function to recursively list TFolder objects and their sub-folders in a file
void ListTFoldersRecursively(TFolder* folder, TFolderPtrVector& folders, int depth) {
    // Add the current folder to the vector
    folders.push_back(folder);

    // Loop over all sub-folders
    TIter next(folder->GetListOfFolders());
    TObject *obj;
    while ((obj = next())) {
        if (obj->InheritsFrom("TFolder")) {
            // Recursively call this function for sub-folder with increased depth
            ListTFoldersRecursively((TFolder*)obj, folders, depth + 1);
        }
    }
}

// Function to list TFolder objects and their sub-folders in a file
void ListTFoldersInFile(const char* filename, DeepFolder folders, int depth = 0) {
    // Open the ROOT file
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    // Get the list of keys (i.e., objects) in the file
    TList *keys = file->GetListOfKeys();

    if (!keys) {
        std::cerr << "Error: No keys found in file " << filename << std::endl;
        file->Close();
        return;
    }

    // Loop over all keys
    TIter next(keys);
    TKey *key;
    while ((key = (TKey*)next())) {
        const char* keyName = key->GetName();
        // Check if the key name indicates that it's an EventHeader
        if (std::string(keyName).find("cbmout") != std::string::npos) {
            // Skip this key
            continue;
        }
        TObject *obj = key->ReadObj();
        if (obj && obj->InheritsFrom("TFolder")) {
            TFolder *folder = (TFolder*)obj;
            // Check if the folder's name starts with "cbmout_" or "cbmout_0"
            if (std::string(folder->GetName()).find("cbmout") == std::string::npos) {
                // Recursively list all sub-folders
                ListTFoldersRecursively(folder, folders, depth);
            }
        }
    } // CALUM WHEN WAKE UP DEEPFOLDER

    // Close the file
    file->Close();
}

// Function to find TFolder objects matched in all files
void FindMatchedTFolders(const std::vector<std::string>& filenames) {
    // Vector of vectors to store matched TFolder objects for each file
    std::vector<DeepFolder> matchedFoldersList(filenames.size());

    // Populate matchedFoldersList for each file
    for (size_t i = 0; i < filenames.size(); ++i) {
        ListTFoldersInFile(filenames[i].c_str(), matchedFoldersList[i].TFolderPtrVector);
    }

    // Check for TFolder objects matched in all files
    std::cout << "TFolder objects matched in all files:" << std::endl;
    if (matchedFoldersList.size() > 0) {
        // Iterate through the TFolder objects in the first vector
        for (auto folder : matchedFoldersList[0]) {
            // Check if the folder exists in all other vectors
            bool foundInAllFiles = true;
            for (size_t i = 1; i < matchedFoldersList.size(); ++i) {
                auto it = std::find_if(matchedFoldersList[i].begin(), matchedFoldersList[i].end(),
                                        [&](TFolder* f) { return std::string(f->GetName()) == std::string(folder->GetName()); });
                if (it == matchedFoldersList[i].end()) {
                    foundInAllFiles = false;
                    break;
                }
            }
            // If the folder is found in all files, print its name and depth level
            if (foundInAllFiles) {
                std::cout << "TFolder: " << folder->GetName() << " (Depth Level: " << depth << ")" << std::endl;
            }
        }
    }
}

// Test function
void test() {
    std::vector<std::string> filenames = {"output1.root", "output2.root"}; // Add more filenames as needed
    FindMatchedTFolders(filenames);
}