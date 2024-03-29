#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <cstring>
#include <cctype>
#include <windows.h>

using namespace std;
// SetConsoleTextAttribute(console, k);
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void printColor(string str, int k)
{
    SetConsoleTextAttribute(console, k);
    cout << str;
    SetConsoleTextAttribute(console, 15);
}
/***************************************************** Structs *****************************************************/
struct Pokemon
{
    string name;
    string type;
    int cp;
    string dateCaptured;
    float height;
    float weight;

    Pokemon(string name, string type, int cp, string dateCaptured, float height, float weight)
    {
        this->name = name;
        this->type = type;
        this->cp = cp;
        this->dateCaptured = dateCaptured;
        this->height = height;
        this->weight = weight;
    }
    void display(int i)
    {
        printf("\t\t\t%-5d %-15s %-15s %-10d %-20s %-15.1f %-15.1f\n", i, name.c_str(), type.c_str(), cp, dateCaptured.c_str(), height, weight);
    }
};
struct Pokemon_Stops
{
    string date;
    string time;
    string items;

    Pokemon_Stops(string date, string time, string items)
    {
        this->date = date;
        this->time = time;
        this->items = items;
    }

    void display(int i)
    {
        printf("\t\t\t%-5d %-15s %-15s %-15s\n", i, date.c_str(), time.c_str(), items.c_str());
    }
};
struct Raid
{
    string date;
    string time;
    string venue;

    Raid(string date, string time, string venue)
    {
        this->date = date;
        this->time = time;
        this->venue = venue;
    }

    void display(int i)
    {
        printf("\t\t\t%-5d %-15s %-15s %-15s\n", i, date.c_str(), time.c_str(), venue.c_str());
    }
};
struct Hunter
{
    string firstName;
    string lastName;
    int level;
    string gender;
    string teamType;
    vector<Pokemon> pokemon;
    vector<Pokemon_Stops> pStop;
    vector<Raid> pRaid;

    Hunter(string firstName, string lastName, int level, string gender, string teamType, vector<Pokemon> pokemon, vector<Pokemon_Stops> pStop, vector<Raid> pRaid)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        this->level = level;
        this->gender = gender;
        this->teamType = teamType;
        this->pokemon = pokemon;
        this->pStop = pStop;
        this->pRaid = pRaid;
    }
    void sortPokemon()
    {
        sort(pokemon.begin(), pokemon.end(), [](const Pokemon &i, const Pokemon &j) {
            return i.cp > j.cp;
        });
    }
    void displayDetails(int i)
    {

        string line = "----------------------------------------------------------------------------------------------";
        string asterisk = "**********************************************************************************************";

        SetConsoleTextAttribute(console, 14);
        printf("\t\t\t%s \n", asterisk.c_str());                   // ************
        printf("\t\t\t%39d %9s %3s %-40d\n", i, "Hunter", " ", i); // 1   Hunter   1
        printf("\t\t\t%s \n", asterisk.c_str());                   // ************
        SetConsoleTextAttribute(console, 15);

        printf("\t\t\t%5s %-12s:     %-25s\n", " ", "First Name", firstName.c_str());
        printf("\t\t\t%5s %-12s:     %-25s\n", " ", "Last Name", lastName.c_str());
        printf("\t\t\t%5s %-12s:     %-25d\n", " ", "Level", level);
        printf("\t\t\t%5s %-12s:     %-25s\n", " ", "Gender", gender.c_str());
        printf("\t\t\t%5s %-12s:     %-25s\n\n", " ", "Team Type", teamType.c_str());

        SetConsoleTextAttribute(console, 14);
        printf("\t\t\t%-39s %10s %3s %-40s\n", "**************************************", "Pokemon", " ", "***************************************");
        printf("\t\t\t%5s %-15s %-15s %-10s %-20s %-15s %-15s\n", " ", "Name", "Type", "CP", "Date Captured", "Height", "Weight");
        SetConsoleTextAttribute(console, 15);

        int k = 0;
        for (auto &p : pokemon)
        {
            k++;
            p.display(k);
        }
        printf("\n"); //

        SetConsoleTextAttribute(console, 14);
        printf("\t\t\t%-39s %9s %4s %-40s\n", "**************************************", "Stops", " ", "***************************************");
        printf("\t\t\t%5s %-15s %-15s %-10s \n", " ", "Date", "Time", "Item");
        SetConsoleTextAttribute(console, 15);

        k = 0;
        for (auto &ps : pStop)
        {
            k++;
            ps.display(k);
        }
        printf("\n"); //

        SetConsoleTextAttribute(console, 14);
        printf("\t\t\t%-39s %9s %4s %-40s\n", "**************************************", "Raids", " ", "***************************************");
        printf("\t\t\t%5s %-15s %-15s %-10s \n", " ", "Date", "Time", "Venue");
        SetConsoleTextAttribute(console, 15);

        k = 0;
        for (auto &pr : pRaid)
        {
            k++;
            pr.display(k);
        }
        printf("\n"); //

        SetConsoleTextAttribute(console, 14);
        printf("\t\t\t%s\n\n", asterisk.c_str()); // ************
        SetConsoleTextAttribute(console, 15);
    }

    void display(int i)
    {
        printf("\t\t\t%-5d %-15s %-15s %-10d %-20s %-15s\n", i, firstName.c_str(), lastName.c_str(), level, gender.c_str(), teamType.c_str());
    }
};

