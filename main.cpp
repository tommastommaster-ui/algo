#include "myClass.h"
#include "PriceEntry.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

static string trim(const string& s) {
   size_t start = s.find_first_not_of(" \t\r\n");
   if (start == string::npos) {
      return "";
   }
   size_t end = s.find_last_not_of(" \t\r\n");
   return s.substr(start, end - start + 1);
}

static vector<string> splitCsvLine(const string& line, char delimiter) {
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

static string normalizeHeader(string h) {
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

static bool parseNumber(const string& raw, double& value) {
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

static bool parseVolume(const string& raw, long long& value) {
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

int main(){

   string name = "ABC";
   int hash = 0;
   hashCalc hc;
   Aktie neu;
   HashTable myTable;

   //cin >> name;
   hash = hc.intToHash(name, "", "");
   //cout << hash;
   bool running = true;

   while(running) {
      cout << "---AKTIENVERWALTUNG---" << endl;
      cout << "Gib folgendes ein, um eine Aktion auszuführen:" << endl;
      cout << "'a' - Aktie hinzufügen" << endl;
      cout << "'d' - Aktie löschen" << endl;
      cout << "'i' - Kurswerte importieren" << endl;
      cout << "'s' - Aktie suchen" << endl;
      cout << "'p' - Ausgabe der Schlusskurse als ASCII Grafik" << endl;
      cout << "'h' - Hashtabelle in Datei speichern" << endl;
      cout << "'l' - Hashtabelle aus Datei laden" << endl;
      cout << "'q' - Programm beenden" << endl;

      char choice;
      cin >> choice;
      
      switch (choice) {
         case 'a':
            cout << "Name: ";
            cin >> neu.name;
            cout << "Kuerzel: ";
            cin >> neu.kuerzel;
            cout << "WKN: ";
            cin >> neu.WKN;
            myTable.addAktie(neu);
            cout << "Aktie wurde hinzugefügt!" << endl;

            break;

         case 'd':
            {
               string suche;
               cout << "Name oder Kürzel der zu löschenden Aktie eingeben: ";
               cin >> suche;

               Aktie* gefunden = myTable.search(suche);
               if (gefunden) {
                  delete myTable.search(suche);
                  cout << "Aktie wurde gelöscht" << endl;// Aktie löschen
               } else {
                  cout << "Keine Aktie mit diesem Namen oder Kürzel gefunden!" << endl;
               }
               break;
               
               

            }
            break;

         case 'i':
         {
            string suche;
            cout << "Name oder Kürzel der Aktie für den Import eingeben: ";
            cin >> suche;

            Aktie* aktie = myTable.search(suche);
            if (!aktie) {
               cout << "Aktie nicht gefunden. Bitte zuerst hinzufügen." << endl;
               break;
            }

            string dateiPfad;
            cout << "CSV-Dateipfad eingeben: ";
            cin >> dateiPfad;

            ifstream csv(dateiPfad);
            if (!csv.is_open()) {
               cout << "Datei konnte nicht geöffnet werden." << endl;
               break;
            }

            string headerLine;
            if (!getline(csv, headerLine)) {
               cout << "CSV-Datei ist leer." << endl;
               break;
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

               if (h == "date") idxDate = i;
               else if (h == "close/last" || h == "closelast" || h == "close") idxClose = i;
               else if (h == "volume") idxVolume = i;
               else if (h == "open") idxOpen = i;
               else if (h == "high") idxHigh = i;
               else if (h == "low") idxLow = i;
            }

            if (idxDate < 0 || idxClose < 0 || idxVolume < 0 || idxOpen < 0 || idxHigh < 0 || idxLow < 0) {
               cout << "Benötigte Spalten fehlen. Erwartet: date, close/last, volume, open, high, low." << endl;
               break;
            }

            int importiert = 0;
            int uebersprungen = 0;
            string line;

            while (getline(csv, line)) {
               if (trim(line).empty()) {
                  continue;
               }

               vector<string> cols = splitCsvLine(line, delimiter);
               int maxIdx = idxDate;
               if (idxClose > maxIdx) maxIdx = idxClose;
               if (idxVolume > maxIdx) maxIdx = idxVolume;
               if (idxOpen > maxIdx) maxIdx = idxOpen;
               if (idxHigh > maxIdx) maxIdx = idxHigh;
               if (idxLow > maxIdx) maxIdx = idxLow;

               if (static_cast<int>(cols.size()) <= maxIdx) {
                  uebersprungen++;
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
                  uebersprungen++;
                  continue;
               }

               aktie->prices.push_back(entry);
               importiert++;
            }

            cout << importiert << " Datensätze importiert";
            if (uebersprungen > 0) {
               cout << ", " << uebersprungen << " Zeilen übersprungen";
            }
            cout << "." << endl;
            break;
         }

         case 's': {
            string suche;
            cout << "Name oder Kürzel der Aktie eingeben: ";
            cin >> suche;

            Aktie* gefunden = myTable.search(suche);
            if (gefunden) {
               cout << "Aktie gefunden: "
                     << gefunden->name << " "
                     << gefunden->kuerzel << " "
                     << gefunden->WKN << endl;
            } else {
               cout << "Keine Aktie mit diesem Namen oder Kürzel gefunden!" << endl;
            }
            break;
         }

         case 'p':
            // Print
            break;

         case 'h':
            // Save
            break;

         case 'l':
            // Load
            break;

         case 'q':
            running = false;
            break;

         default:
            cout << "Ungültige Eingabe, bitte versuche es erneut." << endl;
            break;
      }
   }

  
   return 0;
}
