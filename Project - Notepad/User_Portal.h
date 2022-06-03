#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#include "notepad.pb.h"

using namespace std;

class User_Portal
{
public:
    void clrscr()
    {
        cout << "\033[2J\033[1;1H";
    }

    bool check_email(string email)
    {
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email, pattern);
    }

    string encrpyt_password(string password)
    {
        for (int i = 0; i < password.size(); i++)
            password[i] = (password[i] + 3) % 128;
        return password;
    }

    string validation(string un, string pwd)
    {
        string index = "NOT FOUND";

        notepad::USER_BOOK ub;
        fstream file("user_data", ios::in | ios::binary);
        if (!file)
        {
            cerr << "\n There is no file named: user_data" << endl;
            index = -1;
        }

        else if (!ub.ParseFromIstream(&file))
        {
            cerr << "\n The file cannot be parsed." << endl;
            index = -1;
        }

        else
        {
            for (int i = 0; i < ub.user_size(); i++)
            {
                const notepad::USER &u = ub.user(i);
                if (un == u.email())
                {
                    if (pwd == u.password())
                        index = u.id();
                    else
                        index = "PASSWORD INVALID";
                    break;
                }
            }
        }

        return index;
    }

    string signing_in()
    {
        string un, pwd;
        clrscr();

        cout << "\n WELCOME TO THE LOGGING - IN PORTAL: \n\n";
        cout << "\n Enter the E-Mail Address: ";
        getline(cin >> ws, un);
        if (!check_email(un))
            return "INVALID EMIAL";

        cout << "\n Enter the Password: ";
        getline(cin >> ws, pwd);

        pwd = encrpyt_password(pwd);
        return validation(un, pwd);
    }

    void input_data(notepad::USER *u)
    {
        string value, name;

        cout << "\n Enter the Name of the User: ";
        getline(cin >> ws, name);
        u->set_name(name);
        cout << "\n Enter the ID of the User: ";
        getline(cin >> ws, value);
        u->set_id(value + '_' + name);

        do
        {
            cout << "\n Enter the E-mail Address of the User: ";
            getline(cin >> ws, value);
        } while (!check_email(value));
        u->set_email(value);

        cout << "\n Enter the Password to be used: ";
        getline(cin >> ws, value);
        u->set_password(encrpyt_password(value));

        cout << "\n Enter the Location of the User: ";
        getline(cin >> ws, value);
        u->set_location(value);
    }

    void signing_up()
    {
        clrscr();

        cout << "\n WELCOME TO THE SIGNING - UP PORTAL: \n\n";
        notepad::USER_BOOK ub;
        fstream file("user_data", ios::app | ios::binary);

        if (!file)
            cerr << "\n The file is being generated" << endl;

        input_data(ub.add_user());

        if (!ub.SerializeToOstream(&file))
            cerr << "\n Failed to write to book." << endl;

        else
            cout << "\n The data has been added successfully." << endl;
    }
};
