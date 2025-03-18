#include "List.h"
#include "validators.h"
#include <iostream>
#include <functional>

using namespace std;

void printPerson(Person* p) {
    cout << "Name: " << p->name << ", Phone: " << p->phoneNumber << ", Age: " << p->age << endl;
}

int main() {
    List phoneBook;
    int choice;

    while (true) {
        cout << "\nPhone Book Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Delete Contact\n";
        cout << "3. Search Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Count Contacts\n";
        cout << "6. Clear Phone Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name = inputValidatedName("Enter name: ", false);
            string phone = inputValidatedPhoneNumber("Enter phone number (+375 XX XXX XX XX): ");
            int age = inputValidatedInt("Enter age(1 - 120): ", 1, 120);

            Person* newPerson = new Person{ name, phone, age };
            phoneBook.InsertEnd(newPerson);
            cout << "Contact added successfully!\n";
            break;
        }
        case 2: {
            string name = inputValidatedName("Enter name to delete: ", false);
            if (phoneBook.Delete(name))
                cout << "Contact deleted successfully!\n";
            else
                cout << "Contact not found!\n";
            break;
        }
        case 3: {
            string name = inputValidatedName("Enter name to search: ", false);
            Element* result = phoneBook.Search(name);
            if (result)
                printPerson(result->Data);
            else
                cout << "Contact not found!\n";
            break;
        }
        case 4: {
            cout << "\nAll Contacts:\n";
            phoneBook.PrintList(printPerson);
            break;
        }
        case 5: {
            cout << "Total contacts: " << phoneBook.CountList() << endl;
            break;
        }
        case 6: {
            phoneBook.DeleteList();
            cout << "Phone book cleared!\n";
            break;
        }
        case 7: {
            cout << "Exiting...\n";
            return 0;
        }
        default: {
            cout << "Invalid choice! Please try again.\n";
            break;
        }
        }
    }

    return 0;
}