#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

auto compare = [](int value, string relop, int limit)
{
    if (relop == ">=")
        return value >= limit;

    else if (relop == "<=")
        return value <= limit;

    else if (relop == ">")
        return value > limit;

    else if (relop == "<")
        return value < limit;

    else if (relop == "==")
        return value == limit;

    else if (relop == "!=")
        return value != limit;

    return false;
};

class Sensors
{
    public:
        string device, relop, function;
        int battery_level = 100;
        bool status = true;

        void on_battery_check()
        {
            cout << "\n The current battery_level: " << battery_level;
            battery_level -= 2;

            if (battery_level < 15)
            {
                cout << "\n Low Battery: \t System Exit";
                exit(0);
            }
        }
};

class Devices
{
    public:
        static bool status;
        bool door_sensor;
        int battery_level;

        void on_connect() {}
        void on_disconnect() {}
};

class Temperature_Sensor : public Sensors
{
    public:
        float temperature_limit;
        float temperature_value = 0;

        void on_temperature_change(string msg)
        {
            if (msg == "ti")
                temperature_value += 1;

            else if (msg == "td")
                temperature_value -= 1;

            cout << "\n The temperature value is: " << temperature_value;
        }
};

class Lumionsity_Sensor : public Sensors
{
    public:
        float brightness_limit;
        float brightness_value = 0;

        void on_brightness_change(string msg)
        {
            if (msg == "bi")
                brightness_value += 1;

            else if (msg == "bd")
                brightness_value -= 1;

            cout << "\n The brightness value is: " << brightness_value;
        }
};

class Hydrolic_Sensor : public Sensors
{
    public:
        float water_level_limit;
        float water_level_value = 0;

        void on_water_level_change(string msg)
        {
            if (msg == "wi")
                water_level_value += 1;

            else if (msg == "wd")
                water_level_value -= 1;

            cout << "\n The water_level value is: " << water_level_value;
        }
};

class Gas_Gauge_Sensor : public Sensors
{
    public:
        float gas_level_limit;
        float gas_level_value = 0;

        void on_gas_level_change(string msg)
        {
            if (msg == "gi")
                gas_level_value += 1;

            else if (msg == "gd")
                gas_level_value -= 1;

            cout << "\n The gas_level value is: " << gas_level_value;
        }
};

class Proximity_Sensor : public Sensors
{
    public:
        float distance_limit;
        float distance_value = 0;

        void on_distance_change(string msg)
        {
            if (msg == "di")
                distance_value += 1;

            else if (msg == "dd")
                distance_value -= 1;

            cout << "\n The distance value is: " << distance_value;
        }
};

class Smart_Fan : public Devices
{
    public:
        bool status;

        void on_connect()
        {
            cout << "\n The fan is on.";
        }

        void on_disconnect()
        {
            cout << "\n The fan is off.";
        }
};

class Smart_Light : public Devices
{
    public:
        bool status;

        void on_connect()
        {
            cout << "\n The light is on.";
        }

        void on_disconnect()
        {
            cout << "\n The light is off.";
        }
};

class Smart_Door : public Devices
{
    public:
        bool status;

        void on_connect()
        {
            cout << "\n The door is open.";
        }

        void on_disconnect()
        {
            cout << "\n The door is closed.";
        }
};

class Device_Manager : public Devices
{
    public:
        string command_one, command_two, message;
        vector<string> token_one, token_two;

        Sensors s;

        Temperature_Sensor t;
        Lumionsity_Sensor l;
        Hydrolic_Sensor h;
        Gas_Gauge_Sensor g;
        Proximity_Sensor d;

        Smart_Fan fan;
        Smart_Light light;
        Smart_Door door;

        void get_input()
        {
            s.on_battery_check();
            cout << endl
                << endl;

            regex re(R"([\s|:,]+)");

            cout << "\n The commands should be entered in the lower case::" << endl;

            cout << "\n Enter the command one: ";
            getline(cin >> ws, command_one);
            token_one = tokenize(command_one, re);

            cout << "\n Enter the command two: ";
            getline(cin >> ws, command_two);
            token_two = tokenize(command_two, re);
        }

