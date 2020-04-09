#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

template <typename T, typename Comparator = std::less<typename T>>
class SafePriorityQueue
{
public:

	//Ctors:
	SafePriorityQueue() {}
	SafePriorityQueue(const Comparator&);
	SafePriorityQueue(const SafePriorityQueue&);

	//Ops:
	SafePriorityQueue& operator=(const SafePriorityQueue& src) {
		std::lock(m_mutex, src.m_mutex);
		m_pQueue = src.m_pQueue;
		return this;
	}

	//Methods:
	void push(T);
	std::shared_ptr<T> wait_and_pop();
	std::shared_ptr<T> try_pop();
	bool empty() const;
private:
	std::priority_queue<T> m_pQueue;
	std::condition_variable m_condition_variable;
	mutable std::mutex m_mutex;
};

//Ctors:
template<typename T, typename Comparator>
inline SafePriorityQueue<T, Comparator>::SafePriorityQueue(const Comparator& comparator)
	: m_pQueue(comparator) {}

template<typename T, typename Comparator>
SafePriorityQueue<T, Comparator>::SafePriorityQueue(const SafePriorityQueue& src) {
	std::lock_guard lock(src.m_mutex);
	m_pQueue = src.m_pQueue;
}

//Methods:
template<typename T, typename Comparator>
void SafePriorityQueue<T, Comparator>::push(T value) {
	std::lock_guard lock(m_mutex);
	m_pQueue.push(value);
	m_condition_variable.notify_one();
}

template<typename T, typename Comparator>
std::shared_ptr<T> SafePriorityQueue<T, Comparator>::wait_and_pop() {
	std::unique_lock lock(m_mutex);
	m_condition_variable.wait(lock, [this] {return !m_pQueue.empty(); });
	auto result = std::make_shared<T>(m_pQueue.top());
	m_pQueue.pop();
	return result;
}

template<typename T, typename Comparator>
std::shared_ptr<T> SafePriorityQueue<T, Comparator>::try_pop() {
	std::lock_guard lock(m_mutex);
	if (m_pQueue.empty()) {
		return std::shared_ptr<T>();
	}
	auto result = std::make_shared<T>(m_pQueue.top());
	m_pQueue.pop();
	return result;
}

template<typename T, typename Comparator>
bool SafePriorityQueue<T, Comparator>::empty() const {
	std::lock_guard lock(m_mutex);
	return m_pQueue.empty();
}
