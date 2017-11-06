#include <iostream>
#include <vector>
#include <iomanip>
#include "network.hpp"
#include "constant.h"
#include <tgmath.h>


Network::Network() {}

Network::~Network() {
	for (auto& neu : neurones_) {
		delete neu;
		neu=nullptr;
	}
	neurones_.clear();
}

void Network::initialize() {

	for (size_t i(0); i < Ne; ++i) {
		neurones_.push_back(new Neurone(Excitatory));
	}

	for (size_t i(0); i < Ni; ++i) {
		neurones_.push_back(new Neurone(Inhibitory));
	}
}

void Network::addNeurone(Neurone* neurone) {
	
	if (neurone != nullptr) {
		neurones_.push_back(neurone);
	}
	
}

void Network::update(unsigned int time_f) {
	unsigned int t(0);

	while (t < time_f) {
		if (not neurones_.empty()) {
			int delay (t+synaptic_delay);
			for (auto& neu : neurones_) {
				bool spike(false);
				spike=neu->update(t);
				// Verify for each neurone if it spikes
				if (spike) {
				neu->sendInformation(delay);
				}
			}
			++t;
			std::cout<<t*0.1<<std::endl;
		}
	}
}


void Network::printSpikeTimes(std::ofstream& donnees, int time_f) {

	std::vector<std::vector<int>> AllSpikeTimes = std::vector<std::vector<int>> (time_f);

	for(size_t i(0); i < neurones_.size(); ++i) {
		if (not (neurones_[i]->getStatus()==Inhibitory)) {
		if (neurones_[i]->getSpikeTimes().empty()) {
			//We do nothing
		} else {
			for(size_t j(0); j < (neurones_[i]->getSpikeTimes()).size(); ++j) {
				AllSpikeTimes[(neurones_[i]->getSpikeTimes())[j]].push_back(i);
			} 
		}
	}
	}

	char tab = '\t';
	unsigned int i(0);
	for(auto SpikeTime : AllSpikeTimes) {
		for (auto neu : SpikeTime) {
			donnees << i << tab << neu << std::endl;
		}
	
	++i;
	}
}


void Network::ConnectEachNeurone() {
	for (size_t i(0); i < neurones_.size(); ++i)  {
		neurones_[i]->MakeConnections(neurones_,i);
	}
}

std::vector<Neurone*>& Network::getNeurones() {
	return neurones_;
}
