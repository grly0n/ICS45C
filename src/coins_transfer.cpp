#include <iostream>
#include "coins.h"
using namespace std;

constexpr int CENTS_PER_CHIPS = 149;

int main() {
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);

    cout << "Initial piggy bank: " << piggyBank << endl;
    cout << "Initial pocket: " << pocket << endl;
    cout << endl;

    cout << "Bought chips using pocket" << endl;
    cout << "Coins required for chips: " << coins_required_for_cents(CENTS_PER_CHIPS) << endl;
    Coins pay_for_chips = pocket.extract_exact_change(coins_required_for_cents(CENTS_PER_CHIPS));
    cout << "Pocket after paying for chips: " << pocket << endl;
    cout << endl;

    cout << "Transferring money to pocket" << endl;
    Coins transfer_coins = piggyBank.extract_exact_change(coins_required_for_cents(405));
    cout << "Coins for transfer: " << transfer_coins << endl;
    pocket.deposit_coins(transfer_coins);
    cout << "Pocket: " << pocket << endl;
    cout << "Piggy bank: " << piggyBank << endl;
    cout << endl;

    Coins sofa(10, 10, 10, 10);
    cout << "Transferring sofa change to piggy bank" << endl;
    piggyBank.deposit_coins(sofa);
    cout << "Sofa: " << sofa << endl;
    cout << "Piggy bank: " << piggyBank << endl;
    cout << endl;

    cout << "Piggy bank total: ";
    print_cents(piggyBank.total_value_in_cents(), cout);
    cout << endl;

    return 0;
}
