#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ctime>
namespace fs = std::filesystem;

#include "notepad.pb.h"
using namespace std;

class Project_Portal
{
private:
    string path, current_project;
    vector<string> projects_available;
    int count;

    notepad::PROJECT_LIST pl;
    notepad::PROJECT p;
    notepad::VERSION_POINTER vp;

public:
    void clrscr()
    {
        cout << "\033[2J\033[1;1H";
    }

    void main_screen(string index)
    {
        clrscr();
        int choice;

        create_directory_for_user(index);

        do
        {
            clrscr();

            path = fs::current_path();
            path += "/Directory/";

            cout << "\n\n\n WELCOME TO THE PROJECT PORTAL: \n\n\n \n 0.  Exit \n\n 1. Create New File \n\n 2. List Existing Projects \n\n Enter the choice: ";
            cin >> choice;

            switch (choice)
            {
                case 0:
                {
                    cout << "\n Exiting the system... \n Going back to Sign In Portal! " << endl;
                    return;
                }

                case 1:
                {
                    create_new_file(index);
                    cin.get();
                    break;
                }

                case 2:
                {
                    file_operations(index);
                    cin.get();
                    break;
                }

                default:
                    cout << "\n Invalid Choice!" << endl;
                    break;
                }
        } while (choice);
    }

    void create_directory_for_user(string index)
    {
        string pathway = fs::current_path();
        pathway += "/Directory/" + index;
        if (!fs::exists(pathway))
            fs::create_directory(pathway);
    }

    void read_project_details(notepad::PROJECT &p, string pathway, string fn)
    {
        size_t s = pathway.find_last_of('/') + 1;
        pathway = pathway.substr(0, s);
        pathway = pathway + "log_" + fn;
        fstream inp(pathway, ios::in);
        p.ParseFromIstream(&inp);
        inp.close();
    }

    void write_project_details(notepad::PROJECT &p, string pathway, string fn)
    {
        size_t s = pathway.find_last_of('/') + 1;
        pathway = pathway.substr(0, s);
        pathway = pathway + "log_" + fn;
        fstream outp(pathway, ios::app);
        outp << "\n\n\n";
        p.SerializeToOstream(&outp);
        outp.close();
    }

    void add_gist_contents(notepad::GIST *g, string &l)
    {
        g->set_gist_line(l);
    }

    // void add_to_log(notepad::PROJECT *p, string pathway, string index, int count = 0)
    // {
    //     string pid = current_project + '_' + index + '_' + to_string(rand() % (100 - 1) + 1);

    //     p->set_project_name(current_project);
    //     p->set_user_id(index);
    //     p->set_project_id(pid);
    //     p->set_path(pathway);
    //     p->set_operations(p->operations() + 1);
    //     pid = "";
    //     add_gist_contents(p->add_gist(), pid);
    // }

    void create_new_file(string index)
    {
        clrscr();

        cout << "\n Enter the name of the file: ";
        getline(cin >> ws, current_project);
        string pathway = path + index + '/' + current_project + ".txt";
        cout << pathway << endl;

        if (fs::exists(pathway))
        {
            cout << "\n The file already exists.";
            cin.get();
            return;
        }

        fstream file(pathway, ios::out);

        string pid = current_project + '_' + index + '_' + to_string(rand() % (100 - 1) + 1);
        p.set_project_id(pid);
        p.set_path(pathway);
        p.set_user_id(index);
        p.set_project_name(current_project);
        p.set_operations(0);
        vp.set_project_id(pid);
        vp.set_id(index + '_' + current_project);
        vp.set_version_no(1);
        fstream log(pathway + "log", ios::out | ios::binary);
        p.SerializeToOstream(&log);
        vp.SerializeToOstream(&log);

        file_operations(index);
    }

    void list_existing_projects(string index)
    {
        clrscr();

        string pathway = path + index;
        projects_available.clear();

        cout << "\n The Existing Projects are: " << index << "\n\n\n";
        for (const auto &entry : fs::directory_iterator(pathway))
        {
            string p = entry.path();
            if ((p.find("version") == string::npos) && (p.find("log") == string::npos))
                projects_available.push_back(entry.path());
        }

        cout << "\nINDEX" << "\t" << "PROJECTS" << endl;
        for (int i = 0; i < projects_available.size(); i++)
            cout << i << "\t" << projects_available[i] << endl;
        cout << endl << endl;
        cin.get();
    }

    // void log_version_control(notepad::VERSION_POINTER *vp, int count, string pathway, string operation, string job, notepad::PROJECT_LIST &pl)
    // {
    //     for (int i = 0; i < pl.project_size(); i++)
    //     {
    //         const notepad::PROJECT &p = pl.project(i);

    //         if (p.path() == pathway)
    //         {
    //             // vp->set_version(count);
    //             vp->set_operation(operation);
    //             vp->set_user_id(p.user_id());
    //             vp->set_project_id(p.project_id());
    //             vp->set_job_done(job);
    //         }
    //     }
    // }

