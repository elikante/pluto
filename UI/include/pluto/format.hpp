#include "talent.hpp"

// ─────────────────────────────────────────────────────────────
// Output formatting for `talent` (like money formatting)
// ─────────────────────────────────────────────────────────────

namespace pluto {
template <Talent T>
std::string format_money(T const& t, bool show_symbol = true) {
    std::ostringstream oss;
    auto value = t.count();
    oss << std::fixed << std::setprecision(2) << static_cast<double>(value) / T::ratio::num;

    if (show_symbol) {
        oss << " " << "pluto e.g. $, €...";  // Or any currency name you like, e.g., "$", "€"
    }

    return oss.str();
}
}