#include "talent.hpp"

// ─────────────────────────────────────────────────────────────
// exchange_rate: A conversion factor between two currencies
// ─────────────────────────────────────────────────────────────
namespace pluto {
    template <typename From, typename To>
    class exchange_rate {
    public:
        using from_type = From;
        using to_type = To;

    private:
        double rate_;

    public:
        explicit exchange_rate(double rate) : rate_(rate) {}

        To convert(const From& from_value) const {
            return To(static_cast<typename To::rep>(from_value.count() * rate_));
        }

        double rate() const { return rate_; }
    };

}
