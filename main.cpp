#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

struct Habit {
    string name;
    int type;           
    int time;            
    string prerequisite; 
    string group;
    int lastDone;
    int streak; };

int main() {
    Habit habits[100];
    int count = 0;
    int opt;
    int p;


    ifstream inFile("habits.txt");
    while (count < 100 && getline(inFile, habits[count].name)) {
        inFile >> habits[count].type >> habits[count].time;
        inFile.ignore(1000, '\n');
        getline(inFile, habits[count].prerequisite);
        getline(inFile, habits[count].group);
        count++;
    }
    inFile.close();

    int today = (time(0) + 25200) / 86400;

    for (int i = 0; i < count; i++) {
        if (habits[i].lastDone != 0 && today - habits[i].lastDone >= 2) {
            cout << "\nYou missed: " << habits[i].name << endl;
            cout << "Write a reflection before you can continue.\n";
            cout << "- Why did you forget to do this habit?\n";
            cout << "- What prevented you from doing it?\n";
            cout << "- What concrete action will you take so it happens less?\n";

            string reflection;
            int words;
            do {
                cout << "Write your reflection: ";
                getline(cin, reflection);

                words = 0;
                bool inWord = false;
                for (int k = 0; k < reflection.length(); k++) {
                    if (reflection[k] != ' ' && inWord == false) {
                        words++;
                        inWord = true;
                    } else if (reflection[k] == ' ') {
                        inWord = false;
                    }
                }

                if (words < 100) {
                    cout << "Only " << words << " words, you need at least 100.\n";
                }
            } while (words < 100);

            ofstream refFile("reflections.txt", ios::app);
            refFile << habits[i].name << endl;
            refFile << reflection << endl;
            refFile.close();

            habits[i].streak = 0;
            habits[i].lastDone = 0;

            ofstream saveFile("habits.txt");
            for (int j = 0; j < count; j++) {
                saveFile << habits[j].name << endl;
                saveFile << habits[j].type << " " << habits[j].time << " " << habits[j].lastDone << " " << habits[j].streak << endl;
                saveFile << habits[j].prerequisite << endl;
                saveFile << habits[j].group << endl;
            }
            saveFile.close();
        }
    }

    do {
        cout << "\nMain Menu\n1. Add habit\n2. View habits\n0. Exit\nChoose: ";
        cin >> opt;
        cin.ignore(1000, '\n');

        switch (opt) {
        case 1: {
            if (count >= 100) {
                cout << "Habit list is full.\n";
                break;
            }

            Habit h;

            do {
                cout << "What habit do you want to create? ";
                getline(cin, h.name);
                if (h.name == "") {
                    cout << "Name can't be empty.\n";
                }
            } while (h.name == "");

            h.time = -1;
            h.prerequisite = "";
            h.group = "";

            int mtd;
            if (count == 0) {
                cout << "This is your first habit, so it will be time based\n";
                mtd = 1;
            } else {
                cout << "What method would you prefer?\n";
                cout << "1. Time\n2. Pre-existing habit\n";
                cin >> mtd;
                cin.ignore(1000, '\n');
            }

            if (mtd == 1) {
                h.type = 1;
                cout << "What time (00.00 - 23.00, only write hour) will this habit be done? ";
                cin >> h.time;
                cin.ignore(1000, '\n');
                while (h.time < 0 || h.time > 23) {
                    cout << "Please enter a number from 0 to 23: ";
                    cin >> h.time;
                    cin.ignore(1000, '\n');
                }
            } else if (mtd == 2) {
                h.type = 2;

               
                cout << "Which habit comes before this one?\n";
                for (int i = 0; i < count; i++) {
                    cout << i + 1 << ". " << habits[i].name << endl;
                }
             
                cin >> p;
                cin.ignore(1000, '\n');
                while (p < 1 || p > count) {
                    cout << "Please pick a number from the list: ";
                    cin >> p;
                    cin.ignore(1000, '\n');
                }
                h.prerequisite = habits[p - 1].name;

               
                int newGroup;
                cout << "Create a new grouped habit? 1. Yes  2. No: ";
                cin >> newGroup;
                cin.ignore(1000, '\n');

            
                if (newGroup == 1 || habits[p - 1].group == "") {
                    string title;
                    cout << "Grouped habit title: ";
                    getline(cin, title);
                    h.group = title;
                    habits[p - 1].group = title; 
                } else {
                    h.group = habits[p - 1].group; 
                }
            } else {
                cout << "Error occured - please give the right number\n";
                break;
            }

            habits[count] = h;
            count++;

           
            ofstream outFile("habits.txt");
            for (int i = 0; i < count; i++) {
                outFile << habits[i].name << endl;
                outFile << habits[i].type << " " << habits[i].time << endl;
                outFile << habits[i].prerequisite << endl;
                outFile << habits[i].group << endl;
            }
            outFile.close();
            cout << "Habit saved!\n";
            break;
        }

        case 2:
            if (count == 0) {
                cout << "No habits yet.\n";
            }
            for (int i = 0; i < count; i++) {
                cout << i + 1 << ". " << habits[i].name;
                if (habits[i].type == 1) {
                    cout << " (at " << habits[i].time << ":00)";
                } else {
                    cout << " (after " << habits[i].prerequisite << ")";
                }
                if (habits[i].group != "") {
                    cout << " [group: " << habits[i].group << "]";
                }
                cout << endl;
            }
            break;

        case 0:
            cout << "Bye!\n";
            break;

        default:
            cout << "Error occured - please give the right number\n";
        }
    } while (opt != 0);

    return 0;
}

