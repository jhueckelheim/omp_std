#ifndef OMP_STD_VECTOR
#define OMP_STD_VECTOR
#include <stdio.h>

namespace ostd {
template<typename T> class vector {
private:
    T* data;
    size_t size;

public:
    vector(typename transfer<T>::container trf) {
        this->size = trf.size / sizeof(T);
	this->data = (T*)(trf.data);
    }

    // Destructor
    ~vector() {
	// to check if this gets called before or after openmp's copy
	this->data[0] = 42;
    }

    // Indexing operator
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }
};
}
#endif
