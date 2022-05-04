#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	
	string line = "GeeksForGeeks is a must try";
    vector <string> tokens;
	stringstream check1(line);
	string intermediate;
	
	while(getline(check1, intermediate, ' '))
	{
		tokens.push_back(intermediate);
	}

	for(auto it: tokens)
        cout << it << endl;
}
