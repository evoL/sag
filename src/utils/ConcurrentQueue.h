// Adapted from:
// http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace sag {
    /**
     * @brief Represents normal STL queue adopted to be used with threads.
     */
	template <typename T>
	class ConcurrentQueue {
	public:
		/**
		 * @brief Places an element at the end of the queue
		 *
		 * @param elem The element to be placed.
		 */
		void push(const T& elem) {
			std::unique_lock<std::mutex> lock(theMutex);
			theQueue.push(elem);
			lock.unlock();
			theConditionVariable.notify_one();
		}
		
		/**
		 * @brief Checks if the queue is empty.
		 */
		bool empty() const {
			std::unique_lock<std::mutex> lock(theMutex);
			return theQueue.empty();
		}
		
		/**
		 * @brief Tries to read a value an the beginning of the queue and delete it.
		 *
		 * @param poppedValue Variable where the result is to be stored.
		 *
		 * @returns True if the operation succeeds.
		 */
		bool tryPop(T& poppedValue) {
			std::unique_lock<std::mutex> lock(theMutex);
			if (theQueue.empty()) {
				theMutex.unlock();
				return false;
			}
			poppedValue = theQueue.front();
			theQueue.pop();
			return true;
		}
		
		/**
		 * @brief Waits until the is a value to be read at the beginning of the queue
		 *        and deletes it.
		 *
		 * @param poppedValue Variable where the result is to be stored.
		 */
		void waitAndPop(T& poppedValue) {
			std::unique_lock<std::mutex> lock(theMutex);
			while (theQueue.empty())
				theConditionVariable.wait(lock);
			
			poppedValue = theQueue.front();
			theQueue.pop();
		}
		
		/**
		 * @brief Clears the queue.
		 */
		void clear() {
			std::unique_lock<std::mutex> lock(theMutex);
			while (!theQueue.empty()) theQueue.pop();
		}
			
	private:
		std::queue<T> theQueue;
		mutable std::mutex theMutex;
		std::condition_variable theConditionVariable;
	};
}

#endif
