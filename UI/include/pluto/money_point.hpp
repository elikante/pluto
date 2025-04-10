// ─────────────────────────────────────────────────────────────
// money_point: A specific value at a point in time (like time_point)
// ─────────────────────────────────────────────────────────────
namespace pluto {

    template <typename Ledger, typename Talent>
    class money_point {
    public:
        using ledger_type = Ledger;
        using value_type = Talent;

    private:
        value_type value_;

    public:
        constexpr money_point() : value_{} {}
        constexpr explicit money_point(const value_type& v) : value_{ v } {}

        constexpr value_type value() const { return value_; }

        // Arithmetic
        constexpr money_point operator+(const value_type& delta) const {
            return money_point(value_ + delta);
        }

        constexpr value_type operator-(const money_point& other) const {
            return value_ - other.value_;
        }
    };
}