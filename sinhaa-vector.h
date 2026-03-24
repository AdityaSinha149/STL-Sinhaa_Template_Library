#ifndef SINHAA_VECTOR_H
#define SINHAA_VECTOR_H

namespace sinhaa{
    template <typename T>
    class vector{
        private:
            int length {};
            int capacity {};
            T* data {};
        
        public:
            vector<T>();
            T& operator[](int index);
            void reallocate();
            ~vector();
            
    };
}

#endif