/**************************************************** TRIM ***************************************************/
const string WHITESPACE = " \n\r\t\f\v";
string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const string &s)
{
    return rtrim(ltrim(s));
}

/**************************************************** Validation ***************************************************/
bool validateDate(tm *timestruct)
{
    struct tm copy;
    copy.tm_sec = timestruct->tm_sec;
    copy.tm_min = timestruct->tm_min;
    copy.tm_hour = timestruct->tm_hour;
    copy.tm_mday = timestruct->tm_mday;
    copy.tm_mon = timestruct->tm_mon;
    copy.tm_year = timestruct->tm_year;
    copy.tm_wday = timestruct->tm_wday;
    copy.tm_yday = timestruct->tm_yday;
    copy.tm_isdst = timestruct->tm_isdst;

    // if time is not correct, res will return -1;
    time_t res = mktime(&copy);
    if (res < 0)
    {
        return false;
    }
    if (copy.tm_mday != timestruct->tm_mday || copy.tm_mon != timestruct->tm_mon || copy.tm_year != timestruct->tm_year)
    {
        return false;
    }
    return true;
}
bool validateTime(tm *timestruct)
{
    struct tm copy;
    copy.tm_sec = timestruct->tm_sec;
    copy.tm_min = timestruct->tm_min;
    copy.tm_hour = timestruct->tm_hour;
    copy.tm_mday = timestruct->tm_mday;
    copy.tm_mon = timestruct->tm_mon;
    copy.tm_year = timestruct->tm_year;
    copy.tm_wday = timestruct->tm_wday;
    copy.tm_yday = timestruct->tm_yday;
    copy.tm_isdst = timestruct->tm_isdst;

    // if time is not correct, res will return -1;
    time_t res = mktime(&copy);
    if (res < 0)
    {
        return false;
    }
    if (copy.tm_min != timestruct->tm_min || copy.tm_hour != timestruct->tm_hour)
    {
        return false;
    }
    return true;
}
void dateValid(string &date)
{
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    while (true)
    {
        // Read the date and assign the values to tm;
        sscanf(date.c_str(), "%d-%d-%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
        --tm.tm_mon;
        tm.tm_year -= 1900;

        struct tm *check;
        check = &tm;

        if (!validateDate(check))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printColor("Error !", 12);
            cout << " Invalid date. Please enter a valid date: ";
            cin >> date;
        }
        else
        {
            break;
        }
    };
    time_t timeStamp = mktime(&tm);
    char buff[50];
    strftime(buff, 50, "%d-%m-%Y", localtime(&timeStamp));
    string timeStr(buff);
    date = timeStr;
}
void timeValid(string &time)
{
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    while (true)
    {
        unsigned tmp_hour, tmp_mins;
        sscanf(time.c_str(), "%d:%d", &tmp_hour, &tmp_mins);

        tm.tm_hour = tmp_hour;
        tm.tm_min = tmp_mins;
        tm.tm_mday = 15;
        tm.tm_mon = 10;
        tm.tm_year = 2020;
        --tm.tm_mon;
        tm.tm_year -= 1900;
        struct tm *check;
        check = &tm;

        if (!validateTime(check))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printColor("Error !", 12);
            cout << " Invalid time. Please enter a valid time: ";
            cin >> time;
        }
        else
        {
            break;
        }
    };

    time_t timeStamp = mktime(&tm);
    char buff[50];
    strftime(buff, 50, "%H:%M", localtime(&timeStamp));
    string timeStr(buff);
    time = timeStr;
}
int intValid(bool t, int num, int type)
{
    while (true)
    {
        if (t == true)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (type == 1)
            {
                printColor("Error !", 12);
                cout << " Invalid option. "
                     << "Please enter the available option : ";
                cin >> num;
            }
            else if (type == 2)
            {
                printColor("Error !", 12);
                cout << " Invalid CP. "
                     << "Please enter a valid CP : ";
                cin >> num;
            }
            else if (type == 3)
            {
                printColor("Error !", 12);
                cout << " Invalid level. "
                     << "Please enter a valid Level : ";
                cin >> num;
            }
            else
            {
                cout << ""
                     << "Please enter a valid integer : ";
                cin >> num;
            }
        }
        if (!cin.fail())
        {
            break;
        }
    }
    return num;
}
float floatValid(bool t, float num, int type)
{
    while (true)
    {
        if (t == true)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (type == 1)
            {
                printColor("Error !", 12);
                cout << " Invalid height. "
                     << "Please enter a valid Height : ";
                cin >> num;
            }
            else if (type == 2)
            {
                printColor("Error !", 12);
                cout << " Invalid weight. "
                     << "Please enter a valid Weight : ";
                cin >> num;
            }
            else
            {
                cout << ""
                     << "Please enter a valid float : ";
                cin >> num;
            }
        }
        if (!cin.fail())
        {
            break;
        }
    }
    return num;
}
void pokemonTypeValid(string &pokemonType)
{
    string type = pokemonType;
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    while (true)
    {
        if (type == "normal" || type == "ground" || type == "fire" || type == "fighting" || type == "water" || type == "grass" || type == "rock" || type == "electric" || type == "bug" || type == "physic" || type == "poison" || type == "dragon")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            type[0] = toupper(type[0]);
            pokemonType = type;
            break;
        }
        else
        {
            printColor("\nError !", 12);
            cout << " Invalid Pokemon Type.\n";

            printf("%-34s: ", "Available options for Pokemon Type");
            SetConsoleTextAttribute(console, 9);
            printf("-%-10s  -%-10s  -%-10s  -%-10s\n%-36s-%-10s  -%-10s  -%-10s  -%-10s\n%-36s-%-10s  -%-10s  -%-10s  -%-10s\n", "Normal", "Ground", "Fire", "Fighting", " ", "Water", "Grass", "Rock", "Electric", " ", "Bug", "Physic", "Poison", "Dragon");
            SetConsoleTextAttribute(console, 15);

            cout << "Please enter one of the above options: ";
            cin >> type;
            transform(type.begin(), type.end(), type.begin(), ::tolower);
        }
    }
}
void genderValid(string &gender)
{
    string type = gender;
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    while (true)
    {
        if (type == "male" || type == "female" || type == "agender")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            type[0] = toupper(type[0]);
            gender = type;
            break;
        }
        else
        {
            printColor("\nError !", 12);
            cout << " Gender not recognized.\n";

            printf("%-29s: ", "Available options for Gender");
            SetConsoleTextAttribute(console, 9);
            printf("-%-8s-%-10s-%-10s\n", "Male", "Female", "Agender");
            SetConsoleTextAttribute(console, 15);

            cout << "Please enter one of the above options: ";
            cin >> type;
            transform(type.begin(), type.end(), type.begin(), ::tolower);
        }
    }
}
void teamTypeValid(string &teamType)
{
    string type = teamType;
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    while (true)
    {
        if (type == "mystic" || type == "instinct" || type == "none")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            type[0] = toupper(type[0]);
            teamType = type;
            break;
        }
        else
        {
            printColor("\nError !", 12);
            cout << " Invalid Team Type.\n";

            printf("%-32s: ", "Available options for Team Type");
            SetConsoleTextAttribute(console, 9);
            printf("-%-9s-%-10s -%-10s\n", "Mystic", "Instinct", "None");
            SetConsoleTextAttribute(console, 15);

            cout << "Please enter one of the above options: ";
            cin >> type;
            transform(type.begin(), type.end(), type.begin(), ::tolower);
        }
    }
}
void emptyValid(string &input)
{

    while (true)
    {
        if (input.empty() || all_of(input.begin(), input.end(), [](char c) { return isspace(c); }))
        {
            printColor("\nError !", 12);
            cout << " Input is empty.\n";
            cout << "Please enter again : ";
            getline(cin, input);
        }
        else
        {
            break;
        }
    }
}

