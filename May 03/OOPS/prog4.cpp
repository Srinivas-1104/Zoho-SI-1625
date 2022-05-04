#include <iostream>
using namespace std;

class Point
{
    friend void ChangePrivate(Point &);

    public:
        Point(void) : m_i(0) {}
        void PrintPrivate(void) 
        { 
            cout << m_i << endl; 
        }

    private:
        int m_i;
};

void ChangePrivate(Point &i) 
{ 
    i.m_i++; 
}

int main()
{
    Point sPoint;
    sPoint.PrintPrivate();
    ChangePrivate(sPoint);
    sPoint.PrintPrivate();
}