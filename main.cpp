#include "myClass.h"
#include <iostream>
#include <string>
using namespace std;

int main(){

   string name = "";
   int hash = 0;
   hashCalc hc;
   Aktie neu;
   HashTable myTable;

   bool running = true;

   while(running) {
      cout << "\n---AKTIENVERWALTUNG---" << endl;
      cout << "Gib folgendes ein, um eine Aktion auszuführen:" << endl;
      cout << "'a' - Aktie hinzufügen" << endl;
      cout << "'d' - Aktie löschen" << endl;
      cout << "'s' - Aktie suchen" << endl;
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
                  myTable.remove(suche);
                  cout << "Aktie wurde gelöscht" << endl;
               } else {
                  cout << "Keine Aktie mit diesem Namen oder Kürzel gefunden!" << endl;
               }
               break;
               
            }
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
