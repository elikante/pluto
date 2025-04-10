#include "include/pluto/include.h"

#include <iostream>

int main() {
    pluto::dollars usd(123);
    pluto::euros salary(123);
    pluto::cents fee(50);

    auto total = salary + pluto::talent_cast<pluto::euros>(fee);
    std::cout << "Total salary: " << pluto::format_money(total) << "\n";

    pluto::exchange_rate<pluto::euros, pluto::shekels> euros_to_shekel(1.5);
    auto salary_in_shekel = euros_to_shekel.convert(salary);
    std::cout << "Salary in shekel: " << pluto::format_money(salary_in_shekel) << "\n";

    pluto::euros salary_in_euro(15000);
    std::cout << "Salary in euros: " << pluto::format_money(salary_in_euro) << "\n";

    pluto::exchange_rate<pluto::euros, pluto::dollars> eur_to_usd(1.08);
    auto salary_in_usd2 = eur_to_usd.convert(salary_in_euro);
    std::cout << "Salary in dollars: " << pluto::format_money(salary_in_usd2) << "\n";
}
