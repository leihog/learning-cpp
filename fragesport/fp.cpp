/*
 * Fragesport.cpp (fp.cpp)
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "fragesport.h"

using namespace std;

int quiz(int q, Fraga *f);
int testInput(int svar, int max);

int main () {

	int poang = 0;
	Fraga *f = NULL;
	int fragaNr = 0;
	int antalF = 0;
	int raknat = false;
	string rad;
	char c[100]; //eftersom jag inte vet hur man läser in en hel rad till en string
	ifstream f1("fragor.txt");

	while (true) {
		f1.getline(c,100);
		rad = c; // lättare att hantera en string än en char.. 

		if (f1.eof()) {
			if (raknat)
				break;

			f1.clear(); //ta bort eof flaggan
			f1.seekg(ios::beg); //gå tillbaks till början av filen.
			raknat = true;
			f = new Fraga[antalF];
		}

		// ifall det råkat bli lite fel i filen
		if (rad[0] != '[')
			rad = rad.substr(rad.find("["), rad.size() - rad.find("["));
 
	     if (raknat) {

		if (rad.substr(0,4) == "[F]:") {
			// raden innehåller en fråga
			f[fragaNr].texten = rad.substr(4,rad.size() - 4);
			fragaNr++;
			//cout << rad.substr(4,rad.size() - 4) << endl;
		}
		else if (rad.substr(0,4) == "[S]:") {
			// raden innehåller rätt alternativ
			f[fragaNr-1].alt[f[fragaNr-1].altNr] = rad.substr(4,rad.size() - 4);
			f[fragaNr-1].rSvar = f[fragaNr-1].altNr;
			f[fragaNr-1].altNr++;
			//cout << rad.substr(4,rad.size() - 4) << endl;
		}
		else if (rad.substr(0,4) == "[A]:") {
			// raden innehåller ett alternativ
			f[fragaNr-1].alt[f[fragaNr-1].altNr] = rad.substr(4,rad.size() - 4);
			f[fragaNr-1].altNr++;
			//cout << rad.substr(4, rad.size() - 4) << endl;
		}

	    } //end raknat 
	    else {
		if (rad.substr(0,4) == "[F]:")
			antalF++;
	    }
	}

	cout << "\x1b[2J"; //rensa skärmen

	//introduktion

	cout << "Fr\xE5gesport Deluxe 1.0" << endl << endl;
	cout << "V\xE4lkommen till v\xE5rt musikfr\xE5geprogram!" << endl;
	cout << "H\xE4r kommer du f\xE5 n\xE5gra fr\xE5gor om olika artister, fr\xE5n olika genrer." << endl;
	cout << "Varje r\xE4tt svar ger 1 po\xE4ng, fel svar ger naturligtvis 0 po\xE4ng." << endl;
	cout << "Lycka till!!" << endl;

	for (int i=0;i<antalF;i++) {
		cout << "\n\nFr\xE5ga " << i+1 << endl;
		cout << "=========" << endl;
		if (quiz(i,f)) //plats i array och objektet skickas till quiz
		  poang++;
	}

	cout << "\nDu fick " << poang << " r\xE4tt av " << antalF << " m\xF6jliga." << endl;

	// ge omdömme
	cout << "Omd\xF6me: ";
	if (poang < 2)
		cout << "Du \xE4r ett inbitet metalhuvud, s\xE4tt p\xE5 Mtv och l\xE4r dig n\xE5tt nytt!" << endl;
	else if (poang > 2 && poang < 6)
		cout << "Du kollar f\xF6r mycket p\xE5 Mtv och f\xF6r lite p\xE5 Ztv. Sk\xE4rpning!" << endl;
	else if (poang > 5 && poang < 9)
		cout << "Du \xE4r klart godk\xE4nd i ditt musikvetande. Bra jobbat!" << endl;
	else
		cout << "Expert" << endl;

	// rensa up och avsluta
	delete [] f;
	return 0;

}

int quiz(int q, Fraga *f) {
	
	int ratt, svar = 0;

	cout << f[q].texten << endl;
        for (int k=0;k<f[q].altNr;k++) {
      	   if (k == f[q].rSvar)
             ratt = k+1;
           cout << setw(2) << k+1 << ") " << f[q].alt[k] << endl;
        }
	cout << "Svar: ";

	int foo = false;
	while (!(cin >> svar) || !testInput(svar, f[q].altNr)) {

		if (svar == 0) {
			cin.clear(); // rensa bort fel
			cin.ignore(1); // ignorera felet annars blir det en oändlig loop.
		}
		else
			foo = false;

		if (!foo) {
			cout << "Svaret m\xE5ste vara ett av alternativen ovan!\nProva igen: ";
			foo = true;
		}
	}

	if (svar == ratt) {
		cout << "\nDu svarade r\xE4tt!" << endl;
		return true;
	}
	cout << "\nDitt svar var tyv\xE4rr fel, r\xE4tt svar var: " << f[q].alt[ratt-1] << endl;
	return false;
}

int testInput(int svar, int max) {
	if (svar > 0 && svar <= max)
		return true;
	return false;
}
