#include <iostream>
#include <vector>
#include "ringbuffer.hpp"
#include "constant.h"

RingBuffer::RingBuffer() :
			buffer_(bufferSize), clock_(0) {}
			
void RingBuffer::update() {
	
	for (unsigned int i(0); i < bufferSize ; ++i) {
		buffer_[i] = buffer_[i+1];
	}
		//We deplace each valor to the left
	
	buffer_.back() = 0.0;
	
	++clock_;
}

void RingBuffer::addValue(int time, double J) {
	
	// Rentrée de cette valeur dans le tableau
	buffer_[time-clock_] += J;
}

double RingBuffer::valueFor() const {
	
	//return the value for the current time
	return buffer_[0];

}




