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
	template<typename T>
	class ConcurrentQueue {
	public:
		/**
		 * @brief Default constructor
		 */
		ConcurrentQueue() {}

		/**
		 * @brief Places an element at the end of the queue
		 *
		 * @param newValue The element to be placed.
		 */
		void push(T newValue) {
			std::lock_guard<std::mutex> lk(mut);
			dataQueue.push(std::move(newValue));
			dataCond.notify_one();
		}

		/**
		 * @brief Waits until the is a value to be read at the beginning of the queue and deletes it.
		 *
		 * @param value Variable where the result is to be stored.
		 */
		void waitAndPop(T& value) {
			std::unique_lock<std::mutex> lk(mut);
			dataCond.wait(lk, [this]{ return !dataQueue.empty(); });
			value = std::move(dataQueue.front());
			dataQueue.pop();
		}
		
		/**
		 * @brief Tries to read a value an the beginning of the queue and delete it.
		 *
		 * @param value Variable where the result is to be stored.
		 *
		 * @returns True if the operation succeeds.
		 */
		bool tryPop(T& value) {
			std::lock_guard<std::mutex> lk(mut);
			if (dataQueue.empty()) return false;
			value = std::move(dataQueue.front());
			dataQueue.pop();
			return true;
		}
		
		/**
		 * @brief Checks if the queue is empty
		 *
		 * @returns True if queue is empty
		 */
		bool empty() const {
			std::lock_guard<std::mutex> lk(mut);
			return dataQueue.empty();
		}
		
		/**
		 * @brief Clears queue.
		 */
		void clear() {
			std::lock_guard<std::mutex> lk(mut);
			while (!dataQueue.empty())
				dataQueue.pop();
		}

	private:
		mutable std::mutex mut;
		std::queue<T> dataQueue;
		std::condition_variable dataCond;
	};

}

#endif
