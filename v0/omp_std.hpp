#ifndef OMP_STD_HPP
#define OMP_STD_HPP
/* ideas for modifiers
static const int SHALLOWCOPY = 1; // no deep copy of individual elements is needed
static const int FIXED = 2;       // container will not support insertion/deletion on device, but individual elements can still be modified.
static const int CONST = 4;       // no modification of container or its contents allowed on device
static const int COMPRESSED = 8;  // enables data compression during transfer
*/

#include "omp_std_transfer.hpp"
#include "omp_std_vector.hpp"
#endif
