// Snapchat Streak Calculator
// by shdw9
// Discord - shdw#0009

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>


using namespace std;

struct tm* foo;
struct stat attrib;

//
// DATE METHODS 
//

int check_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)   //if year is a leap year
        return 1;

    else
        return 0;
}
int no_of_days_in_month(int month, int year)
{
    // jan, march, may, july, aug, oct, dec contains 31 days
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;

    // april, jun, sept, nov contains 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    if (month == 2)
    {
        int n = check_leap_year(year);
        if (n == 1)    // if year is a leap year then Feb will contain 29 days, otherwise it contains 28 days
            return 29;

        else
            return 28;
    }
}
long long int difference_of_days(int day1, int month1, int year1, int day2, int month2, int year2)
{
    if (year1 == year2)
    {
        if (month1 == month2)
        {
            if (day1 == day2)      //for same dates
                return 0;
            else
                return abs(day1 - day2);  //for same year, same month but diff days
        }
        else if (month1 < month2)
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)      //for same year, same day but diff month 
                return result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return result;
            }
            else
            {
                result = result - (day1 - day2);
                return result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)
                return result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return result;
            }
            else
            {
                result = result - (day2 - day1);
                return result;
            }
        }
    }
    else if (year1 < year2)
    {
        int temp = 0;
        for (int i = year1; i < year2; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (month1 == month2)
        {
            if (day1 == day2)      //for same month, same day but diff year
                return temp;
            else if (day1 < day2)
                return temp + (day2 - day1);
            else
                return temp - (day1 - day2);
        }
        else if (month1 < month2)
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year2);

            if (day1 == day2)      // for same day, diff year and diff month
                return temp + result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return temp + result;
            }
            else
            {
                result = result - (day1 - day2);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year2);

            if (day1 == day2)
                return temp - result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return temp - result;
            }
            else
            {
                result = result - (day2 - day1);
                return temp - result;
            }
        }
    }
    else
    {
        int temp = 0;
        for (int i = year2; i < year1; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (month1 == month2)
        {
            if (day1 == day2)      // for same day, same month but diff year
                return temp;
            else if (day2 < day1)
                return temp + (day1 - day2);
            else
                return temp - (day2 - day1);
        }
        else if (month2 < month1)
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)
                return temp + result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return temp + result;
            }
            else
            {
                result = result - (day2 - day1);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)      // for same day, diff year and diff month
                return temp - result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return temp - result;
            }
            else
            {
                result = result - (day1 - day2);
                return temp - result;
            }
        }
    }
}

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
    cout << "\n1 - Save Streaks \ 2 - Read Streaks \ 3 - Calculate Streaks \ 4 - Exit Program\n" << endl;
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
    if (option == 4) {
        cout << "---------------------------------------" << endl;
        cout << "C\tL\tO\tS\tI\tN\tG" << endl;;
        cout << "---------------------------------------" << endl;
    }
    if (option == 3) {
        int option;
        int day1;
        int day2;
        int month1;
        int month2;
        int year1;
        int year2;
        int oldstreak;
        int newstreak;

        cout << "---------------------------------------" << endl;
        cout << "\nCalculate Streak\n" << endl;
        cout << "1 - Individual Streak \ 2 - Last Streak Log?" << endl;
        cin >> option;

        if (option == 1) {

            cout << "\n--------------------------------" << endl;
            cout << "\nWhat number was their streak?\n" << endl;
            cin >> oldstreak;
            cout << "--------------------------------" << endl;
            cout << "\nWhat was the date of this old streak?\n" << endl;
            cout << "Month? ";
            cin >> month1;
            cout << "Day? ";
            cin >> day1;
            cout << "Year? ";
            cin >> year1;
            
            cout << "\n--------------------------------" << endl;
            cout << "\nWhich date would you like to use?" << endl;
            cout << "1 - Today \t 2 - Custom Date\n" << endl;
            cin >> option;

            if (option == 1) {
                month2 = getMonth();
                day2 = getDay();
                year2 = getYear();
            }
            else if (option == 2) {
                cout << "\n--------------------------------" << endl;
                cout << "\nMonth? ";
                cin >> month2;
                cout << "Day? ";
                cin >> day2;
                cout << "Year? ";
                cin >> year2;
            }

            cout << "--------------------------------" << endl;
            cout << "Now calculating the difference from " << month1 << "/" << day1 << "/" << year1 << " up to " << month2 << "/" << day2 << "/" << year2 << endl;
            long long int diff = difference_of_days(day1, month1, year1, day2, month2, year2);
            cout << "The difference is " << diff << " days" << endl;
            cout << "Meaning that your streak should be at " << oldstreak + diff << ". " << endl;
            cout << "--------------------------------" << endl;
            menu();
        }
        if (option == 2) {
            cout << "\n---------------------------------------" << endl;
            string streakName;
            int streakNum;
            string dateLogged;
            ifstream inputfile("snapchatstreaks.txt");

            cout << "\nWhen was this streak log last modified? (Use Read Streaks feature)" << endl;
            cout << "Input format: 12 31 2000" << endl;
            cin >> month1 >> day1 >> year1;

            cout << "\n--------------------------------" << endl;
            cout << "\nWhich date would you like to use?" << endl;
            cout << "1 - Today \t 2 - Custom Date" << endl;
            cin >> option;

            if (option == 1) {
                month2 = getMonth();
                day2 = getDay();
                year2 = getYear();
            }
            else if (option == 2) {
                cout << "\nMonth? ";
                cin >> month2;
                cout << "Day? ";
                cin >> day2;
                cout << "Year? ";
                cin >> year2;
            }

            cout << "\n--------------------------------" << endl;
            
            //
            // read file and take last editted
            //



            cout << "\nNow calculating the difference from " << month1 << "/" << day1 << "/" << year1 << " up to " << month2 << "/" << day2 << "/" << year2 << endl;
            long long int diff = difference_of_days(day1, month1, year1, day2, month2, year2);
            cout << "The difference is " << diff << " days\n" << endl;
            cout << "--------------------------------" << endl;
            cout << "\nThis is how your streaks are supposed to look like:" << endl;
            cout << "Streak Name\tStreak Number" << endl;

            if (inputfile.is_open()) {

                while (true) {

                    inputfile >> streakName;
                    inputfile >> streakNum;
                    inputfile >> dateLogged;

                    cout << streakName << "\t\t" << streakNum + diff << endl;

                    if (inputfile.eof()) {
                        break;
                    }

                }
            }
            inputfile.close();
            cout << "\n---------------------------------------" << endl;
            menu();
        }

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
