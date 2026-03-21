#include "myClass.h"
#include "PriceEntry.h"
#include "CsvImporter.h"
#include <iostream>
#include <string>
using namespace std;

int main(){

   string name = "ABC";
   int hash = 0;
   hashCalc hc;
   Aktie neu;
   HashTable myTable;
   CsvImporter importer;

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

            ImportResult result = importer.importFromCsv(dateiPfad, *aktie);
            if (!result.success) {
               cout << result.errorMessage << endl;
               break;
            }

            cout << result.imported << " Datensaetze importiert";
            if (result.skipped > 0) {
               cout << ", " << result.skipped << " Zeilen uebersprungen";
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

               if (!gefunden->prices.empty()) {
                  const PriceEntry& latest = gefunden->prices.back();
                  cout << "Aktuellster Kurs: Date: " << latest.date
                       << ", Close: " << latest.close
                       << ", Volume: " << latest.volume
                       << ", Open: " << latest.open
                       << ", High: " << latest.high
                       << ", Low: " << latest.low << endl;
               }
            } else {
               cout << "Keine Aktie mit diesem Namen oder Kürzel gefunden!" << endl;
            }
            break;
         }

         case 'p':
            // Print
            break;

         case 'h':
            {
               string dateiPfad;
               cout << "Dateipfad zum Speichern eingeben: ";
               cin >> dateiPfad;

               if (myTable.saveToFile(dateiPfad)) {
                  cout << "Hashtabelle wurde gespeichert." << endl;
               } else {
                  cout << "Speichern fehlgeschlagen." << endl;
               }
            }
            break;

         case 'l':
            {
               string dateiPfad;
               cout << "Dateipfad zum Laden eingeben: ";
               cin >> dateiPfad;

               if (myTable.loadFromFile(dateiPfad)) {
                  cout << "Hashtabelle wurde geladen." << endl;
               } else {
                  cout << "Laden fehlgeschlagen." << endl;
               }
            }
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
