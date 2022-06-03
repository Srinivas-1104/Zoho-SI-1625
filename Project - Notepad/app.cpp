#include "User_Portal.h"
#include "Project_Portal.h"

class Notepad
{
    User_Portal up;
    Project_Portal pp;
public:
    void menu_user_portal()
    {
        int choice;
        do
        {
            up.clrscr();

            cout << "\n WELCOME TO THE LOG-IN PORTAL: \n\n\n";
            cout << "\n 0.  Exit \n\n 1. Sign In \n\n 2. Sign Up \n\n";
            cout << "\n Enter the choice: ";
            cin >> choice;

            switch (choice)
            {
            case 0:
                cout << "\n Exiting the system... \n Goodbye! " << endl;
                cin.get();
                up.clrscr();
                exit(0);
                break;

            case 1:
            {
                string index = up.signing_in();

                if (index == "NOT FOUND")
                {
                    cout << "\n The user does not exist." << endl;
                    cin.get();
                    up.signing_up();
                }

                else if (index == "PASSWORD INVALID")
                {
                    cout << "\n The password is invalid." << endl;
                    cin.get();
                    break;
                }

                else
                {
                    cout << "\n The user has been signed in successfully." << endl;
                    cin.get();
                    pp.main_screen(index);
                }

                break;
            }

            case 2:
                up.signing_up();
                break;

            default:
                cout << "\n Invalid Choice!" << endl;
                break;
            }
        } while (choice);
    }
};

int main()
{
    Notepad note;

    note.menu_user_portal();

    return EXIT_SUCCESS;
}