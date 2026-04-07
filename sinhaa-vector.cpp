#include <limits>
#include <iterator>
#include <utility>
#include "sinhaa-vector.h"



//Private Functions
template <typename T>
void sinhaa::vector<T>::reallocate ()
{
    resize(m_capacity ? m_capacity * 2 : 1);
}

//Member Functions
template <typename T>
sinhaa::vector<T>::vector ()
    : m_length {0}
    , m_capacity {0}
    , m_data {nullptr} 
{
}

template <typename T>
sinhaa::vector<T>::vector (size_t count)
    : m_length {count}
    , m_capacity {count}
    , m_data {nullptr}
{
    if (m_capacity > 0)
        m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
    for (size_t idx = 0; idx < m_length; ++idx)
        new (m_data + idx) T();
}

template <typename T>
sinhaa::vector<T>::vector (size_t count, const T& value)
    : m_length {count}
    , m_capacity {count}
    , m_data {nullptr}
{
    if (m_capacity > 0)
        m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
    for (size_t idx = 0; idx < m_capacity; ++idx)
        new (m_data + idx) T(value);
}

template <typename T>
template <class InputIt>
sinhaa::vector<T>::vector (InputIt first, InputIt last)
    : m_length {static_cast<size_t>(std::distance(first, last))}
    , m_capacity {m_length}
    , m_data {nullptr}
{
    if (m_capacity > 0)
        m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
    size_t i = 0;
    for (InputIt it = first; it != last; ++it, ++i)
        new (m_data + i) T(*it);
}

template <typename T>
sinhaa::vector<T>::vector (const sinhaa::vector<T>& other)
    : m_length {other.m_length}
    , m_capacity {other.m_capacity}
    , m_data {nullptr}
{
    if (m_capacity > 0)
        m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
    for (size_t idx = 0; idx < m_length; ++idx)
        new (m_data + idx) T(other.m_data[idx]);
}

