#include <iostream>
#include <cstring>
using namespace std;

int main ()
{
    char *line = "Hello How are You?";

    char *str = strtok(line, " ");

    while (str)
    {
        cout << str << endl;
        str = strtok(NULL, " ");
    }

    return 0;
}