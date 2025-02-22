#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct SanatoriumVoucher {
    string name;
    string location;
    string treatmentProfile;
    int vouchersCount;
};

SanatoriumVoucher inputVoucher() {
    SanatoriumVoucher voucher;

    cout << "\nEnter voucher details:\n";
    cout << "Sanatorium name: ";
    getline(cin, voucher.name);

    cout << "Location: ";
    getline(cin, voucher.location);

    cout << "Treatment profile: ";
    getline(cin, voucher.treatmentProfile);

    voucher.vouchersCount = 0;
    while (voucher.vouchersCount <= 0) {
        cout << "Number of vouchers: ";
        cin >> voucher.vouchersCount;
        cin.ignore();
        if (voucher.vouchersCount <= 0) {
            cout << "Invalid value! Enter positive number\n";
        }
    }
    return voucher;
}

map<string, vector<SanatoriumVoucher>> processData(const vector<SanatoriumVoucher>& data) {
    map<string, vector<SanatoriumVoucher>> groupedData;

    // Grouping and sorting
    for (const auto& voucher : data) {
        groupedData[voucher.treatmentProfile].push_back(voucher);
    }

    // Sort within groups
    for (auto& group : groupedData) {
        sort(group.second.begin(), group.second.end(),
            [](const SanatoriumVoucher& a, const SanatoriumVoucher& b) {
                return a.name < b.name;
            });
    }

    return groupedData;
}

void printTable(const map<string, vector<SanatoriumVoucher>>& groupedData) {
    cout << "\n";
    for (const auto& group : groupedData) {
        cout << "Treatment Profile: " << group.first << "\n";
        cout << "------------------------------------------------------\n";
        cout << "| Name                | Location          | Vouchers |\n";
        cout << "------------------------------------------------------\n";

        for (const auto& voucher : group.second) {
            cout << "| " << voucher.name;
            cout << string(20 - voucher.name.length(), ' ');

            cout << "| " << voucher.location;
            cout << string(18 - voucher.location.length(), ' ');

            cout << "| " << voucher.vouchersCount;
            cout << string(8 - to_string(voucher.vouchersCount).length(), ' ');
            cout << " |\n";
        }
        cout << "------------------------------------------------------\n\n";
    }
}

void searchVouchers(const vector<SanatoriumVoucher>& data) {
    int choice;
    string searchTerm;

    cout << "\nSearch by:\n"
        << "1. Treatment Profile\n"
        << "2. Location\n"
        << "3. Name\n"
        << "Choice: ";
    cin >> choice;
    cin.ignore();

    cout << "Search term: ";
    getline(cin, searchTerm);

    vector<SanatoriumVoucher> results;

    switch (choice) {
    case 1:
        for (const auto& v : data) {
            if (v.treatmentProfile.find(searchTerm) != string::npos)
                results.push_back(v);
        }
        break;
    case 2:
        for (const auto& v : data) {
            if (v.location.find(searchTerm) != string::npos)
                results.push_back(v);
        }
        break;
    case 3:
        for (const auto& v : data) {
            if (v.name.find(searchTerm) != string::npos)
                results.push_back(v);
        }
        break;
    default:
        cout << "Invalid choice!\n";
        return;
    }

    if (results.empty()) {
        cout << "No results found!\n";
        return;
    }

    cout << "\nSearch Results:\n";
    auto processed = processData(results);
    printTable(processed);
}

int main() {
    vector<SanatoriumVoucher> data;
    int choice;

    while (true) {
        cout << "\nMain Menu:\n"
            << "1. Add Voucher\n"
            << "2. Show All Vouchers\n"
            << "3. Search\n"
            << "4. Exit\n"
            << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            data.push_back(inputVoucher());
            break;
        case 2:
            if (data.empty()) {
                cout << "No data available!\n";
                break;
            }
            printTable(processData(data));
            break;
        case 3:
            if (data.empty()) {
                cout << "No data to search!\n";
                break;
            }
            searchVouchers(data);
            break;
        case 4:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
}