    void file_operations(string index)
    {
        int choice;
        string line = "0";

        notepad::PROJECT live_project;
        // notepad::VERSION version;

        list_existing_projects(index);
        if (projects_available.size() == 0)
        {
            cout << "\n There exists no project.";
            return;
        }

        cout << "\n Enter the choice: ";
        cin >> choice;

        if (choice < 0 || projects_available.size() <= choice)
        {
            cout << "\n Your choice is invalid.";
            return;
        }

        string pathway = projects_available[choice];
        size_t s = pathway.find_last_of('/') + 1;
        string file_name = pathway.substr(s);

        cin.get();
        cin.get();

        fstream log(pathway + "log", ios::in | ios::binary);
        p.ParseFromIstream(&log);

        clrscr();

        cout << "\n The File Operations Menu: \n\n\n \n 0. Exit \n 1. Add \n 2. Update \n 3. Remove \n 4. Display \n 5. Version Control \n\n Enter the choice: ";
        cin >> choice;
        cin.get();

        cout << "\n The chosen file: " << file_name;
        read_project_details(live_project, pathway, file_name);
        cout << file_name << endl;

        switch (choice)
        {
            case 0:
                cout << "\n Exiting the menu!";
                break;

            case 1:
                add_content(pathway, file_name, live_project);
                // log_version_control(version.add_pointer(), count, pathway, "APPEND", line, pl);
                break;

            case 2:
                update_content(pathway, file_name, live_project);
                // log_version_control(version.add_pointer(), count, pathway, "UPDATE", line, pl);
                break;

            case 3:
                remove_content(pathway, file_name, live_project);
                // log_version_control(version.add_pointer(), count, pathway, "REMOVE", line, pl);
                break;

            case 4:
                display_content(pathway, file_name, live_project);
                // log_version_control(version.add_pointer(), count, pathway, "DISPLAY", line, pl);
                break;

            case 5:
                version_control(pathway, file_name, live_project);
                // log_version_control(version.add_pointer(), count, pathway, "VERSION", line, pl);
                break;

            default:
                cout << "\n Invalid Choice: ";
                break;
        }
        cin.get();

        if (live_project.operations() % 5 == 0)
            versioning(pathway, file_name, p, p.operations());

        fstream log(pathway + "log", ios::out | ios::binary);
        live_project.SerializeToOstream(&log);
        vp.SerializeToOstream(&log);

        // version.SerializePartialToOstream(&vers);
        // for (int i = 0; i < version.pointer_size(); i++)
        // {
        //     const notepad::VERSION_POINTER &u = version.pointer(i);
        //     cout << u.operation() << " " << u.job_done() << " " << u.project_id() << " " << u.user_id() << " ";
        // }
        // cout << count << endl;
        write_project_details(live_project, pathway, file_name);
        cin.get();
    }

    void add_content(string pathway, string file_name, notepad::PROJECT &p)
    {
        clrscr();

        cout << "\n THE CONTENTS: \t\t " << file_name;
        cout << "\n PATH: \t\t" << pathway;
        cout << "\n The file is going to be appened. \n\n\n\n";

        fstream file(pathway, ios::app);
        cout << "\n Enter the content! \n (Enter 'halt' (or) 'HALT' to exit) \n";
        while (1)
        {
            string content;
            getline(cin >> ws, content);
            if (content == "halt" || content == "HALT")
            {
                cout << "\n The appending is completed.";
                break;
            }
            add_gist_contents(p.add_gist(), content);
            file << content << endl;
        }
        file.close();
    }

    void update_content(string pathway, string file_name, notepad::PROJECT &p)
    {
        clrscr();

        int choice;

        cout << "\n THE CONTENTS: \t\t " << file_name;
        cout << "\n PATH: \t\t" << pathway;
        cout << "\n The file is going to be updated. \n\n\n\n";

        fstream file;
        cout << "\n The choices are: ";
        cout << "\n 0. Exit \n 1. Update - Line \n 2. Update - Document \n\n Enter the choice: ";
        cin >> choice;

        switch (choice)
        {
            case 0:
                cout << "\n Returning to the original menu!";
                cin.get();
                break;

            case 1:
                utility_function_editing(pathway, file_name, true, false, p);
                return;

            case 2:
                cout << "\n The entire file is truncated and is ready to be updated.";
                file.open(pathway, ios::out | ios::trunc);
                file.close();
                add_content(pathway, file_name, p);
                break;

            default:
                cout << "\n Invalid choice!";
                break;
        }
        cin.get();
    }

