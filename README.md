# omp_std

A collection of prototypes for OpenMP target offloading with C++ STD containers.


## Using the map clause directly

Each time a `std::vector` is mapped to the device, use the `map` clause on the
base pointer + range of the vector.
Currently does not work because of limitations in clang++ (?)

## Declare a mapper for std::vector externally

Provide a mapper, e.g. within `omp.h`, that uses the public interface of
`std::vector` to provide a mapper.
Currently does not work because of limitations in clang++ (?)

## Declare a mapper for std::vector internally

Modify the C++ headers to provide mappers internally. This would allow more
flexibility with how data is handled or packed during transfer.
Currently does not work because of limitations in clang++ (?)

## Use iterators in OpenMP mapper clause

## Use a wrapper type that packs and unpacks

## Use custom function hooks in OpenMP
