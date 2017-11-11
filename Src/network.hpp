#include <iostream>
#include "neuron.hpp"
#include <fstream>
#include <iomanip>

#ifndef NETWORK_H
#define NETWORK_H

// Destructeur


/*!
 * @class Network
 *
 * @brief Represents a neuron network, allows to simulate their life and make them
 * interact.
 */
class Network {
	

	private :
	
		/**
		*  The neurons of the network
		*/
		std::vector<Neuron*> neurons_;
	

	public :
	
		/**
		*  @brief  Network constructor.
		*/
		Network();
	
		/**
		*  @brief  Network destructor.
		*/
		~Network();
	
		/**
		*  @brief Initialize the network (create each neuron) : 10'000 excitatory neurons, 2'500 inhibitory neurons.
		*/
		void initialize();

		/**
		*  @brief  Add a neuron to the network.
		* 
		*  @param neuron		Neuron to add.
		*/
		void addNeuron(Neuron* neuron);
	
		/**
		*  @brief  Update the network (update each neuron and make them interact if necessary).
		* 
		*  @param time_f			Final simulation time.
		*/
		void update(unsigned int time_f);

		/**
		*  @brief  Make each neuron connect with the others.
		*/
		void ConnectEachNeuron();

		/**
		*  @brief TestMode
		*/
		std::vector<Neuron*>& getNeurons();
	
		/**
		*  @brief Print the run progress
		*
		*  @param time 			Simulation time.
		*  @param time_f		Final simulation time.
		*/
		void PrintProgress(double time, double time_f);

		/**
		*  @brief  Print how many spikes are identified by unit of time.
		* 
		*  @param donnees		Where to write.
		*  @param time_f		Final simulation time.
		*/
		void printSpikeTimes(std::ofstream& donnees, int time_f);
};

#endif
