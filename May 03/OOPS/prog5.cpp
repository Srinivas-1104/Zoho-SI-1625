#include <iostream>
using namespace std;

class encap
{
    private:
        int x;

    public:
        void set (int a)
        {
            x = a;
        }

        int get ()
        {
            return x;
        }
};

int main ()
{
    encap a;
    a.set(25);
    cout << a.get();
    return 0;
}