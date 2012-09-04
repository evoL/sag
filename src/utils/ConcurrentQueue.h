// Adapted from:
// http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace sag {
	template<typename T>
	class ConcurrentQueue {
	public:
		ConcurrentQueue() {}

		void push(T newValue) {
			std::lock_guard<std::mutex> lk(mut);
			dataQueue.push(std::move(newValue));
			dataCond.notify_one();
		}

		void waitAndPop(T& value) {
			std::unique_lock<std::mutex> lk(mut);
			dataCond.wait(lk, [this]{ return !dataQueue.empty(); });
			value = std::move(dataQueue.front());
			dataQueue.pop();
		}
		
		std::shared_ptr<T> waitAndPop() {
			std::unique_lock<std::mutex> lk(mut);
			dataCond.wait(lk, [this]{ return !dataQueue.empty(); });
			std::shared_ptr<T> res(std::make_shared<T>(std::move(dataQueue.front())));
			dataQueue.pop();
			return res;
		}
		
		bool tryPop(T& value) {
			std::lock_guard<std::mutex> lk(mut);
			if (dataQueue.empty()) return false;
			value = std::move(dataQueue.front());
			dataQueue.pop();
			return true;
		}
		std::shared_ptr<T> tryPop() {
			std::lock_guard<std::mutex> lk(mut);
			if(dataQueue.empty()) return std::shared_ptr<T>();
			std::shared_ptr<T> res(std::make_shared<T>(std::move(dataQueue.front())));
			dataQueue.pop();
			return res;
		}
		
		bool empty() const {
			std::lock_guard<std::mutex> lk(mut);
			return dataQueue.empty();
		}
		
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
