#include <iostream>
#include <vector>
using namespace std;

int main ()
{
    //  Direct Assignment
    int x1 = 10;

    // We can assign using this technique also.
    int x2 {10};    //  Matches exact constructor call.    
    int x3 (10);    //  Matches the closest constructor call.

    cout << x1 << "\t" << x2 << "\t" << x3 << endl;

    //  Similar expansion for vector.

    //  Direct Assignment
    vector<int> a = {10, 20, 30};

    //  Constructor call but reacts like direct assignment
    vector<int> b {10,20,30};

    //  The first parameter is the length and the second is the value to be filled.
    vector<int> c (10, 20);

    for (auto it: a)
        cout << it << " ";
    cout << endl;

    for (auto it: b)
        cout << it << " ";
    cout << endl;

    for (auto it: c)
        cout << it << " ";
    cout << endl;

    return 0;
}