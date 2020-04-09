#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template <typename T, typename Comparator>
class SafePriorityQueue
{
public:

	SafePriorityQueue() = default;

	SafePriorityQueue(const Comparator&);

	SafePriorityQueue(const SafePriorityQueue& src);

	/*SafePriorityQueue& operator=(const SafePriorityQueue& src);*/

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_pQueue.push(value);
		m_condition_variable.notify_one();
	}

	void wait_and_pop(T& value)
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this]{return !m_pQueue.empty(); });
		value = m_pQueue.front();
		m_pQueue.pop();
	}

	std::shared_ptr < T > wait_and_pop()
	{
		std::unique_lock lock(m_mutex);

		m_condition_variable.wait(lock, [this]{return !m_pQueue.empty(); });
		auto result = std::make_shared(m_pQueue.front());
		m_pQueue.pop();

		return result;
	} 
	
	std::shared_ptr < T > try_pop()
	{
		std::lock_guard lock(m_mutex);

		if (m_pQueue.empty())
		{
			return std::shared_ptr < T >();
		}

		auto result = std::make_shared < T >(m_pQueue.front());
		m_pQueue.pop();

		return result;
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_pQueue.empty();
	}

private:

	std::priority_queue<T> m_pQueue;
	std::condition_variable m_condition_variable;
	mutable std::mutex m_mutex;
};

template<typename T, typename Comparator>
inline SafePriorityQueue<T, Comparator>::SafePriorityQueue(const Comparator& comparator)
	: m_pQueue(comparator) {}

template<typename T, typename Comparator>
SafePriorityQueue<T, Comparator>::SafePriorityQueue(const SafePriorityQueue& src) {
	std::lock_guard lock(src.m_mutex);
	m_pQueue = src.m_pQueue;
}

//template<typename T, typename Comparator>
//SafePriorityQueue& SafePriorityQueue<T, Comparator>::operator=(const SafePriorityQueue& src) {
//	std::lock(m_mutex, src.m_mutex);
//	m_pQueue = src.m_pQueue;
//	return this;
//}