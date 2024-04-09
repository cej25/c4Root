#include <TFile.h>
#include <TFolder.h>
#include <TDirectory.h>

#include <TFile.h>
#include <TFolder.h>
#include <TDirectory.h>
// #include <TIter.h>

void CopyFolderToDirectory(TFolder* sourceFolder, TDirectory* destinationDirectory) {
    // Create the TFolder in the destination directory
    if (sourceFolder == nullptr)
    {
        std::cout << "nullptr jackass" << std::endl;
    }

    TFolder* destFolder = new TFolder(sourceFolder->GetName(), sourceFolder->GetTitle());
    destinationDirectory->Add(destFolder);

    // Iterate over the collection of objects in the sourceFolder
    TIter next(sourceFolder->GetListOfFolders());
    TObject* obj;
    while ((obj = next())) {
        if (obj->InheritsFrom(TDirectory::Class())) {
            // If it's a directory, recursively copy it
            TDirectory* subdir = dynamic_cast<TDirectory*>(obj);
            TDirectory* newSubDir = destinationDirectory->mkdir(subdir->GetName());
            CopyFolderToDirectory(dynamic_cast<TFolder*>(subdir), newSubDir);
        } else {
            // Otherwise, add object to the destination folder
            destFolder->Add(obj->Clone());
        }
    }
}


int hadd() {
    // Open the source ROOT file
    TFile sourceFile("output.root");
    sourceFile.ls();

    // Get the TFolder from the source file
    TFolder* sourceFolder = (TFolder*)(sourceFile.Get("Histograms"));

    // Open or create the destination ROOT file
    TFile destFile("output_test.root", "RECREATE");

    // Create a directory in the destination file
    TDirectory* destDir = destFile.mkdir("Histograms");

    // Copy the TFolder to the destination directory
    CopyFolderToDirectory(sourceFolder, destDir);

    // Write changes to the destination file and close
    destFile.Write();
    destFile.Close();

    // Close the source file
    sourceFile.Close();

    return 0;
}