#include <iostream>
using namespace std;

// declaring_a_union.cpp
union RecordType // Declare a simple union type
{
    char ch;
    int i;
    long l;
    float f;
    double d;
    int *int_ptr;

    void print ()
    {
        cout << ch << '\t' << i << '\t' << l << '\t' << f << '\t' << d << '\t' << *int_ptr;
    }
};

int main()
{
    RecordType t;
    
    t.i = 5;   
    t.print();

    t.f = 7.25; 
    t.print();
    
    return 0;
}