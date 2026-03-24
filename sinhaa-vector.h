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
        
        public:
            vector<T> ();
            ~vector ();
            T& operator[] (int index);

            std::size_t size() const;
            std::size_t max_size() const;
            void resize (size_t new_capacity);
            void resize (size_t new_capacity, T value);
            size_t capacity () const;
            bool empty () const;
            void reserve (size_t min_capacity);
            void shrink_to_fit ();


            void push_back (int value);
            void reallocate ();
    };
}

#endif