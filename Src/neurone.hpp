#include <iostream>
#include <vector>
#include <random>
#include "ringbuffer.hpp"

#ifndef NEURONE_H
#define NEURONE_H


/**
* enum Status
* Represents the differents neurone categories : Excitatory or Inhibitory
*/ 
enum Status {
Excitatory, 
Inhibitory};


/*!
 * @class Neurone
 *
 * @brief Represents a neurone. It can spike, interact with other neurones...
 */
class Neurone {

	private : 

		/**
		*  Contains the type of the neurone (Excitatory or inhibitory)
		*/
		Status status_;
		
		/**
		*  Represents the neurone's membrane potential
		*/
		double membrane_potential_;
		
		/**
		*  Used to store the spike times
		*/
		std::vector<int> spikes_times_;
		
		/**
		*  Manage the rest time
		*/
		double clock_rest_time_;
		
		/**
		*  Buffer for the neurone (used to manage incoming events)
		*/
		RingBuffer buffer_;

		/**
		*  External input current
		*/
		double I_ext_;

		/**
		*  All of the neurones linked with the neurone. When it spikes,
		*  it sends informations to every neurones in the vector.
		*/
		std::vector<Neurone*> targets_;

		/**
		*  If true we retire the backgroung input (used in UnitTest)
		*/
		bool test_;



	public :

		/**
		*  @brief  Neurone constructor (the initiation constants are in constant.h).
		*/
		Neurone(Status status);

		/**
		*  @brief  Neurone destructor
		*/
		~Neurone();

		/**
		*  @brief  Update the neurone (change the membrane potential, make it 
		*  spike if the treshold is reached and manage rest time).
		* 
		*  @param t 					Simulation time.
		*/
		bool update (unsigned int t);
		
		/**
		*  @brief	Set the external input current.
		* 
		*  @param I 					New input current.
		*/
		void setIext(double I);
		
		/**
		*  @brief  Getter for the membrane potential.
		*/
		double getMembranePotential () const ;
		
		/**
		*  @brief  Test if the treshold is reached, if it is, make the neurone spike
		*  and reinitialize the membrane potential. Store the spike's time.
		* 
		*  @param t 					Used to store the spike's time.
		*/
		bool Spike(unsigned int t);
		
		/**
		*  @brief  Test if the neuron is in rest. If it is, subtract an unit of time
		*  to the rest time.
		*/
		bool isInRest();
		
		/**
		*  @brief  Getter for the spike times.
		*/
		std::vector<int> getSpikeTimes() const;
		
		/**
		*  @brief Receive a spike from another neurone.
		* 
		*  @param D				Delay before the spike causes a membrane potential change.
		*  @param status		Status of the spiking neurone (Excitatory or Inhibitory) : 
		*  an inhibitory will low the membrane potential and an excitatory neurone will increase it.
		*/
		void receive(size_t D, Status status);
		
		/**
		*  @brief  Return the outside input (from other neurones) for the current time.
		*/
		double outsideInput(size_t current_index) const;

		/**
		*  @brief  Make connections with others neurones.
		* 
		*  @param neurones		Network's neurones list.
		*  @param neuroneNumber	The current neurone number's in the network neurones list
		*/
		void MakeConnections(std::vector<Neurone*>& neurones, int neuroneNumber);

		/**
		*  @brief  Returns the current induced by the background.
		*/
		double BackgroundInput() const;

		/**
		*  @brief Getter for the status of the neurone.
		*/
		Status getStatus() const;

		/**
		*  @brief Send to every targetted neurone the spike information (used only if it spikes).
		*  
		*  @param t			Spike time
		*/
		void sendInformation (size_t current_index) const ;

		/**
		*  @brief Set test mode to true.
		*/
		void setTestMode();

		/**
		*  @brief Add one connection (one new targetted neurone)
		*  
		*  @param neurones		Network's neurones list
		*  @param targetNumber	Number of the target int the network's list
		*/

		void addConnection(std::vector<Neurone*>& neurones, int targetNumber);

		/**
		*  @brief TestMode
		*/

		int countConnection(int i,std::vector<Neurone*>& neurones, int& InCounteur, int& ExCounteur);
	
};

#endif


