#include <iostream>
#include "coins.h"
using namespace std;

constexpr int CENTS_PER_CANDYBAR = 482;

int main() {
    Coins pocket(100, 10, 10, 100);

    cout << "I started with " << pocket << " in my pocket." << endl;
    Coins pay_for_candy = pocket.extract_exact_change(coins_required_for_cents(CENTS_PER_CANDYBAR));
    cout << "I bought a candy bar for " << CENTS_PER_CANDYBAR << " cents using " << 
    pay_for_candy << "." << endl;
    cout << "I have " << pocket << " left in my pocket." << endl;
}
