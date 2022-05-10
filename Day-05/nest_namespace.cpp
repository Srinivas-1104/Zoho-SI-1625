//  The <iostream> header for using the stream objects.
#include <iostream>

//  The "nest_namespace.h" is the header file that contains the namespaces that are to be used in this file.
//  It includes the parent namespace with mathematics and its children arithmetics (normal) and logical (inline).
#include "nest_namespace.h" 

//  The namespace 'mathematics' is put into use by the 'using' directive.  It imports all the contents of the mathematics namespace and provides access to its contents.
using namespace mathematics;

//  As 'mathematics' is invoked with using directive, it is implicitly called whenever the elements of the namespace are invoked.  For ease of use, we provide the abbreviation 'nm' to the arithemtics namespace (child to mathematics.)
//  If using is not used, we need to access it as:  namespace nm = mathematics::arithmetics.
namespace nm = arithmetics;

//  A class problem is created to handle the namespace and scopes.
class problems
{
    
    public:

        //  It invokes the mathematics::arithmetics::numbers and creates an object for the class and call the calculate function.
        void arithmetic_calculator ()
        {
            nm::numbers n;
            n.calculate();
        }

        //  In this, calculate from the namespace logical is called, as it is in-line.
        void bitwise_calculator ()
        {
            calculate();
        }

};

//  The Driver Code:    Main Function
int main ()
{
    //  The class problems is instantiated.
    problems p;

    //  The function arithmetic_calculator is called.
    cout << endl << endl;
    p.arithmetic_calculator();

    //  The method bitwise_calculator is called.
    cout << endl << endl;
    p.bitwise_calculator();

    cout << endl << endl;

    //  Returns 0 on success.
    return 0;
}