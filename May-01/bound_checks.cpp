#include <iostream>
#include <vector>

using namespace std;

int main ()
{
    const size_t container_size {1000};
    vector<int> v (container_size, 100);

    //  Out of bound referreed by [] methods.
    cout << "Out of range element value: " << v[container_size + 10] << '\n';

    //  Out of bound referred by at methods.
    cout << "Out of range element value: " << v.at(container_size + 10) << '\n';


    return 0;
}