#include "atm_balance.h"
#include "customer_details.h"

ATM_Balance cash;
Customer_Details customers;

class ATM_Operations
{
public:
    void withdraw_money(int id, string acc)
    {
        int withdrawal, money, count = 0;
        string pin;

        cash.read_cash();
        customers.read_data();

        cout << "\n Enter the pin number: ";
        cin >> pin;

        if (customers.check_customer(acc, pin) == -1)
        {
            cout << "\n Invalid Pin Number! \n Transaction failed!";
            return;
        }

        cout << "\n The pin number has been verified!" << endl << endl;

        cout << "\n Enter the amount to be withdrawn: ";
        cin >> withdrawal;
        money = withdrawal;

        if (withdrawal > 10000 || withdrawal < 100)
        {
            cout << "\n The specified amount exceeds the limit.";            return;
        }

        else if (withdrawal > customers.c[id].amount)
        {
            cout << "\n The specified amount exceeds the account balance.";            return;
        }

        else if (withdrawal > cash.total)
        {
            cout << "\n The specified amount exceeds the balance in ATM.";            return;
        }

        else if ((withdrawal % 100 != 0 && cash.hundered != 0))
        {
            cout << "\n The specified denominations could not be given.";            return;
        }

        else if (withdrawal > 5000)
        {
            int a = cash.two_thousand;
            int b = cash.five_hundered;
            int c = cash.hundered;

            if (a > 2)
            {
                for (int i = 1; i <= a; i++)
                {
                    if (money > 2000)
                    {
                        money -= 2000;  count += 2000;
                    }
                    else
                        break;
                }

                a = a - (count / 2000);
                count = 0;

                if (a < 0)
                {
                    cout << "\n The denomination is unavailable. \t" << 2000;
                    return;
                }
            }
            else
            {
                cout << "\n The denomination is unavailable. \t" << 2000;
                return;
            }

            if (b > 2)
            {
                for (int i = 1; i <= b; i++)
                {
                    if (money >= 500)
                    {
                        money -= 500;   count += 500;
                    }
                    else
                        break;
                }

                b = b - (count / 500);
                count = 0;

                if (b < 0)
                {
                    cout << "\n The denomination is unavailable. \t" << 500;
                    return;
                }
            }
            else
            {
                cout << "\n The denomiation is unavailable. \t" << 500;
                return;
            }

            if (c >= 0)
            {
                if (money > 1000)
                {
                    cout << "\n The denomination is availing maximum condition: \t 100";
                    return;
                }
                for (int i = 1; i <= c; i++)
                {
                    if (money >= 100)
                    {
                        money -= 100;   count += 100;
                    }
                    else
                        break;
                }

                c = c - (count / 100);
                count = 0;
                if (c < 0 && money != 0)
                {
                    cout << "\n The denomination is unavailable. \t" << 100;
                    return;
                }
            }
            else
            {
                cout << "\n The denomination is unavailable. \t" << 100;
                return;
            }

            customers.c[id].amount -= withdrawal;
            customers.print_data();
            customers.write_data_withdraw(id, withdrawal);
            cout << "\n The withdrawal has been made successfully: ";
            cout << "\n 2000 \t X \t " << cash.two_thousand - a << "\t --> \t" << (2000 * (cash.two_thousand - a));
            cout << "\n 500 \t X \t " << cash.five_hundered - b << "\t --> \t" << (500 * (cash.five_hundered - b));
            cout << "\n 100 \t X \t " << cash.hundered - c << "\t --> \t" << (100 * (cash.hundered - c));
            cout << endl << endl;

            cash.set_cash(a, b, c);
        }

        else if (withdrawal >= 100)
        {
            int a = cash.two_thousand;
            int b = cash.five_hundered;
            int c = cash.hundered;

            if (a > 0)
            {
                if (money >= 3000)
                {
                    money -= 2000;  a -= 1;
                }

                if (a < 0)
                {
                    cout << "\n The denomination is unavailable. \t" << 2000;
                    return;
                }
            }
            else
            {
                cout << "\n The denomination is unavailable. \t" << 2000;
                return;
            }

            if (b > 0)
            {
                for (int i = 1; i <= b; i++)
                {
                    if (money == 1000)
                        break;

                    if (money > 500 && (money >= 1500))
                    {
                        money -= 500;   count += 500;
                    }

                    else
                        break;
                }

                b = b - (count / 500);
                count = 0;

                if (b < 0)
                {
                    cout << "\n The denomination is unavailable. \t" << 500;
                    return;
                }
            }
            else
            {
                cout << "\n The denomination is unavailable. \t" << 500;
                return;
            }

            if (c > 0)
            {
                if (money > 1500)
                {
                    cout << "\n The denomination exceeds the maximum limit. \t 100";
                    return;
                }
                for (int i = 1; i <= c; i++)
                {
                    if (money >= 100)
                    {
                        money -= 100;   count += 100;
                    }
                    else
                        break;
                }

                c = c - (count / 100);
                count = 0;
                if (c < 0 || money > 0)
                {
                    cout << "\n The denomination is unavailable. \t" << 100;
                    return;
                }
            }
            else
            {
                cout << "\n The denomination is unavailable. \t" << 100;
                return;
            }

            customers.c[id].amount -= withdrawal;
            customers.print_data();
            customers.write_data_withdraw(id, withdrawal);
            cout << "\n The withdrawal has been made successfully: ";
            cout << "\n 2000 \t X \t " << cash.two_thousand - a << "\t --> \t" << (2000 * (cash.two_thousand - a));
            cout << "\n 500 \t X \t " << cash.five_hundered - b << "\t --> \t" << (500 * (cash.five_hundered - b));
            cout << "\n 100 \t X \t " << cash.hundered - c << "\t --> \t" << (100 * (cash.hundered - c));

            cash.set_cash(a, b, c);
        }

        else
        {
            cout << "\n The amount cannot be withdrawn";
            return;
        }

        return;
    }

