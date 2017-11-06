#include <cmath>

const double Spike_Treshold(0.020); 	//V
const double Tau(0.020);				//s
const double TauR(0.002);				//s (temps de repos après spike)
const double DeltaTime(0.0001);			//pas de temps	
const double Resistance(20e6);			//Ohm
const double Standard_potential(0);		//V
const double Refractory_potential(0.010);
const double ETA(2);
const int mV(1000);						//transform mV into V
const int ms(1000);						//transform ms into s
const double toMs(0.001);				//transform second into ms
const int bufferSize(16);  				//1+synaptic_delay
const int synaptic_delay(15);			//delay before the spike is recorded by the receiving neurone
const double g(5);
const double Je(0.0001); 
const double Ji(-g*Je);			
const int Ne(10000);					//Excitatory neurons
const int Ni(2500);						//Inhibitory neurons
const int Ce(1000);						//Connected Excitatory neurons 
const int Ci(250);						//Connected Inhibitory neurons
const int Cext(1000);					//Connections from outside the network


const double c1 (exp(-DeltaTime/Tau));	//constant for the calculation of the new potential
const double NuExt((ETA*Spike_Treshold)/(Je*Tau));
const double MeanByDeltaTime(NuExt*DeltaTime);			//Mean of spikes from the outside of the network by unit of time
