#include "neurone.hpp"
#include "constant.h"
#include <math.h>
#include <vector>
#include <cmath>

Neurone::Neurone(Status status) :
	status_(status),
	membrane_potential_(Standard_potential),
	clock_rest_time_(0.0), 
	I_ext_(0.0),
	test_(false) {}


Neurone::~Neurone()
 					{}


bool Neurone::update(unsigned int t) {

	bool spike(false);
	spike=Spike(t);
	// 1) make the neurone spike and set it refractory (if necessary)
	
	double new_potential(0.0);
	if(not isInRest()) {
		new_potential = c1*(membrane_potential_);
		new_potential += I_ext_*(Resistance)*(1-c1);
		// 2) calculate the new potential
		new_potential += outsideInput();
		// 3) add the potential created by other neurones
		if (not test_) {
			new_potential += BackgroundInput();
		}
		// 4) add the potential created by the background
		membrane_potential_=new_potential;
		// 5) update the membrane potential
		if (membrane_potential_<0.0) {
			membrane_potential_=0.0;
		}
	} else {
		membrane_potential_=Standard_potential;
	}
	
	buffer_.update();
	
	return spike;
}


double Neurone::getMembranePotential () const {

	return membrane_potential_-0.070;
	// -0.070 because we use a 0 origin for the membrane potential
}


bool Neurone::isInRest() {

	if (not (clock_rest_time_ <= 0.0)) {
		clock_rest_time_-=DeltaTime;
		// retires an unit of time
		return true;
	}
	
	return false;
}


bool Neurone::Spike(unsigned int t) {
	
	bool spike(false);
	
	if(membrane_potential_ >= Spike_Treshold) {
		spikes_times_.push_back(t);
		// 1) stores the spike time
		membrane_potential_=Standard_potential;
		// 2) reinitialize the membrane potential
		clock_rest_time_=TauR;
		// 3) set the rest time
		spike=true;
	};
	return spike;
}


std::vector<int> Neurone::getSpikeTimes() const {
	return spikes_times_;
} 


void Neurone::receive(int D, Status status) {
	if (status==Excitatory) {
		buffer_.addValue(D,Je);
	}
	if (status==Inhibitory) {
		buffer_.addValue(D,Ji);
	}
}


double Neurone::outsideInput() const {
	double input(buffer_.valueFor());
	return input;
}


void Neurone::setIext(double I) {
	I_ext_=I;
}


void Neurone::MakeConnections(std::vector<Neurone*>& neurones, int neuroneNumber) {
	std::mt19937 rng(time(NULL));
	int newNeuroneNumber(0);

		for(size_t i(0); i < Ce ; ++i) {
			do {
			std::uniform_int_distribution<int> distribution(0, Ne-1);
			newNeuroneNumber = distribution(rng);
		} while (newNeuroneNumber == neuroneNumber);
			neurones[newNeuroneNumber]->addConnection(neurones,neuroneNumber);
		}

		for (size_t i(0); i < Ci ; ++i) {
			do {
			std::uniform_int_distribution<int> distribution(0, Ni-1);
			newNeuroneNumber = distribution(rng) + Ne;
		} while (newNeuroneNumber == neuroneNumber);
			neurones[newNeuroneNumber]->addConnection(neurones, neuroneNumber);
		}
}


double Neurone::BackgroundInput() const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::poisson_distribution<> d(MeanByDeltaTime);

	return (d(rd))*Je;
}


Status Neurone::getStatus() const {
	return status_;
}


void Neurone::sendInformation (int t) const {
	for (auto neu : targets_) {
		neu->receive(t,status_);
	}
}


void Neurone::setTestMode() {
	test_=true;
}


void Neurone::addConnection(std::vector<Neurone*>& neurones, int targetNumber) {
	targets_.push_back(neurones[targetNumber]);
}


int Neurone::countConnection(int i,std::vector<Neurone*>& neurones,int& InCounteur, int& ExCounteur)  {
	int counter(0);

	for(auto neu : targets_) {
		if (neu==neurones[i]) {
			if (status_==Excitatory) {
				++ExCounteur;
			} else {
				++InCounteur;
			}
			++counter;
		}
	}
	return counter;
}