/**************************************************** HUNTER ***************************************************/
void readHunter(vector<Hunter> &hunter)
{
    string data;
    bool state = true;

    string firstName;
    string lastName;
    int level;
    string gender;
    string teamType;

    vector<Pokemon> pokemon;
    string pName;
    string pType;
    int pCP;
    string pDateCaptured;
    float pHeight;
    float pWeight;

    vector<Pokemon_Stops> pStop;
    string sDate;
    string sTime;
    string sItems;

    vector<Raid> pRaid;
    string rDate;
    string rTime;
    string rVenue;

    ifstream readFile;
    try
    {
        readFile.open("Hunters.txt", ios::in);

        while (!readFile.eof())
        {
            getline(readFile, data); //
            getline(readFile, data); //
            getline(readFile, data); // *******
            getline(readFile, data); // 1 Hunter 1
            getline(readFile, data); // *******

            readFile >> data;        // First
            readFile >> data;        // Name
            readFile >> data;        // :
            getline(readFile, data); // Yeoh Xuan
            firstName = trim(data);

            readFile >> data;        // Last
            readFile >> data;        // Name
            readFile >> data;        // :
            getline(readFile, data); // Kok Eugene
            lastName = trim(data);

            readFile >> data; // Level
            readFile >> data; // :
            readFile >> data; // 15
            level = stoi(data);

            readFile >> data;   // Gender
            readFile >> data;   // :
            readFile >> gender; // Male

            readFile >> data;     // Team
            readFile >> data;     // Type
            readFile >> data;     // :
            readFile >> teamType; // Fire

            getline(readFile, data); //
            getline(readFile, data); //
            getline(readFile, data); // ****** Pokemon ******
            getline(readFile, data); // Name Type CP Date Captured Height Weight
            while (readFile >> data)
            {
                if (data.find("****") != string::npos)
                {
                    break;
                }
                else
                {
                    string cp, ht, wt;
                    readFile >> pName;
                    readFile >> pType;
                    readFile >> cp;

                    readFile >> pDateCaptured;
                    readFile >> ht;
                    readFile >> wt;
                    try
                    {
                        pCP = stoi(cp);
                        pHeight = stof(ht);
                        pWeight = stof(wt);
                    }
                    catch (...)
                    {
                    }
                    Pokemon poke = Pokemon(pName, pType, pCP, pDateCaptured, pHeight, pWeight);
                    pokemon.push_back(poke);
                }
            }

            getline(readFile, data); // Stops ********
            getline(readFile, data); // Date Time Item
            while (readFile >> data)
            {
                if (data.find("****") != string::npos)
                {
                    break;
                }
                else
                {
                    readFile >> sDate;
                    readFile >> sTime;
                    readFile >> sItems;

                    Pokemon_Stops stop = Pokemon_Stops(sDate, sTime, sItems);
                    pStop.push_back(stop);
                }
            }

            getline(readFile, data); // Raids ******
            getline(readFile, data); // Date Time Venue
            while (readFile >> data)
            {
                if (data.find("****") != string::npos)
                {
                    break;
                }
                else
                {
                    readFile >> rDate;
                    readFile >> rTime;
                    getline(readFile, data);
                    rVenue = trim(data);

                    Raid raid = Raid(rDate, rTime, rVenue);
                    pRaid.push_back(raid);
                }
            }

            Hunter hunt = Hunter(firstName, lastName, level, gender, teamType, pokemon, pStop, pRaid);
            hunt.sortPokemon();
            hunter.push_back(hunt);
            pokemon.clear();
            pStop.clear();
            pRaid.clear();
        }
    }
    catch (...)
    {
        printColor("\n\n ! Error !\n", 12);
        cout << "Unable to read the file either due to the ";
        printColor("file does not exist ", 12);
        cout << "or ";
        printColor("the structure of the file is not the same as the program computed\n\n", 12);
        printColor("New file will be created upon saving \n\nProceeding to Main Menu...", 10);
    }

    readFile.close();
}
void writeHunter(vector<Hunter> hunter)
{
    FILE *pFile;
    pFile = fopen("Hunters.txt", "w");

    string asterisk = "**********************************************************************************************";

    int i = 0;
    for (auto &h : hunter)
    {
        fprintf(pFile, "\n\n");
        i++;
        fprintf(pFile, "%s \n", asterisk.c_str());                   // ***********
        fprintf(pFile, "%39d %9s %3s %-40d\n", i, "Hunter", " ", i); // 1  Hunter  1
        fprintf(pFile, "%s \n", asterisk.c_str());                   // ***********
        fprintf(pFile, "%5s %-12s: %-25s\n", " ", "First Name", h.firstName.c_str());
        fprintf(pFile, "%5s %-12s: %-25s\n", " ", "Last Name", h.lastName.c_str());
        fprintf(pFile, "%5s %-12s: %-25d\n", " ", "Level", h.level);
        fprintf(pFile, "%5s %-12s: %-25s\n", " ", "Gender", h.gender.c_str());
        fprintf(pFile, "%5s %-12s: %-25s\n\n", " ", "Team Type", h.teamType.c_str());

        fprintf(pFile, "%-39s %10s %3s %-40s\n", "**************************************", "Pokemon", " ", "***************************************");
        fprintf(pFile, "%5s %-15s %-15s %-10s %-20s %-15s %-15s\n", " ", "Name", "Type", "CP", "Date Captured", "Height", "Weight");

        vector<Pokemon> pokemon = h.pokemon;
        int k = 0;
        for (auto &p : pokemon)
        {
            k++;
            fprintf(pFile, "%-5d %-15s %-15s %-10d %-20s %-15.1f %-15.1f\n", k, p.name.c_str(), p.type.c_str(), p.cp, p.dateCaptured.c_str(), p.height, p.weight);
        }
        fprintf(pFile, "\n");

        fprintf(pFile, "%-39s %9s %4s %-40s\n", "**************************************", "Stops", " ", "***************************************");
        fprintf(pFile, "%5s %-15s %-15s %-10s \n", " ", "Date", "Time", "Item");

        vector<Pokemon_Stops> pStop = h.pStop;
        k = 0;
        for (auto &ps : pStop)
        {
            k++;
            fprintf(pFile, "%-5d %-15s %-15s %-15s\n", k, ps.date.c_str(), ps.time.c_str(), ps.items.c_str());
        }
        fprintf(pFile, "\n"); //

        fprintf(pFile, "%-39s %9s %4s %-40s\n", "**************************************", "Raids", " ", "***************************************");
        fprintf(pFile, "%5s %-15s %-15s %-10s \n", " ", "Date", "Time", "Venue");

        vector<Raid> pRaid = h.pRaid;
        k = 0;
        for (auto &pr : pRaid)
        {
            k++;
            fprintf(pFile, "%-5d %-15s %-15s %-15s\n", k, pr.date.c_str(), pr.time.c_str(), pr.venue.c_str());
        }
        fprintf(pFile, "\n"); //

        fprintf(pFile, "%s", asterisk.c_str()); // ************
    }
    fclose(pFile);
}
void displayHuntersDetails(vector<Hunter> hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }
    int i = 0;
    for (auto &h : hunter)
    {
        i++;
        h.displayDetails(i);
    }
    system("pause");
}
void displayHunters(vector<Hunter> hunter)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    string line = "----------------------------------------------------------------------------------------------";

    printf("\t\t\t%s \n", line.c_str());
    cout << "\t\t\t                                           Hunters                                          " << endl;
    printf("\t\t\t%s \n", line.c_str());

    printf("\t\t\t%5s %-15s %-15s %-10s %-20s %-15s\n", " ", "First Name", "Last Name", "Level", "Gender", "Team Type");
    printf("\t\t\t%s \n", line.c_str());

    int i = 0;
    for (auto &h : hunter)
    {
        i++;
        SetConsoleTextAttribute(console, 6);

        h.display(i);
    }
    SetConsoleTextAttribute(console, 15);

    printf("\n");
}
void searchHunter(vector<Hunter> &hunter, string searchBy, string input)
{
    vector<Hunter> result;

    if (searchBy == "firstName")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string firstName = h.firstName;
            transform(firstName.begin(), firstName.end(), firstName.begin(), ::tolower);
            if (firstName == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "lastName")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string lastName = h.lastName;
            transform(lastName.begin(), lastName.end(), lastName.begin(), ::tolower);
            if (lastName == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "teamType")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string teamType = h.teamType;
            transform(teamType.begin(), teamType.end(), teamType.begin(), ::tolower);
            if (teamType == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "gender")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string gender = h.gender;
            transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
            if (gender == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "level")
    {

        int lvl;
        bool state = true;
        do
        {

            try
            {
                lvl = stoi(input);
                state = false;
            }
            catch (...)
            {
                cout << "Please enter a valid integer : ";
                cin >> input;
                cout << "\n";
                continue;
            }
        } while (state);

        for (auto &h : hunter)
        {
            if (h.level == lvl)
            {
                result.push_back(h);
            }
        }
    }

    if (result.empty())
    {
        SetConsoleTextAttribute(console, 12);
        cout << "No result is found.\n"
             << endl;
        SetConsoleTextAttribute(console, 15);
    }
    else
    {
        displayHunters(result);
        bool state = true;
        do
        {
            string input;
            cout << "Please select a hunter to view his/her details (number):";
            cin >> input;
            cout << "\n";
            try
            {
                int i = stoi(input);
                i--;
                Hunter hunter = result.at(i);
                hunter.displayDetails(++i);
                system("pause");
                cout << endl;
                state = false;
            }
            catch (...)
            {
                printColor("Error !", 12);
                cout << " There is no such selection" << endl;
                continue;
            }
        } while (state);
    }
}

