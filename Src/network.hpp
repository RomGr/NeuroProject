#include <iostream>
#include "neurone.hpp"
#include <fstream>
#include <iomanip>

#ifndef NETWORK_H
#define NETWORK_H

// Destructeur


/*!
 * @class Network
 *
 * @brief Represents a neurone network, allows to simulate their life and make them
 * interact.
 */
class Network {
	
	private :
	
		/**
		*  The neurones of the network
		*/
		std::vector<Neurone*> neurones_;
	
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
		*  @brief Initialize the network (create each neurone) : 10'000 excitatory neurones, 2'500 inhibitory neurones.
		*/
		void initialize();

		/**
		*  @brief  Add a neurone to the network.
		* 
		*  @param neurone		Neurone to add.
		*/
		void addNeurone(Neurone* neurone);
	
		/**
		*  @brief  Update the network (update each neurone and make them interact if necessary).
		* 
		*  @param time_f			Final simulation time.
		*/
		void update(unsigned int time_f);
		
		/**
		*  @brief  Print how many spikes are identified by unit of time.
		* 
		*  @param donnees		Where to write.
		*  @param time_f		Final simulation time.
		*/
		void printSpikeTimes(std::ofstream& donnees, int time_f);

		/**
		*  @brief  Make each neurone connect with the others.
		*/
		void ConnectEachNeurone();

		/**
		*  @brief TestMode
		*/
		std::vector<Neurone*>& getNeurones();
	
		/**
		*  @brief Print the run progress
		*
		*  @param time 			Simulation time.
		*  @param time_f		Final simulation time.
		*/
		void PrintProgress(double time, double time_f);
};

#endif
