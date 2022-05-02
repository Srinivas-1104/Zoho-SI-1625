#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
void quick_remove_at (vector<T> &v, size_t idx)
{
    if (idx < v.size()) 
    {
        v[idx] = std::move(v.back());
        v.pop_back();
    }
}

template <typename T>
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it)
{
    if (it != std::end(v)) 
    {
        *it = std::move(v.back());
        v.pop_back();
    }
}

void print (vector<int> &v)
{
    for (auto it: v)
        cout << it << " ";
    cout << endl;
}




int main ()
{
    vector<int> v {123, 456, 789, 100, 200};
    print (v);

    quick_remove_at (v, 2);
    print (v);

    quick_remove_at(v, find(begin(v), end(v), 123));
    print (v);

    return 0;
}