/**************************************************** Selection ***************************************************/
int selectHunter(vector<Hunter> hunter)
{
    displayHunters(hunter);

    int i = 0;
    bool state = true;
    do
    {
        string input;
        cout << "Please select a Hunter by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Hunter selectedHunter = hunter.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            printColor("\nError !", 12);
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);

    return i;
}
int selectPokemon(vector<Pokemon> pokemon)
{

    string line = "----------------------------------------------------------------------------------------------";
    printf("\t\t\t%s \n", line.c_str());
    cout << "\t\t\t                                           POKEMONS                                           " << endl;
    printf("\t\t\t%s \n", line.c_str());
    printf("\t\t\t%5s %-15s %-15s %-10s %-20s %-15s %-15s\n", " ", "Name", "Type", "CP", "Date Captured", "Height", "Weight");
    printf("\t\t\t%s \n", line.c_str());

    int i = 0;
    for (auto &p : pokemon)
    {
        i++;
        SetConsoleTextAttribute(console, 6);
        p.display(i);
    }
    cout << "\n";
    SetConsoleTextAttribute(console, 15);

    bool state = true;
    do
    {
        string input;
        cout << "Please select a Pokemon by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Pokemon selectedPokemon = pokemon.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            printColor("\nError !", 12);
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);
    return i;
}
int selectStop(vector<Pokemon_Stops> pStop)
{

    string line = "----------------------------------------------------------------------------------------------";
    printf("\t\t\t%s \n", line.c_str());
    cout << "\t\t\t                                          Stops                                           " << endl;
    printf("\t\t\t%s \n", line.c_str());
    printf("\t\t\t%-5s %-15s %-15s %-15s\n", " ", "Date", "Time", "Item");
    printf("\t\t\t%s \n", line.c_str());

    int i = 0;
    for (auto &ps : pStop)
    {
        i++;
        SetConsoleTextAttribute(console, 6);
        ps.display(i);
    }
    cout << "\n";
    SetConsoleTextAttribute(console, 15);

    bool state = true;
    do
    {
        string input;
        cout << "Please select a Stop by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Pokemon_Stops selectedStop = pStop.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            printColor("\nError !", 12);
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);
    return i;
}
int selectRaid(vector<Raid> pRaid)
{
    string line = "----------------------------------------------------------------------------------------------";
    printf("\t\t\t%s \n", line.c_str());
    cout << "                                          Raids                                           " << endl;
    printf("\t\t\t%s \n", line.c_str());
    printf("\t\t\t%-5s %-15s %-15s %-15s\n", " ", "Date", "Time", "Venue");
    printf("\t\t\t%s \n", line.c_str());

    int i = 0;
    for (auto &pr : pRaid)
    {
        i++;
        SetConsoleTextAttribute(console, 6);
        pr.display(i);
    }
    cout << "\n";
    SetConsoleTextAttribute(console, 15);

    bool state = true;
    do
    {
        string input;
        cout << "Please select a Raid by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Raid selectedRaid = pRaid.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            printColor("\nError !", 12);
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);
    return i;
}

