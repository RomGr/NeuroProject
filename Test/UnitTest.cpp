#include <iostream>
#include <vector>
#include "../Src/neurone.hpp"
#include "../Src/network.hpp"
#include "../../googletest/include/gtest/gtest.h"
#include "../Src/constant.h"


TEST (NeuroneTest , PotentialInitialisation) {
	Neurone neurone(Excitatory);
	EXPECT_EQ(-0.070, neurone.getMembranePotential());
}

TEST (NeuronTest , SpikeTimes) {
	Neurone neurone(Excitatory);
	neurone.setTestMode();
	neurone.setIext(1.01e-9);
	for (unsigned int i(0); i < 3000 ; ++i) {
		neurone.update(i);
	}
	std::vector<int> SpikeTimes (neurone.getSpikeTimes());
	EXPECT_EQ(924, SpikeTimes[0]);
	EXPECT_EQ(1868, SpikeTimes[1]);
	EXPECT_EQ(2812, SpikeTimes[2]);	
}

TEST (NeuronTest, Doesnt_reach_treshold) {
	Neurone neurone(Excitatory);
	neurone.setTestMode();
	neurone.setIext(1.0e-9);
	for (unsigned int i(0); i < 10000 ; ++i) {
		neurone.update(i);
	}
	std::vector<int> SpikeTimes(neurone.getSpikeTimes());
	unsigned int size (0);
	EXPECT_EQ(size, SpikeTimes.size());
}

TEST (TwoNeurones, ReceiveTime) {
	Neurone neurone1(Excitatory);
	neurone1.setIext(1.01e-9);
	neurone1.setTestMode();
	Neurone neurone2(Excitatory);
	neurone2.setTestMode();

	for (unsigned int i (0) ; i < 925 + synaptic_delay; ++i) {
		if (neurone1.update(i)) {
			neurone2.receive(i+synaptic_delay,Excitatory);
			EXPECT_EQ(-0.070, neurone1.getMembranePotential());
		}
		neurone2.update(i);
	}
	EXPECT_EQ(-0.0699,neurone2.getMembranePotential());
}

TEST (TwoNeurones , Neurone2_Spike) {
	Neurone neurone1(Excitatory);
	neurone1.setIext(1.01e-9);
	neurone1.setTestMode();
	Neurone neurone2(Excitatory);
	neurone2.setIext(1.0e-9);
	neurone2.setTestMode();

	for (unsigned int i (0) ; i < 1869 + synaptic_delay; ++i) {
		if (neurone1.update(i)) {
			neurone2.receive(i+synaptic_delay,Excitatory);
			EXPECT_EQ(-0.070, neurone1.getMembranePotential());
		}
		bool update;
		update = neurone2.update(i);
	}
	//just before neurone 2 spikes
	unsigned long int size = 0;
	EXPECT_EQ(size,(neurone2.getSpikeTimes()).size());
	bool update;
	update = neurone2.update(1869+synaptic_delay);

	size = 1;
	EXPECT_EQ(-0.070, neurone2.getMembranePotential());
	EXPECT_EQ(size,(neurone2.getSpikeTimes()).size());
}

TEST (TwoNeurones, Inhibitory_Excitatory_Test) {
	RingBuffer buffer;
	buffer.addValue(0,Ji);
	EXPECT_EQ(-0.0005, buffer.valueFor());
	buffer.addValue(0,Je);
	EXPECT_EQ(-0.0004,buffer.valueFor());
	buffer.addValue(0,4*Je);
	EXPECT_EQ(0.0000,buffer.valueFor());
}

TEST(NetworkTest, NetworkNumbers) {
	Network network;
	network.initialize();
	std::vector<Neurone*> neurones;
	neurones = network.getNeurones();

	int Icompteur(0);
	int Ecompteur(0);
	int NeuronesCompteur(0);

	for (auto neu : neurones) {
			if (neu->getStatus()==Excitatory) {
				++Ecompteur;
			} else {
				++Icompteur;
			}
			++NeuronesCompteur;
	} 

	EXPECT_EQ(12500,NeuronesCompteur);
	EXPECT_EQ(10000,Ecompteur);
	EXPECT_EQ(2500,Icompteur);
}

TEST(NetworkTest, Verify_Excitatory_Connection) {
	Network network;
	network.initialize();
	std::vector<Neurone*> neurones;
	neurones = network.getNeurones();

	neurones[0]->addConnection(neurones,1);
	neurones[0]->sendInformation(0);

	EXPECT_EQ(0.0001,neurones[1]->outsideInput());

}

TEST (NetworkTest, Verify_Inhibitory_Connection) {
	Network network;
	network.initialize();
	std::vector<Neurone*> neurones;
	neurones = network.getNeurones();

	neurones[10000]->addConnection(neurones,1);
	neurones[10000]->sendInformation(0);

	EXPECT_EQ(-0.0005,neurones[1]->outsideInput());
}

TEST (NetworkTest, Verify_Connection_Numbers) {
	Network network;
	network.initialize();
	std::vector<Neurone*> neurones;
	neurones = network.getNeurones();
	network.ConnectEachNeurone();

	std::vector<Neurone*> targets;

	int connectionCompteur(0);
	int InCounteur(0);
	int ExCounteur(0);


	for (auto neu : neurones) {
		connectionCompteur+=neu->countConnection(0,neurones, InCounteur, ExCounteur);
	}

	EXPECT_EQ(1250,connectionCompteur);
	EXPECT_EQ(250, InCounteur);
	EXPECT_EQ(1000, ExCounteur);
}

int main (int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}