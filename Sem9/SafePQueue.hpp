#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <memory>

template <class T, class Container = std::vector<T>, class Comparator = std::less<typename Container::value_type>>
class SafePriorityQueue {
public:

	//Ctors:
	SafePriorityQueue() = default;
	SafePriorityQueue(const SafePriorityQueue& src) {
		std::lock_guard lock(src.m_mutex);
		m_pQueue = src.m_pQueue;
	}

	//Ops:
	SafePriorityQueue& operator=(const SafePriorityQueue& src) {
		std::scoped_lock(m_mutex, src.m_mutex);
		m_pQueue = src.m_pQueue;
		return this;
	}

	//Methods:
	void push(T);
	void swap(SafePriorityQueue&);

	std::shared_ptr<T> wait_and_pop();
	std::shared_ptr<T> try_pop();


	void wait_and_pop(T& value);
	bool try_pop(T& value);

	bool empty() const;
private:
	std::priority_queue<T, Container, Comparator> m_pQueue;
	std::condition_variable m_condition_variable;
	mutable std::mutex m_mutex;
};


//Methods:
template<class T, class Container, class Comparator>
void SafePriorityQueue<T, Container, Comparator>::push(T value) {
	std::lock_guard lock(m_mutex);
	m_pQueue.push(value);
	m_condition_variable.notify_one();
}

template<class T, class Container, class Comparator>
void SafePriorityQueue<T, Container, Comparator>::swap(SafePriorityQueue& other) {
	std::scoped_lock lock{ m_mutex, other.m_mutex };
	m_pQueue.swap(other.m_pQueue);
}

template<class T, class Container, class Comparator>
std::shared_ptr<T> SafePriorityQueue<T, Container, Comparator>::wait_and_pop() {
	std::unique_lock lock(m_mutex);
	m_condition_variable.wait(lock, [this] {return !m_pQueue.empty(); });
	auto result = std::make_shared<T>(m_pQueue.top());
	m_pQueue.pop();
	return result;
}

template<class T, class Container, class Comparator>
std::shared_ptr<T> SafePriorityQueue<T, Container, Comparator>::try_pop() {
	std::lock_guard lock(m_mutex);
	if (m_pQueue.empty()) {
		return std::shared_ptr<T>();
	}
	auto result = std::make_shared<T>(m_pQueue.top());
	m_pQueue.pop();
	return result;
}

template<class T, class Container, class Comparator>
bool SafePriorityQueue<T, Container, Comparator>::empty() const {
	std::lock_guard lock(m_mutex);
	return m_pQueue.empty();
}

template<class T, class Container, class Comparator>
bool SafePriorityQueue<T, Container, Comparator>::try_pop(T& value)
{
	std::lock_guard lock(m_mutex);
	if (m_pQueue.empty()) {
		return false;
	}
	value = m_pQueue.front();
	m_pQueue.pop();
	return true;
}

template<class T, class Container, class Comparator>
void SafePriorityQueue<T, Container, Comparator>::wait_and_pop(T& value)
{
	std::unique_lock lock(m_mutex);
	m_condition_variable.wait(lock, [this]{return !m_pQueue.empty(); });
	value = m_pQueue.front();
	m_pQueue.pop();
}
