#pragma once

#include <ModuleServices.h>
#include <TrackerSettingsDatabase.h>

class WAVExportParams {
public:
    class Parameters : public ModuleServices::WAVWriterParameters {
    public:
        Parameters();
        ~Parameters();
        bool verbose;  // Flag for verbose output
    };

    static Parameters parseFromCommandLine(int argc, char* argv[], TrackerSettingsDatabase& settingsDB);
    static void printUsage(const char* programName);

private:
    static int getIntOption(int argc, char* argv[], const char* option, int defaultValue);
    static bool hasOption(int argc, char* argv[], const char* option);
}; 