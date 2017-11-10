#include <iostream>
#include <iomanip>
#include "neurone.hpp"
#include "network.hpp"
#include "constant.h"
#include <fstream>
#include <string>

using namespace std;

double AskForTime();

int main () {

	double temps_f(0.0);

	do {
		temps_f = AskForTime();
	} while (temps_f <= 0 );
	
	ofstream donnees ("data.txt", ios::out);
	
	unsigned int t (std::round(temps_f/DeltaTime));
	
	Network network;

	network.initialize();

	cerr << "Neurones added, the network is initialized !" << endl;
	cout << endl;

	network.ConnectEachNeurone();

	cerr << "The neurones are connected, we are ready for the simulation" << endl;
	cout << endl;

	network.update(t);

	cout << endl;
	cout << endl;
	cerr << "The simulation is completed" << endl;
	cout << endl;

	network.printSpikeTimes(donnees, t);

	cerr << "The datas are printed in build/data.txt" << endl;
	cout << endl;
	
	donnees.close();
	
	cerr << "See you Soon !" << endl;
	return 0;
}


double AskForTime() {

	double duree (0);

	try {
	cout << "Entrez la durée de la simulation (en ms) : " << endl << endl;
	cin >> duree;
	if(!cin) {
		throw string("Merci d'entrer un nombre"); 
	}
}
	catch (string& message) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << endl;
		cerr << message << endl;
	}

	std::cout << endl;

	return duree*toMs;
}
