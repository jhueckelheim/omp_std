#include <stdio.h>
#include <vector>
#include "omp_std.hpp"

/*
 * Questions:
 *  - does a constructor get called on the device for mapped items? Which one?
 *  - does OpenMP do a trivial memcopy? For each item or just the entire object?
 *  - is the destructor called? before or after the copy back to host?
 *  - can we use templates in declare mappers?
 *  - can we use function calls within expression in declare mappers?
 *  - how to avoid extra data copies into vector, do we need to modify std::vector itself?
 */

int main() {
    std::vector<int> vec({1, 2, 3, 4});
    auto trf = ostd::transfer<int>::container(vec);
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

