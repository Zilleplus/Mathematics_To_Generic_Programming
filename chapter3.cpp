#include <iostream>
#include <string>
#include <vector>

// compile with clang++ chapter3.cpp
#define RandomAccessIterator typename
#define Integer typename

template <RandomAccessIterator I, Integer N>
void mark_sieve(I first, I last, N factor) {
    *first = false;
    while (last - first > factor) {
        first = first + factor;
        *first = false;
    }
}

// first implementation sieve
// The iterator should at least be able to interate
// N times, otherwise we get acces violation
template <RandomAccessIterator I, Integer N>
void sift0(I first, N n) {
    std::fill(first, first + n, true);
    N i(0);
    N index_square(3);
    while (index_square < n) {
        // invariant: index_square =2i^2 + 6i + 3
        if (first[i]) {
            mark_sieve(first + index_square, first + n, i + i + 3);
        }
        ++i;
        index_square = 2 * i * (i + 3) + 3;
    }
}

// first implementation sieve
// The iterator should at least be able to interate
// N times, otherwise we get acces violation
template <RandomAccessIterator I, Integer N>
void sift1(I first, N n) {
    I last = first + n;
    std::fill(first, first + n, true);
    N i(0);
    N index_square(3);
    N factor(3);
    while (index_square < n) {
        // invariant: index_square =2i^2 + 6i + 3
        //              factor = 2i+3
        if (first[i]) {
            mark_sieve(first + index_square, last, factor);
        }
        ++i;
        factor = i + i + 3;
        index_square = 2 * i * (i + 3) + 3;
    }
}

std::string bool_to_string(bool x) {
    return x ? std::string("true") : std::string("false");
}

// Print method that assumes every position
// defines if its a prime number.
template <RandomAccessIterator I, Integer N>
void print_primes(I first, N n, N step_size) {
    auto last = first + n;
    unsigned int index = 1;
    unsigned int batch_size = 10;

    while (first < last) {
        // print all the stuff in batches
        for (int j = 0; j < batch_size && first < last; j += step_size) {
            if (*first) {
                std::cout << std::to_string(index) << ", ";
            }
            index += step_size;
            first += 1;
        }
        std::cout << std::endl;
    }
}

int main() {
    const unsigned int size = 100;
    auto is_prime_number = std::vector<bool>{};
    for (int i = 0; i < size; i++) {
        is_prime_number.push_back(true);
    }
    unsigned int step_size_1 = 1;
    unsigned int step_size_2 = 2;
    // We don't use the vector explicitly here,
    // to stay generic, and not vector specific.
    // We simply need the randomAccessIterator.

    std::cout << "Chapter3: algo to find primes" << std::endl;

    std::cout << "mark_sieve with a factor of 3" << std::endl;
    std::cout << "this should remove all numbers that can be devided by 3,"
              << std::endl;
    std::cout << "such as 6,9,12,... " << std::endl;
    const unsigned int mark_sieve_test_vector_size = 100;
    auto mark_sieve_test_vector = std::vector<bool>();
    mark_sieve_test_vector.reserve(mark_sieve_test_vector_size);

    for (int i = 0; i < mark_sieve_test_vector_size; i++) {
        mark_sieve_test_vector.push_back(true);
    }
    mark_sieve(mark_sieve_test_vector.begin() + 5, mark_sieve_test_vector.end(),
               3);
    print_primes(mark_sieve_test_vector.begin(), mark_sieve_test_vector_size,
                 step_size_1);

    std::cout << std::endl << "sift0" << std::endl;
    sift0(is_prime_number.begin(), size);
    print_primes(is_prime_number.begin(), (size / step_size_1, step_size_1);

    std::cout << std::endl << "sift1" << std::endl;
    sift1(is_prime_number.begin(), size);
    print_primes(is_prime_number.begin(), size / step_size_2, step_size_2);

    std::cout << "End of program!" << std::endl << std::flush;
}
