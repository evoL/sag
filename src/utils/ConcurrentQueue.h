// Adapted from:
// http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/thread/locks.hpp>
#  include <boost/thread/mutex.hpp>
#  include <boost/thread/condition_variable.hpp>
#else
#  include <mutex>
#  include <condition_variable>
#endif

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
			THREAD_NAMESPACE::lock_guard<THREAD_NAMESPACE::mutex> lk(mut);
			dataQueue.push(std::move(newValue));
			dataCond.notify_one();
		}

		/**
		 * @brief Waits until the is a value to be read at the beginning of the queue and deletes it.
		 *
		 * @param value Variable where the result is to be stored.
		 */
		void waitAndPop(T& value) {
			THREAD_NAMESPACE::unique_lock<THREAD_NAMESPACE::mutex> lk(mut);
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
			THREAD_NAMESPACE::lock_guard<THREAD_NAMESPACE::mutex> lk(mut);
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
			THREAD_NAMESPACE::lock_guard<THREAD_NAMESPACE::mutex> lk(mut);
			return dataQueue.empty();
		}
		
		/**
		 * @brief Clears queue.
		 */
		void clear() {
			THREAD_NAMESPACE::lock_guard<THREAD_NAMESPACE::mutex> lk(mut);
			while (!dataQueue.empty())
				dataQueue.pop();
		}

	private:
		mutable THREAD_NAMESPACE::mutex mut;
		std::queue<T> dataQueue;
		THREAD_NAMESPACE::condition_variable dataCond;
	};

}

#endif
