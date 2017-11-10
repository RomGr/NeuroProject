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
		 	{
		 		for (auto& target : targets_) {
		 			target=nullptr;
		 			//They are deleted in the network destructor
		 		}
		 	}



	//Every methods that are used in the updating of the neurone :



		bool Neurone::update(unsigned int t) {

			bool spike(false);
			size_t current_index(t%bufferSize);

			spike=Spike(t);
			// 1) make the neurone spike and set it refractory (if necessary)
			
			double new_potential(0.0);
				if(not isInRest()) {
					new_potential = c1*(membrane_potential_);
					new_potential += I_ext_*c2;
					// 2) calculate the new potential
					new_potential += outsideInput(current_index);
					// 3) add the potential created by other neurones
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


		bool Neurone::Spike(unsigned int t) {
			
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


		bool Neurone::isInRest() {

				if (not (clock_rest_time_ <= 0.0)) {
					clock_rest_time_-=DeltaTime;
					// retires an unit of time
					return true;
				}
			
			return false;
		}


	//Every methods that are used to manage incomning informations and prevent other neurones of spiking :



		void Neurone::receive(unsigned int current_index, Status status) {

			if (status==Excitatory) {
				buffer_.addValue(current_index,Je);
			}
			if (status==Inhibitory) {
				buffer_.addValue(current_index,Ji);
			}
		}

		double Neurone::outsideInput(size_t current_index) const {
			double input(buffer_.valueFor(current_index));
			return input;
		}

		double Neurone::BackgroundInput() const {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::poisson_distribution<> d(MeanByDeltaTime);

			return (d(rd))*Je;
		}

		void Neurone::sendInformation (unsigned int current_index) const {
			for (auto neu : targets_) {
				neu->receive(current_index,status_);
			}
		}




	//Every methods that are used to create connections:



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

		void Neurone::addConnection(std::vector<Neurone*>& neurones, int targetNumber) {
			targets_.push_back(neurones[targetNumber]);
		}



	//Getters, setters and test mode methods:


		double Neurone::getMembranePotential () const {
			return membrane_potential_;
			// -0.070 because we use a 0 origin for the membrane potential
		}

		std::vector<int> Neurone::getSpikeTimes() const {
			return spikes_times_;
		}

		Status Neurone::getStatus() const {
			return status_;
		}
		
		void Neurone::setIext(double I) {
			I_ext_=I;
		}

		void Neurone::setTestMode() {
			test_=true;
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
