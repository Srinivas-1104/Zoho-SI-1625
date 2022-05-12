#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <regex>
#include <string>

using namespace std;
using std::string;

class Devices
{
public:
    static bool status;
    bool door_sensor;
    int battery_level;

    void on_connect()
    {
        cout << "\n The Devices has been connected. ";
        status = true;
    }

    void on_disconnect()
    {
        cout << "\n The Devices has been disconnceted.";
        status = false;
    }
};

class Temperature_Sensor : public Devices
{
public:
    int temperature_limit;
    int temperature_value;
};

class Smart_Fan : public Temperature_Sensor
{
public:
    string m, operand;
    bool status, on_off;

    void set_temperature(int temp)
    {
        temperature_limit = temp;
        temperature_value = temp;
        cout << "\n The temperature has been set.";
    }

    void on_temperature_change(string msg)
    {
        if (msg == "ti")
            temperature_value += 1;

        else if (msg == "td")
            temperature_value -= 1;

        cout << "\n The temperature value is: " << temperature_value;
    }

    void set_status(string op, int value, string message)
    {
        operand = op;
        m = message;
        if (strstr(m.c_str(), "On"))
            on_off = true;
        else
            on_off = false;
        temperature_value = value;
    }

    bool compare(int limit, string op, int value)
    {
        if (op == ">=")
            return value >= limit;

        else if (op == "<=")
            return value <= limit;

        else if (op == ">")
            return value > limit;

        else if (op == "<")
            return value < limit;

        else if (op == "==")
            return value == limit;

        else if (op == "!=")
            return value != limit;

        return false;
    }

    void check_status()
    {
        status = compare(temperature_limit, operand, temperature_value);

        if (status && on_off == true)
            cout << "\n The fan is On.";
        else
            cout << "\n The fan is closed.";
    }
};

class Device_Manager : public Devices
{
public:
    string command_one, command_two, message;
    vector<string> token_one, token_two;
    Smart_Fan fan;

    void get_input()
    {
        regex re(R"([\s|:,]+)");

        cout << "\n Enter the command one: ";
        getline(cin, command_one);
        token_one = tokenize(command_one, re);

        cout << "\n Enter the command two: ";
        getline(cin, command_two);
        token_two = tokenize(command_two, re);
    }

    vector<string> tokenize(string str, regex re)
    {
        sregex_token_iterator it{str.begin(), str.end(), re, -1};
        vector<std::string> tokenized{it, {}};
        tokenized.erase(std::remove_if(tokenized.begin(), tokenized.end(), 
                        [](std::string const &s) { return s.size() == 0; }),
                        tokenized.end());
        return tokenized;
    }

    void print ()
    {
        for (auto it: token_one)
            cout << it << '\t';

        for (auto it: token_two)
            cout << it << '\t';
    }

    void remote_sensing_part_one ()
    {
        if (token_one[0] == "If")
        {
            if (token_one[1] == "Temperature")
            {
                string op = token_one[2];
                string val = token_one[3];
                int temp = stof(val);

                fan.set_temperature(temp);
                remote_sensing_part_two (op, temp);
            }
        }
    }

    void remote_sensing_part_two (string op, int val)
    {
        if (token_two[1] == "Fan")
        {
            fan.set_status(op, val, token_two[2]);
            cout << "\n The status has been set.";
        }
    }

    void key_press_event ()
    {
        string key;
        cout << "\n Enter the key: ";
        cin >> key;

        if (key == "ti" || key == "td")
        {
            fan.on_temperature_change(key);
            fan.check_status();
        }
    }
};

int main ()
{
    int num;
    Device_Manager dm;

    dm.get_input();
    dm.print();
    dm.remote_sensing_part_one();

    do
    {
        dm.key_press_event();

        cout << "\n Do you wish to continue (1/0)? ";
        cin >> num;
    }while (num);

    return 0;
}
