#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> vec({1, 2, 3, 4});
    // some attempts, neither of them works

    //#pragma omp declare mapper(std::vector<int> v) map(tofrom: v[0:v.size()])
//    main.cpp:6:64: error: subscripted value is not an array or pointer
//    6 |     #pragma omp declare mapper(std::vector<int> v) map(tofrom: v[0:v.size()])
//      |                                                                ^

    //#pragma omp declare mapper(std::vector<int> v) map(tofrom: (&v[0])[0:v.size()])
//    main.cpp:11:64: error: expected addressable lvalue in 'map' clause
//       11 |     #pragma omp declare mapper(std::vector<int> v) map(tofrom: (&v[0])[0:v.size()])
//          |                                                                ^~~~~~~~~~~~~~~~~~~

    //#pragma omp declare mapper(std::vector<int> v) map(tofrom: (v.data())[0:v.size()])
//    main.cpp:18:64: error: expected addressable lvalue in 'map' clause
//       18 |     #pragma omp declare mapper(std::vector<int> v) map(tofrom: (v.data())[0:v.size()])
//          |                                                                ^~~~~~~~~~~~~~~~~~~~~~

    #pragma omp target teams map(tofrom:vec)
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