template <typename T>
sinhaa::vector<T>::vector (sinhaa::vector<T>&& other)
    : m_length {other.m_length}
    , m_capacity {other.m_capacity}
    , m_data {other.m_data}
{
    other.m_length = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

template <typename T>
sinhaa::vector<T>::vector (std::initializer_list<T> init)
    : m_length {init.size()}
    , m_capacity {init.size()}
    , m_data {nullptr}
{
    if (m_capacity > 0)
        m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
    size_t i = 0;
    for (const T& val : init)
        new (m_data + i++) T(val);
}

template <typename T>
sinhaa::vector<T>::~vector ()
{
    for (size_t i = 0; i < m_length; ++i)
        (m_data + i)->~T();
    ::operator delete(m_data);
}

template <typename T>
sinhaa::vector<T>& sinhaa::vector<T>::operator= (const sinhaa::vector<T>& other)
{
    if (this == &other) return *this;
    for (size_t i = 0; i < m_length; ++i)
        (m_data + i)->~T();
    ::operator delete(m_data);
    m_capacity = other.m_capacity;
    m_length = other.m_length;
    m_data = nullptr;
    if (m_capacity > 0)
        m_data = static_cast<T*>(::operator new(sizeof(T) * m_capacity));
    for (size_t i = 0; i < m_length; ++i)
        new (m_data + i) T(other.m_data[i]);
    return *this;
}

template <typename T>
sinhaa::vector<T>& sinhaa::vector<T>::operator=(sinhaa::vector<T>&& other)
{
    if (this == &other) return *this;
    for (size_t i = 0; i < m_length; ++i)
        (m_data + i)->~T();
    ::operator delete(m_data);
    m_data = other.m_data;
    m_length = other.m_length;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    other.m_length = 0;
    other.m_capacity = 0;
    return *this;
}

template <typename T>
sinhaa::vector<T>& sinhaa::vector<T>::operator= (std::initializer_list<T> ilist)
{
    for (size_t i = 0; i < m_length; ++i)
        (m_data + i)->~T();
    m_length = 0;
    insert(begin(), ilist);
    return *this;
}

//Element Access
template <typename T>
T& sinhaa::vector<T>::operator[] (size_t index)
{
    if (index < 0 || index >= m_length)
        throw std::out_of_range("sinhaa::vector: index out of range");
    return m_data[index];
}

template <typename T>
const T& sinhaa::vector<T>::operator[] (size_t index) const
{
    if (index < 0 || index >= m_length)
        throw std::out_of_range("sinhaa::vector: index out of range");
    return m_data[index];
}

template <typename T>
T& sinhaa::vector<T>::at (size_t pos)
{
    if (pos >= m_length)
        throw std::out_of_range("sinhaa::vector: index out of range");
    return m_data[pos];
}

template <typename T>
const T& sinhaa::vector<T>::at (size_t pos) const
{
    if (pos >= m_length)
        throw std::out_of_range("sinhaa::vector: index out of range");
    return m_data[pos];
}

template <typename T>
T* sinhaa::vector<T>::data ()
{
    return m_data;
}

template <typename T>
const T* sinhaa::vector<T>::data () const
{
    return m_data;
}

template <typename T>
T& sinhaa::vector<T>::front ()
{
    return m_data[0];
}

template <typename T>
const T& sinhaa::vector<T>::front () const
{
    return m_data[0];
}

template <typename T>
T& sinhaa::vector<T>::back ()
{
    return m_data[m_length - 1];
}

template <typename T>
const T& sinhaa::vector<T>::back () const
{
    return m_data[m_length - 1];
}

//Iterators
template <typename T>
T* sinhaa::vector<T>::begin ()
{
    return m_data;
}

template <typename T>
const T* sinhaa::vector<T>::begin () const
{
    return m_data;
}

template <typename T>
const T* sinhaa::vector<T>::cbegin () const noexcept
{
    return m_data;
}

template <typename T>
T* sinhaa::vector<T>::end ()
{
    return m_data + m_length;
}

template <typename T>
const T* sinhaa::vector<T>::end () const
{
    return m_data + m_length;
}

template <typename T>
const T* sinhaa::vector<T>::cend () const noexcept
{
    return m_data + m_length;
}

template <typename T>
std::reverse_iterator<T*> sinhaa::vector<T>::rbegin ()
{
    return std::reverse_iterator<T*>(begin());
}

template <typename T>
const std::reverse_iterator<T*> sinhaa::vector<T>::rbegin () const
{
    return std::reverse_iterator<const T*>(begin());
}

template <typename T>
const std::reverse_iterator<T*> sinhaa::vector<T>::crbegin () const noexcept
{
    return std::reverse_iterator<const T*>(cbegin());
}

template <typename T>
std::reverse_iterator<T*> sinhaa::vector<T>::rend ()
{
    return std::reverse_iterator<T*>(end());
}

template <typename T>
const std::reverse_iterator<T*> sinhaa::vector<T>::rend () const
{
    return std::reverse_iterator<const T*>(end());

}

template <typename T>
const std::reverse_iterator<T*> sinhaa::vector<T>::crend () const noexcept
{
    return std::reverse_iterator<const T*>(cend());
}

//Capacity
template <typename T>
bool sinhaa::vector<T>::empty () const
{
    return m_length == 0;
}

template <typename T>
std::size_t sinhaa::vector<T>::size() const
{
    return m_length;
}

template <typename T>
std::size_t sinhaa::vector<T>::max_size () const
{
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template <typename T>
void sinhaa::vector<T>::reserve (size_t min_capacity)
{
    if(m_capacity < min_capacity)
        resize(min_capacity);
}

template <typename T>
size_t sinhaa::vector<T>::capacity () const
{
    return m_capacity;
}

template <typename T>
void sinhaa::vector<T>::shrink_to_fit ()
{
    resize(m_length);
}

//Modifiers
template <typename T>
void sinhaa::vector<T>::clear ()
{
    resize(0);
}

template <typename T>
T* sinhaa::vector<T>::erase (T* pos)
{
    for (T* it = pos; it != end(); it++)
        *it = *(it + 1); 
    m_length--;
    return pos;
}

template <typename T>
T* sinhaa::vector<T>::erase (const T* pos)
{
    for (T* it = pos; it != end(); it++)
        *it = *(it + 1); 
    m_length--;
    return pos;
}

template <typename T>
T* sinhaa::vector<T>::erase (T* first, T* last)
{
    for (T* it = first; it != end() - last + first; it++)
        *it = *(it + last - first); 
    m_length -= last -  first;
    return last;
}

template <typename T>
T* sinhaa::vector<T>::insert(const T* pos, const T& value)
{
    if (pos < data || pos > data + length)
        throw std::out_of_range("sinhaa::vector: index out of range");
        
    size_t index = pos - data;

    if (length == capacity)
        reallocate();

    T* non_const_pos = m_data + index;

    for (T* it = data + length; it != non_const_pos; --it)
        *it = *(it - 1);

    *non_const_pos = value;
    length++;

    return non_const_pos;
}

template <typename T>
T* sinhaa::vector<T>::insert(const T* pos, T&& value)
{
    if (pos < data || pos > data + length)
        throw std::out_of_range("sinhaa::vector: index out of range");

    size_t index = pos - data;

    if (length == capacity)
        reallocate();

    T* non_const_pos = m_data + index;

    for (T* it = data + length; it != non_const_pos; --it)
        *it = std::move(*(it - 1));

    *non_const_pos = std::move(value);
    length++;

    return non_const_pos;
}

template <typename T>
T* sinhaa::vector<T>::insert (const T *pos, size_t count, const T &value)
{
    if (pos < data || pos > data + length)
        throw std::out_of_range("sinhaa::vector: index out of range");

    size_t index = pos - data;
    
    if (length + count > capacity) 
        reserve(length + count);

    T* non_const_pos = m_data + index;

    for (T* it = data + length - 1; it != non_const_pos - 1; --it)
        *(it + count) = *it;

    for (T* it = non_const_pos; it != non_const_pos + count; ++it)
        *it = value;
    
    length += count;

    return non_const_pos;
}

template <typename T>
template <class InputIt>
T* sinhaa::vector<T>::insert (const T* pos, InputIt first, InputIt last)
{
    if (pos < data || pos > data + length)
        throw std::out_of_range("sinhaa::vector: index out of range");

    size_t index = pos - data;

    size_t count = 0;
    for (InputIt it = first; it != last; ++it)
        ++count;

    if (length + count > capacity)
        reserve(length + count);

    T* non_const_pos = m_data + index;

    for (T* it = data + length - 1; it != non_const_pos + 1; --it)
        *(it + count) = *it;

    T* dest = non_const_pos;
    for (InputIt it = first; it != last; it++, dest++)
        *dest = *it;

    length += count;

    return non_const_pos;
}

template <typename T>
T* sinhaa::vector<T>::insert (const T* pos, std::initializer_list<T> ilist)
{
    return insert(pos, ilist.begin(), ilist.end());
}

template <typename T>
template <class... Args>
T* sinhaa::vector<T>::emplace (const T* pos, Args&&... args)
{
    if (pos < m_data || pos > m_data + m_length)
        throw std::out_of_range("sinhaa::vector: index out of range");

    size_t index = pos - m_data;

    if (m_length == m_capacity)
        reallocate();

    T* non_const_pos = m_data + index;

    if (index == m_length)
    {
        new (m_data + m_length) T(std::forward<Args>(args)...);
    }
    else
    {
        new (m_data + m_length) T(std::move(m_data[m_length - 1]));

        for (size_t i = m_length - 1; i > index; --i)
        {
            m_data[i].~T();
            new (m_data + i) T(std::move(m_data[i - 1]));
        }

        m_data[index].~T();
        new (m_data + index) T(std::forward<Args>(args)...);
    }

    ++m_length;
    return non_const_pos;
}

template <typename T>
template <class... Args>
void sinhaa::vector<T>::emplace_back (Args&&... args)
{
    if (m_length == m_capacity)
        reallocate();
    new (m_data + m_length) T(std::forward<Args>(args)...);
    ++m_length;
}

template <typename T>
void sinhaa::vector<T>::push_back (const T& value)
{
    if(length == capacity) reallocate();
    m_data[m_length++] = value;
}

template <typename T>
void sinhaa::vector<T>::push_back (T&& value)
{
    if(length == capacity) reallocate();
    m_data[m_length++] = std::move(value);
}

template <typename T>
void sinhaa::vector<T>::pop_back ()
{
    if (m_length > 0) --m_length;
}

template <typename T>
void sinhaa::vector<T>::resize (size_t new_capacity)
{
    if (new_capacity == m_capacity) return;
    T* new_data = nullptr;
    if (new_capacity > 0)
        new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

    for (int i = 0; i < length; i++)
        new_data[i] = data[i];
    
    for (int i = length; i < capacity; i++)
        new_data[i] = new T();

    for (size_t i = 0; i < m_length; ++i)
        (m_data + i)->~T();
    ::operator delete(m_data);
    m_data = new_data;
    m_capacity = new_capacity;
    m_length = min_len;
}

template <typename T>
void sinhaa::vector<T>::resize (size_t new_capacity, const T& value)
{
    if (new_capacity == m_capacity) return;
    T* new_data = nullptr;
    if (new_capacity > 0)
        new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

    for (int i = 0; i < length; i++)
        new_data[i] = data[i];

    for (int i = length; i < capacity; i++)
        new_data[i] = new T(value);

    for (size_t i = 0; i < m_length; ++i)
        (m_data + i)->~T();
    ::operator delete(m_data);
    m_data = new_data;
    m_capacity = new_capacity;
    m_length = min_len;
}

template <typename T>
void sinhaa::vector<T>::swap(sinhaa::vector<T>& other)
{
    std::swap(m_data, other.m_data);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_length, other.m_length);
}