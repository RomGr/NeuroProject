#include <iostream>
#include <vector>
#include "ringbuffer.hpp"
#include "constant.h"

RingBuffer::RingBuffer() :
			buffer_(bufferSize) {}
			

void RingBuffer::update(size_t current_index) {
	

	buffer_[current_index] = 0.0;

}


void RingBuffer::addValue(unsigned int index, double J) {
	
	//we put the value into the vector
	buffer_[index] += J;
}


double RingBuffer::valueFor(size_t current_index) const {
	
	//return the value for the current time
	return buffer_[current_index];

}




