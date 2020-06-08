#include<iostream> 
// compiled with "clang++ chapter2.cpp"

bool odd(int n){
    return (n%2)==1;
}

int half(int n){
    return n >> 1;
}

int multiply(int n, int a){
    if(n==1) return a;
    
    // this is a mutliply accumulate operation
    int result = multiply(half(n),a+a);
    if(odd(n)) result+=a;
    return result;
}
 
// Put r on 0, if you want the same behavior as the classical 
// multiply method. -> this fuction is tail-recursive
int mult_acc0(int r, int n,int a){ 
    if(n==1) return r + a; 
    if(odd(n)){ 
        return mult_acc0(r+a,half(n),a+a); 
    }else{
        return mult_acc0(r,half(n),a+a);
    }
}

int mult_acc1(int r, int n,int a){ 
    if(n==1) return r +a;
    if(odd(n)) r=r+a;
    return mult_acc1(r,half(n),a+a);
}

// n is rarely 1 so:
int mult_acc2(int r, int n,int a){ 
    if(odd(n)){ 
        r=r+a;
        if(n==1) return r;
    }
    return mult_acc2(r,half(n),a+a);
}

// A strictly recursive function is one in which all the tail-
// recursive calls are done with th formal parameters of the
// procedure being the corresponding arguments.
// n is rarely 1 so:
int mult_acc3(int r, int n,int a){ 
    if(odd(n)){ 
        r=r+a;
        if(n==1) return r;
    }
    n=half(n);
    a+=a;
    return mult_acc3(r,n,a);
}

// Strictly recursive functions are easily transformed into 
// iterative ones.
int mult_acc4(int r, int n,int a){ 
    while(true){
        if(odd(n)){ 
            r=r+a;
            if(n==1) return r;
        }
        n=half(n);
        a+=a;
    }
}

int main()
{
    int a=2; 
    int b=3; 
    int aTimesB=6; 

    std::cout << "mult_acc0:" << std::to_string(mult_acc0(0,a,b)) << std::endl;
    std::cout << "mult_acc1:" << std::to_string(mult_acc1(0,a,b)) << std::endl;
    std::cout << "mult_acc2:" << std::to_string(mult_acc2(0,a,b)) << std::endl;
    std::cout << "mult_acc3:" << std::to_string(mult_acc3(0,a,b)) << std::endl;
    std::cout << "mult_acc4:" << std::to_string(mult_acc4(0,a,b)) << std::endl;
}
