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

		/**
		*  Local clock
		*/
		int clock_;
	
	public :
		
		/**
		*  @brief  Buffer constructor.
		*/
		RingBuffer();

		/**
		*  @brief  Updates the buffer : we make the ring turn and we
		*  increment the local clock.
		*/
		void update();

		/**
		*  @brief  Add a new value at time t.
		*
		*  @param  time 		Incoming time.
		*  @param J				Weight of the connection.
		*/
		void addValue(int time, double J);

		/**
		*  @brief  Returns the value of incoming spikes for the current time.
		*/
		double valueFor() const;
}; 

#endif
