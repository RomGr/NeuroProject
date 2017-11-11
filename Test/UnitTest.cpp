#include <iostream>
#include <vector>
#include "../Src/neuron.hpp"
#include "../Src/network.hpp"
#include "../../googletest/include/gtest/gtest.h"
#include "../Src/constant.h"


TEST (NeuronTest , PotentialInitialisation) {
	Neuron neuron(Excitatory);
	EXPECT_EQ(0, neuron.getMembranePotential());
}

TEST (NeuronTest , SpikeTimes) {
	Neuron neuron(Excitatory);
	neuron.setTestMode();
	neuron.setIext(1.01e-9);
	for (unsigned int i(0); i < 3000 ; ++i) {
		neuron.update(i);
	}
	std::vector<int> SpikeTimes (neuron.getSpikeTimes());
	EXPECT_EQ(924, SpikeTimes[0]);
	EXPECT_EQ(1731, SpikeTimes[1]);
	EXPECT_EQ(2538, SpikeTimes[2]);	
}

TEST (NeuronTest, Doesnt_reach_treshold) {
	Neuron neuron(Excitatory);
	neuron.setTestMode();
	neuron.setIext(1.0e-9);
	for (unsigned int i(0); i < 10000 ; ++i) {
		neuron.update(i);
	}
	std::vector<int> SpikeTimes(neuron.getSpikeTimes());
	unsigned int size (0);
	EXPECT_EQ(size, SpikeTimes.size());
}

TEST (TwoNeurons, ReceiveTime) {
	Neuron neuron1(Excitatory);
	neuron1.setIext(1.01e-9);
	neuron1.setTestMode();
	Neuron neuron2(Excitatory);
	neuron2.setTestMode();

	for (unsigned int i (0) ; i < 924 + synaptic_delay; ++i) {
		if (neuron1.update(i)) {
			neuron2.receive((i+synaptic_delay-1)%bufferSize,Excitatory);
			EXPECT_EQ(0.010, neuron1.getMembranePotential());
		}
		neuron2.update(i);
	}
	EXPECT_EQ(0.0001,neuron2.getMembranePotential());
}

TEST (TwoNeurons , Neuron2_Spike) {
	Neuron neuron1(Excitatory);
	neuron1.setIext(1.01e-9);
	neuron1.setTestMode();
	Neuron neuron2(Excitatory);
	neuron2.setIext(1.0e-9);
	neuron2.setTestMode();

	for (unsigned int i (0) ; i < 1731 + synaptic_delay; ++i) {
		if (neuron1.update(i)) {
			neuron2.receive((i+synaptic_delay-1)%bufferSize,Excitatory);
			EXPECT_EQ(0.010, neuron1.getMembranePotential());
		}
		bool update;
		update = neuron2.update(i);
	}
	//just before neurone 2 spikes
	unsigned long int size = 0;
	EXPECT_EQ(size,(neuron2.getSpikeTimes()).size());
	bool update;
	update = neuron2.update(1732+synaptic_delay);

	size = 1;
	EXPECT_EQ(0.010, neuron2.getMembranePotential());
	EXPECT_EQ(size,(neuron2.getSpikeTimes()).size());
}

TEST (TwoNeurons, Inhibitory_Excitatory_Test) {
	RingBuffer buffer;
	buffer.addValue(0,Ji);
	EXPECT_EQ(-0.0005, buffer.valueFor(0));
	buffer.addValue(0,Je);
	EXPECT_EQ(-0.0004,buffer.valueFor(0));
	buffer.addValue(0,4*Je);
	EXPECT_EQ(0.0000,buffer.valueFor(0));
}

TEST(NetworkTest, NetworkNumbers) {
	Network network;
	network.initialize();
	std::vector<Neuron*> neurons;
	neurons = network.getNeurons();

	int Icompteur(0);
	int Ecompteur(0);
	int NeuronsCompteur(0);

	for (auto neu : neurons) {
			if (neu->getStatus()==Excitatory) {
				++Ecompteur;
			} else {
				++Icompteur;
			}
			++NeuronsCompteur;
	} 

	EXPECT_EQ(12500,NeuronsCompteur);
	EXPECT_EQ(10000,Ecompteur);
	EXPECT_EQ(2500,Icompteur);
}

TEST(NetworkTest, Verify_Excitatory_Connection) {
	Network network;
	network.initialize();
	std::vector<Neuron*> neurons;
	neurons = network.getNeurons();

	neurons[0]->addConnection(neurons,1);
	neurons[0]->sendInformation(0);

	EXPECT_EQ(0.0001,neurons[1]->outsideInput(0));

}

TEST (NetworkTest, Verify_Inhibitory_Connection) {
	Network network;
	network.initialize();
	std::vector<Neuron*> neurons;
	neurons = network.getNeurons();

	neurons[10000]->addConnection(neurons,1);
	neurons[10000]->sendInformation(0);

	EXPECT_EQ(-0.0005,neurons[1]->outsideInput(0));
}

TEST (NetworkTest, Verify_Connection_Numbers) {
	Network network;
	network.initialize();
	std::vector<Neuron*> neurons;
	neurons = network.getNeurons();
	network.ConnectEachNeuron();

	std::vector<Neuron*> targets;

	int connectionCompteur(0);
	int InCounteur(0);
	int ExCounteur(0);


	for (auto neu : neurons) {
		connectionCompteur+=neu->countConnection(0,neurons, InCounteur, ExCounteur);
	}

	EXPECT_EQ(1250,connectionCompteur);
	EXPECT_EQ(250, InCounteur);
	EXPECT_EQ(1000, ExCounteur);
}

int main (int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}