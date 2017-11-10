#include <iostream>
#include <vector>
#include "ringbuffer.hpp"
#include "constant.h"

RingBuffer::RingBuffer() :
			buffer_(bufferSize) {}
			
void RingBuffer::update(size_t current_index) {
	

	buffer_[current_index] = 0.0;

}

void RingBuffer::addValue(size_t index, double J) {
	
	// Rentrée de cette valeur dans le tableau
	buffer_[index] += J;
}

double RingBuffer::valueFor(size_t current_index) const {
	
	//return the value for the current time
	return buffer_[current_index];

}




