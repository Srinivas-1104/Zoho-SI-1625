#include <iostream>
#include <string>
using namespace std;

class dog
{
    private:
        string name;
        int size, legs;
        bool bark;

    public:
        dog()
        {
            legs = 4;
            bark = true;
        }

        void set (string name, int size)
        {
            this->name = name;
            this->size = size;
        }

        void get ()
        {
            cout << name << '\t' << size << '\t' << legs << '\t' << bark;
        }
};

int main ()
{
    dog d;
    d.set ("Sri", 15);
    d.get();

    return 0;
}