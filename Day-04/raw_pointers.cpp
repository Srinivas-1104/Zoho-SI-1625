//  A program to understand the usage of Constructors and Destructors.

//  The <iostream> header file is used for the standard input-output stream functions.
#include <iostream>

//  The <cmath> header file is used for the utilization of mathematical functions such as round, ceil or floor.
#include <cmath>

//  The standard namespace contains several utility functions for us to implement which provides us ease of access.
using namespace std;


//  The Rectangle Class holds the data necessary and provides all the basic OOPS facilities.
class Rectangle
{
    //  The private memebers of the class which cannot be accessed else where.s
    private:
        int *left, *top, *width, *height, *area = nullptr;

    public:

        //  DEFAULT CONSTRUCTOR WITH NO PARAMETERS
        Rectangle ()
        {
            left = new int(0);
            top = new int(0);
            width = new int(0);
            height = new int(0);
        }

        //  CONSTRUCTOR WITH TWO PARAMETERS (WIDTH AND HEIGHT)
        Rectangle (int w, int h)
        {   
            left = new int(0);
            top = new int(0);
            width = new int(w);
            height = new int(h);
        }

        //  CONSTRUCTOR WITH ALL PARAMETERS
        Rectangle (int l, int t, int w, int h)
        {
            left = new int(l);
            top = new int(t);
            width = new int(w);
            height = new int(h);
        }

        //  CONSTRUCTOR WITH ALL PARAMETERS: TYPE CASTED
        Rectangle (float l, float t, float w, float h)
        {
            left = new int(round(l));
            top = new int(round(t));
            width = new int(round(w));
            height = new int(round(h));
        }

        //  COPY CONSTRUCTOR
        Rectangle (Rectangle &r)
        {
            left = r.left;
            top = r.top;
            width = r.width;
            height = r.height;

            r.area = new int (*(width) * *(height));
            area = r.area;
        }

        //  UTILITY FUNCTION TO PRINT THE VALUES
        void print ()
        {
            cout << "\n THE CONTENTS OF THE RECTANGLE CLASS ARE: ";
            cout << "\n POINTER \t VALUE \t\t ADDRESS";
            cout << "\n LEFT \t\t " << *left << "\t\t " << left;      
            cout << "\n TOP \t\t " << *top << "\t\t " << top; 
            cout << "\n WIDTH  \t " << *width << "\t\t " << width; 
            cout << "\n HEIGHT \t " << *height << "\t\t " << height; 
            if (area)
                cout << "\n AREA \t\t " << *area << "\t\t " << area;
        }

        //  DESTRUCTOR
        ~ Rectangle ()
        {
            delete left;
            delete top;
            delete width;
            delete height;
            delete area;

            left = top = width = height = area = nullptr;

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