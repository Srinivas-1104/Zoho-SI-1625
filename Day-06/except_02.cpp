#include <iostream>
#include <exception>
#include <string>

using namespace std;

//  When the outer exception acts first.
void case_1()
{

    try
    {
        throw "Outer Exception";

        try
        {
            throw 10;
        }
        catch (int a)
        {
            cerr << "\n Inner Exception-Handler: " << a << endl;
        }
    }
    catch (const char *s)
    {
        cerr << "\n Outer Exception-Handler: " << s << endl;
    }
}

//  When the inner exception acts first.
void case_2()
{
    try
    {
        try
        {
            throw "Inner Exception";
        }
        catch (const char *s)
        {
            cerr << "\n Inner Exception-Handler: " << s << endl;
        }
    }
    catch (const exception &ex)
    {
        cerr << "\n Outer Exception-Handler: " << ex.what() << endl;
    }
}

//  When the catch-all is used.
void case_3()
{
    try
    {
        cout << endl;

        try
        {
            throw 10;
            throw runtime_error("Catch-All");
        }
        catch (runtime_error &ex)
        {
            cerr << "\n Inner Exception-Handler: " << ex.what() << endl;
        }
    }
    catch (exception &ex)
    {
        cerr << "\n Outer Exception-Handler: " << ex.what() << endl;
    }
    catch (...)
    {
        cerr << "\n Exception-Handler: \t No such notable exception!" << endl;
    }
}

//  The caught exception is rethrown for handlement.
void case_4()
{
    try
    {
        cout << endl;

        try
        {
            throw runtime_error("Re-Throw");
        }
        catch (runtime_error &ex)
        {
            cerr << "\n Inner Exception-Handler: " << ex.what() << endl;
            throw;
        }
    }
    catch (exception &ex)
    {
        cerr << "\n Outer Exception-Handler: " << ex.what() << endl;
    }
}

int main()
{

    cout << endl << endl;

    cout << "\n CASE - 01: \t EXCEPTION OCCURS WITHIN THE OUTER TRY BLOCK" << endl;
    case_1();
    cout << endl << endl;

    cout << "\n CASE - 02: \t EXCEPTION OCCURS WITHIN THE INNER TRY BLOCK" << endl;
    case_2();
    cout << endl << endl;

    cout << "\n CASE - 03: \t NO NOTABLE EXCEPTION OCCURS";
    case_3();
    cout << endl << endl;

    cout << "\n CASE - 04: \t RE-THROWING AN ALREADY CAUGHT EXCEPTION";
    case_4();
    cout << endl << endl;

    return 0;
}