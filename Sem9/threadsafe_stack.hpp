#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <stdexcept>

template < typename T >
class Threadsafe_Stack
{
public:

	Threadsafe_Stack() = default;

	Threadsafe_Stack(const Threadsafe_Stack & other)
	{
		std::lock_guard < std::mutex > lock(other.m_mutex);
		m_data = other.m_data;
	}

	Threadsafe_Stack& operator=(const Threadsafe_Stack &) = delete;

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_data.push(value);
	}

	std::shared_ptr < T > pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			throw std::range_error("empty stack");
		}

		const auto result = std::make_shared < T > (m_data.top());
		m_data.pop();

		return result;
	}

	void pop(T & value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			throw std::range_error("empty stack");
		}

		value = m_data.top();
		m_data.pop();
	}

	void wait_and_pop(T& value)
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_data.empty(); });
		value = m_data.top();
		m_data.pop();
	}

	std::shared_ptr < T > wait_and_pop()
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_data.empty(); });
		auto result = std::make_shared < T >(m_data.top());
		m_data.pop();

		return result;
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_data.empty();
	}

private:

	std::stack < T > m_data;

private:

	std::condition_variable m_condition_variable;
	mutable std::mutex m_mutex;
};
