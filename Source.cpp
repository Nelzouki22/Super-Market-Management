#include <windows.h>
#include <mmsystem.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
using namespace std;

// Class for item
class item {
    int ino;
    char name[100];
    float price, qty, tax, dis;

public:
    void create_item() {
        cout << "\n\nPlease Enter The No. of The Item : ";
        cin >> ino;
        cout << "\nPlease Enter The Name of The Item : ";
        cin.ignore();
        cin.getline(name, 100);
        cout << "\nPlease Enter The price of The Item : ";
        cin >> price;
        cout << "\nPlease Enter The Discount (%): ";
        cin >> dis;
    }

    void show_item() {
        cout << "\nThe Item No. of The Item : " << ino;
        cout << "\nThe Name of The Item : " << name;
        cout << "\nThe price of The Item : " << price;
        cout << "\nDiscount : " << dis;
    }

    int retino() { return ino; }

    float retprice() { return price; }

    char* retname() { return name; }

    int retdis() { return dis; }
};

// Function prototypes
void write_item();
void display_all();
void display_sp(int n);
void modify_item();
void delete_item();
void menu();
void place_order();
void main_menu();

// Global fstream object
fstream fp;
item itm;

// Function to write item to file
void write_item() {
    fp.open("Shop.dat", ios::out | ios::app);
    char a;
    cout << "\n\nPlease Enter Item Details:\n";
    do {
        itm.create_item();
        fp.write(reinterpret_cast<char*>(&itm), sizeof(item));
        cout << "\nDo you want to add another item? (y/n): ";
        cin >> a;
    } while (a == 'y' || a == 'Y');
    fp.close();
}

// Function to display all items
void display_all() {
    system("cls");
    cout << "\n\n\t\tDISPLAY ALL ITEMS\n\n";
    fp.open("Shop.dat", ios::in);
    while (fp.read(reinterpret_cast<char*>(&itm), sizeof(item))) {
        itm.show_item();
        cout << "\n\n";
    }
    fp.close();
    cout << "\n\n";
    system("pause");
}

// Function to display specific item
void display_sp(int n) {
    int flag = 0;
    fp.open("Shop.dat", ios::in);
    while (fp.read(reinterpret_cast<char*>(&itm), sizeof(item))) {
        if (itm.retino() == n) {
            itm.show_item();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nRecord not found";
    cout << "\n\n";
    system("pause");
}

// Function to modify item
void modify_item() {
    int no, found = 0;
    system("cls");
    cout << "\n\n\tModify Item";
    cout << "\n\n\tEnter The Item No. to Modify: ";
    cin >> no;
    fp.open("Shop.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&itm), sizeof(item)) && found == 0) {
        if (itm.retino() == no) {
            itm.show_item();
            cout << "\n\n\tEnter New Details:\n";
            itm.create_item();
            int pos = -1 * static_cast<int>(sizeof(itm));
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&itm), sizeof(item));
            cout << "\n\n\tRecord Updated\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\nRecord Not Found\n";
    cout << "\n\n";
    system("pause");
}

// Function to delete item
void delete_item() {
    int no;
    system("cls");
    display_all();
    cout << "\n\n\tDelete Record";
    cout << "\n\n\tEnter The Item No. to Delete: ";
    cin >> no;
    cout << "\nAre you sure? (y/n): ";
    char a;
    cin >> a;
    if (a == 'y' || a == 'Y') {
        fp.open("Shop.dat", ios::in | ios::out);
        fstream fp2;
        fp2.open("Temp.dat", ios::out);
        fp.seekg(0, ios::beg);
        while (fp.read(reinterpret_cast<char*>(&itm), sizeof(item))) {
            if (itm.retino() != no)
                fp2.write(reinterpret_cast<char*>(&itm), sizeof(item));
        }
        fp2.close();
        fp.close();
        remove("Shop.dat");
        rename("Temp.dat", "Shop.dat");
        cout << "\n\n\tRecord Deleted\n";
    }
    cout << "\n\n";
    system("pause");
}

// Function to display menu
void menu() {
    system("cls");
    fp.open("Shop.dat", ios::in);
    if (!fp) {
        cout << "Error: File could not be opened\n\n";
        cout << "Go to Admin Menu to create File\n";
        cout << "Program is closing...\n";
        exit(0);
    }

    cout << "\n\t\tITEM MENU\n\n";
    cout << "==============================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "==============================\n";
    while (fp.read(reinterpret_cast<char*>(&itm), sizeof(item))) {
        cout << itm.retino() << "\t\t" << itm.retname() << "\t\t" << itm.retprice() << "\n";
    }
    cout << "==============================\n\n";
    fp.close();
    system("pause");
}

// Function to place order and generate bill for items
void place_order() {
    // Function body for place_order
}

// Function to display main menu
void main_menu() {
    system("cls");
    cout << "\n\n\n\tMAIN MENU\n";
    cout << "===========================\n";
    cout << "\t1. Customer\n";
    cout << "\t2. Administrator\n";
    cout << "\t3. About the Project\n";
    cout << "\t4. Exit\n";
    cout << "===========================\n";
    cout << "Enter your choice (1-4): ";
}

// Main function
int main() {
    char ch;
    do {
        main_menu();
        cin >> ch;
        switch (ch) {
        case '1':
            // Call function for customer
            break;
        case '2':
            // Call function for administrator
            break;
        case '3':
            // About the project
            break;
        case '4':
            exit(0);
        default:
            cout << "Invalid choice! Please try again.\n";
            system("pause");
        }
    } while (ch != '4');
    return 0;
}
