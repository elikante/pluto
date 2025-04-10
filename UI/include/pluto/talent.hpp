#pragma once

#include <ratio>
#include <type_traits>
#include <cstdint>
#include <cmath>     // For rounding if needed
#include <iomanip>   // For formatting output
#include <sstream>   // For string stream formatting
#include <iostream>  // For std::cout

// ─────────────────────────────────────────────────────────────
// Core type: talent<Rep, Ratio>
// ─────────────────────────────────────────────────────────────

namespace pluto {

    template<typename Rep, typename Ratio = std::ratio<1>>
    class talent {
    public:
        static_assert(!std::ratio_equal<Ratio, std::ratio<0>>::value, "Ratio cannot be zero");
        using rep = Rep;
        using ratio = Ratio;

    private:
        rep amount_;

    public:
        // Constructors
        constexpr talent() : amount_{} {}
        constexpr explicit talent(const rep& v) : amount_{ v } {}

        // Accessor
        constexpr rep count() const { return amount_; }

        // Arithmetic operators
        constexpr talent operator+(const talent& other) const {
            return talent{ amount_ + other.amount_ };
        }

        constexpr talent operator-(const talent& other) const {
            return talent{ amount_ - other.amount_ };
        }

        constexpr talent& operator+=(const talent& other) {
            amount_ += other.amount_;
            return *this;
        }

        constexpr talent& operator-=(const talent& other) {
            amount_ -= other.amount_;
            return *this;
        }

        auto operator<=>(talent const&) const = default;
    };

    template<typename To, typename Rep, typename Ratio>
    constexpr To talent_cast(const talent<Rep, Ratio>& from) {
        using CommonRatio = std::ratio_divide<Ratio, typename To::ratio>;
        return To(static_cast<typename To::rep>(from.count() * CommonRatio::num / CommonRatio::den));
    }

    // ─────────────────────────────────────────────────────────────
    // Ancient Greek talents
    // ─────────────────────────────────────────────────────────────

    using decadrachm = talent<int64_t, std::ratio<60>>;
    using tetradrachm = talent<int64_t, std::ratio<24>>;
    using didrachm = talent<int64_t, std::ratio<12>>;
    using drachma = talent<int64_t, std::ratio<6>>;
    using tetrobol = talent<int64_t, std::ratio<4>>;
    using triobol = talent<int64_t, std::ratio<3>>;
    using Diobol = talent<int64_t, std::ratio<2>>;
    using trihemiobol = talent<int64_t, std::ratio<3,2>>;
    using obol = talent<int64_t, std::ratio<1>>;
    using tritartemorion = talent<int64_t, std::ratio<3,4>>;
    using hemiobol = talent<int64_t, std::ratio<1,2>>;
    using trihemitetartemorion = talent<int64_t, std::ratio<3,8>>;
    using tetartemorion = talent<int64_t, std::ratio<1,4>>;
    using hemitetartemorion = talent<int64_t, std::ratio<1,8>>;

    // ─────────────────────────────────────────────────────────────
    // Roman talents
    // ─────────────────────────────────────────────────────────────

    using aureus = talent<int64_t, std::ratio<400>>;
    using gold_quinarius = talent<int64_t, std::ratio<200>>;
    using antoninianus = talent<int64_t, std::ratio<32>>;
    using denarius = talent<int64_t, std::ratio<16>>;
    using silver_quinarius = talent<int64_t, std::ratio<8>>;
    using sertertius = talent<int64_t, std::ratio<4>>;
    using dupondius = talent<int64_t, std::ratio<2>>;
    using as = talent<int64_t, std::ratio<1>>;
    using semis = talent<int64_t, std::ratio<1, 2>>;
    using quadrans = talent<int64_t, std::ratio<1, 4>>;

    // ─────────────────────────────────────────────────────────────
    // EU talents
    // ─────────────────────────────────────────────────────────────

    using es1_500 = talent<int64_t, std::ratio<500>>;
    using es1_200 = talent<int64_t, std::ratio<200>>;
    using europa_200 = talent<int64_t, std::ratio<200>>;
    using es1_100 = talent<int64_t, std::ratio<100>>;
    using europa_100 = talent<int64_t, std::ratio<100>>;
    using es1_50 = talent<int64_t, std::ratio<50>>;
    using europa_50 = talent<int64_t, std::ratio<50>>;
    using es1_20 = talent<int64_t, std::ratio<20>>;
    using europa_20 = talent<int64_t, std::ratio<20>>;
    using es1_10 = talent<int64_t, std::ratio<10>>;
    using europa_10 = talent<int64_t, std::ratio<10>>;
    using es1_5 = talent<int64_t, std::ratio<5>>;
    using europa_5 = talent<int64_t, std::ratio<5>>;
    using euros = talent<int64_t, std::ratio<1>>;
    using cents = talent<int64_t, std::centi>;

    // ─────────────────────────────────────────────────────────────
    // USA talents
    // ─────────────────────────────────────────────────────────────

    using franklins = talent<int64_t, std::ratio<100>>;
    using grants = talent<int64_t, std::ratio<50>>;
    using jacksons = talent<int64_t, std::ratio<20>>;
    using hamiltons = talent<int64_t, std::ratio<10>>;
    using lincolns = talent<int64_t, std::ratio<5>>;
    using jeffersons = talent<int64_t, std::ratio<2>>;
    using washingtons = talent<int64_t, std::ratio<1>>;
    using half_dollars = talent<int64_t, std::ratio<1,2>>;
    using quarters = talent<int64_t, std::ratio<1,4>>;
    using dollars = talent<int64_t, std::ratio<1>>;
    using dimes = talent<int64_t, std::deci>;
    using nickels = talent<int64_t, std::ratio<5,100>>;
    using pennies = talent<int64_t, std::centi>;

    // ─────────────────────────────────────────────────────────────
    // 
    // ─────────────────────────────────────────────────────────────

    using shekel = talent<int64_t, std::ratio<250>>;

    ///////////
    // temp
    ///////////
    // Define common currencies
    using dollar = talent<int64_t, std::ratio<100>>; // 1 dollar = 100 cents
    using cent = talent<int64_t, std::ratio<1>>;
    using yen = talent<int64_t, std::ratio<1>>;    // If yen doesn’t use subunits
    using euro = talent<int64_t, std::ratio<100>>;

    constexpr dollar to_dollar(const euro& eur) {
        constexpr double rate = 1.08;
        return dollar(static_cast<dollar::rep>(eur.count() * rate));
    }

} // namespace pluto
