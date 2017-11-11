#include <iostream>
#include <vector>
#include <iomanip>
#include "network.hpp"
#include "constant.h"
#include <tgmath.h>


	Network::Network() {}

	Network::~Network() {
		for (auto& neu : neurons_) {
			delete neu;
			neu=nullptr;
		}
		neurons_.clear();
	}

	void Network::initialize() {

		for (size_t i(0); i < Ne; ++i) {
			neurons_.push_back(new Neuron(Excitatory));
		}

		for (size_t i(0); i < Ni; ++i) {
			neurons_.push_back(new Neuron(Inhibitory));
		}
	}

	void Network::addNeuron(Neuron* neuron) {
		
		if (neuron != nullptr) {
			neurons_.push_back(neuron);
		}
		
	}

	void Network::update(unsigned int time_f) {
		unsigned int t(0);

		while (t < time_f) {
			if (not neurons_.empty()) {
				size_t current_index((t+synaptic_delay-1)%bufferSize);
					for (auto& neu : neurons_) {
						bool spike(false);
						spike=neu->update(t);
						// Verify for each neurone if it spikes
						if (spike) {
						neu->sendInformation(current_index);
						}
					}
				++t;
				PrintProgress(t,time_f);
			}
		}
	}

	void Network::ConnectEachNeuron() {
		for (size_t i(0); i < neurons_.size(); ++i)  {
			neurons_[i]->MakeConnections(neurons_,i);
		}
	}

	std::vector<Neuron*>& Network::getNeurons() {
		return neurons_;
	}

	void Network::PrintProgress(double time, double time_f) {
		double progress = 0.0;
	    int barWidth = 70;

	    progress = (time)/(time_f);

	   	int pos (progress*barWidth);

	    std::cout << "[";
	    for (int i = 0; i < barWidth; ++i) {
	        if (i < pos) std::cout << "=";
	        else if (i == pos) std::cout << "|";
	        else std::cout << " ";
	    }
	    std::cout << "] " << int(progress * 100.0) << " %\r";
		std::cout.flush();
	}

	void Network::printSpikeTimes(std::ofstream& donnees, int time_f) {

		std::vector<std::vector<int>> AllSpikeTimes = std::vector<std::vector<int>> (time_f);

		for(size_t i(0); i < numberOfInterest; ++i) {
			if (neurons_[i]->getSpikeTimes().empty()) {
				//We do nothing
			} else {
				for(size_t j(0); j < (neurons_[i]->getSpikeTimes()).size(); ++j) {
					AllSpikeTimes[(neurons_[i]->getSpikeTimes())[j]].push_back(i);
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