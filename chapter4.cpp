// compile with "clang++ chapter4.cpp"
// -> code from the book "From Mathematics to Generic Programming"
#include <iostream>
#include <string>
#define integer int
#define line_segment int

template <typename T>
auto half(T x) {
    return x * 0.5;
}

line_segment gcm0(line_segment a, line_segment b) {
    while (a != b) {
        if (b < a) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

line_segment gcm1(line_segment a, line_segment b) {
    while (a != b) {
        while (b < a) {
            a = a - b;
        }
        std::swap(a, b);
    }
    return a;
}

line_segment segment_remainder(line_segment a, line_segment b) {
    while (b < a) {
        a = a - b;
    }
    return a;
}

line_segment gcm(line_segment a, line_segment b) {
    while (a != b) {
        a = segment_remainder(a, b);
        std::swap(a, b);
    }
    return a;
}

line_segment fast_segment_remainder(line_segment a, line_segment b) {
    if (a <= b) return a;
    if (a - b <= b) return a - b;

    a = fast_segment_remainder(a, b + b);

    if (a <= b) return a;
    return a - b;
}

line_segment fast_segment_gcm(line_segment a, line_segment b) {
    while (a != b) {
        a = fast_segment_remainder(a, b);
        std::swap(a, b);
    }
    return a;
}

void print(int num, std::string title) {
    std::cout << title << ": " << std::to_string(num) << std::endl;
}

void printLine() {
    std::cout << "---------------------------------" << std::endl;
}

// Method with precondtion changed the <= into <
line_segment fast_segment_remainder1(line_segment a, line_segment b) {
    // precondition: b !=0
    if (a < b) return a;
    if (a - b < b) return a - b;

    a = fast_segment_remainder1(a, b + b);

    if (a < b) return a;
    return a - b;
}

line_segment largest_doubling(line_segment a, line_segment b) {
    // precondition: b != 0
    while (a - b >= b) b = b + b;
    return b;
}

// a mod b
line_segment remainder(line_segment a, line_segment b) {
    // precondition: b!=0
    if (a < b) return a;
    line_segment c = largest_doubling(a, b);
    a = a - c;
    while (c != b) {
        c = half(c);
        if (c <= a) a = a - c;
    }
    return a;
}

integer quotient(line_segment a, line_segment b) {
    // Precodition: b > 0
    if (a < b) return integer(0);
    line_segment c = largest_doubling(a, b);
    integer n(1);
    a = a - c;
    while (c != b) {
        c = half(c);
        n = n + n;
        if (c <= a) {
            a = a - c;
            n = n + 1;
        }
    }
    return n;
}

// Efficient remainder and quotient algo
std::pair<integer, line_segment> quotient_remainder(line_segment a,
                                                    line_segment b) {
    // Precodition: b > 0
    if (a < b) return {integer(0), a};
    line_segment c = largest_doubling(a, b);
    integer n(1);
    a = a - c;
    while (c != b) {
        c = half(c);
        n = n + n;
        if (c <= a) {
            a = a - c;
            n = n + 1;
        }
    }
    return {n, a};
}

// Special algo that does not use the half method.
line_segment remainder_fibonacci(line_segment a, line_segment b) {
    // Precodition: b > 0
    if (a < b) return a;
    line_segment c = b;
    do {
        line_segment tmp = c;
        c = b + c;
        b = tmp;
    } while (a >= c);
    do {
        if (a >= b) {
            a = a - b;
        }
        line_segment tmp = c - b;
        c = b;
        b = tmp;
    } while (b < c);
    return a;
}

line_segment gcm_remainder(line_segment a, line_segment b){
    while(b!=line_segment(0)){
        a = remainder(a,b);
        std::swap(a,b);
    }

    return a;
}

line_segment gcm_fastest(integer a, integer b){
    while(b!=integer(0)){
        a = a % b;
        std::swap(a,b);
    }

    return a;
}

int main() {
    std::cout << "Chapter4" << std::endl;
    line_segment test1 = 14;
    line_segment test2 = 21;

    std::cout << "gcm0: " << std::to_string(gcm0(test1, test2)) << std::endl;
    std::cout << "gcm1: " << std::to_string(gcm1(test1, test2)) << std::endl;
    std::cout << "gcm: " << std::to_string(gcm(test1, test2)) << std::endl;
    std::cout << "gcm fast segment: "
              << std::to_string(fast_segment_gcm(test1, test2)) << std::endl;

    std::cout << "gcm fast segment remainder1: " << std::to_string(test2)
              << " mod " << std::to_string(test1) << " = "
              << std::to_string(fast_segment_remainder1(test2, test1))
              << std::endl;
    std::cout << "gcm remainder: " << std::to_string(test2) << " mod "
              << std::to_string(test1) << " = "
              << std::to_string(remainder(test2, test1)) << std::endl;
    std::cout << "remainer fib remainder: " << std::to_string(test2) << " mod "
              << std::to_string(test1) << " = "
              << std::to_string(remainder_fibonacci(730, 37)) << std::endl;
    std::cout << "quotient a=" << std::to_string(test2)
              << " b=" << std::to_string(test1)
              << "   answer=" << quotient(test2, test1) << std::endl;
}
