#include "coins.h"
#include <iostream>
using namespace std;

Coins::Coins(int q, int d, int n, int p) : quarters(q), dimes(d), nickels(n), pennies(p){}

void Coins::print(ostream& out) const {
    out << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, "
    << pennies << " pennies";
}

ostream& operator<<(ostream& out, Coins const& coins) {
    coins.print(out);
    return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
   int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
   while (amount_in_cents >= CENTS_PER_QUARTER) {
        amount_in_cents -= CENTS_PER_QUARTER;
        quarters++;
    }
    while (amount_in_cents >= CENTS_PER_DIME) {
        amount_in_cents -= CENTS_PER_DIME;
        dimes++;
    }
    while (amount_in_cents >= CENTS_PER_NICKEL) {
        amount_in_cents -= CENTS_PER_NICKEL;
        nickels++;
    }
    pennies += amount_in_cents;
    return Coins(quarters, dimes, nickels, pennies);
}

Coins Coins::extract_exact_change(Coins const& coins) {
    if (coins.quarters <= quarters && coins.dimes <= dimes && coins.nickels <= nickels
    && coins.pennies <= pennies) {
        quarters -= coins.quarters;
        dimes -= coins.dimes;
        nickels -= coins.nickels;
        pennies -= coins.pennies;

        return Coins(coins.quarters, coins.dimes, coins.nickels, coins.pennies);
    } else {
        return Coins(0, 0, 0, 0);
    }
}

void Coins::deposit_coins(Coins& coins) {
    quarters += coins.quarters;
    dimes += coins.dimes;
    nickels += coins.nickels;
    pennies += coins.pennies;

    coins = Coins(0, 0, 0, 0);
}

int Coins::total_value_in_cents() const {
    return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME + nickels * CENTS_PER_NICKEL
    + pennies;
}

void print_cents(int cents, ostream& out) {
    if (cents < 10) {
       out << "$0.0" << cents;
    } else if (cents >= 10 && cents < 100) {
        out << "$0." << cents;
    } else if (cents % 100 == 0) {
        out << "$" << cents / 100 << ".00";
    } else if (cents % 10 == 0) {
        out << "$" << cents / 10.0 << "0";
    } else {
        out << "$" << cents/ 100.0;
    }
}

Coins ask_for_coins(istream& in, ostream& out) {
    int quarters, dimes, nickels, pennies;
    out << "Quarters? ";
    in >> quarters;
    out << "Dimes? ";
    in >> dimes;
    out << "Nickels? ";
    in >> nickels;
    out << "Pennies? ";
    in >> pennies;
    return Coins(quarters, dimes, nickels, pennies);
}

bool Coins::has_exact_change_for_coins(Coins const& coins) const {
    if (quarters <= coins.quarters && dimes <= coins.dimes && nickels <= coins.nickels
    && pennies <= coins.pennies) {
        return true;
    } else {
        return false;
    }
}

void coins_menu(istream& in, ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    out << "Coins Menu" << endl;
    out << endl;

    int command = 0;
    while (command != 4) {
        out << "1. Deposit Change" << endl;
        out << "2. Extract Change" << endl;
        out << "3. Print Balance" << endl;
        out << "4. Exit" << endl;
        out << endl;
        out << "User Input: ";
        in >> command;

        if (command == 1) {
            out << endl;
            Coins input = ask_for_coins(in, out);
            myCoins.deposit_coins(input);
            out << endl;
            out << "Thank you!" << endl;
            out << endl;
        } else if (command == 2) {
            out << endl;
            Coins input = ask_for_coins(in, out);
            out << endl;
            out << "Thank you!" << endl;
            out << endl;
            if (input.has_exact_change_for_coins(myCoins)) {
                myCoins.extract_exact_change(input);
            } else {
                out << "ERROR: Insufficient Funds" << endl;
                out << endl;
            }
        } else if (command == 3) {
            out << endl;
            print_cents(myCoins.total_value_in_cents(), out);
            out << endl;
            out << endl;
            out << "Thank you!" << endl;
            out << endl;
        } else if (command == 4) {
            out << endl;
            break;
        } else {
            out << endl;
            out << "ERROR: Invalid Command" << endl;
            out << endl;
        }
    }
}
