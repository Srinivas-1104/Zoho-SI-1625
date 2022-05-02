#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

template <typename T>
void print (vector<T> &v)
{
    for (auto it: v)
        cout << it << "\t";
    cout << endl;
}


void insert_sorted(vector<string> &v, const string &word)
{
    const auto insert_pos (lower_bound(begin(v), end(v), word));
    v.insert(insert_pos, word);
}

int main ()
{
    vector<string> v {"some", "random", "words", "without", "order", "aaa", "yyy"};

    print (v);

    assert (false == is_sorted (begin(v), end(v)));
    sort (begin(v), end(v));
    assert (true == is_sorted (begin(v), end(v)));

    print (v);

    insert_sorted (v, "foobar");
    print (v);
    
    insert_sorted (v, "zzz");
    print (v);

    return 0;
}