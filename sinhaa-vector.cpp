#include <limits>
#include "sinhaa-vector.h"

//Exeptions
const char* sinhaa::out_of_bounds_error::what () const noexcept {
    return "sinhaa::vector: index out of bounds";
}

//Private Functions
template <typename T>
void sinhaa::vector<T>::reallocate () {
    resize(capacity * 2);
}

//Member Functions
template <typename T>
sinhaa::vector<T>::vector () {
    capacity = 0;
    length = 0;
    data = nullptr;    
}

template <typename T>
sinhaa::vector<T>::~vector () {
    delete[] data;
}

template <typename T>
sinhaa::vector<T>& sinhaa::vector<T>::operator= (const sinhaa::vector<T>& x) {
    if (this == &x) return *this;
    delete[] data;
    capacity = x.capacity;
    length = x.length;
    data = new T[capacity];
    for (size_t i = 0; i < length; ++i) {
        data[i] = x.data[i];
    }
    return *this;
}

//Element Access
template <typename T>
T& sinhaa::vector<T>::operator[] (int index) {
    if (index < 0 || index >= length) {
        throw out_of_bounds_error();
    }
    return data[index];
}

template <typename T>
T& sinhaa::vector<T>::at (size_t pos) {
    if (pos < 0 || pos >= length)
        throw out_of_bounds_error();
    return data[pos];
}

template <typename T>
T* sinhaa::vector<T>::data () {
    return data;
}

template <typename T>
T& sinhaa::vector<T>::front () {
    return data[0];
}

template <typename T>
T& sinhaa::vector<T>::back () {
    return data[length];
}

//Iterators

//Capacity
template <typename T>
bool sinhaa::vector<T>::empty () const {
    return length == 0;
}

template <typename T>
std::size_t sinhaa::vector<T>::size() const {
    return length;
}

template <typename T>
std::size_t sinhaa::vector<T>::max_size () const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template <typename T>
void sinhaa::vector<T>::reserve (size_t min_capacity) {
    if(capacity < min_capacity)
        resize(min_capacity);
}

template <typename T>
size_t sinhaa::vector<T>::capacity () const {
    return capacity;
}

template <typename T>
void sinhaa::vector<T>::shrink_to_fit () {
    resize(length);
}

//Modifiers
template <typename T>
void sinhaa::vector<T>::push_back (int value) {
    if(length == capacity) reallocate();
    data[length++] = value;
}

template <typename T>
void sinhaa::vector<T>::pop_back () {
    length--;
}

template <typename T>
void sinhaa::vector<T>::resize (size_t new_capacity) {
    capacity = new_capacity;
    T* new_data = new T[capacity];

    for (int i = 0; i < length; i++)
        new_data[i] = data[i];
    
    for (int i = length; i < capacity; i++) {
        new_data[i] = new T();
    }

    delete[] data;
    data = new_data;
}

template <typename T>
void sinhaa::vector<T>::resize (size_t new_capacity, T value) {
    capacity = new_capacity;
    T* new_data = new T[capacity];

    for (int i = 0; i < length; i++)
        new_data[i] = data[i];

    for (int i = length; i < capacity; i++)
        new_data[i] = new T(value);

    delete[] data;
    data = new_data;
}

template <typename T>
void sinhaa::vector<T>::swap(sinhaa::vector<T>& other) {
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(length, other.length);
}