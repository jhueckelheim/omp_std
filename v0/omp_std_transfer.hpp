#ifndef OMP_STD_TRANSFER
#define OMP_STD_TRANSFER
#include <stdio.h>
namespace ostd {

template<typename T> class transfer {
public:
    class container {
    public:
        T* data;
        size_t size;
    
        container(std::vector<T>& data) {
            if(std::is_trivially_copyable_v<T>) {
                this->data = &(data[0]);
                this->size = data.size() * sizeof(T);
            }
            else {
                // do something more complicated
            }
        }
    #pragma omp declare mapper(inout:container v) map(tofrom: v.data[0:v.size], v.size)
    };
};


//#pragma omp declare mapper(transfer_container v) map(tofrom: v.data[0:v.size], v.size)
}
#endif
