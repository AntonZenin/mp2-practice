#include "tmonom.h"
#include <gtest.h>


TEST(Monom, can_create_monom)
{
    ASSERT_NO_THROW(Monom m);
}

TEST(Monom, can_create_monom_with_degree_and_coeff)
{
    Monom m(7, 12);
    EXPECT_EQ(7, m.GetDegree());
    EXPECT_EQ(12, m.GetCoeff());
}

TEST(Monom, cant_create_monom_with_degree_out_of_range)
{
    ASSERT_ANY_THROW(Monom m(-1, 12));
}

TEST(Monom, can_create_monom_from_string)
{
    Monom m("-x^2");
    EXPECT_EQ(200, m.GetDegree());
    EXPECT_EQ(-1, m.GetCoeff());
}

TEST(Monom, cant_create_monom_from_invalid_string)
{
    ASSERT_ANY_THROW(Monom m(" x ^2"));
}

TEST(Monom, cant_create_monom_from_string_with_invalid_monom)
{
    ASSERT_ANY_THROW(Monom m("x^20"));
}

TEST(Monom, can_get_degree)
{
    Monom m("x^2");
    ASSERT_NO_THROW(m.GetDegree());
    EXPECT_EQ(200, m.GetDegree());
}

TEST(Monom, can_get_coeff)
{
    Monom m("-x^2");
    ASSERT_NO_THROW(m.GetCoeff());
    EXPECT_EQ(-1, m.GetCoeff());
}

TEST(Monom, equal_monoms_are_equal)
{
    Monom m("-x^2");
    Monom m1("-x^2");
    EXPECT_TRUE(m == m);
    EXPECT_TRUE(m == m1);
}

TEST(Monom, not_equal_monoms_are_not_equal)
{
    Monom m("x");
    Monom m1("x^2");
    EXPECT_TRUE(m != m1);
}

TEST(Monom, can_compare_monoms)
{
    Monom m("x");
    Monom m1("x^2");
    Monom m3("y*z");
    EXPECT_TRUE(m >= m);
    EXPECT_TRUE(m <= m);
    EXPECT_TRUE(m < m1);
    EXPECT_TRUE(m > m3);
    EXPECT_FALSE(m < m3);
    EXPECT_FALSE(m > m1);
}

TEST(Monom, can_sum_monoms_with_same_degree)
{
    Monom m("x");
    Monom m1("2*x");
    Monom m2;
    ASSERT_NO_THROW(m2 = m + m1);
    EXPECT_EQ(3, m2.GetCoeff());
    EXPECT_EQ(100, m2.GetDegree());
}

TEST(Monom, cant_sum_monoms_with_diff_degree)
{
    Monom m("x");
    Monom m1("2*x^6");
    ASSERT_ANY_THROW(m + m1);
}

TEST(Monom, can_sub_monoms_with_same_degree)
{
    Monom m("x");
    Monom m1("2*x");
    Monom m2;
    ASSERT_NO_THROW(m2 = m - m1);
    EXPECT_EQ(-1, m2.GetCoeff());
    EXPECT_EQ(100, m2.GetDegree());
}

TEST(Monom, cant_sub_monoms_with_diff_degree)
{
    Monom m("x");
    Monom m1("2*x^6");
    ASSERT_ANY_THROW(m - m1);
}

TEST(Monom, can_mul_monoms_within_degree_range)
{
    Monom m("x");
    Monom m1("2*x");
    Monom m2;
    ASSERT_NO_THROW(m2 = m * m1);
    EXPECT_EQ(2, m2.GetCoeff());
    EXPECT_EQ(200, m2.GetDegree());
}

TEST(Monom, cant_mul_monoms_outside_of_degree_range)
{
    Monom m("x^9");
    Monom m1("2*x");
    Monom m2;
    ASSERT_ANY_THROW(m2 = m * m1);
}

TEST(Monom, can_calculate_monom)
{
    Monom m("6*x^6*y");
    EXPECT_EQ(0, m(1, 0, 12314));
}