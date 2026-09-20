#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;


const double BASE_CHARGE = 18.50;
const double TIER1_RATE = 0.08;
const double TIER2_RATE = 0.12;
const double TIER3_RATE = 0.16;

const double TIER1_LIMIT = 500.0;
const double TIER2_LIMIT = 1000.0;
const double TAX_RATE = 0.055; // 5.5% Municipal Clean Energy Tax


double getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0.0) {
            return value;
        }
        cout << "[ERROR] Invalid input. Please enter a valid non-negative number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    string accountNumber, customerName;
    double prevReading = 0.0, currReading = 0.0;

    cout << "======================================================\n";
    cout << "                 Orange Walk BEL Agency               \n";
    cout << "               MONTHLY BILLING CALCULATOR             \n";
    cout << "======================================================\n\n";

    cout << "Enter Customer Account Number : ";
    getline(cin >> ws, accountNumber);

    cout << "Enter Customer Full Name       : ";
    getline(cin, customerName);

    // Defensive validation loop for meter readings
    while (true) {
        prevReading = getValidDouble("Enter Previous Reading (kWh)  : ");
        currReading = getValidDouble("Enter Current Reading (kWh)   : ");

        if (currReading >= prevReading) break;

        cout << "[ERROR] Current reading (" << currReading 
             << " kWh) cannot be less than previous reading (" << prevReading 
             << " kWh). Please re-enter.\n\n";
    }

    cout << "\nComputing charges... Done.\n\n";

    double totalConsumption = currReading - prevReading;
    double t1Units = 0.0, t2Units = 0.0, t3Units = 0.0;

    if (totalConsumption > TIER2_LIMIT) {
        t1Units = TIER1_LIMIT;
        t2Units = TIER2_LIMIT - TIER1_LIMIT;
        t3Units = totalConsumption - TIER2_LIMIT;
    } else if (totalConsumption > TIER1_LIMIT) {
        t1Units = TIER1_LIMIT;
        t2Units = totalConsumption - TIER1_LIMIT;
    } else {
        t1Units = totalConsumption;
    }

    double t1Charge = t1Units * TIER1_RATE;
    double t2Charge = t2Units * TIER2_RATE;
    double t3Charge = t3Units * TIER3_RATE;

    double consumptionSubtotal = t1Charge + t2Charge + t3Charge;
    double taxSurcharge = consumptionSubtotal * TAX_RATE;
    double totalBalanceDue = BASE_CHARGE + consumptionSubtotal + taxSurcharge;

    cout << fixed << setprecision(2);
    
    cout << "               [ITEMIZED UTILITY INVOICE]               \n";
    
    cout << left << setw(21) << "Account Number" << ": " << accountNumber << "\n";
    cout << left << setw(21) << "Customer Name" << ": " << customerName << "\n";
    cout << left << setw(21) << "Total Consumption" << ": " << totalConsumption << " kWh\n";
    cout << "------------------------------------------------------\n";
    cout << left << setw(38) << "Line Item Breakdown" << right << setw(16) << "Amount ($)" << "\n";
    cout << "------------------------------------------------------\n";

    cout << left << setw(38) << "Base Customer Charge" << "$" << right << setw(15) << BASE_CHARGE << "\n";
    cout << left << setw(20) << "Tier 1 Usage (First" << right << setw(7) << t1Units << " kWh)       $" << right << setw(15) << t1Charge << "\n";
    cout << left << setw(20) << "Tier 2 Usage (Next " << right << setw(7) << t2Units << " kWh)       $" << right << setw(15) << t2Charge << "\n";
    cout << left << setw(20) << "Tier 3 Usage (Excess" << right << setw(7) << t3Units << " kWh)       $" << right << setw(15) << t3Charge << "\n";
    cout << "------------------------------------------------------\n";
    cout << left << setw(38) << "Total Consumption Subtotal" << "$" << right << setw(15) << consumptionSubtotal << "\n";
    cout << left << setw(38) << "Municipal Clean Energy Surcharge (5.5%)" << "$" << right << setw(15) << taxSurcharge << "\n";
    cout << "======================================================\n";
    cout << left << setw(38) << "TOTAL BALANCE DUE" << "$" << right << setw(15) << totalBalanceDue << "\n";
    cout << "======================================================\n";
    cout << "Payment Due Date: 21 Days From Statement Generation.\n";
    cout << "Thank you for being a valued customer!\n";

    return 0;
}