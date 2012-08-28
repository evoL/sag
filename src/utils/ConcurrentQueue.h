// Original code:
// http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace sag {
    template <typename T>
	class ConcurrentQueue {
	public:
		void push(const T& elem) {
			std::unique_lock<std::mutex> lock(theMutex);
			theQueue.push(elem);
			lock.unlock();
			theConditionVariable.notify_one();
		}
		
		bool empty() const {
			std::unique_lock<std::mutex> lock(theMutex);
			bool res = theQueue.empty();
			lock.unlock();
			return res;
		}
		
		bool try_pop(T& poppedValue) {
			std::unique_lock<std::mutex> lock(theMutex);
			if (theQueue.empty()) {
				theMutex.unlock();
				return false;
			}
			poppedValue = theQueue.front();
			theQueue.pop();
			lock.unlock();
			return true;
		}
		
		void waitAndPop(T& poppedValue) {
			std::unique_lock<std::mutex> lock(theMutex);
			while (theQueue.empty())
				theConditionVariable.wait(lock);
			
			poppedValue = theQueue.front();
			theQueue.pop();
			lock.unlock();
		}
			
	private:
		std::queue<T> theQueue;
		mutable std::mutex theMutex;
		std::condition_variable theConditionVariable;
	};
}

#endif