    void menu(int id, string acc)
    {
        int choice;
        do
        {
            cout << "\n\n\n ATM PROCESS SIMULATION: " << endl;
            cout << "\n 0. Exit \n 1. Check Balance \n 2. Withdraw Money \n 3. Transfer Money \n 4. Check ATM Balance \n 5. Mini Statement "<< endl << endl; 
            cout << "\n Enter the choice: ";
            cin >> choice;
            cout << endl << endl;

            switch (choice)
            {
                case 0:
                    cout << "Exiting...";
                    break;

                case 1:
                    cout << "\n The remaining balance is: " << customers.check_balance(id);
                    break;

                case 2:
                    withdraw_money(id, acc);
                    break;

                case 3:
                    customers.transfer_money(id);
                    break;

                case 4:
                    cash.read_cash();
                    cash.print_cash_screen();
                    break;
                
                case 5:
                    customers.mini_statement(id);
                    break;

                default:
                    cout << "\n Invalid Choice";
                    break;
            }
        } while (choice);
    }
};

int main()
{
    int choice;
    string acc_no, pin_no;
    ATM_Operations operations;

    do
    {
        cout << "\n ATM OPERATIONS: \n";
        cout << "\n 0. Exit \n 1. Load Cash into the ATM \n 2. Show Customer Details \n 3. ATM Process \n\n Enter the choice: ";
        cin >> choice;

        cout << endl << endl;

        switch (choice)
        {
            case 0:
                cout << "Exiting..." << endl << endl;
                break;

            case 1:
                cash.add_cash();
                cout << endl << endl;
                break;

            case 2:
                customers.print_data_screen();
                cout << endl << endl;
                break;

            case 3:
                {
                    cout << "\n Enter the Account Number: ";           cin >> acc_no;
                    cout << "\n Enter the Pin Number: ";               cin >> pin_no;

                    int check = customers.check_customer(acc_no, pin_no);
                    if (check != -1)
                        operations.menu(check, acc_no);
                    else
                        cout << "\n Invalid Match!";

                    cout << endl << endl;
                }
                break;

            default:
                cout << "\n Invalid Choice!"<< endl << endl;
                break;
        }
        cout << endl << endl;
    } while (choice);

    return 0;
}
