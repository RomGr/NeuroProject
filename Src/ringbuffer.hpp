#include <iostream>
#include <vector>

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

/*!
 * @class RingBuffer
 *
 * @brief Contains every informations of potential variation due to other neurones.
 * One vector's case represents one time step.
 */

class RingBuffer {
	
	private :
		
		/**
		*  Contains the informations about incoming spikes
		*/
		std::vector<double> buffer_;
		

	public :
		
		/**
		*  @brief  Buffer constructor.
		*/
		RingBuffer();

		/**
		*  @brief  Updates the buffer : we make the ring turn and we
		*  increment the local clock.
		*
		*  @param current_index 	The current index, its value should be replaced by 0.
		*/
		void update(size_t current_index);

		/**
		*  @brief  Add a new value at time t.
		*
		*  @param index			The index of the incoming spike.
		*  @param J				Weight of the connection.
		*/
		void addValue(unsigned int index, double J);

		/**
		*  @brief  Returns the value of incoming spikes for the current time.
		*
		*  @param current_index		The index that we want the value for.
		*/
		double valueFor(size_t current_index) const;
}; 

#endif
