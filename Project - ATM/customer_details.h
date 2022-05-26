#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

class Customer
{
    public:
        string account_number, account_holder, pin_number;
        float amount;

        Customer ()     {}

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
        int trans_no = 1001;

        bool is_empty(ifstream& pFile)
        {
            return pFile.peek() == ifstream::traits_type::eof();
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
                    
                    string ano, aho, pin;

                    file >> ano >> aho >> pin >> ch;
                    Customer cust (ano, aho, pin, stof(ch));
                    c.push_back(cust);
                }          
            }
        }

        void print_data ()
        {
            c.resize(5);
            ofstream file;
            file.open("customer.txt");

            file << "Customer Details" << endl;
            file << "Account Number \t\t Account Holder \t\t Pin Number \t\t Account Balance" << endl;

            for (int i = 0; i < c.size(); i++)
                file << c[i].account_number << "\t\t\t\t\t\t" << c[i].account_holder << "\t\t\t\t" << c[i].pin_number << "\t\t\t\t\t" << c[i].amount << endl;
        }

        void print_data_screen ()
        {
            read_data();
            cout << "Customer Details" << endl;
            cout << "Account Number \t\t Account Holder \t\t Pin Number \t\t Account Balance" << endl;
            for (int i = 0; i < 5; i++)
                cout << c[i].account_number << "\t\t" << c[i].account_holder << "\t\t" << c[i].pin_number << "\t\t" << c[i].amount << endl;
        }

        void write_data_transfer(int id_01, int id_02, int amt)
        {
            string value;
            fstream file_01, file_02;

            value = c[id_01].account_number + ".txt";
            file_01.open(value, ios::app);
            file_01 << trans_no << "\t\t" << "Transfer to " << c[id_02].account_number << "\t\t" << "Debit" << "\t\t" << amt << "\t\t" << c[id_01].amount << endl;

            value = c[id_02].account_number + ".txt";
            file_02.open(value, ios::app);
            file_02 << trans_no << "\t\t" << "Transfer from " << c[id_01].account_number << "\t\t" << "Credit" << "\t\t" << amt << "\t\t" << c[id_02].amount << endl;

            trans_no += 1;
        }

        void write_data_withdraw (int id_01, int amt)
        {
            string value = c[id_01].account_number + ".txt";
            fstream file;
            file.open(value, ios::app);
            file << trans_no << "\t\t\t" << "Withdrawal" << "\t\t" << "Debit" << "\t\t" << amt << "\t\t" << c[id_01].amount << endl;
            trans_no += 1;
        }

        int check_customer (string acc_no, string pin_no)
        {
            read_data();
            for (int i = 0; i < c.size(); i++)
                if (c[i].account_number == acc_no && c[i].pin_number == pin_no)
                    return i;
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
                    if (acc == c[i].account_number)
                        id_02 = i;
            }

            if (id_02 == -1)
            {
                cout << "\n The target account does not exist.";
                cout << "\n The transaction does not happen.";
                return false;
            }

            else
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
                    write_data_transfer(id_01, id_02, amt);

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
