//  Importing the needed utility functions from the standard namespace 
//  std::cout --> Output Stream;    std::cin --> Input Stream;  std::endl --> Flush Stream.
using std::cout, std::cin, std::endl;

//  The namespace named mathematics
namespace mathematics
{
    //  The nested namespace ARITHMETICS
    namespace arithmetics
    {
        //  The contained class: numbers
        //  It is accessed using:   mathematics::arithmetics::numbers object_name;
        class numbers
        {
            //  The private data memebers of the class
            private:
                int a, b, c;

            //  The methods supported by the class.
            public:
                numbers();
                void add();
                void subtract();
                void multiply();
                void divide();
                void modulo();
                void calculate();
        };

        numbers::numbers()
        {
            cout << "\n Enter the numbers: ";
            cin >> a >> b;
        }

        void numbers::add()
        {
            cout << a + b;
        }

        void numbers::subtract()
        {
            cout << a - b;
        }

        void numbers::multiply()
        {
            cout << a * b;
        }

        void numbers::divide()
        {
            if (b != 0)
                cout << a / b;
            else
                cout << "Divide by Zero";
        }

        void numbers::modulo()
        {
            if (b != 0)
                cout << a % b;
            else
                cout << "Divide by Zero";
        }

        void numbers::calculate()
        {
            cout << "\n The Options are: " << endl;
            cout << "\n 1. ADD \n 2. SUBTRACT \n 3. MULTIPLY \n 4. DIVIDE \n 5. MODULO";
            cout << "\n Enter the choice: ";
            cin >> c;

            cout << "\n The Result is: ";
            switch (c)
            {
                case 1:                    add();                       break;
                case 2:                    subtract();                  break;
                case 3:                    multiply();                  break;
                case 4:                    divide();                    break;
                case 5:                    modulo();                    break;
                default:                   cout << "Invalid";           break;
            }
        }
    }

    //  The nested namespace logical which is specified as 'in-line'.
    //  The access for it will be implicit 
    inline namespace logical
    {
        //  The data memebers of the inline class.
        int a, b, c;

        //  The logical operations that can be done.
        void and_expr()
        {
            cout << (a & b);
        }

        void or_expr ()
        {
            cout << (a | b);
        }

        void exor_expr ()
        {
            cout << (a ^ b);
        }

        void not_expr()
        {
            cout << ~a << '\t' << ~b;
        }

        void calculate ()
        {
            cout << "\n Enter the numbers: ";
            cin >> a >> b;

            cout << "\n 1. AND \n 2. OR \n 3. NOT \n 4. EXOR";
            cout << "\n Enter the choice: ";
            cin >> c;

            cout << "\n The Result is: ";
            switch (c)
            {
                case 1:                    and_expr();                 break;
                case 2:                    or_expr();                  break;
                case 3:                    not_expr();                 break;
                case 4:                    exor_expr();                break;
                default:                   cout << "Invalid";          break;
            }
        }
    }

}   