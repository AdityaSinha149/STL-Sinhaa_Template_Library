#include <exception>
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
            vector<T> ();
            ~vector ();
            vector& operator= (const vector& x);

            T& operator[] (int index);
            T& at (size_t pos);
            T* data ();
            T& front();
            T& back ();

            bool empty () const;
            std::size_t size () const;
            std::size_t max_size () const;
            void reserve (size_t min_capacity);
            std::size_t capacity () const;
            void shrink_to_fit ();

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