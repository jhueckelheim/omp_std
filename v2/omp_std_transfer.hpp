#ifndef OMP_STD_TRANSFER
#define OMP_STD_TRANSFER
#include <stdio.h>
namespace ostd {

class transfer_container {
public:
    char* data;
    size_t size;
};

template<typename T> transfer_container pack(std::vector<T>& data) {
    transfer_container ret;
    if(std::is_trivially_copyable_v<T>) {
        ret.data = (char*)&(data[0]);
	ret.size = data.size() * sizeof(T);
    }
    else {
        // do something more complicated
    }
    return ret;
}

template<typename T> void unpack(std::vector<T> dest, transfer_container src) {
    if(std::is_trivially_copyable_v<T>) {
	// nothing to be done
    }
    else {
        // do something more complicated
    }
}

#pragma omp declare mapper(transfer_container v) map(tofrom: v.data[0:v.size], v.size)

}
#endif
