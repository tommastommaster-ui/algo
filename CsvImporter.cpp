#include "CsvImporter.h"

#include <fstream>

using namespace std;

string CsvImporter::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }

    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

vector<string> CsvImporter::splitCsvLine(const string& line, char delimiter) {
    vector<string> fields;
    string current;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == delimiter && !inQuotes) {
            fields.push_back(trim(current));
            current.clear();
        } else {
            current.push_back(c);
        }
    }

    fields.push_back(trim(current));
    return fields;
}

string CsvImporter::normalizeHeader(string h) {
    h = trim(h);

    if (!h.empty() && h.front() == '"' && h.back() == '"') {
        h = h.substr(1, h.size() - 2);
    }

    string out;
    for (char c : h) {
        if (c >= 'A' && c <= 'Z') {
            out.push_back(static_cast<char>(c - 'A' + 'a'));
        } else if (c != ' ' && c != '\t') {
            out.push_back(c);
        }
    }

    return out;
}

bool CsvImporter::parseNumber(const string& raw, double& value) {
    string s;
    for (char c : raw) {
        if (c != '"' && c != '$' && c != ',') {
            s.push_back(c);
        }
    }

    s = trim(s);
    if (s.empty()) {
        return false;
    }

    try {
        value = stod(s);
        return true;
    } catch (...) {
        return false;
    }
}

bool CsvImporter::parseVolume(const string& raw, long long& value) {
    string s;
    for (char c : raw) {
        if (c >= '0' && c <= '9') {
            s.push_back(c);
        }
    }

    if (s.empty()) {
        return false;
    }

    try {
        value = stoll(s);
        return true;
    } catch (...) {
        return false;
    }
}

ImportResult CsvImporter::importFromCsv(const string& filePath, Aktie& aktie) const {
    ifstream csv(filePath);
    if (!csv.is_open()) {
        return {false, 0, 0, "Datei konnte nicht geoeffnet werden."};
    }

    string headerLine;
    if (!getline(csv, headerLine)) {
        return {false, 0, 0, "CSV-Datei ist leer."};
    }

    char delimiter = headerLine.find(';') != string::npos ? ';' : ',';
    vector<string> headers = splitCsvLine(headerLine, delimiter);

    int idxDate = -1;
    int idxClose = -1;
    int idxVolume = -1;
    int idxOpen = -1;
    int idxHigh = -1;
    int idxLow = -1;

    for (int i = 0; i < static_cast<int>(headers.size()); i++) {
        string h = normalizeHeader(headers[i]);

        if (h == "date") {
            idxDate = i;
        } else if (h == "close/last" || h == "closelast" || h == "close") {
            idxClose = i;
        } else if (h == "volume") {
            idxVolume = i;
        } else if (h == "open") {
            idxOpen = i;
        } else if (h == "high") {
            idxHigh = i;
        } else if (h == "low") {
            idxLow = i;
        }
    }

    if (idxDate < 0 || idxClose < 0 || idxVolume < 0 || idxOpen < 0 || idxHigh < 0 || idxLow < 0) {
        return {false, 0, 0, "Benoetigte Spalten fehlen. Erwartet: date, close/last, volume, open, high, low."};
    }

    int imported = 0;
    int skipped = 0;
    string line;

    while (getline(csv, line)) {
        if (trim(line).empty()) {
            continue;
        }

        vector<string> cols = splitCsvLine(line, delimiter);
        int maxIdx = idxDate;
        if (idxClose > maxIdx) {
            maxIdx = idxClose;
        }
        if (idxVolume > maxIdx) {
            maxIdx = idxVolume;
        }
        if (idxOpen > maxIdx) {
            maxIdx = idxOpen;
        }
        if (idxHigh > maxIdx) {
            maxIdx = idxHigh;
        }
        if (idxLow > maxIdx) {
            maxIdx = idxLow;
        }

        if (static_cast<int>(cols.size()) <= maxIdx) {
            skipped++;
            continue;
        }

        PriceEntry entry;
        entry.date = trim(cols[idxDate]);
        if (!entry.date.empty() && entry.date.front() == '"' && entry.date.back() == '"') {
            entry.date = entry.date.substr(1, entry.date.size() - 2);
        }

        bool okClose = parseNumber(cols[idxClose], entry.close);
        bool okOpen = parseNumber(cols[idxOpen], entry.open);
        bool okHigh = parseNumber(cols[idxHigh], entry.high);
        bool okLow = parseNumber(cols[idxLow], entry.low);
        bool okVolume = parseVolume(cols[idxVolume], entry.volume);

        if (!okClose || !okOpen || !okHigh || !okLow || !okVolume) {
            skipped++;
            continue;
        }

        aktie.prices.push_back(entry);
        imported++;
    }

    return {true, imported, skipped, ""};
}
