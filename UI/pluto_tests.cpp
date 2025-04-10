//#include <gtest/gtest.h>
//#include "pluto/talent.hpp"
//
//TEST(talentTest, Addition) {
//    pluto::drachma salary(100);
//    pluto::obolus fee(50);
//    auto total = salary + pluto::talent_cast<pluto::drachma>(fee);
//    EXPECT_EQ(total.count(), 150);
//}
//
//TEST(talentTest, Conversion) {
//    pluto::exchange_rate<pluto::drachma, pluto::shekel> rate(1.5);
//    pluto::drachma salary(100);
//    auto converted = rate.convert(salary);
//    EXPECT_EQ(converted.count(), 150); // 100 drachma * 1.5
//}
//
//TEST(FixedPointTest, ConversionFromtalent) {
//    pluto::drachma salary(100);
//    pluto::fixed_point<int64_t, std::ratio<100>> fixed_salary(salary);
//    EXPECT_EQ(fixed_salary.count(), 10000); // 100 drachma -> 10000 cents
//}
