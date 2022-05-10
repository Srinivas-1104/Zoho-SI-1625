//  A program to understand the usage of Constructors and Destructors.

//  The <iostream> header file is used for the standard input-output stream functions.
#include <iostream>

//  The <cmath> header file is used for the utilization of mathematical functions such as round, ceil or floor.
#include <cmath>

//  The <memory> header file is used to provide accesss to the unique pointers.
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
            left = make_unique<int>(0);
            top = make_unique<int>(0);            
            width = make_unique<int>(0);            
            height = make_unique<int>(0);            
        }

        //  CONSTRUCTOR WITH TWO PARAMETERS (WIDTH AND HEIGHT)
        Rectangle (int w, int h)
        {   
            left = make_unique<int>(0);
            top = make_unique<int>(0);            
            width = make_unique<int>(w);            
            height = make_unique<int>(h);  
        }

        // //  CONSTRUCTOR WITH ALL PARAMETERS
        Rectangle (int l, int t, int w, int h)
        {
            left = make_unique<int>(l);
            top = make_unique<int>(t);            
            width = make_unique<int>(w);            
            height = make_unique<int>(h);  
        }

        //  CONSTRUCTOR WITH ALL PARAMETERS: TYPE CASTED
        Rectangle (double l, double t, double w, double h)
        {
            left = make_unique<int>(round(l));
            top = make_unique<int>(round(t));            
            width = make_unique<int>(round(w));            
            height = make_unique<int>(round(h));  
        }

        //COPY CONSTRUCTOR
        Rectangle (Rectangle &r)
        {

            left = make_unique<int>(*r.left);
            top = make_unique<int>(*r.top);            
            width = make_unique<int>(*r.width);            
            height = make_unique<int>(*r.height);  

            r.area = make_unique<int>(*width * *height);
            area = make_unique<int>(*r.area);
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
