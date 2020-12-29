// Snapchat Streak Calculator
// by shdw9
// Discord - shdw#0009

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>


using namespace std;

//
// TIME METHODS
//

int getMonth() {
    int month;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    month = 1 + ltm->tm_mon;
    return month;
}

int getYear() {
    int year;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    return year;
}

int getDay() {
    int day;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    day = ltm->tm_mday;
    return day;
}

void menu() {
    cout << "\n1 - Save Streaks \ 2 - Read Streaks Log \ 3 - Exit Program\n" << endl;
    int option;
    cin >> option;
    if (option == 1) {
        cout << "\n---------------------------------------" << endl;
        int numOfStreaks;
        string streakName;
        int streakNum;

        int dateOpt;
        string date;

        int month;
        int year;
        int day;

        ofstream streakLog;

        cout << "\nHow many streaks would you like to save? \n" << endl;
        cin >> numOfStreaks;

        cout << "\n--------------------------------" << endl;
        cout << "\nWhich date would you like to use?" << endl;
        cout << "1 - Today \t 2 - Custom Date\n" << endl;
        cin >> dateOpt;

        if (dateOpt == 1) {
            month = getMonth();
            day = getDay();
            year = getYear();
        }
        else if (dateOpt == 2) {
            cout << "\n--------------------------------" << endl;
            cout << "\nMonth? ";
            cin >> month;
            cout << "Day? ";
            cin >> day;
            cout << "Year? ";
            cin >> year;
        }

        cout << "\nNow logging from the date " << month << "-" << day << "-" << year << endl;
        cout << "\n--------------------------------" << endl;
        cout << "Please input " << numOfStreaks << " streak names and streak numbers\n" << endl;

        streakLog.open("snapchatstreaks.txt");
        for (int i = 0; i < numOfStreaks; i++) {
            cout << "Streak Name " << i + 1 << ": ";
            cin >> streakName;
            cout << "Streak Number " << i + 1 << ": ";
            cin >> streakNum;
            streakLog << streakName << " " << streakNum << " " << month << "-" << day << "-" << year << endl;
            cout << "\n";
            cout << streakName << " - " << streakNum << " saved!\n" << endl;
        }
        cout << "--------------------------------" << endl;
        cout << "\nStreaks saved! You can now read the streak log\n" << endl;
        cout << "--------------------------------\n" << endl;
        streakLog.close();
        menu();
    }
    if (option == 2) {
        cout << "---------------------------------------" << endl;
        string streakName;
        int streakNum;
        string dateLogged;
        ifstream inputfile("snapchatstreaks.txt");

        cout << "Streak Name\tStreak Number" << endl;
        if (inputfile.is_open()) {

            while (true) {

                inputfile >> streakName;
                inputfile >> streakNum;
                inputfile >> dateLogged;

                cout << streakName << "\t\t" << streakNum << endl;

                if (inputfile.eof()) {
                    cout << "\nThis log was last saved on " << dateLogged << endl;
                    cout << "---------------------------------------" << endl;
                    break;
                }

            }
        }
        inputfile.close();
        menu();
    }
    if (option == 3) {
        cout << "---------------------------------------" << endl;
        cout << "C\tL\tO\tS\tI\tN\tG" << endl;;
        cout << "---------------------------------------" << endl;
    }
}

int main()
{
    cout << "---------------------------------------" << endl;
    cout << "\nWelcome to shdw's Snapchat Streak Calculator! \n";
    cout << "Current Date: " << getMonth() << " - " << getDay() << " - " << getYear() << endl;
    cout << "\n---------------------------------------" << endl;
    menu();
}
