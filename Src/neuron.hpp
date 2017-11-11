#include <iostream>
#include <vector>
#include <random>
#include "ringbuffer.hpp"

#ifndef NEURON_H
#define NEURON_H


/**
* enum Status
* Represents the differents neurone categories : Excitatory or Inhibitory
*/ 
enum Status {
Excitatory, 
Inhibitory};


/*!
 * @class Neuron
 *
 * @brief Represents a neuron. It can spike, interact with other neurons...
 */
class Neuron {

	private : 

		/**
		*  Contains the type of the neuron (Excitatory or inhibitory)
		*/
		Status status_;
		
		/**
		*  Represents the neuron's membrane potential
		*/
		double membrane_potential_;
		
		/**
		*  Buffer for the neuron (used to manage incoming events)
		*/
		RingBuffer buffer_;

		/**
		*  All of the neurons linked with the neuron. When it spikes,
		*  it sends informations to every neurons in the vector.
		*/
		std::vector<Neuron*> targets_;

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
		*  @brief  Neuron constructor (the initiation constants are in constant.h).
		*/
		Neuron(Status status);

		/**
		*  @brief  Neuron destructor
		*/
		~Neuron();



	//Every methods that are used in the updating of the neuron :



		/**
		*  @brief  Update the neuron (change the membrane potential, make it 
		*  spike if the treshold is reached and manage rest time).
		* 
		*  @param t 					Simulation time.
		*/
		bool update (unsigned int t);

		/**
		*  @brief  Test if the treshold is reached, if it is, make the neuron spike
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




	//Every methods that are used to manage incomning informations and transmit the information :




		/**
		*  @brief Receive a spike from another neuron.
		* 
		*  @param current_index	Index in the buffer for the spike.
		*  @param status		Status of the spiking neuron (Excitatory or Inhibitory) : 
		*  an inhibitory one will low the membrane potential and an excitatory one will increase it.
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
		*  @brief Send to every targetted neuron the spike information (used only if it spikes).
		*  
		*  @param current_index			Current index.
		*/
		void sendInformation (unsigned int current_index) const ;




	//Every methods that are used to create connections:



		/**
		*  @brief  Make connections with others neurons.
		* 
		*  @param neurones		Network's neurons list.
		*  @param neuroneNumber	The current neuron number's in the network neurons list
		*/
		void MakeConnections(std::vector<Neuron*>& neurones, int neuroneNumber);

		/**
		*  @brief Add one connection (one new targetted neuron)
		*  
		*  @param neurones		Network's neuroes list
		*  @param targetNumber	Number of the target in the network's list
		*/

		void addConnection(std::vector<Neuron*>& neurones, int targetNumber);




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
		*  @brief Getter for the status of the neuron.
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

		int countConnection(int i,std::vector<Neuron*>& neurons, int& InCounteur, int& ExCounteur);
	
};

#endif


