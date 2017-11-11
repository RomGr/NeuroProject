# NeuroProject

The program allows the simulation of a 12'500 neurons network. The neurons can interact with the others and with a background (the brain).



## Presentation

### Neurone

A neuron is an electrically excitable cell that receives, processes, and transmits information through electrical and chemical signals. The connection between two neurons is called synapse. There are two types of neuron :
- Inhibitory : it will send inhibitory spikes (to « prevent » other neurons to spike),
- Excitatory : it will send excitatory spikes (to make others neurons spike). 

In the simulation, the neuron can receive incoming informations (spikes), reacts to it ("update" the membrane potential), and transmits information two other neurons (if necessary).


### Network

A biological neural network is a series of interconnected neurons. In the simulation, it contains a collection of neurons and allows their management.


### RingBuffer

In the simulation, it is used to store the information (the spikes) coming from the neurons connected to the neuron of interest.



## Getting Started

These instructions will give you instructions to run the program, the tests and how to make the documentation.


### Compilation

In a terminal, go to the build folder and type :

```
cmake ..
```

Then, type :

```
make
```

You can also create the doxygen documentation by typing :
```
make doc 
```

### Simulation

You can launch the program by tiping in the build repository : 

```
./Neuro
```

After that, you have to enter the duration of the simulation and... let's go !

To plot the results, you may open a [Jupyter](https://try.jupyter.org/) notebook. You upload the data.txt file, paste into a Python 3 notebook the content of the Jupyter file. Then you run it... It's ok!

You can change the parameters of the simulation in the file /Src/Constants.h (by default, g=5 and ETA = 2)


## Running the tests

There are some unit tests made with GoogleTest

### How to launch it 

Go to the build folder and type : 

```
cmake ..
```

Then, type :

```
make
```

And, to launch it, type :

```
./UnitTest
```



## Authors

* **Romain GROS** - [RomGR](https://c4science.ch/p/RomGR/)

