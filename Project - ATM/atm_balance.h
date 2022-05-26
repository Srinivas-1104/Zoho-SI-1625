#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ATM_Balance
{
public:
    int hundered, five_hundered, two_thousand;
    long total;

    void reset()
    {
        hundered = five_hundered = two_thousand = total = 0;
    }

    void add_cash()
    {
        read_cash();

        int a, b, c;
        cout << "Adding the cash: " << endl;
        cout << "\n Enter the denomination: (100): \t";     cin >> a;
        cout << "\n Enter the denomination: (500): \t";     cin >> b;
        cout << "\n Enter the denomination: (2000): \t";    cin >> c;
        cout << endl;

        hundered += a;        five_hundered += b;        two_thousand += c;
        total = (hundered * 100) + (five_hundered * 500) + (two_thousand * 2000);
        print_cash();
        cout << "\n The amount has been updated" << endl << endl;
    }

    void set_cash (int a, int b, int c)
    {
        read_cash();
        two_thousand = a;        five_hundered = b;        hundered = c;
        total = (hundered * 100) + (five_hundered * 500) + (two_thousand * 2000);
        print_cash();
    }

    void print_cash()
    {
        ofstream file;
        file.open("balance.txt");
        file << "ATM BALANCE: " << endl;
        file << "DENOMINATION \t NUMBER \t VALUES" << endl;
        file << "100 \t\t\t\t" << hundered << "\t\t\t" << hundered * 100 << endl;
        file << "500 \t\t\t\t" << five_hundered << "\t\t\t" << five_hundered * 500 << endl;
        file << "2000 \t\t\t\t" << two_thousand << "\t\t\t" << two_thousand * 2000 << endl;
        total = (hundered * 100) + (five_hundered * 500) + (two_thousand * 2000);
        file << "Total: \t\t" << total;
    }

    void print_cash_screen()
    {
        cout << "ATM BALANCE: " << endl;
        cout << "DENOMINATION \t NUMBER \t VALUES" << endl;
        cout << "100 \t\t" << hundered << "\t\t" << hundered * 100 << endl;
        cout << "500 \t\t" << five_hundered << "\t\t" << five_hundered * 500 << endl;
        cout << "2000 \t\t" << two_thousand << "\t\t" << two_thousand * 2000 << endl;
        total = (hundered * 100) + (five_hundered * 500) + (two_thousand * 2000);
        cout << "Total: \t\t" << total;
    }

    bool is_empty(ifstream &p)
    {
        return p.peek() == ifstream::traits_type::eof();
    }

    void read_cash()
    {
        ifstream file;
        file.open("balance.txt");

        if (is_empty(file))
            reset();

        else
        {
            string ch;
            for (int i = 0; i < 5; i++)
                file >> ch;

            file >> ch >> ch;
            hundered = stoi(ch);
            
            file >> ch >> ch >> ch;
            five_hundered = stoi(ch);
            
            file >> ch >> ch >> ch;
            two_thousand = stoi(ch);
            
            file >> ch >> ch >> ch;
            total = stol(ch);
        }
    }
};
