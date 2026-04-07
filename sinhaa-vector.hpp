#include <exception>
#include <iterator>
#ifndef SINHAA_VECTOR_H
#define SINHAA_VECTOR_H

namespace sinhaa {
    template <typename T>
    class vector {
        private:
            size_t m_length {};
            size_t m_capacity {};
            T* m_data {};
            void reallocate ();
        
        public:
            //Member Functions
            vector ();
            explicit vector (size_t count);
            vector (size_t count, const T& value);
            template <class InputIt>
            vector (InputIt first, InputIt last);
            vector (const vector& other);
            vector (vector&& other);
            vector (std::initializer_list<T> init);
            ~vector ();
            vector& operator= (const vector& other);
            vector& operator= (vector&& other);
            vector& operator= (std::initializer_list<T> ilist);

            //Element Access
            T& operator[] (size_t index);
            const T& operator[] (size_t index) const;
            T& at (size_t pos);
            const T& at (size_t pos) const;
            T* data ();
            const T* data () const;
            T& front ();
            const T& front () const;
            T& back ();
            const T& back () const;

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
            T* erase (T* pos);
            T* erase (const T* pos);
            T* erase (T* first, T* last);
            T* erase (const T* first, const T* last);
            T* insert (const T* pos, const T& value);
            T* insert (const T* pos, T&& value);
            T* insert (const T* pos, size_t count, const T& value);
            template <class InputIt>
            T* insert (const T* pos, InputIt first, InputIt last);
            T* insert (const T* pos, std::initializer_list<T> ilist);
            template <class... Args>
            T* emplace (const T* pos, Args&&... args);
            template <class... Args>
            void emplace_back (Args&&... args);
            void push_back (const T& value);
            void push_back (T&& value);
            void pop_back ();
            void resize (size_t new_capacity);
            void resize (size_t new_capacity, const T& value);
            void swap (vector& other);
    };
}

#endif