#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;
    again = true;

    while (again) {
        int choice = main_menu();

        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                again = false;
                cout << "\nGoodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}




int main_menu() {
    int choice;

    cout << "\n===== GOAT MENU =====\n";
    cout << "1. Add Goat\n";
    cout << "2. Delete Goat\n";
    cout << "3. Display Trip\n";
    cout << "4. Quit\n";
    cout << "Enter your choce";
    cin >> choice;

    return choice;
}

void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "\nThere are no goat in the trip\n";
        return;
    }

    cout << "\n===== GOAT TRIP =====\n";
    int count = 1;

    for (Goat g : trip) {
        cout << count << ". "
             << left << setw(12) << g.get_name()
             << setw(8) << g.get_age()
             << g.get_color() << endl;
        count++;
    }
}


void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    int age = rand() % MAX_AGE +1;
    string color = colors[rand() % SZ_COLORS];

    Goat g(name, age, color);
    trip.push_back(g);
    trip.sort();

    cout << "Added goat:\n";
    cout << g.get_name() 
         << g.get_age()
         << g.get_color() << endl;
}

int select_goat(list<Goat> trip) {
    if (trip.empty()) {
        return -1;
    }

    display_trip(trip);

    int choice;
    cout << "\nSelect a goat by number: ";
    cin >> choice;

    return choice;
}


void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "There are no goats to delete";
        return;
    }

    int choice = select_goat(trip);

    if (choice < 1 || choice > trip.size()) {
        cout << "Invalid selection";
        return;
    }

    auto it = trip.begin();
    advance(it, choice - 1);

    cout << "\nDeleted goat:\n";
    cout << it->get_name() 
         << it->get_age() 
         << it->get_color() << endl;

    trip.erase(it);
}