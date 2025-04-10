//
//// ─────────────────────────────────────────────────────────────
//// Fixed-point handling (for precise money handling)
//// ─────────────────────────────────────────────────────────────
//namespace math {
//template <typename Rep, typename Ratio>
//class fixed_point {
//public:
//    using rep = Rep;
//    using ratio = Ratio;
//
//private:
//    rep amount_;
//
//public:
//    constexpr fixed_point() : amount_{} {}
//    constexpr explicit fixed_point(rep v) : amount_{ v } {}
//
//    constexpr fixed_point(talent<Rep, Ratio> const& t) : amount_{ t.count() } {}
//
//    constexpr rep count() const { return amount_; }
//
//    // Arithmetic operators
//    constexpr fixed_point operator+(const fixed_point& other) const {
//        return fixed_point(amount_ + other.amount_);
//    }
//
//    constexpr fixed_point operator-(const fixed_point& other) const {
//        return fixed_point(amount_ - other.amount_);
//    }
//
//    constexpr fixed_point& operator+=(const fixed_point& other) {
//        amount_ += other.amount_;
//        return *this;
//    }
//
//    constexpr fixed_point& operator-=(const fixed_point& other) {
//        amount_ -= other.amount_;
//        return *this;
//    }
//};
//}
