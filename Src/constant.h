#include <cmath>

// Neuron Constants :

const double Spike_Treshold(0.020); 	//V
const double Tau(0.020);				//s
const double TauR(0.002);				//s (temps de repos après spike)
const double DeltaTime(0.0001);			//pas de temps	
const double Resistance(20e6);			//Ohm
const double Standard_potential(0);		//V
const double Refractory_potential(0.010);


// Network constants :

const double ETA(2);
const int synaptic_delay(15);			//delay before the spike is recorded by the receiving neuron
const double g(5);
const double Je(0.0001); 				//Excitatory connection weight
const double Ji(-g*Je);					//Inhibitory connection weight
const double probabilityOfConnection(0.1);		
const int Ne(10000);					//Excitatory neurons
const int Ni(2500);						//Inhibitory neurons
const int Cext(1000);					//Connections from outside the Network

// Ploting constants :

const int numberOfInterest(100);

// Constants obtained by other constants :

const double c1 (exp(-DeltaTime/Tau));	//constant for the calculation of the new potential
const double NuExt((ETA*Spike_Treshold)/(Je*Tau));
const double MeanByDeltaTime(NuExt*DeltaTime);			//Mean of spikes from the outside of the network by unit of time
const double c2(Resistance*(1-c1));
const int Ce(Ne*probabilityOfConnection);						//Connected Excitatory neurons 
const int Ci(Ni*probabilityOfConnection);						//Connected Inhibitory neurons
const int bufferSize(1+synaptic_delay);  				//1+synaptic_delay

// Conversion constants :

const int mV(1000);						//transform mV into V
const int ms(1000);						//transform ms into s
const double toMs(0.001);				//transform second into ms