        vector<string> tokenize(string str, regex re)
        {
            sregex_token_iterator it{str.begin(), str.end(), re, -1};
            vector<std::string> tokenized{it, {}};
            tokenized.erase(remove_if(tokenized.begin(), tokenized.end(),
                                    [](string const &s)
                                    { return s.size() == 0; }),
                            tokenized.end());
            return tokenized;
        }

        void remote_sensing()
        {
            if (token_one[1] == "temperature")
            {
                t.temperature_limit = stof(token_one[3]);
                t.relop = token_one[2];
                t.device = token_two[1];
                t.function = token_two[2];
            }

            if (token_one[1] == "brightness")
            {
                l.brightness_limit = stof(token_one[3]);
                l.relop = token_one[2];
                l.device = token_two[1];
                l.function = token_two[2];
            }

            if (token_one[1] == "waterlevel")
            {
                h.water_level_limit = stof(token_one[3]);
                h.relop = token_one[2];
                h.device = token_two[1];
                h.function = token_two[2];
            }

            if (token_one[1] == "gaslevel")
            {
                g.gas_level_limit = stof(token_one[3]);
                g.relop = token_one[2];
                g.device = token_two[1];
                g.function = token_two[2];
            }

            if (token_one[1] == "distance")
            {
                d.distance_limit = stof(token_one[3]);
                d.relop = token_one[2];
                d.device = token_two[1];
                d.function = token_two[2];
            }
        }

        void key_press(string key)
        {
            string device, function;
            bool status;

            s.on_battery_check();
            cout << endl << endl;

            if (key == "ti" || key == "td")
            {
                t.on_temperature_change(key);
                status = compare(t.temperature_value, t.relop, t.temperature_limit);
                device = t.device;
                function = t.function;
            }

            else if (key == "bi" || key == "bd")
            {
                l.on_brightness_change(key);
                status = compare(l.brightness_value, l.relop, l.brightness_limit);
                device = l.device;
                function = l.function;
            }

            else if (key == "wi" || key == "wd")
            {
                h.on_water_level_change(key);
                status = compare(h.water_level_value, h.relop, h.water_level_limit);
                device = h.device;
                function = h.function;
            }

            else if (key == "gi" || key == "gd")
            {
                g.on_gas_level_change(key);
                status = compare(g.gas_level_value, g.relop, g.gas_level_limit);
                device = g.device;
                function = g.function;
            }

            else if (key == "di" || key == "dd")
            {
                d.on_distance_change(key);
                status = compare(d.distance_value, d.relop, d.distance_limit);
                device = d.device;
                function = d.function;
            }

            else
                cout << "\n Invalid Key-Press Event";

            carry_over(device, function, status);
        }

        void carry_over(string device, string function, bool status)
        {
            if (device == "fan")
            {
                if (function == "turnon" && status == true)
                    fan.on_connect();

                else if (function == "turnoff" && status == true)
                    fan.on_disconnect();

                else if (function == "turnoff")
                    fan.on_connect();

                else
                    fan.on_disconnect();
            }

            if (device == "light")
            {
                if (function == "turnon" && status == true)
                    light.on_connect();

                else if (function == "turnoff" && status == true)
                    light.on_disconnect();

                else if (function == "turnoff")
                    light.on_connect();

                else
                    light.on_disconnect();
            }

            if (device == "door")
            {
                if (function == "open" && status == true)
                    door.on_connect();

                else if (function == "close" && status == true)
                    door.on_disconnect();

                else if (function == "close")
                    door.on_connect();

                else
                    door.on_disconnect();
            }
        }
};

int main()
{
    int num;
    Device_Manager dm;

    do
    {
        dm.get_input();
        dm.remote_sensing();

        cout << "\n Do you wish to continue (1/0)? \t";
        cin >> num;
    } while (num);

    do
    {
        string key;
        cout << "\n Enter the key: ";
        cin >> key;
        dm.key_press(key);

        cout << "\n Do you wish to continue (1/0)? \t";
        cin >> num;
    } while (num);

    return 0;
}
