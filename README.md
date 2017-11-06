# NeuroProject

The program allows the simulation of a 12'500 neurones network. The neurones can interact with the others and with a background (the brain).

## Presentation

### Neurone

A neurone can be inhibitory or excitatory. If it is inhibitory, it will send inhibitory spikes (to « prevent » other neurones to spike). If it is excitatory, it will send excitatory spikes (to make others neurones spike).

### Network

Contains a collection of neurones and allows their management.

### RingBuffer

Used to store the information (the spikes) coming from the neurones
connected to the neurone.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

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

