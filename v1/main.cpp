#include <stdio.h>
#include <vector>
#include "omp_std.hpp"

int main() {
    std::vector<int> vec({1, 2, 3, 4});
    auto trf = ostd::pack<int>(vec);
    #pragma omp target teams map(tofrom:trf)
    {
	ostd::vector<int> vec(trf);
        #pragma omp distribute
        for (auto i = 0; i < 4; ++i) {
            vec[i] *= 2;
        }
    }
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        printf("%d ", *i);
    }
    printf("\n");
}

