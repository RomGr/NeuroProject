#include "neuron.hpp"
#include "constant.h"
#include <math.h>
#include <vector>
#include <cmath>

		Neuron::Neuron(Status status) :
			status_(status),
			membrane_potential_(Standard_potential),
			clock_rest_time_(0.0), 
			I_ext_(0.0),
			test_(false) {}


		Neuron::~Neuron()
		 	{
		 		for (auto& target : targets_) {
		 			target=nullptr;
		 			//They are deleted in the network destructor
		 		}
		 	}



	//Every methods that are used in the updating of the neuron :



		bool Neuron::update(unsigned int t) {

			bool spike(false);
			size_t current_index(t%bufferSize);

			spike=Spike(t);
			// 1) make the neuron spike and set it refractory (if necessary)
			
			double new_potential(0.0);
				if(not isInRest()) {
					new_potential = c1*(membrane_potential_);
					new_potential += I_ext_*c2;
					// 2) calculate the new potential
					new_potential += outsideInput(current_index);
					// 3) add the potential created by other neurons
						if (not test_) {
							new_potential += BackgroundInput();
						}
					// 4) add the potential created by the background
					membrane_potential_=new_potential;
					// 5) update the membrane potential
					if (membrane_potential_<0.0) {
						membrane_potential_=Refractory_potential;
					}
				} else {
					membrane_potential_=Refractory_potential;
				}
			
			buffer_.update(current_index);
			
			return spike;
		}


		bool Neuron::Spike(unsigned int t) {
			
			bool spike(false);
			
				if(membrane_potential_ >= Spike_Treshold) {
					spikes_times_.push_back(t);
					// 1) stores the spike time
					membrane_potential_=Refractory_potential;
					// 2) reinitialize the membrane potential
					clock_rest_time_=TauR;
					// 3) set the rest time
					spike=true;
				};

			return spike;
		}


		bool Neuron::isInRest() {

				if (not (clock_rest_time_ <= 0.0)) {
					clock_rest_time_-=DeltaTime;
					// retires an unit of time
					return true;
				}
			
			return false;
		}


	//Every methods that are used to manage incomning informations and transmit the information :



		void Neuron::receive(unsigned int current_index, Status status) {

			if (status==Excitatory) {
				buffer_.addValue(current_index,Je);
			}
			if (status==Inhibitory) {
				buffer_.addValue(current_index,Ji);
			}
		}

		double Neuron::outsideInput(size_t current_index) const {
			double input(buffer_.valueFor(current_index));
			return input;
		}

		double Neuron::BackgroundInput() const {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::poisson_distribution<> d(MeanByDeltaTime);

			return (d(rd))*Je;
		}

		void Neuron::sendInformation (unsigned int current_index) const {
			for (auto neu : targets_) {
				neu->receive(current_index,status_);
			}
		}




	//Every methods that are used to create connections:



		void Neuron::MakeConnections(std::vector<Neuron*>& neurons, int neuronNumber) {
			std::mt19937 rng(time(NULL));
			int newNeuronNumber(0);

				for(size_t i(0); i < Ce ; ++i) {
					do {
					std::uniform_int_distribution<int> distribution(0, Ne-1);
					newNeuronNumber = distribution(rng);
				} while (newNeuronNumber == neuronNumber);
					neurons[newNeuronNumber]->addConnection(neurons,neuronNumber);
				}

				for (size_t i(0); i < Ci ; ++i) {
					do {
					std::uniform_int_distribution<int> distribution(0, Ni-1);
					newNeuronNumber = distribution(rng) + Ne;
				} while (newNeuronNumber == neuronNumber);
					neurons[newNeuronNumber]->addConnection(neurons, neuronNumber);
				}
		}

		void Neuron::addConnection(std::vector<Neuron*>& neurons, int targetNumber) {
			targets_.push_back(neurons[targetNumber]);
		}



	//Getters, setters and test mode methods:


		double Neuron::getMembranePotential () const {
			return membrane_potential_;
		}

		std::vector<int> Neuron::getSpikeTimes() const {
			return spikes_times_;
		}

		Status Neuron::getStatus() const {
			return status_;
		}
		
		void Neuron::setIext(double I) {
			I_ext_=I;
		}

		void Neuron::setTestMode() {
			test_=true;
		}
		
		int Neuron::countConnection(int i,std::vector<Neuron*>& neurons,int& InCounteur, int& ExCounteur)  {
			int counter(0);

				for(auto neu : targets_) {
					if (neu==neurons[i]) {
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
