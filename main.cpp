#include "myClass.h"
#include "PriceEntry.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){

   string name = "ABC";
   int hash = 0;
   hashCalc hc;
   Aktie neu;
   HashTable myTable;

   cin >> name;
   hash = hc.intToHash(name);
   cout << hash;
   bool running = true;

   while(running) {
      cout << "---AKTIENVERWALTUNG---" << endl;
      cout << "Gib folgendes ein, um eine Aktion auszuführen:" << endl;
      cout << "'a' - Aktie hinzufügen" << endl;
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

         case 'i':
            // Import
            break;

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