/**************************************************** Add New Entry ***************************************************/
void addHunter(vector<Hunter> &hunter)
{

    string s;
    string firstName;
    string lastName;
    int level;
    string gender;
    string teamType;
    vector<Pokemon> pokemon;
    vector<Pokemon_Stops> pStop;
    vector<Raid> pRaid;

    SetConsoleTextAttribute(console, 11);
    cout << "--------Filling up the Hunter details--------\n";
    SetConsoleTextAttribute(console, 15);
    getline(cin, gender);

    cout << "First Name: ";
    getline(cin, firstName);
    emptyValid(firstName);
    cout << "Last Name: ";
    getline(cin, lastName);
    emptyValid(lastName);

    cout << "Level: ";
    cin >> level;
    level = intValid(cin.fail(), level, 3);

    cout << "Gender: ";
    cin >> gender;
    genderValid(gender);

    cout << "Team Type: ";
    cin >> teamType;
    teamTypeValid(teamType);

    bool state = true;
    do
    {
        string input;
        SetConsoleTextAttribute(console, 14);
        cout << "\n--Adding a Pokemon details for this hunter? (Y/N) : ";
        SetConsoleTextAttribute(console, 15);

        cin >> input;

        if (input == "Y" || input == "y")
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            string name;
            string type;
            int cp;
            string dateCaptured;
            float height;
            float weight;

            cout << "Pokemon Name: ";
            getline(cin, name);

            cout << "Pokemon Type: ";
            cin >> type;
            pokemonTypeValid(type);

            cout << "Pokemon CP: ";
            cin >> cp;
            cp = intValid(cin.fail(), cp, 2);

            cout << "Date Captured (dd-mm-yyyy): ";
            cin >> dateCaptured;
            dateValid(dateCaptured);

            cout << "Height: ";
            cin >> height;
            height = floatValid(cin.fail(), height, 1);

            cout << "Weight: ";
            cin >> weight;
            weight = floatValid(cin.fail(), weight, 2);

            Pokemon poke = Pokemon(name, type, cp, dateCaptured, height, weight);
            pokemon.push_back(poke);
        }
        else
        {
            state = false;
        }

    } while (state);

    state = true;
    do
    {
        string input;
        getline(cin, input);
        SetConsoleTextAttribute(console, 14);
        cout << "\n--Adding a Stop details for this hunter? (Y/N) : ";
        SetConsoleTextAttribute(console, 15);
        cin >> input;

        if (input == "Y" || input == "y")
        {
            string date;
            string time;
            string items;

            cout << "Stop Date (dd-mm-yyy): ";
            cin >> date;
            dateValid(date);

            cout << "Stop Time (hh:mm): ";
            cin >> time;
            timeValid(time);

            cout << "Stop Item: ";
            cin >> items;

            Pokemon_Stops poke = Pokemon_Stops(date, time, items);
            pStop.push_back(poke);
        }
        else
        {
            state = false;
        }

    } while (state);

    state = true;
    do
    {
        string input;
        getline(cin, input);
        SetConsoleTextAttribute(console, 14);
        cout << "\n--Adding a Raid details for this hunter? (Y/N) : ";
        SetConsoleTextAttribute(console, 15);
        cin >> input;

        if (input == "Y" || input == "y")
        {
            string date;
            string time;
            string venue;

            cout << "Raid Date (dd-mm-yyy): ";
            cin >> date;
            dateValid(date);

            cout << "Raid Time (hh:mm): ";
            cin >> time;
            timeValid(time);

            cout << "Raid Venue: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, venue);
            emptyValid(venue);

            Raid poke = Raid(date, time, venue);
            pRaid.push_back(poke);
        }
        else
        {
            state = false;
        }

    } while (state);

    Hunter hunt = Hunter(firstName, lastName, level, gender, teamType, pokemon, pStop, pRaid);
    hunt.sortPokemon();
    hunter.push_back(hunt);
    writeHunter(hunter);

    SetConsoleTextAttribute(console, 10);
    printf("\n* Hunter %s %s has successfully registered into the Journal *\n", firstName.c_str(), lastName.c_str());
    SetConsoleTextAttribute(console, 15);
}
void addPokemonToHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }
    int i = selectHunter(hunter);
    Hunter added = hunter.at(i);

    string name;
    string type;
    int cp;
    string dateCaptured;
    float height;
    float weight;

    SetConsoleTextAttribute(console, 11);
    printf("------ Adding new Pokemon to Hunter %s ------\n", added.lastName.c_str());
    SetConsoleTextAttribute(console, 15);

    cout << "Pokemon Name: ";
    cin >> name;
    cout << "Pokemon Type: ";
    cin >> type;
    pokemonTypeValid(type);
    cout << "CP: ";
    cin >> cp;
    cp = intValid(cin.fail(), cp, 2);
    cout << "Date Captured (dd-mm-yyy): ";
    cin >> dateCaptured;
    dateValid(dateCaptured);
    cout << "Height: ";
    cin >> height;
    height = floatValid(cin.fail(), height, 1);
    cout << "Weight: ";
    cin >> weight;
    weight = floatValid(cin.fail(), height, 2);

    Pokemon poke = Pokemon(name, type, cp, dateCaptured, height, weight);
    hunter.at(i).pokemon.push_back(poke);
    hunter.at(i).sortPokemon();

    added = hunter.at(i);
    added.displayDetails(++i);
    writeHunter(hunter);

    SetConsoleTextAttribute(console, 10);
    printf("\n* Added new Pokemon %s to Hunter %s *\n", poke.name.c_str(), added.lastName.c_str());
    SetConsoleTextAttribute(console, 15);
}
void addStopToHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }
    int i = selectHunter(hunter);
    Hunter added = hunter.at(i);

    string date;
    string time;
    string items;

    SetConsoleTextAttribute(console, 11);
    printf("------ Adding new Stop to Hunter %s ------\n", added.lastName.c_str());
    SetConsoleTextAttribute(console, 15);

    cout << "Date (dd-mm-yyy): ";
    cin >> date;
    dateValid(date);
    cout << "Time (hh:mm): ";
    cin >> time;
    timeValid(time);
    cout << "Item: ";
    cin >> items;

    Pokemon_Stops stop = Pokemon_Stops(date, time, items);
    hunter.at(i).pStop.push_back(stop);

    added = hunter.at(i);
    added.displayDetails(++i);
    writeHunter(hunter);

    SetConsoleTextAttribute(console, 10);
    printf("\n* Added new Stop to Hunter %s *\n", added.lastName.c_str());
    SetConsoleTextAttribute(console, 15);
}
void addRaidToHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }
    int i = selectHunter(hunter);
    Hunter added = hunter.at(i);

    string date;
    string time;
    string venue;

    SetConsoleTextAttribute(console, 11);
    printf("------ Adding new Raid to Hunter %s ------\n", added.lastName.c_str());
    SetConsoleTextAttribute(console, 15);

    cout << "Date (dd-mm-yyy): ";
    cin >> date;
    dateValid(date);
    cout << "Time (hh:mm): ";
    cin >> time;
    timeValid(time);
    cout << "Venue: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, venue);
    emptyValid(venue);

    Raid raid = Raid(date, time, venue);
    hunter.at(i).pRaid.push_back(raid);

    added = hunter.at(i);
    added.displayDetails(++i);
    writeHunter(hunter);

    SetConsoleTextAttribute(console, 10);
    printf("\n* Added new Raid at %s to Hunter %s *\n", raid.venue.c_str(), added.lastName.c_str());
    SetConsoleTextAttribute(console, 15);
}

