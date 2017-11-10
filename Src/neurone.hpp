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
		*  Buffer for the neurone (used to manage incoming events)
		*/
		RingBuffer buffer_;

		/**
		*  All of the neurones linked with the neurone. When it spikes,
		*  it sends informations to every neurones in the vector.
		*/
		std::vector<Neurone*> targets_;

		/**
		*  Manage the rest time
		*/
		double clock_rest_time_;

		/**
		*  External input current
		*/
		double I_ext_;

		/**
		*  Used to store the spike times
		*/
		std::vector<int> spikes_times_;
		
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



	//Every methods that are used in the updating of the neurone :



		/**
		*  @brief  Update the neurone (change the membrane potential, make it 
		*  spike if the treshold is reached and manage rest time).
		* 
		*  @param t 					Simulation time.
		*/
		bool update (unsigned int t);

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




	//Every methods that are used to manage incomning informations and prevent other neurones of spiking:




		/**
		*  @brief Receive a spike from another neurone.
		* 
		*  @param current_index	Index in the buffer for the spike.
		*  @param status		Status of the spiking neurone (Excitatory or Inhibitory) : 
		*  an inhibitory will low the membrane potential and an excitatory neurone will increase it.
		*/
		void receive(unsigned int current_index, Status status);

		/**
		*  @brief  Return the outside input (from other neurones) for the current time.
		*
		*  @param current_index 		The index of the current time in the buffer.
		*/
		double outsideInput(size_t current_index) const;

		/**
		*  @brief  Returns the current induced by the background.
		*/
		double BackgroundInput() const;

		/**
		*  @brief Send to every targetted neurone the spike information (used only if it spikes).
		*  
		*  @param current_index			Current index.
		*/
		void sendInformation (unsigned int current_index) const ;




	//Every methods that are used to create connections:



		/**
		*  @brief  Make connections with others neurones.
		* 
		*  @param neurones		Network's neurones list.
		*  @param neuroneNumber	The current neurone number's in the network neurones list
		*/
		void MakeConnections(std::vector<Neurone*>& neurones, int neuroneNumber);

		/**
		*  @brief Add one connection (one new targetted neurone)
		*  
		*  @param neurones		Network's neurones list
		*  @param targetNumber	Number of the target int the network's list
		*/

		void addConnection(std::vector<Neurone*>& neurones, int targetNumber);




	//Getters, setters and test mode methods:



		/**
		*  @brief  Getter for the membrane potential.
		*/
		double getMembranePotential () const ;
		
		/**
		*  @brief  Getter for the spike times.
		*/
		std::vector<int> getSpikeTimes() const;
	
		/**
		*  @brief Getter for the status of the neurone.
		*/
		Status getStatus() const;

		/**
		*  @brief	Set the external input current.
		* 
		*  @param I 					New input current.
		*/
		void setIext(double I);

		/**
		*  @brief Set test mode to true.
		*/
		void setTestMode();
		
		/**
		*  @brief TestMode
		*/

		int countConnection(int i,std::vector<Neurone*>& neurones, int& InCounteur, int& ExCounteur);
	
};

#endif


