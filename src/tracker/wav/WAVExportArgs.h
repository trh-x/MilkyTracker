#pragma once

#include <ModuleServices.h>
#include <TrackerSettingsDatabase.h>
#include <vector>
#include <cstring>

class WAVExportArgs {
public:
    class Arguments : public ModuleServices::WAVWriterParameters {
    public:
        Arguments();
        ~Arguments();

        // Copy constructor
        Arguments(const Arguments& other);
        // Copy assignment
        Arguments& operator=(const Arguments& other);

        // Only declare fields we add beyond WAVWriterParameters
        const char* inputFile;
        const char* outputFile;
        bool verbose;  // Flag for verbose output
        pp_uint32 channelCount;  // Number of channels in the module

    private:
        // Helper to handle deep copying of strings
        void copyStrings(const Arguments& other);
    };

    static Arguments parseFromCommandLine(int argc, char* argv[], TrackerSettingsDatabase& settingsDB);
    static void printUsage(const char* programName);
}; 