    void remove_content(string pathway, string file_name, notepad::PROJECT &p)
    {
        clrscr();

        int choice, line = 1, line_number;
        string content;

        cout << "\n THE CONTENTS: \t\t " << file_name;
        cout << "\n PATH: \t\t" << pathway;
        cout << "\n\n\n";

        cout << "\n The choices are: ";
        cout << "\n 0. Exit \n 1. Remove - Line \n 2. Remove - Document \n\n Enter the choice: ";
        cin >> choice;

        switch (choice)
        {
            case 0:
                cout << "\n Returning to the original menu!";
                cin.get();
                break;

            case 1:
                utility_function_editing(pathway, file_name, false, true, p);
                return;

            case 2:
                cout << "\n The entire file is removed.";
                fs::remove(pathway);
                break;

            default:
                cout << "\n Invalid choice!";
                break;
        }
    }

    void utility_function_editing(string pathway, string file_name, bool updation, bool removal, notepad::PROJECT &p)
    {
        display_content(pathway, file_name, p);
        int line = 1, line_number;
        string content;
        bool check = false;

        fstream fread, fwrite;
        fread.open(pathway, ios::in);
        size_t s = pathway.find_last_of('/') + 1;
        string temp = pathway.substr(0, s) + "temp.txt";

        fwrite.open(temp, ios::out);
        if (updation)
        {
            cout << "\n Enter the line number to be updated: ";
            cin >> line_number;
            if (line_number < 0)
            {
                cout << "\n Invalid Number";
                return;
            }
            while (getline(fread, content))
            {
                if (line == line_number)
                {
                    string message;
                    cout << "\n Enter the updated line: ";
                    getline(cin >> ws, message);
                    add_gist_contents(p.add_gist(), message);
                    fwrite << message << endl;
                    line++;
                    check = true;
                    continue;
                }

                fwrite << content << endl;
                add_gist_contents(p.add_gist(), content);
                line++;
            }
        }

        if (removal)
        {
            cout << "\n Enter the line number to be removed: ";
            cin >> line_number;

            while (getline(fread, content))
            {
                if (line_number < 0)
                {
                    cout << "\n Invalid Number";
                    return;
                }

                if (line != line_number)
                {
                    fwrite << content << endl;
                    add_gist_contents(p.add_gist(), content);
                }

                if (line == line_number)
                    check = true;

                line++;
            }
        }

        if (!check)
            cout << "\n Invalid Number" << endl;

        fread.close();
        fwrite.close();
        fs::remove(pathway);
        fs::rename(temp, pathway);
    }

    void display_content(string pathway, string file_name, notepad::PROJECT &p)
    {
        clrscr();

        cout << "\n THE CONTENTS: \t\t " << file_name;
        cout << "\n PATH: \t\t" << pathway;
        cout << "\n The file is being displayed! \n \n\n\n";

        fstream file(pathway, ios::in);

        int count = 1;
        if (file.is_open())
        {
            string content;
            while (getline(file, content))
                cout << count << '\t' << content << endl;
        }
        file.close();
    }

    void versioning(string pathway, string file_name, notepad::PROJECT &p, int count)
    {
        time_t current;
        struct tm *local;
        time(&current);
        local = localtime(&current);
        int min = local->tm_hour + local->tm_min;

        string iam = to_string(min);
        string input, output;
        input = pathway;
        size_t s = pathway.find_last_of('/') + 1;
        output = pathway.substr(0, s) + "version_" + iam + '_' + file_name;

        fstream fread(input, ios::in);
        fstream fwrite(output, ios::out);
        string content;
        while (getline(fread, content))
            fwrite << content << endl;

        fread.close();
        fwrite.close();
    }

    void version_control(string pathway, string file_name, notepad::PROJECT &p)
    {
        clrscr();
        vector<string> versions_available;
        int choice;

        cout << "\n The Existing Versions are: \n\n\n";
        size_t s = pathway.find_last_of('/') + 1;
        pathway = pathway.substr(0, s);

        for (const auto &entry : fs::directory_iterator(pathway))
        {
            string p = entry.path();
            if (p.find("version") != string::npos && p.find(file_name))
                versions_available.push_back(entry.path());
        }

        if (versions_available.size() == 0)
        {
            cout << "\n No version files: ";
            return;
        }

        if (versions_available.size() == 1)
        {
            cout << "\n Only one version of the file available.";
            cout << "\n Reversion cannot happen";
            return;
        }

        sort(versions_available.begin(), versions_available.end());

        cout << "\nINDEX" << "\t" << "PROJECTS" << endl;
        for (int i = 0; i < versions_available.size(); i++)
            cout << i << '\t' << versions_available[i] << endl;

        cout << "\n\n Enter the version index to revert and keep: (Be aware that choosing a version index now means that all other versions will be deleted.)" << endl;
        cin >> choice;

        string name = versions_available[choice];
        fs::remove(pathway + file_name);
        fs::rename(name, pathway + file_name);

        for (int i = choice + 1; versions_available.size(); i++)
            fs::remove(versions_available[i]);

        versions_available.resize(choice);
    }
};
