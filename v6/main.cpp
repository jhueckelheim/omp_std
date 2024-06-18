#include <stdio.h>
#include <limits>
#include <omp.h>
#include <vector>
#include <list>

extern "C" {
  void* llvm_omp_target_alloc_shared(size_t, int);
}

template <class T>
struct Mallocator {
    typedef T value_type;

    Mallocator() = default;

    template <class U> constexpr Mallocator(const Mallocator<U>&) noexcept {}

    [[nodiscard]] T* allocate(std::size_t n) {
        if (auto p = static_cast<T*>(llvm_omp_target_alloc_shared(n * sizeof(T), omp_get_default_device()))) {
            return p;
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n) noexcept {
        omp_target_free(p, omp_get_default_device());
    }
};

int main() {
    {
        int* vec = (int*)llvm_omp_target_alloc_shared(4*sizeof(int), omp_get_default_device());
        vec[0] = 1;
        vec[1] = 2;
        vec[2] = 3;
        vec[3] = 4;

        #pragma omp target teams distribute parallel for simd
        for (auto i = 0; i < 4; ++i) {
            vec[i] *= 2;
        }

        for (auto i = 0; i < 4; ++i) {
            printf("%d ", vec[i]);
        }
        printf("\n");
        omp_target_free(vec, omp_get_default_device());
    }
    {
        std::vector<int, Mallocator<int>> vec({1, 2, 3, 4});
        #pragma omp target teams distribute parallel for simd
        for (auto i = 0; i < 4; ++i) {
            vec[i] *= 2;
        }
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            printf("%d ", *i);
        }
        printf("\n");
    }
    {
        std::list<int, Mallocator<int>> lst({1, 2, 3, 4});
        #pragma omp target teams distribute parallel for
        for (int i = 0; i != lst.size(); ++i) {
	    auto it = lst.begin();
	    for(int j = 0; j < i; ++j) ++it;
            (*it) *= 2;
        }
        for (auto i = lst.begin(); i != lst.end(); ++i) {
            printf("%d ", *i);
        }
        printf("\n");
    }
}

