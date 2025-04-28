#include "tpolynom.h"
#include <gtest.h>

TEST(Polinom, can_create_polinom)
{
    ASSERT_NO_THROW(Polinom p);
}

TEST(Polinom, can_copy_polinom)
{
    Polinom p("x");
    ASSERT_NO_THROW(Polinom p1(p));
}

TEST(Polinom, copied_polinoms_are_equal)
{
    Polinom p("x");
    Polinom p1(p);
    EXPECT_TRUE(p == p1);
}

TEST(Polinom, can_create_polinom_from_string)
{
    ASSERT_NO_THROW(Polinom p("x+y+z+x^5"));
}

TEST(Polinom, cant_create_polinom_from_invalid_string)
{
    ASSERT_ANY_THROW(Polinom p("x+y +x^5"));
    ASSERT_ANY_THROW(Polinom p("x+y^999"));
}

TEST(Polinom, equal_polinoms_are_equal)
{
    Polinom p("x");
    Polinom p1("x");
    EXPECT_TRUE(p == p1);
}

TEST(Polinom, same_polinoms_are_equal)
{
    Polinom p("x");
    EXPECT_TRUE(p == p);
}

TEST(Polinom, not_equal_polinoms_are_not_equal)
{
    Polinom p("x");
    Polinom p1("x+4");
    EXPECT_TRUE(p != p1);
}

TEST(Polinom, can_assign_polinoms)
{
    Polinom p("x+y");
    Polinom p1;
    ASSERT_NO_THROW(p1 = p);
}

TEST(Polinom, assigned_polinoms_are_equal)
{
    Polinom p("x+y");
    Polinom p1("-x+y+x+x");
    p1 = p;
    EXPECT_TRUE(p1 == p);
}

TEST(Polinom, can_add_const_to_polinom)
{
    Polinom p("x+y");
    ASSERT_NO_THROW(p + 123);
}

TEST(Polinom, can_substract_const_from_polinom)
{
    Polinom p("x+y");
    ASSERT_NO_THROW(p - 123);
}

TEST(Polinom, can_multiply_polinom_on_const)
{
    Polinom p("x+y");
    ASSERT_NO_THROW(p * 123);
}

TEST(Polinom, can_add_monom_to_polinom)
{
    Polinom p("x+y");
    Monom m(100, 2);
    ASSERT_NO_THROW(p + m);
}

TEST(Polinom, can_substract_monom_from_polinom)
{
    Polinom p("x+y");
    Monom m(100, 2);
    ASSERT_NO_THROW(p - m);
}

TEST(Polinom, can_multiply_polinom_on_monom)
{
    Polinom p("x+y");
    Monom m(100, 2);
    ASSERT_NO_THROW(p * m);
}

TEST(Polinom, can_add_polinom_to_polinom)
{
    Polinom p("x+y");
    Polinom p1("z");
    ASSERT_NO_THROW(p + p1);
}

TEST(Polinom, can_substract_polinom_from_polinom)
{
    Polinom p("x+y");
    Polinom p1("z");
    ASSERT_NO_THROW(p - p1);
}

TEST(Polinom, can_multiply_polinom_on_polinom)
{
    Polinom p("x+y");
    Polinom p1("z");
    ASSERT_NO_THROW(p * p1);
}

TEST(Polinom, can_calculate_polinom)
{
    Polinom p("x+y^2-2*z-y+3*x");
    EXPECT_EQ(2, p(1, 1, 1));
}

TEST(Polinom, sum)
{
    Polinom p1("x+1");
    Polinom p2("x-1");
    EXPECT_EQ(Polinom("2*x"), p1 + p2);
}

TEST(Polinom, sub)
{
    Polinom p1("x+1");
    Polinom p2("x-1");
    EXPECT_EQ(Polinom("2"), p1 - p2);
}

TEST(Polinom, mult)
{
    Polinom p1("x+1");
    Polinom p2("x-1");
    EXPECT_EQ(Polinom("x^2-1"), p1 * p2);
}


