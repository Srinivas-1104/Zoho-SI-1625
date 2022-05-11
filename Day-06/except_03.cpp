#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

using namespace std;

//  Age Not Within the Range Exception
class AgeNotWithinRangeException : public exception
{
public:
    virtual const char *what() const throw()
    {
        return "The age is not within the range!";
    }
};

//  Name Is Not Valid Exception
class NameNotValidException : public exception
{
public:
    virtual const char *what() const throw()
    {
        return "The name is not valid!";
    }
};

//  Invalid Course Option Exception
class InvalidCourseOption : public exception
{
public:
    virtual const char *what() const throw()
    {
        return "The course is not available!";
    }
};

//  The student class
class Student
{
    //  The data memebrs of the function are:
private:
    int roll_number, age;
    string name, course;
    vector<string> course_options{"CSE", "IT", "EEE", "ECE"};
    bool except = false;

    //  The used exceptions in this class.
    NameNotValidException invalid_name;
    AgeNotWithinRangeException invalid_age;
    InvalidCourseOption invalid_course;

public:
    //  The parameterized constructor for initializaton.
    Student(int roll_number, string name, int age, string course)
    {
        try
        {
            //  Pass the roll_number to this.
            this->roll_number = roll_number;

            //  The name is checked for its validity.
            try
            {
                if (!name_verification(name))
                {
                    except = true;
                    throw invalid_name;
                }

                //  else the name is assigned.
                this->name = name;
            }
            catch (const exception &e)
            {
                cerr << "\n Exception Caught: \t" << e.what() << endl;
            }

            try
            {
                //  If 1s5 < x < 21 is violated, invalid age condition is used.
                if (!age_verification(age))
                {
                    except = true;
                    throw invalid_age;
                }

                //  Else the age is assigned.
                this->age = age;
            }
            catch (const exception &e)
            {
                cerr << "\n Exception Caught: \t" << e.what() << endl;
            }

            try
            {
                //  The course is verified.
                if (!courses_verification(course))
                {
                    except = true;
                    throw invalid_course;
                }
                this->course = course;
            }
            catch (const exception &e)
            {
                cerr << "\n Exception Caught: \t" << e.what() << endl;
            }
        }
        catch (...)
        {
            cerr << "\n Exception Caught: \t Catch All Block" << endl;
        }
    }

    void print()
    {
        if (except == false)
        {
            cout << "\n The Student Details are: ";
            cout << "\n Roll Number: " << roll_number;
            cout << "\n Name: " << name;
            cout << "\n Age: " << age;
            cout << "\n Course: " << course;
        }
        else
        {
            cout << "\n The details need to be re-entered as they face exceptions." << endl;
        }
    }

    bool name_verification(string nm)
    {
        for (int i = 0; i < nm.size(); i++)
        {
            if (!isalpha(nm[i]))
                return false;
        }
        return true;
    }

    bool age_verification(int a)
    {
        if (15 < a && a < 21)
            return true;
        return false;
    }

    bool courses_verification(string c)
    {
        transform(c.begin(), c.end(), c.begin(), ::toupper);
        for (int i = 0; i < course_options.size(); i++)
        {
            if (course_options[i] == c)
                return true;
        }
        return false;
    }
};

//  The implementation of the parameterized constructor.

int main()
{
    int roll, age, num;
    string name, course;
    try
    {
        do
        {
            cout << "\n Enter the roll number: ";
            cin >> roll;

            cout << "\n Enter the name: ";
            getline(cin >> ws, course);

            cout << "\n Enter the age: ";
            cin >> age;

            cout << "\n Enter the course: ";
            getline(cin >> ws, course);

            Student s(roll, name, age, course);
            s.print();

            cout << "\n Do you want to continue? (1/0) \t";
            cin >> num;

            if (num == 1)
                throw num;
        } while (num);
    }
    catch (int num)
    {
            cerr << "\n The user tries to create more than one object. \n The execution is terminated." << endl;
            exit(0);
    }
    return 0;
}
