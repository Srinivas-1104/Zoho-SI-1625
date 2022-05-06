//  The <iostream> header file is used for the standard input-output stream functions.
#include <iostream>

//  The <memory> header file is used to instantiate the unique_pointer (a kind of Smart Pointer) to perform dynamic memory management.
#include <memory>

using namespace std;

//  The Matrix Class forms the base for this problem.
class Matrix
{
    private:
        //  The number of rows, columns, the population, the leader and the size of the groups are instantiated.
        int row, column, population = 0, leader = 0, size = 0;

        //  The City and Visit Arrays along with a utility array is instantiated using the unique_ptrs which has unique ownership semantics.
        unique_ptr <unique_ptr<int[]>[]> city, visit, distance;
        unique_ptr <int[]> array;

    public:

        //  Dummy Constructor
        Matrix ()   {}
        
        //  The Utility Function to gather the required data.
        void get_data ()
        {
            int x = 0;

            cout << "\n Enter the number of rows: ";
            cin >> row;

            cout << "\n Enter the number of columns: ";
            cin >> column;

            city = make_unique<unique_ptr<int[]>[]> (row);
            visit = make_unique<unique_ptr<int[]>[]> (row);
            distance = make_unique<unique_ptr<int[]>[]> (row);

            cout << "\n Enter the elements of the city: " << endl;
            for (int i = 0; i < row; i++)
            {
                array = make_unique<int[]> (column);
                for (int j = 0; j < column; j++)
                {
                    cin >> x;
                    array[j] = x;
                }
                city[i] = move(array);
            }

            for (int i = 0; i < row; i++)
            {
                array = make_unique<int[]> (column);

                for (int j = 0; j < column; j++)
                    array[j] = 0;
                visit[i] = move(array);
            }
        }

        //  The Utility Function to print the values in the array.
        void print ()
        {
            cout << "\n The Matrix Values are: " << endl;
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                    cout << city[i][j] << "\t";
                cout << endl;
            }

            cout << endl << endl;
            cout << "\n The Visit Values are: " << endl;
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                    cout << visit[i][j] << "\t";
                cout << endl;
            }
        }

        //  The Helper Function that is used to calculate every available possibilities and sum up the entire population of a group.
        void conditions (int x, int y)
        {
            //  If the particular (x, y) is visited, then they can be ignored and returned.
            if (visit[x][y] == 1)
                return;

            //  Else, its value is taken into account and the neighbouring population is found out.
            else
            {
                population += city[x][y];
                if (population != 0)
                    visit[x][y] = 1;

                if (x+1 < row && city[x+1][y] != 0)
                {
                    visit[x][y] = 1;
                    conditions (x+1, y);
                }

                if (x-1 >= 0 && city[x-1][y] != 0)
                {
                    visit[x][y] = 1;
                    conditions (x-1, y);
                }

                if (y+1 < column && city[x][y+1] != 0)
                {
                    visit[x][y] = 1;
                    conditions (x, y+1);
                }

                if (y-1 >= 0 && city[x][y-1] != 0)
                {
                    visit[x][y] = 1;
                    conditions (x, y-1);
                }

                return;
            }
        }

        //  The Utility function which makes use of the traversal of the matrix to perform the required values necessary.
        void traversal ()
        {
            array = make_unique<int[]> (row * column);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    //  If that particular co-y contains a family,  we need to gather its neighbours.
                    if (city[i][j] != 0)
                    {
                        conditions(i, j);

                        //  If the neighbours are not present, ignore them.
                        if (population != 0)
                        {
                            array[size] = population;
                            size++;
                        }

                        //  Find the maxmium available of the population and mark it as LEADER.
                        leader = max(leader, population);

                        //  Make the population as ZERO to further the calculation for other nodes.
                        population = 0;
                    }
                }
            }
        }

        //  Print the values in the groups and the leader found.
        void groups ()
        {
            cout << endl << endl;
            cout << "\n The Total Number of Groups available are: \t" << size;
            cout << "\n The Maximum Population contained are: ";
            for (int i = 0; i < size; i++)
                cout << '\t' << array[i];
            cout << "\n The Leader is: " << leader;
        }

        //  The Destructor that deletes the pointers that are used in the heap memory.
        ~Matrix()
        {
            cout << endl << endl;
            cout << "\n Destructor";
            cout << "\n The memory allocated for unique pointers has been freed!";
        }
};


//  The Main Function:
int main ()
{
    //  Creating an object for the Matrix Class
    Matrix m;

    //  The data is acquired to the m object.
    m.get_data();

    //  The Traversal is done to find the groups and the leader.
    m.traversal();

    //  The object is printed directly.
    m.print();

    //  The group and the leader is printed.
    m.groups();

    //  Return 0 on successful exit.
    return 0;
}