#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> vec({1, 2, 3, 4});

    #pragma omp target enter data map(to:vec)
    for (auto i = 0; i<4; ++i) {
        #pragma omp target enter data map(to: vec[i])
    }
    #pragma omp target teams distribute parallel for simd
    for (auto i = 0; i < 4; ++i) {
        vec[i] *= 2;
    }
    for (auto i = 0; i<4; ++i) {
        #pragma omp target exit data map(from: vec[i])
    }
    #pragma omp target exit data map(from:vec)
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        printf("%d ", *i);
    }
    printf("\n");
}

