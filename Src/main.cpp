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
	
	unsigned int t (std::round(temps_f/DeltaTime));
	
	Network network;

	network.initialize();

	std::cerr << "Neurones added, the network is initialized !" << std::endl;
	std::cout << std::endl;

	network.ConnectEachNeurone();

	std::cerr << "The neurones are connected, we are ready for the simulation" << std::endl;
	std::cout << std::endl;

	network.update(t);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cerr << "The simulation is completed" << std::endl;
	std::cout << std::endl;

	network.printSpikeTimes(donnees, t);

	std::cerr << "The datas are printed in build/donnees.txt" << std::endl;
	std::cout << std::endl;
	
	donnees.close();
	
	std::cerr << "See you Soon !" << std::endl;
	return 0;
}


double AskForTime() {

	double duree (0);

	std::cout << "Entrez la durée de la simulation (en ms) : " << std::endl << std::endl;
	cin >> duree;
	std::cout << endl;

	return duree*toMs;
}
