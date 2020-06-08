// compile with "clang++ chapter4.cpp"
// -> code from the book "From Mathematics to Generic Programming"
#include <iostream>
#include <string>
#define line_segment int

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
        while(b<a) {a = a-b;}
        std::swap(a,b);
    }
    return a;
}

line_segment segment_remainder(line_segment a, line_segment b){
    while(b<a) {a= a-b;}
    return a;
}

line_segment gcm(line_segment a, line_segment b){
    while(a!=b){
        a = segment_remainder(a,b);
        std::swap(a,b);
    }
    return a;
}

line_segment fast_segment_remainder(line_segment a, line_segment b){
    if(a<=b) return a;
    if(a -b<=b) return a -b;

    a = fast_segment_remainder(a,b+b);

    if ( a<=b) return a;
    return a-b;
}

line_segment fast_segment_gcm(line_segment a, line_segment b){
    while(a!=b){
        a = fast_segment_remainder(a,b);
        std::swap(a,b);
    }
    return a;
}

int main() {
    std::cout << "Chapter4" << std::endl;
    line_segment test1 = 14;
    line_segment test2 = 21;

    std::cout << "gcm0: " << std::to_string(gcm0(test1,test2)) << std::endl;
    std::cout << "gcm1: " << std::to_string(gcm1(test1,test2)) << std::endl;
    std::cout << "gcm: " << std::to_string(gcm(test1,test2)) << std::endl;
    std::cout << "gcm fast segment: " << std::to_string(fast_segment_gcm(test1,test2)) << std::endl;
}
