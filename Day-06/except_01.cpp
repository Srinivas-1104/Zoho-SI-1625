#include <iostream>
#include <string>

//  The <exception> header file provides a wide array of standard exceptions along with their assorted definitions in the standard namespace.  All standard exceptions can be caught by the reference.
#include <exception>

//  The std namespace is utilizied here for ease of access.
using namespace std;

/*

    try
    {
        //  The statements to be made.
        //  If the error is based on conditions, it will be thrown.
        If the error is based on actions, it will be detected automatically.
        throw _____ (error) 
    }

    The thrown object will be caught here and will be dealth with accordingly.
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

*/

class exception_handling : public exception
{
    public:

    //  The divide by zero is checked here.
        void division()
        {
            int a, b;
            cout << "\n Enter the numbers: ";
            cin >> a >> b;

            try
            {
                //  If it is 0, then runtime error is thrown.
                if (b == 0)
                    throw runtime_error("Invalid Division");
                cout << "\n The Quotient is: " << (int)(a / b);
            }

            //  the thrown exception is caught here.
            catch (const runtime_error &e)
            {
                cerr << "\n Exception Caught: \t" << e.what() << endl;
            }
        }

    //  The string index validity is checked here.
        void string_except()
        {
            string s;
            cout << "\n Enter the string: ";
            getline(cin >> ws, s);

            int id;
            cout << "\n Enter the index: ";
            cin >> id;
            try
            {
                //  Access to an invalid index is detected and caught automatically.
                char c = s.at(id);
                cout << "\n The value at that particular index: " << c;
            }
            catch (const out_of_range &e)
            {
                cerr << "\n Exception Caught: \t Invalid Index" << endl;
            }
        }

    //  The array index validity is checked here.
        void array_except()
        {
            int n, x;

            cout << "\n Enter the size of the vector: ";
            cin >> n;

            int arr[100];

            cout << "\n Enter the elements: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }

            try
            {
                cout << "\n Enter the index: ";
                cin >> x;
                
                //  The index is checked and manually thrown.
                if (x < 0 && n < x)
                    throw(0);
                    
                cout << "\n The value at the index: "<< n << endl;
            }
            catch (int a)
            {
                cerr << "\n Exception Caught: \t Invalid Index" << endl;
            }

        }

    //  The dynamic allocation is checked here.
        void heap_allocation()
        {
            try
            {
                long MEMORY_SIZE = 0x7fffffff;
                cout << "\n Creating dynamic pointer arrays";
                cout << "\n The allocated memory size: " << MEMORY_SIZE;
                int *a = new int[MEMORY_SIZE];
                cout << "\n Dynamic Allocation Successful!";
                delete[] a;
            }
            catch (const bad_alloc &e)
            {
                cerr << "\n Exception Caught: \t The Memory is Compromised." << endl;
            }
        }

    //  The format mismatch and type checking is done here.
        void typing()
        {
            try
            {
                string s;
                cout << "\n Enter the number: ";
                cin >> s;

                //  If the stoi returns invalid arguments, the value is automatically detected.
                int num = stoi(s);
                cout << "\n The number is: " << num;
            }
            catch (const invalid_argument &e)
            {
                cerr << "\n Exception Caught: \t Format Mismatch" << endl;
            }
        }

        
        // We can also perform:
        //     try
        //     {
        //         int a;
        //         cin >> a;

        //         if (cin.fail())
        //             throw (0);
        //     }
        //     catch (0)
        //         cerr << "Format Mismatch" << endl;
        
};

//  The user-defined exception.
class my_exception : public exception
{
    string s;

    public:
        //  The user-parameter is gained here.
        my_exception(string s)
        {
            this->s = s;
        }

        virtual const char * what () const throw ()
        {
            string except = "My Exception (" + s + ")";
            const char *c = except.c_str();
            cout << c;
            return "";
        }
            
};

int main()
{
    //  All the execptions are tried here for their viability.
    try
    {
        cout << endl << endl;
        exception_handling e;

        cout << endl << endl;
        e.division();

        cout << endl << endl;
        e.heap_allocation();

        cout << endl << endl;
        e.typing();

        cout << endl << endl;
        e.string_except();

        cout << endl << endl;
        e.array_except();

        cout << endl << endl;
        
        my_exception m("User-Defined-Exception");
        throw m;

        cout << endl << endl;
    }
    catch (const exception &ex)
    {
        cerr << "\n Exception Caught: \t" <<  ex.what() << endl;
    }
    //  The catch all exception.
    catch (...)
    {
        cerr << "\n Exception Caught!" << endl;
    }

    //  The final message.
    cout << "\n Exception Handling Accomplished!" << endl << endl;

    return 0;
}