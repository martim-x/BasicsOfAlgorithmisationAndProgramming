#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
#include "validators.h"

using namespace std;


enum ProductType {
    JEWELRY,
    ELECTRONICS,
    FURNITURE,
    VEHICLES,
    OTHERS,
    PRODUCT_TYPE_COUNT
};


string productTypeToString(ProductType pt) {
    switch (pt) {
    case JEWELRY:      return "Jewelry";
    case ELECTRONICS:  return "Electronics";
    case FURNITURE:    return "Furniture";
    case VEHICLES:     return "Vehicles";
    case OTHERS:       return "Others";
    default:           return "Unknown";
    }
}


struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;
};


struct PawnItem {
    string clientLastName;
    string productName;
    ProductType productType;
    double appraisedValue;
    double pawnedAmount;
    Date depositDate;
    int storagePeriod;
};


Date inputDate() {
    Date d;
    d.day = inputValidatedInt("Enter day (1-31): ", 1, 31);
    d.month = inputValidatedInt("Enter month (1-12): ", 1, 12);
    d.year = inputValidatedInt("Enter year (1900-2099): ", 1900, 2099);
    return d;
}


ProductType inputProductType() {
    cout << "Select product type:\n"
        << "1. Jewelry\n"
        << "2. Electronics\n"
        << "3. Furniture\n"
        << "4. Vehicles\n"
        << "5. Others\n";
    int choice = inputValidatedInt("Choice (1-5): ", 1, 5);
    return static_cast<ProductType>(choice - 1);
}


void addPawnItem(vector<PawnItem>& items) {
    PawnItem item;
    item.clientLastName = inputValidatedString("Enter client's last name: ", " -", false);
    item.productName = inputValidatedString("Enter product name: ", " -", false);
    item.productType = inputProductType();
    item.appraisedValue = inputValidatedDouble("Enter appraised value (0.01 - 100000.0): ", 0.01, 100000.0);
    item.pawnedAmount = inputValidatedDouble("Enter pawned amount (0.01 - appraised value): ", 0.01, item.appraisedValue);
    cout << "Enter deposit date:\n";
    item.depositDate = inputDate();
    item.storagePeriod = inputValidatedInt("Enter storage period in days (1-1000): ", 1, 1000);
    items.push_back(item);
    cout << "Item added successfully!\n";
}


void printPawnItem(const PawnItem& item) {
    cout << "\n---------------------------------------\n"
        << "Client Last Name : " << item.clientLastName << "\n"
        << "Product Name     : " << item.productName << "\n"
        << "Product Type     : " << productTypeToString(item.productType) << "\n"
        << "Appraised Value  : $" << fixed << setprecision(2) << item.appraisedValue << "\n"
        << "Pawned Amount    : $" << fixed << setprecision(2) << item.pawnedAmount << "\n"
        << "Deposit Date     : "
        << setw(2) << setfill('0') << item.depositDate.day << "/"
        << setw(2) << setfill('0') << item.depositDate.month << "/" << item.depositDate.year << "\n"
        << "Storage Period   : " << item.storagePeriod << " days\n"
        << "---------------------------------------\n";
    cout << setfill(' ');
}


void showAllItems(const vector<PawnItem>& items) {
    if (items.empty()) {
        cout << "\nNo items to display.\n";
        return;
    }
    for (const auto& item : items)
        printPawnItem(item);
}


void deletePawnItem(vector<PawnItem>& items) {
    cout << "Enter client's last name of the item to delete: ";
    string lastName;
    getline(cin, lastName);
    cout << "Enter product name of the item to delete: ";
    string prodName;
    getline(cin, prodName);

    auto it = remove_if(items.begin(), items.end(), [&](const PawnItem& item) {
        return (item.clientLastName == lastName && item.productName == prodName);
        });

    if (it != items.end()) {
        items.erase(it, items.end());
        cout << "Item(s) deleted successfully.\n";
    }
    else {
        cout << "No matching item found.\n";
    }
}


int convertDateToDays(const Date& d) {
    int a = (14 - d.month) / 12;
    int y = d.year + 4800 - a;
    int m = d.month + 12 * a - 3;
    int julianDay = d.day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return julianDay;
}


void searchExpiredItems(const vector<PawnItem>& items) {
    cout << "Enter current date to check for expired items:\n";
    Date currentDate = inputDate();
    int currentDays = convertDateToDays(currentDate);
    bool found = false;
    for (const auto& item : items) {
        int depositDays = convertDateToDays(item.depositDate);
        int expirationDays = depositDays + item.storagePeriod;
        if (expirationDays <= currentDays) {
            printPawnItem(item);
            found = true;
        }
    }
    if (!found)
        cout << "No expired items found.\n";
}


int main() {
    vector<PawnItem> items;
    while (true) {
        cout << "\n=== Pawnshop Management System ===\n"
            << "1. Add Pawn Item\n"
            << "2. Show All Items\n"
            << "3. Delete Item\n"
            << "4. Search Expired Items\n"
            << "5. Exit\n"
            << "Enter choice: ";
        int choice = inputValidatedInt("", 1, 5);
        switch (choice) {
        case 1:
            addPawnItem(items);
            break;
        case 2:
            showAllItems(items);
            break;
        case 3:
            deletePawnItem(items);
            break;
        case 4:
            searchExpiredItems(items);
            break;
        case 5:
            return 0;
        }
    }
    return 0;
}
