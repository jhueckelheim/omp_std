#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> vec({1, 2, 3, 4});

    #pragma omp target teams map(iterator(i=0:vec.size()), tofrom: vec, vec[i])
    {
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

