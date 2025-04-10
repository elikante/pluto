#include "include/pluto/talent.hpp"
#include "include/pluto/format.hpp"
#include "include/pluto/exchange_rate.hpp"
#include "include/pluto/money_point.hpp"
#include "include/fixedpoint/fixedpoint.hpp"

#include <iostream>

int main() {
    // talent types (standard)
    pluto::euros salary(123);
    pluto::cents fee(50);

    // Add fee to salary (in drachma)
    auto total = salary + pluto::talent_cast<pluto::euros>(fee);
    std::cout << "Total salary: " << pluto::format_money(total) << "\n";

    // Exchange rate: 1 drachma = 1.5 shekel
    pluto::exchange_rate<pluto::euros, pluto::shekel> euros_to_shekel(1.5);
    auto salary_in_shekel = euros_to_shekel.convert(salary);
    std::cout << "Salary in shekel: " << pluto::format_money(salary_in_shekel) << "\n";

    // Fixed point usage
    //math::fixed_point<int, std::ratio<100>> fixed_salary(salary);
    //std::cout << "Fixed salary (in cents): " << fixed_salary.count() << "\n";


    pluto::euro salary_in_euro(15000); // €150.00
    auto salary_in_usd = pluto::to_dollar(salary_in_euro);

    std::cout << "Salary in dollars: " << pluto::format_money(salary_in_usd) << "\n";

    pluto::exchange_rate<pluto::euro, pluto::dollar> eur_to_usd(1.08);
    auto salary_in_usd2 = eur_to_usd.convert(salary_in_euro);

    std::cout << "Salary in dollars: " << pluto::format_money(salary_in_usd2) << "\n";


    // Output: Salary in dollars: 162.00 pluto
}

// ===> soon :

//
//#include "pluto/talent.hpp"
//#include "pluto/money_point.hpp"
//#include "pluto/exchange_rate.hpp"
//#include "pluto/fixed_point.hpp"
//#include <iostream>
//
//int main() {
//    // Basic talent usage
//    pluto::drachma salary(123);
//    pluto::obolus fee(50);
//    auto total = salary + pluto::talent_cast<pluto::drachma>(fee);
//    std::cout << "Total salary in drachma: " << pluto::format_money(total) << "\n";
//
//    // Exchange rate
//    pluto::exchange_rate<pluto::drachma, pluto::shekel> exchange(1.5);
//    auto salary_in_shekel = exchange.convert(salary);
//    std::cout << "Salary in shekel: " << pluto::format_money(salary_in_shekel) << "\n";
//
//    // Fixed point example
//    pluto::fixed_point<int64_t, std::ratio<100>> fixed_salary(salary);
//    std::cout << "Salary in fixed point (cents): " << fixed_salary.count() << "\n";
//
//    // Money point
//    pluto::money_point<pluto::drachma, pluto::talent<int64_t>> account_balance(1000);
//    std::cout << "Account balance: " << pluto::format_money(account_balance) << "\n";
//
//    return 0;
//}