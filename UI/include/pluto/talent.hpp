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
    enum class Devise {
        euros, us_dollars, denarii, obols, shekels, rubles
    };

    template<typename T>
    struct is_talent : std::false_type {};

    template<typename T>
    concept Talent = is_talent<T>::value;

    namespace impl {
        template<Devise D/*, typename Symbol, typename Name*/, typename Rep, typename Ratio>
        class talent;
    }

    template<Devise D, typename... Args>
    struct is_talent<impl::talent< D, Args...>> : std::true_type {};

    namespace impl {
        template<Devise D/*, typename Symbol, typename Name*/, typename Rep, typename Ratio = std::ratio<1>>
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
    }

    template<Talent To, Talent From>
    constexpr To talent_cast(From const& from) {
        using CommonRatio = std::ratio_divide<typename From::ratio, typename To::ratio>;
        return To(static_cast<typename To::rep>(from.count() * CommonRatio::num / CommonRatio::den));
    }

    // ─────────────────────────────────────────────────────────────
    // Ancient Greek talents
    // ─────────────────────────────────────────────────────────────

    using decadrachm = impl::talent < Devise::obols /*, {""}, {"decadrachm"}*/, int64_t, std::ratio<60 >>;
    using tetradrachm = impl::talent < Devise::obols/*, { "" }, { "tetradrachm" }*/, int64_t, std::ratio<24 >>;
    using didrachm = impl::talent < Devise::obols/*, { "" }, { "decadrachm" }*/, int64_t, std::ratio<12 >>;
    using drachma = impl::talent < Devise::obols/*, { "Δρ" }, { "drachma" }*/, int64_t, std::ratio<6 >>;
    using tetrobol = impl::talent < Devise::obols/*, { "" }, { "tetrobol" }*/, int64_t, std::ratio<4 >>;
    using triobol = impl::talent < Devise::obols/*, { "" }, { "triobol" }*/, int64_t, std::ratio<3 >>;
    using diobol = impl::talent < Devise::obols/*, { "" }, { "diobol" }*/, int64_t, std::ratio<2 >>;
    using trihemiobol = impl::talent < Devise::obols/*, { "" }, { "trihemiobol" }*/, int64_t, std::ratio<3, 2 >>;
    using obol = impl::talent < Devise::obols/*, { "" }, { "obol" }*/, int64_t, std::ratio<1 >>;
    using tritartemorion = impl::talent < Devise::obols/*, { "" }, { "tritartemorion" }*/, int64_t, std::ratio<3, 4 >>;
    using hemiobol = impl::talent < Devise::obols/*, { "" }, { "hemiobol" }*/, int64_t, std::ratio<1, 2 >>;
    using trihemitetartemorion = impl::talent < Devise::obols/*, { "" }, { "trihemitetartemorion" }*/, int64_t, std::ratio<3, 8 >>;
    using tetartemorion = impl::talent < Devise::obols/*, { "" }, { "tetartemorion" }*/, int64_t, std::ratio<1, 4 >>;
    using hemitetartemorion = impl::talent < Devise::obols/*, { "" }, { "hemitetartemorion" }*/, int64_t, std::ratio<1, 8 >>;

    // ─────────────────────────────────────────────────────────────
    // Roman talents
    // ─────────────────────────────────────────────────────────────

    using aureus = impl::talent < Devise::denarii/*, { "" }, { "aureus" }*/, int64_t, std::ratio<400 >>;
    using gold_quinarii = impl::talent < Devise::denarii/*, { "" }, { "gold_quinarii" }*/, int64_t, std::ratio<200 >>;
    using antoninianus = impl::talent < Devise::denarii/*, { "" }, { "antoninianus" }*/, int64_t, std::ratio<32 >>;
    using denarii = impl::talent < Devise::denarii/*, { "" }, { "denarii" }*/, int64_t, std::ratio<16 >>;
    using silver_quinarii = impl::talent < Devise::denarii/*, { "" }, { "silver_quinarii" }*/, int64_t, std::ratio<8 >>;
    using sestertii = impl::talent < Devise::denarii/*, { "" }, { "sertertii" }*/, int64_t, std::ratio<4 >>;
    using duopondii = impl::talent < Devise::denarii/*, { "" }, { "duopondii" }*/, int64_t, std::ratio<2 >>;
    using assēs = impl::talent < Devise::denarii/*, { "" }, { "assēs" }*/, int64_t, std::ratio<1 >>; // a plural form of the roman as 
    using assarii = impl::talent < Devise::denarii/*, { "" }, { "assarii" }*/, int64_t, std::ratio<1 >>; // another plural form of the roman as 
    using semis = impl::talent < Devise::denarii/*, { "" }, { "semis" }*/, int64_t, std::ratio<1, 2 >>;
    using triens = impl::talent < Devise::denarii/*, { "" }, { "triens" }*/, int64_t, std::ratio<1, 3 >>;
    using quadrans = impl::talent < Devise::denarii/*, { "" }, { "quadrans" }*/, int64_t, std::ratio<1, 4 >>;
    using sextans = impl::talent < Devise::denarii/*, { "" }, { "sextans" }*/, int64_t, std::ratio<1, 6 >>;
    using uncia = impl::talent < Devise::denarii/*, { "" }, { "uncia" }*/, int64_t, std::ratio<1, 12 >>;
    using semiuncia = impl::talent < Devise::denarii/*, { "∑","𐆒" }, { "semiuncia" }*/, int64_t, std::ratio<1, 24 >>;

    // ─────────────────────────────────────────────────────────────
    // EU talents
    // ─────────────────────────────────────────────────────────────

    using es1_500 = impl::talent < Devise::euro/*, { "" }, { "es1_500" }*/, int64_t, std::ratio<500 >>;
    using es1_200 = impl::talent < Devise::euro/*, { "" }, { "es1_200" }*/, int64_t, std::ratio<200 >>;
    using europa_200 = impl::talent < Devise::euro/*, { "" }, { "europa_200" }*/, int64_t, std::ratio<200 >>;
    using es1_100 = impl::talent < Devise::euro/*, { "hecto €" }, { "es1_100" }*/, int64_t, std::ratio<100 >>;
    using europa_100 = impl::talent < Devise::euro/*, { "hecto €" }, { "europa_100" }*/, int64_t, std::ratio<100 >>;
    using es1_50 = impl::talent < Devise::euro/*, { "" }, { "es1_50" }*/, int64_t, std::ratio<50 >>;
    using europa_50 = impl::talent < Devise::euro/*, { "" }, { "europa_50" }*/, int64_t, std::ratio<50 >>;
    using es1_20 = impl::talent < Devise::euro/*, { "" }, { "es1_20" }*/, int64_t, std::ratio<20 >>;
    using europa_20 = impl::talent < Devise::euro/*, { "" }, { "europa_20" }*/, int64_t, std::ratio<20 >>;
    using es1_10 = impl::talent < Devise::euro/*, { "deca €" }, { "es1_10" }*/, int64_t, std::ratio<10 >>;
    using europa_10 = impl::talent < Devise::euro/*, { "" }, { "europa_10" }*/, int64_t, std::ratio<10 >>;
    using es1_5 = impl::talent < Devise::euro/*, { "" }, { "es1_5" }*/, int64_t, std::ratio<5 >>;
    using europa_5 = impl::talent < Devise::euro/*, { "" }, { "europa_5" }*/, int64_t, std::ratio<5 >>;
    using euros = impl::talent < Devise::euro/*, { "€" }, { "euros" }*/, int64_t, std::ratio<1 >>;
    using cents = impl::talent < Devise::euro/*, { "cents" }, { "cents" }*/, int64_t, std::centi >;

    // ─────────────────────────────────────────────────────────────
    // USA talents
    // ─────────────────────────────────────────────────────────────

    using franklins = impl::talent < Devise::usd/*, { "hecto $" }, { "franklins" }*/, int64_t, std::ratio<100 >>;
    using grants = impl::talent < Devise::usd/*, { "" }, { "grants" }*/, int64_t, std::ratio<50 >>;
    using jacksons = impl::talent < Devise::usd/*, { "" }, { "jacksons" }*/, int64_t, std::ratio<20 >>;
    using hamiltons = impl::talent < Devise::usd/*, { "deca $" }, { "hamiltons" }*/, int64_t, std::ratio<10 >>;
    using lincolns = impl::talent < Devise::usd/*, { "" }, { "lincolns" }*/, int64_t, std::ratio<5 >>;
    using jeffersons = impl::talent < Devise::usd/*, { "" }, { "jeffersons" }*/, int64_t, std::ratio<2 >>;
    using washingtons = impl::talent < Devise::usd/*, { "$" }, { "washingtons" }*/, int64_t, std::ratio<1 >>;
    using half_dollars = impl::talent < Devise::usd/*, { "½$" }, { "half-dollars" }*/, int64_t, std::ratio<1, 2 >>;
    using dollars = impl::talent < Devise::usd/*, { "$", "USD" }, { "dollars" }*/, int64_t, std::ratio<1 >>;
    using quarters = impl::talent < Devise::usd/*, { "¼$" }, { "quarters" }*/, int64_t, std::ratio<1, 4 >>;
    using dimes = impl::talent < Devise::usd/*, { "" }, { "dimes" }*/, int64_t, std::deci >;
    using nickels = impl::talent < Devise::usd/*, { "" }, { "nickels" }*/, int64_t, std::ratio<5, 100 >>;
    using pennies = impl::talent < Devise::usd/*, { "¢" }, { "pennies" }*/, int64_t, std::centi >;

    // ─────────────────────────────────────────────────────────────
    // 
    // ─────────────────────────────────────────────────────────────

    using shekels = impl::talent<Devise::shekel/*, { "₪" }, { "shekel" }*/, int64_t, std::ratio<1>>;

    using rubles = impl::talent<Devise::ruble/*, { "₽" }, { "ruble" }*/, int64_t, std::ratio<1>>;
} // namespace pluto
