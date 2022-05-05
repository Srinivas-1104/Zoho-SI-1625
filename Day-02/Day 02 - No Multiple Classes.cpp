//  The necessary input files needed for processing.
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace std;

//  The Base Class BANK:  for overarching problems.
class Bank
{
    public:
        string establish_date, bank_type, name, branch;

        //  The Abstract Methods that are to be over-riden.
        string get_establish_date() { return " "; }
        string get_bank_type() { return " "; }
        string get_name() { return " "; }
        string get_branch() { return " "; }
        void get_info() {}
};


//  The 
class Loan
{
    public:
        vector<string> loans;
        float interest;
        vector<string> documents;

        void get_available_loans () {}
        void get_documents_required () {}
        float get_interest () { return 0.0;}

};

class Organizations : public Bank, Loan
{
    public:

        //  The Broker Class is made a friend to the Organization Class to provide free access to the available ideas and objects.
        friend class Broker;

        //  Dummy Constructors
        Organizations() {}

        //  The Necessary ideas that is given to have an idea about the bank organizations.
        Organizations(int i)
        {
            int n; 
            string str;

            cout << "\n Enter the Name: "; 
            cin >> name;
            cin.ignore(1, '\n');

            cout << "\n Enter the Bank Type: "; 
            getline(cin, bank_type);

            cout << "\n Enter the Establishment Date: "; 
            getline(cin, establish_date);

            cout << "\n Enter the Branch Name: ";
            getline (cin, branch);

            cout << "\n Enter the number of loans supported: "; 
            cin >> n;
            cin.ignore(1, '\n');
            for (int i=0; i<n; i++)
            {
                getline(cin, str); 
                loans.push_back(str);
            }

            cout << "\n Enter the number of documents needed: ";
            cin >> n;
            cin.ignore(1, '\n');
            for (int i=0; i<n; i++)
            {
                getline(cin, str);
                documents.push_back(str);
            }
            
            cout << "\n Enter the Bank Interest Rate: "; cin >> interest;
            
        }

        //  Returns the name of the bank (OVER-RIDING)
        string get_name()
        {
            return name;
        }

        string get_branch()
        {
            return branch;
        }

        //  Returns the type of the bank (OVER-RIDING)
        string get_bank_type()
        {
            return bank_type;
        }

        //  Returns the date of establishment of the bank (OVER-RIDING)
        string get_establish_date()
        {
            return establish_date;
        }

                //  The Loan Methods to produce the available loan modes provided by each bank.
        void get_available_loans()
        {
            cout << "\n THE AVAILABLE LOANS ARE: " << endl;
            for (int i = 0; i < loans.size(); i++)
            {
                cout << "\n \t" << loans[i];
            }
            cout << endl;
        }

        //  The Documents that are required as a proof for your existence.
        void get_documents_required()
        {
            cout << "\n THE REQUIRED DOCUMENTS ARE: " << endl;
            for (int i = 0; i < documents.size(); i++)
            {
                cout << "\n \t" << documents[i];
            }

            cout << endl;
        }

        //  Returns the interest appointed by the bank
        float get_interest()
        {
            return interest;
        }

        //  Returns the information about the bank (OVER-RIDING)
        void get_info()
        {
            cout << "\n BANK NAME: \t" << get_name();
            cout << "\n BANK ESTABLISHMENT DATE: \t" << get_establish_date();
            cout << "\n BANK TYPE: \t" << get_bank_type();
            cout << "\n BANK BRANCH: \t" << get_branch();
            get_available_loans();
            cout << "\n INTEREST RATE: \t" << get_interest();
            get_documents_required();
        }

        //  Operator Overloading
        bool operator<(Organizations &o)
        {
            return this->interest < o.get_interest();
        }
};

class Broker
{
    public:
        //  Comparing the available three Organizations:  
        void compare(Organizations a, Organizations b, Organizations c)
        {
            float min = 999;
            string str;

            if (a.get_interest() < min)
            {
                min = a.get_interest();
                str = a.get_name();
            }

            if (b.get_interest() < min)
            {
                min = b.get_interest();
                str = b.get_name();
            }

            if (c.get_interest() < min)
            {
                min = c.get_interest();
                str = c.get_name();
            }

            cout << str << " is the bank that provides the lowest interest out of the chosen three." << endl;
        }

        //  Comparing 'n' Organizations:
        void compare(Organizations orns[], int n)
        {
            float min = 9999.00;
            int min_id = 0;

            for (int i = 0; i < n; i++)
            {
                if (orns[i].get_interest() < min)
                {
                    min = orns[i].get_interest();
                    min_id = i;
                }
            }

            cout << orns[min_id].get_name() << " is the bank that provides the lowest interest." << endl;
        }

        //  Printing 'n' Organizations
        void print(Organizations orns[], int n)
        {
            for (int i = 0; i < n; i++)
            {                
                cout << "\n BANK NUMBER - " << i+1 << endl;
                orns[i].get_info();
                cout << endl << endl;
            }
        }

        //  Printing 
        void print (Organizations orns[], int n, string name)
        {
            cout << "\n BANK DETAILS: " << name << endl;
            for (int i = 0; i < n; i++)
                if (name == orns[i].get_name())
                    orns[i].get_info();
        }
};

int main()
{
    //  Scalable to the available number of banks:
    int n;
    cout << "\n Enter the number of Organizations: ";
    cin >> n;

    //  Declaring 'n' array of objects.
    Organizations *orns = new Organizations[n];

    //  Initializing the 'n' array of objects.
    for (int i = 0; i < n; i++)
        orns[i] = Organizations(i);

    //  Instantiation the Broaker Class
    Broker ir;

    //  Printing using the broker class --> Single and Multiple Prints.
    ir.print(orns, n);
    ir.print (orns, n, "HDFC");

    //  Comaprision of 'n' available banks
    ir.compare(orns, n);

    if (n > 3)
    {
        //  Comparing only 3 objects using Function Overloding:
        ir.compare(orns[1], orns[2], orns[0]);

        //  Comparing 2 objects using Operator Overloading given by the operator '<'.
        bool temp = (orns[1] < orns[2]);
        (temp) ? cout << orns[1].get_name() : cout << orns[2].get_name();
        cout << " provides Cheaper Interest compared to ";
        (not temp) ? cout << orns[1].get_name() : cout << orns[2].get_name();
    }    

    //  Returns 0 on successful execution of the program.
    return 0;
}