/**************************************************** Delete Entry ***************************************************/
void deleteHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
    }
    else
    {

        int i = selectHunter(hunter);
        Hunter deletedHunter = hunter.at(i);
        hunter.erase(hunter.begin() + i);
        writeHunter(hunter);

        SetConsoleTextAttribute(console, 12);
        printf("\n* Hunter %s %s has successfully deleted from the journal *\n", deletedHunter.firstName.c_str(), deletedHunter.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
}
void deletePokemon(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }
    int i = selectHunter(hunter);
    vector<Pokemon> pokemon = hunter.at(i).pokemon;
    Hunter hunt = hunter.at(i);

    if (pokemon.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* Hunter %s does not own any Pokemon yet *\n", hunt.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
    else
    {
        int k = selectPokemon(pokemon);
        Pokemon deletedPokemon = hunter.at(i).pokemon.at(k);
        pokemon.erase(pokemon.begin() + k);
        hunter.at(i).pokemon = pokemon;

        writeHunter(hunter);

        SetConsoleTextAttribute(console, 12);
        printf("\n* Pokemon %s has successfully deleted from the Hunter %s *\n", deletedPokemon.name.c_str(), hunt.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
}
void deleteStop(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }

    int i = selectHunter(hunter);
    vector<Pokemon_Stops> stop = hunter.at(i).pStop;
    Hunter hunt = hunter.at(i);

    if (stop.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* Hunter %s has not been to any Stop yet *\n", hunt.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
    else
    {

        int k = selectStop(stop);
        Pokemon_Stops deletedStop = hunter.at(i).pStop.at(k);
        stop.erase(stop.begin() + k);
        hunter.at(i).pStop = stop;
        writeHunter(hunter);

        SetConsoleTextAttribute(console, 12);
        printf("\n* Stop on %s at %s has successfully deleted from the Hunter %s *\n", deletedStop.date.c_str(), deletedStop.time.c_str(), hunt.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
}
void deleteRaid(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* There is no hunter registered yet *\n");
        SetConsoleTextAttribute(console, 15);
        return;
    }

    int i = selectHunter(hunter);
    vector<Raid> raid = hunter.at(i).pRaid;
    Hunter hunt = hunter.at(i);

    if (raid.empty())
    {
        SetConsoleTextAttribute(console, 12);
        printf("\n* Hunter %s has not been to any Raid yet *\n", hunt.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
    else
    {

        int k = selectRaid(raid);
        Raid deletedRaid = hunter.at(i).pRaid.at(k);
        raid.erase(raid.begin() + k);
        hunter.at(i).pRaid = raid;
        writeHunter(hunter);

        SetConsoleTextAttribute(console, 12);
        printf("\n* Raid on %s at %s has successfully deleted from the Hunter %s *\n", deletedRaid.date.c_str(), deletedRaid.venue.c_str(), hunt.lastName.c_str());
        SetConsoleTextAttribute(console, 15);
    }
}

/**************************************************** Loops ***************************************************/
void searchHunterLoop(vector<Hunter> hunter)
{
    // system("CLS");
    int input4 = 0;
    string search;
    do
    {
        SetConsoleTextAttribute(console, 11);
        cout << "\n------Search Hunter By------" << endl;
        SetConsoleTextAttribute(console, 15);
        cout << "1) First Name" << endl;
        cout << "2) Last Name" << endl;
        cout << "3) Level" << endl;
        cout << "4) Gender" << endl;
        cout << "5) Team Type" << endl;
        cout << "6) Back to Main Menu\n\n";

        cout << "Option : ";
        cin >> input4;
        cout << "\n";

        switch (input4)
        {
        case 1:
            getline(cin, search);
            cout << "Search Hunters by first name : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "firstName", search);
            break;
        case 2:
            getline(cin, search);
            cout << "Search Hunters by last name : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "lastName", search);
            break;
        case 3:
            getline(cin, search);
            cout << "Search Hunters by level : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "level", search);
            break;
        case 4:
            getline(cin, search);
            cout << "Search Hunters by gender : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "gender", search);
            break;
        case 5:
            getline(cin, search);
            cout << "Search Hunters by team type : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "teamType", search);
            break;
        case 6:
            break;
        default:
            cout << "*Please enter the available option*\n";
            break;
        }
    } while (input4 != 6);
}
void addNewEntryLoop(vector<Hunter> &hunter)
{

    int input2 = 0;
    do
    {
        SetConsoleTextAttribute(console, 11);
        cout << "\n----------Add new entry----------" << endl;
        SetConsoleTextAttribute(console, 15);
        cout << "1) Register a new Hunter" << endl;
        cout << "2) Add new Pokemon to an existing Hunter" << endl;
        cout << "3) Add new Stop to an existing Hunter" << endl;
        cout << "4) Add new Raid to an existing Hunter" << endl;
        cout << "5) Back to Main Menu \n\n";

        cout << "Option : ";
        cin >> input2;
        cout << "\n";
        input2 = intValid(cin.fail(), input2, 1);

        switch (input2)
        {
        case 1:
            // Register a new hunter
            addHunter(hunter);
            break;
        case 2:
            // Add new pokemon
            addPokemonToHunter(hunter);
            break;
        case 3:
            // Add new stop
            addStopToHunter(hunter);
            break;
        case 4:
            // Add new raid
            addRaidToHunter(hunter);
            break;
        case 5:
            // Return back to Main Menu
            break;
        default:
            cout << "*Please enter the available option*\n";
            break;
        }

    } while (input2 != 5);
}
void deleteEntryLoop(vector<Hunter> &hunter)
{
    int input3 = 0;
    do
    {
        SetConsoleTextAttribute(console, 11);
        cout << "\n----------Delete Entry----------" << endl;
        SetConsoleTextAttribute(console, 15);
        cout << "1) Delete an existing Hunter" << endl;
        cout << "2) Delete a Pokemon from a Hunter" << endl;
        cout << "3) Delete a Stop from a Hunter" << endl;
        cout << "4) Delete a Raid from a Hunter" << endl;
        cout << "5) Back to Main Menu\n\n";

        cout << "Option : ";
        cin >> input3;
        cout << "\n";
        input3 = intValid(cin.fail(), input3, 1);

        switch (input3)
        {
        case 1:
            deleteHunter(hunter);
            break;
        case 2:
            deletePokemon(hunter);
            break;
        case 3:
            deleteStop(hunter);
            break;
        case 4:
            deleteRaid(hunter);
            break;
        case 5:
            break;
        default:
            cout << "*Please enter the available option*\n";
            break;
        }

    } while (input3 != 5);
}

/**************************************************** MAIN***************************************************/
int main()
{
    // system("Color 0F");

    vector<Hunter> hunter;
    readHunter(hunter);
    bool state = true;
    int input = 0;

    do
    {
        // system("CLS");
        //Create a list and let user to choose
        SetConsoleTextAttribute(console, 14);
        cout << "\n\n WELCOME to Pokemon Journal \n\n";
        SetConsoleTextAttribute(console, 11);
        cout << "---------Main Menu---------" << endl;
        SetConsoleTextAttribute(console, 15);
        cout << "1) Show all Hunters details" << endl;
        cout << "2) Add new entry" << endl;
        cout << "3) Delete an entry" << endl;
        cout << "4) Search Hunters" << endl;
        cout << "5) Exit The Program\n\n";
        cout << "Option: ";
        cin >> input;
        input = intValid(cin.fail(), input, 1);
        switch (input)
        {
        case 1:
            displayHuntersDetails(hunter);
            break;
        case 2:
            addNewEntryLoop(hunter);
            break;
        case 3:
            deleteEntryLoop(hunter);
            break;
        case 4: // Search Hunters with First Name, Last Name, Level, Gender, Team Type
            searchHunterLoop(hunter);
            break;
        case 5:
            writeHunter(hunter);
            cout << "Saving data and exiting the program...";
            break;

        default:
            cout << "Please enter the available option.";
            break;
        }
    } while (input != 5);
    return 0;
}
