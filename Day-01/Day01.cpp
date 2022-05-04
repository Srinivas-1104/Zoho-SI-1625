//  Importing the necessary files.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//  The Base Class: VEHICLE CLASS
//  It contains the Vehicle_Type (Petrol or Diesel or Electric or Gas Based), the Brand refers the House Company, the model refers the In-House Model Production, the color refers the outside color, mileage refers to the mileage it gives and price is its total cost.
class Vehicle
{
    protected:
        string vehicle_type, brand, model, color, type;
        float mileage, price;

    public:

        //  The Vehicle Base Class Constructor for each instance.
        Vehicle (string fuel, string brand, string model, string color, float mileage, float price)
        {
            this->vehicle_type = fuel;
            this->brand = brand;
            this->model = model;
            this->color = color;
            this->mileage = mileage;
            this->price = price;
        }

        //  Overloading the << operator to make use of the ostream for object.
        friend ostream& operator << (ostream &os, const Vehicle &c);

        //  Overloading the comparison operator to determine the price.
        friend bool operator < (const Vehicle &a, const Vehicle &b);

        //  The Virtual Function which is overrided in each function to be assigned different values.
        virtual int get_no_wheels () = 0;
};

//  The Car Class derived from the Vehicle Class
class Car : public Vehicle
{
    //  The number of persons which the car can hold and the car_type refers whether it is an SUV or a Sedan or other forms.
    private:
        int persons;
        string car_type;

    public:
        //  Car Constructor, here the base class Constructor is made use for initializing the common objects
        Car(string fuel, string brand, string model, string color, float mileage, float price, int persons, string type)    : Vehicle (fuel, brand, model, color, mileage, price)
        {
            this->type = "Car";
            this->persons = persons;
            this->car_type = type;
        }

        //  The overrided method which gives the number of wheels.
        int get_no_wheels ()
        {
            return 4;
        }
};


//  The Bike Class derived from the Vehicle Class
class Bike : public Vehicle
{
    //  The weight of the bike and bike_type whether it is a Scooter or Motor bike or other forms.
    private:
        float weight;
        string bike_type;

    public:
        //  Bike Constructor, here the base class Constructor is made use for initializing the common objects
        Bike(string fuel, string brand, string model, string color, float mileage, float price, float weight, string type) : Vehicle (fuel, brand, model, color, mileage, price)
        {
            this->type = "Bike";
            this->weight = weight;
            this->bike_type = type;
        }

        //  The overrided method which gives the number of wheels.
        int get_no_wheels ()
        {
            return 2;
        }
};

//  Overloading the Stream Insertion Operator '<<'.
ostream& operator << (ostream &os, const Vehicle &a)
{
    os << "TYPE" << "\t\t" << "BRAND" << "\t\t" << "MODEL" << "\t\t" << "FUEL" << "\t\t" << "COLOR" << "\t\t" << "PRICE" << endl;
    os << a.type << "\t\t" <<a.brand << "\t\t" << a.model << "\t\t" << a.vehicle_type << "\t\t" << a.color << "\t\t" << fixed << setprecision(2) << a.price << endl;
    os << endl;
    return os;
}

//  Overloading the comparison operator for the vehicle prices.
bool operator < (const Vehicle &a, const Vehicle &b)
{
    return (a.price < b.price);
}

int main ()
{
    //  Creating the Car Object
    Car c1("Petrol", "Hyundai", "I-10", "Red", 100.0, 1000000.0, 5, "SUV");
    Car c2("Petrol", "Toyota", "Camary", "Black", 160.0, 2000000.0, 5, "Sedan");

    //  Creating the Bike Object
    Bike b1("Petrol", "TVS", "XL Pro", "Blue", 125.00, 75000.00, 75.00, "Scooter");
    Bike b2("Petrol", "Bajaj", "Pulsar", "Green", 150.00, 175000.00, 100.00, "Motor Bike");

    //  Operator Overloading for the car and bike Object.
    cout << c1;
    cout << c2;

    cout << b1;
    cout << b2;

    //  Access using Encapsulation --> Virtual Method Overriding
    cout << "\nCar \t Wheels: " << c1.get_no_wheels();
    cout << "\nBike \t Wheels: " << b1.get_no_wheels();

    //  Operator Overloading for Comparison Operator.
    (c1 < c2)?    cout << "\n Car1 is Cheaper"  : cout << "\n Car2 is Cheaper";
    (c1 < b1)?    cout << "\n Car1 is Cheaper"   : cout << "\n Bike1 is Cheaper";
    (c1 < b2)?    cout << "\n Car1 is Cheaper"   : cout << "\n Bike2 is Cheaper";
    (c2 < b1)?    cout << "\n Car2 is Cheaper"   : cout << "\n Bike1 is Cheaper";
    (c2 < b2)?    cout << "\n Car2 is Cheaper"   : cout << "\n Bike2 is Cheaper";
    (b1 < b2)?    cout << "\n Bike1 is Cheaper"   : cout << "\n Bike2 is Cheaper";

    //  Return 0 on Success.
    return 0;
}