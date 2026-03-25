#include <exception>
#include <iterator>
#ifndef SINHAA_VECTOR_H
#define SINHAA_VECTOR_H

namespace sinhaa {
    
    class out_of_bounds_error : public std::exception {
    public:
        const char* what() const noexcept override;
    };
    
    template <typename T>
    class vector {
        private:
            size_t length {};
            size_t capacity {};
            T* data {};
            void reallocate ();
        
        public:
            //Member Functions
            vector<T> ();
            ~vector ();
            vector& operator= (const vector& x);

            //Element Access
            T& operator[] (int index);
            T& at (size_t pos);
            T* data ();
            T& front();
            T& back ();

            //Iterators
            T* begin ();
            const T* begin () const;
            const T* cbegin () const noexcept;
            T* end ();
            const T* end () const;
            const T* cend () const noexcept;
            std::reverse_iterator<T*> rbegin ();
            const std::reverse_iterator<T*> rbegin () const;
            const std::reverse_iterator<T*> crbegin () const noexcept;
            std::reverse_iterator<T*> rend ();
            const std::reverse_iterator<T*> rend () const;
            const std::reverse_iterator<T*> crend () const noexcept;

            //Capacity
            bool empty () const;
            std::size_t size () const;
            std::size_t max_size () const;
            void reserve (size_t min_capacity);
            std::size_t capacity () const;
            void shrink_to_fit ();

            //Modifiers
            void clear ();
            //some impl left
            void push_back (int value);
            void pop_back ();
            void resize (size_t new_capacity);
            void resize (size_t new_capacity, T value);
            void swap (vector& other);
            
    };
}

#endif