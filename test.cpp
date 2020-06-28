#include<iostream>



void func(int* blah);
void func2(int& blah);
int  main()
{
    const int a=1;
    int*b=NULL;
    func(&a);
    func(b);

    func2(a);
    func2(*a);
}
