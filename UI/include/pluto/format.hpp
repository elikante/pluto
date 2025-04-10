#include "talent.hpp"

// ─────────────────────────────────────────────────────────────
// Output formatting for `talent` (like money formatting)
// ─────────────────────────────────────────────────────────────

namespace pluto {
template <typename Rep, typename Ratio>
std::string format_money(const talent<Rep, Ratio>& t, bool show_symbol = true) {
    std::ostringstream oss;
    auto value = t.count();
    oss << std::fixed << std::setprecision(2) << static_cast<double>(value) / Ratio::num;

    // Add currency symbol, if requested
    if (show_symbol) {
        oss << " " << "pluto";  // Or any currency name you like, e.g., "$", "€"
    }

    return oss.str();
}
}