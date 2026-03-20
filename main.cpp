#include "myClass.h"
#include "PriceEntry.h"
#include <iostream>
#include <string>
using namespace std;

enum State { EMPTY, OCCUPIED, DELETED };

int main(){

    std::string name = "ABC";
    long long hash = 0;
    hashCalc hc;
    hash = hc.intToHash(name);
    cout << hash << std::endl;

    bool running = true;

    while(true) {
        cout << "---AKTIENVERWALTUNG---" << endl;
        cout << "Gib folgendes ein, um eine Aktion auszuführen:" << endl;
        cout << "'a' - Aktie hinzufügen" << endl;
        cout << "'i' - Kurswerte importieren" << endl;
        cout << "'s' - Aktie suchen" << endl;
        cout << "'p' - Ausgabe der Schlusskurse als ASCII Grafik" << endl;
        cout << "'h' - Hashtabelle in Datei speichern" << endl;
        cout << "'l' - Hashtabelle aus Datei laden" << endl;
        cout << "'q' - Programm beenden" << endl;

        char choise;
        cin >> choise;
        
        if(choise == 'a') {
           // Add
        } else if (choise == 'i') {
           // Import
        } else if (choise == 's') {
           // Search
        } else if (choise == 'p') {
           // Print
        } else if (choise == 'h') {
           // Save
        } else if (choise == 'l') {
           // Load
        } else if (choise == 'q') {
            running = false;
        } else {
           cout << "Ungültige Eingabe, bitte versuche es erneut." << endl;
        }
    }

  
    return 0;
}
