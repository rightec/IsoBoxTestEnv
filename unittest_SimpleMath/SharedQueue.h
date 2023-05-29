#ifndef SHAREDQUEUE_H
#define SHAREDQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

/// <summary>
/// Basic Queue Class
/// Push and Pop from a Template Queue
/// </summary>
/// <typeparam name="T"></typeparam>

template<class T>
class SharedQueue
{
public:

    void push(const T &elem)
    {
        std::unique_lock<std::mutex> locker(m_mutex);

        m_queue.push(elem);

        m_cond.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> locker(m_mutex);

        m_cond.wait(locker, [&]()
        {
            return !m_queue.empty();
        });

        auto elem = m_queue.front();
        m_queue.pop();

        return elem;
    }

    
    int size() const
    {
        std::unique_lock<std::mutex> locker(m_mutex);

        return m_queue.size();
    }


    void clear()
    {
        std::unique_lock<std::mutex> locker(m_mutex);

        std::queue<T> empty;
        m_queue.swap(empty);
    }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
};

#endif // SHAREDQUEUE_H
