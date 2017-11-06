#include <iostream>
#include <iomanip>
#include "neurone.hpp"
#include "network.hpp"
#include "constant.h"
#include <fstream>
#include <tgmath.h>

using namespace std;

double AskForTime();

int main () {

	double temps_f(0.0);

	do {
		temps_f = AskForTime();
	} while (temps_f <= 0 );
	
	ofstream donnees ("donnees.txt", ios::out);

	std::cout << MeanByDeltaTime << std::endl;

	unsigned int t (std::round(temps_f/DeltaTime));
	
	Network network;

	network.initialize();

	network.ConnectEachNeurone();

	network.update(t);

	network.printSpikeTimes(donnees, t);
	
	donnees.close();
	
	return 0;
}


double AskForTime() {

	double duree (0);

	std::cout << "Entrez la durée de la simulation (en ms) : " << std::endl;
	cin >> duree;

	return duree*toMs;
}




