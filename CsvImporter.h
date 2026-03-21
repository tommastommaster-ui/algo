#ifndef CSV_IMPORTER_H
#define CSV_IMPORTER_H

#include <string>
#include <vector>
#include "myClass.h"

using namespace std;

struct ImportResult {
    bool success;
    int imported;
    int skipped;
    string errorMessage;
};

class CsvImporter {
public:
    ImportResult importFromCsv(const string& filePath, Aktie& aktie) const;

private:
    static string trim(const string& s);
    static vector<string> splitCsvLine(const string& line, char delimiter);
    static string normalizeHeader(string h);
    static bool parseNumber(const string& raw, double& value);
    static bool parseVolume(const string& raw, long long& value);
};

#endif
