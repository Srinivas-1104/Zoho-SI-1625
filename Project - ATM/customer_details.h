#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

class Customer
{
    public:
        string account_number;
        string account_holder;
        string pin_number;
        float amount;

        Customer () {}
        Customer (string ano, string aho, string pin, float amo)
        {
            account_number = ano;
            account_holder = aho;
            pin_number = pin;
            amount = amo;
        }
};

class Customer_Details
{
    public:
        vector<Customer> c;

        bool is_empty(std::ifstream& pFile)
        {
            return pFile.peek() == std::ifstream::traits_type::eof();
        }

        void read_data ()
        {
            c.clear();
            ifstream file;
            file.open("customer.txt");

            if (is_empty(file))
            {
                cout << "\n The customer details is empty: ";
                cout << "\n Please add a customer to process the state";
            }

            else
            {
                string ch;
                for (int i = 0; i < 10; i++)
                    file >> ch;

                while (1)
                {
                    if (file.eof())
                        break;
                    
                    string ano, aho, pin;   float no;

                    file >> ano;
                    file >> aho;
                    file >> pin;
                    file >> ch;
                    no = stof(ch);

                    Customer cust (ano, aho, pin, no);
                    c.push_back(cust);
                }          
            }
        }

        void print_data ()
        {
            ofstream file;
            file.open("customer.txt");

            file << "Customer Details" << endl;
            file << "Account Number \t\t Account Holder \t\t Pin Number \t\t Account Balance" << endl;

            for (int i = 0; i < c.size(); i++)
            {
                file << c[i].account_number << "\t\t\t\t\t\t" << c[i].account_holder << "\t\t\t\t" << c[i].pin_number << "\t\t\t\t\t" << c[i].amount << endl;
            }

        }

        void print_data_screen ()
        {
            read_data();

            cout << "Customer Details" << endl;
            cout << "Account Number \t\t Account Holder \t\t Pin Number \t\t Account Balance" << endl;
            for (int i = 0; i < c.size(); i++)
            {
                cout << c[i].account_number << "\t\t" << c[i].account_holder << "\t\t" << c[i].pin_number << "\t\t" << c[i].amount << endl;
            }

            cout << "\n printed.";

        }

        // void add_customer ()
        // {
        //     read_data();

        //     int n;
        //     cout << "\n Enter the number of customers: ";
        //     cin >> n;
        //     for (int i = 0; i < n; i++)
        //     {
        //         string ano, aho, pin;   float amo;
        //         cout << "\n Enter the account number: ";
        //         cin >> ano;
        //         cout << "\n Enter the account holder: ";
        //         cin >> aho;
        //         cout << "\n Enter the pin number: ";
        //         cin >> pin;
        //         cout << "\n Enter the amount: ";
        //         cin >> amo;

        //         Customer cust (ano, aho, pin, amo);
        //         c.push_back(cust);
        //     }

        //     print_data();
        // }

        int check_customer (string acc_no, string pin_no)
        {
            read_data();
            for (int i = 0; i < c.size(); i++)
            {
                if (c[i].account_number == acc_no && c[i].pin_number == pin_no)
                    return i;
            }

            return -1;
        }

        int check_balance (int id)
        {
            read_data();
            return c[id].amount;
        }

        bool transfer_money (int id_01)
        {
            int id_02 = -1;
            float amt;

            read_data();

            string acc;
            cout << "\n Enter the target account number: ";
            cin >> acc;

            if (acc != c[id_01].account_number)
            {
                for (int i = 0; i < c.size(); i++)
                {
                    if (acc == c[i].account_number)
                        id_02 = i;
                }
            }

            if (id_02 == -1)
            {
                cout << "\n The target account does not exist.";
                cout << "\n The transaction does not happen.";
                return false;
            }

            if (id_02 != -1)
            {
                cout << "\n Enter the amount to be transferred: ";
                cin >> amt;

                if (amt > 10000 || amt < 1000)
                {
                    cout << "\n The amount to be transferred is not within the limit.";
                    cout << "\n The transaction is failed.";
                    return false;
                }

                if (amt < c[id_01].amount)
                {
                    cout << "\n The fund transfer is initiated.";

                    c[id_02].amount += amt;
                    c[id_01].amount -= amt;

                    cout << "\n The fund transfer is completed.";                    
                    print_data();

                    return true;
                }

                else
                {
                    cout << "\n The transfer cannot be initiated.";
                    cout << "\n Insufficient Funds.";
                    return false;
                }
            }            
            return false;
        }
};