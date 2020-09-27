#include<iostream>
#include<string>
#include<functional>

#define NonCommutativeAdditiveSemigroup typename
#define MultiplicativeSemiGroup typename
#define MultiplicativeMonoid typename
#define MultiplicativeGroup typename
#define Integer typename
#define Regular typename
#define SemigroupOperation typename
#define NonCommutativeAdditiveMonoid typename
#define MultiplicativeMonoid typename

template<typename T>
bool odd(T n)
{
    return (n%T{2})==T{1};
}

//template<>
//bool odd<int>(int n)
//{
//    return bool(n & 0x1);
//}

template<typename T>
T half(T n)
{
    return n/T{2};
}

//template<>
//int half<int>(int n)
//{
//    return n >> int{1};
//}

int mult_acc4(int r, int n, int a){
    while(true){
        if(odd(n)){
            r = r + a;
            if(n==1) return r;
        }
        n = half(n);
        a = a + a;
    }
}

template<NonCommutativeAdditiveSemigroup A, Integer N>
A multiply_accumulate_semigroup(A r, N n, A a){
    if(n==0) return r;
    while(true){
        if(odd(n)){
            r = r + a;
            if(n==1) return r;
        }
        n = half(n);
        a = a + a;
    }
}

template<NonCommutativeAdditiveSemigroup A, Integer N>
A multiply_semigroup(N n, A a) {
    // precondition( n > 0 )
    while(!odd(n)){
        a = a + a;
        n = half(n);
    }
    if ( n == 1 ) return a;
    return multiply_accumulate_semigroup(a, half(n-1), a + a);
}

template<NonCommutativeAdditiveSemigroup A, Integer N>
A multiply_monoid(N n, A a){
    // precondition n >= 0
    if( n==0 ) return A{0};
    return multiply_semigroup(n, a);
}

template<NonCommutativeAdditiveSemigroup A, Integer N>
A multiply_group(N n, A a){
    if ( n < 0 ){
        n = -n;
        a = -a;
    }
    return multiply_monoid(n, a);
}

template<MultiplicativeSemiGroup A, Integer N>
A power_accumulate_semigroup(A r, A a, N n){
    // precondition n >= 0
    if(n==0) return r;
    while(true){
        if(odd(n)){
            r = r * a;
            if(n==1) return r;
        }
        n = half(n);
        a = a * a;
    }
}

// 
template<MultiplicativeSemiGroup A, Integer N>
A power_semigroup(A a, N n){
    // precondition n > 0
    while(!odd(n)){
        a = a * a;
        n = half(n);
    }
    if(n==1) return a;
    return power_accumulate_semigroup(a, a*a, half(n-1));
}

// monoid has entitiy
template<MultiplicativeMonoid A, Integer N>
A power_monoid(A a, N n)
{
    if(n==0) return A{1};
    return power_semigroup(a, n);
}

template<MultiplicativeGroup A>
A multiplicative_inverse(A a){
    return A{1}/a;
}

template<MultiplicativeGroup A, Integer N> 
A power_group(A a, N n){
    if( n < 0){
        n = -n;
        a = multiplicative_inverse(a);
    }
    return power_monoid(a, n);
}

template<Regular A, Integer N, SemigroupOperation Op>
// requires (Domain<Op, A>
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
    // precondition(n >= 0)
    if( n == 0 ) return r;
    while(true){
        if(odd(n)){
            r = op(r, a);
            if (n == 1) return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

template<Regular A, Integer N, SemigroupOperation Op>
A power_semigroup(A a, N n, Op op){
    while(!odd(n)){
        a = op(a,a);
        n = half(n);
    }
    if(n==1) return a;
    return power_accumulate_semigroup(a, op(a, a), half(n-1) , op);
}

template<NonCommutativeAdditiveMonoid T>
T identitiy_element(std::plus<T>) { return T(0);}

template<MultiplicativeMonoid T>
T identitiy_element(std::multiply<T>) { return T(1);}

int main()
{
    auto resAcc = multiply_accumulate_semigroup(0, 5 , 9);
    std::cout << "5 * 9 = " << std::to_string(resAcc) << std::endl;

    auto resPower = power_accumulate_semigroup(int{1}, int{2} , int{4});
    std::cout << "2 ** 4 = " << std::to_string(resPower) << std::endl;
}
