#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print (vector<int> &v)
{
    for (auto it: v)
        cout << it << " ";
    cout << endl;
}

int main ()
{
    //  Initialize the taken vector.
    vector<int> v {1, 2, 3, 2, 5, 2, 6, 2, 4, 8};

    //  Print it.
    print (v);

    //  Remove the duplicate twos.
    const auto new_end (remove(begin(v), end(v), 2));
    v.erase(new_end, end(v));
    print (v);

    /*

    1.  When removing items from the middle of the vector, they need to be removed and erased.

        const auto new_end (remove(begin(v), end(v), 2))

        begin() and end() --> Returns us the iterators that point to the first item and past the last item of the vector.

        Feeding them to the remove function with 2, makes us iterate over the vector and remove the 2 while preserving the order of items.

        Then erase --> vector will not consider new_end to end.  It is considered smaller now.  The old items which are now out of the range are still in memory.

    */

    const auto odd ([](int i) { return i % 2 != 0; });
    v.erase(remove_if(begin(v), end(v), odd), end(v));

   /*
        A predicate function is defined using remove_if.  
   */

    print (v);

    v.shrink_to_fit();
    /*
        In-order to make the vector occupy only their size, we call the shrink_to_fit function.
    */


    print (v);


    return 0;
}