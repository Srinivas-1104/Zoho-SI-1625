#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename A>
inline const char *get_type_name(A)
{
    return typeid(A).name();
}

class Directory
{
public:
    string type;
    string number;
    float amount;

    void add_entry(string t, string no, float amt)
    {
        type = string(t);
        number = no;
        amount = amt;
    }

    void print()
    {
        cout << '\t' << number << '\t' << amount;
    }
};

vector<Directory> d;

class Mobile_Connection
{
public:
    string number;
    float amount;

    bool Add_Connection(string no)
    {
        if (no.size() != 10)
        {
            cout << "\n The phone number is not of the given size.";
            return false;
        }

        else
        {
            number = no;
            amount = 0;
            return true;
        }
    }

    void bill_updation(int i)
    {
        cout << "\n Enter the amount: ";
        cin >> amount;

        d[i].amount += amount;
    }

    void bill_payment(int i)
    {
        cout << "\n Enter the amount: ";
        cin >> amount;

        if (amount == d[i].amount)
        {
            d[i].amount = 0;
            cout << "\n The amount has been paid off.";
            cout << "\n The current balance: " << d[i].amount;
        }

        else if (amount > d[i].amount)
        {
            amount -= d[i].amount;
            d[i].amount = 0;
            cout << "\n The excess amount is paid off: " << amount;
        }

        else
        {
            d[i].amount -= amount;
            cout << "\n The remaining amount to be paid is: " << d[i].amount;
        }
    }
};

class LandLine_Connection
{
public:
    string code;
    string number;
    float amount;

    bool Add_Connection(string no)
    {
        if (no.size() < 7)
        {
            cout << "\n The landline number is not of the given size.";
            return false;
        }

        else
        {
            int l = no.size() - 6;
            code = no.substr(0, l);
            number = no.substr(l);
            amount = 0;
            return true;
        }
    }

    void bill_updation(int i)
    {
        cout << "\n Enter the amount: ";
        cin >> amount;

        d[i].amount += amount;
    }

    void bill_payment(int i)
    {
        cout << "\n Enter the amount: ";
        cin >> amount;

        if (amount == d[i].amount)
        {
            d[i].amount = 0;
            cout << "\n The amount has been paid off.";
            cout << "\n The current balance: " << d[i].amount;
        }

        else if (amount > d[i].amount)
        {
            amount -= d[i].amount;
            d[i].amount = 0;
            cout << "\n The excess amount is paid off: " << amount;
        }

        else
        {
            d[i].amount -= amount;
            cout << "\n The remaining amount to be paid is: " << d[i].amount;
        }
    }
};

template <class T>
class Bill_Processing
{
public:
    T m;

    bool is_number (string s)
    {
        for (auto it: s)
        {
            if (isdigit(it) == 0)
                return false;
        }

        return true;
    }

    void add_connection()
    {
        string id;
        cout << "\n Enter the number: ";
        cin >> id;

        if (is_number(id) == true)
        {
            if (m.Add_Connection(id) == true)
            {
                cout << "\n The connection has been added.";
                Directory dir;
                dir.add_entry(get_type_name(m), id, 0);
                d.push_back(dir);
            }

            else
                cout << "\n The connection has not been added.";
        }

        else
            cout << "\n The number is invalid.";

    }

    void bill_updation(string number, int id)
    {
        m.bill_updation(id);
    }

    void bill_payment(string no, int id)
    {
        m.bill_payment(id);
    }

    void print_contents()
    {
        for (int i = 0; i < d.size(); i++)
        {
            if (d[i].type == get_type_name(m))
                d[i].print();
        }
    }
};

int main()
{

    Bill_Processing<Mobile_Connection> mc;
    Bill_Processing<LandLine_Connection> lc;

    do
    {
        string value = "", number;
        float amt;
        int choice;

        cout << "\n\n";
        cout << "\n TELECOMMUNICATIONS SYSTEM: ";

        cout << "\n 0. \t EXIT \n 1. \t ADD MOBILE CONNECTION \n 2. \t ADD LANDLINE CONNECTION \n 3. \t VIEW MOBILE \n 4. \t VIEW LANDLINE \n 5. \t BILL UPDATION \n 6. \t BILL PAYMENT";

        cout << "\n\n Enter the choice: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "\n The system is exiting.";
            exit(0);

        case 1:
            mc.add_connection();
            break;

        case 2:
            lc.add_connection();
            break;

        case 3:
            mc.print_contents();
            break;

        case 4:
            lc.print_contents();
            break;

        case 5:
        {
            int id;
            cout << "\n Enter the number: ";
            cin >> number;

            for (int i = 0; i < d.size(); i++)
            {
                if (d[i].number == number)
                {
                    value = d[i].type;
                    id = i;
                    break;
                }
            }

            cout << "\n Number matched.";

            if (value == "")
            {
                cout << "\n No number match!";
                break;
            }

            if (value == "17Mobile_Connection")
                mc.bill_updation(number, id);

            if (value == "19LandLine_Connection")
                mc.bill_updation(number, id);
        }
        break;

        case 6:
        {
            int id;
            cout << "\n Enter the number: ";
            cin >> number;

            for (int i = 0; i < d.size(); i++)
            {
                if (d[i].number == number)
                {
                    value = d[i].type;
                    id = i;
                    break;
                }
            }

            cout << "\n Number matched.";

            if (value == "")
            {
                cout << "\n No number match!";
                break;
            }

            if (value == "17Mobile_Connection")
                mc.bill_payment(number, id);

            if (value == "19LandLine_Connection")
                mc.bill_payment(number, id);
        }
        break;

        default:
            cout << "\n Invalid Operation";
            break;
        }
    } while (1);

    return 0;
}
