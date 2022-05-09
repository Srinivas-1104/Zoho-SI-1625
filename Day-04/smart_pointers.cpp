//  A program to understand the usage of Constructors and Destructors.

//  The <iostream> header file is used for the standard input-output stream functions.
#include <iostream>

//  The <cmath> header file is used for the utilization of mathematical functions such as round, ceil or floor.
#include <cmath>

#include <memory>

//  The standard namespace contains several utility functions for us to implement which provides us ease of access.
using namespace std;


//  The Rectangle Class holds the data necessary and provides all the basic OOPS facilities.
class Rectangle
{
    //  The private memebers of the class which cannot be accessed else where.s
    private:
        unique_ptr<int> left, top, width, height, area;

    public:

        //  DEFAULT CONSTRUCTOR WITH NO PARAMETERS
        Rectangle ()
        {
            left.reset(new int(0));
            top.reset(new int(0));
            width.reset(new int(0));
            height.reset(new int(0));
            //area.reset(new int(0));
        }

        //  CONSTRUCTOR WITH TWO PARAMETERS (WIDTH AND HEIGHT)
        Rectangle (int w, int h)
        {   
            left.reset(new int(0));
            top.reset(new int(0));
            width.reset(new int(w));
            height.reset(new int(h));
            //area.reset(new int(0));
        }

        // //  CONSTRUCTOR WITH ALL PARAMETERS
        Rectangle (int l, int t, int w, int h)
        {
            left.reset(new int(l));
            top.reset(new int(t));
            width.reset(new int(w));
            height.reset(new int(h));
            //area.reset(new int(0));
        }

        //  CONSTRUCTOR WITH ALL PARAMETERS: TYPE CASTED
        Rectangle (double l, double t, double w, double h)
        {
            left.reset(new int(round(l)));
            top.reset(new int(round(t)));
            width.reset(new int(round(w)));
            height.reset(new int(round(h)));
            //area.reset(new int(0));
        }

        //COPY CONSTRUCTOR
        Rectangle (Rectangle &r)
        {
            left.reset(new int(*r.left));
            top.reset(new int(*r.top));
            width.reset(new int(*r.width));
            height.reset(new int(*r.height));
            r.area.reset(new int(*width * *height));
            area.reset (new int(*r.area));
        }

        //  UTILITY FUNCTION TO PRINT THE VALUES
        void print ()
        {
            cout << "\n THE CONTENTS OF THE RECTANGLE CLASS ARE: ";
            cout << "\n POINTER \t VALUE";
            cout << "\n LEFT \t\t " << *left;      
            cout << "\n TOP \t\t " << *top; 
            cout << "\n WIDTH  \t " << *width; 
            cout << "\n HEIGHT \t " << *height; 
            if (area)
                cout << "\n AREA \t\t " << *area;
        }

        //  DESTRUCTOR
        ~ Rectangle ()
        {
            cout << "\n THE OBJECT HAS BEEN DELETED." << endl;
        }
};

int main ()
{
    //  The Object Declaration:
    Rectangle a;
    Rectangle b(5,10);
    Rectangle c(11,12,13,14);
    Rectangle d(11.25f, 56.2f, 7785.3f, 223.2f);
    Rectangle e(c);

    cout << "\n OBJECT --> DEFAULT CONSTRUCTOR: ";
    a.print();
    cout << endl << endl;

    cout << "\n OBJECT --> PARAMETERIZED CONSTRUCTOR (WIDTH, HEIGHT): ";
    b.print();
    cout << endl << endl;

    cout << "\n OBJECT --> PARAMETERIZED CONSTRUCTOR (ALL VALUES): ";
    c.print();
    cout << endl << endl;

    cout << "\n OBJECT --> PARAMETERIZED CONSTRUCTOR (FLOAT OVERLOAD):: ";
    d.print();
    cout << endl << endl;

    cout << "\n OBJECT --> COPY CONSTRUCTOR: ";
    e.print ();
    cout << endl << endl;

    return 0;
}