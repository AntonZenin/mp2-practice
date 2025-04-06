#include <gtest.h>
#include "tmonom.h"

TEST(TMonom, can_creat_empty_monom) {
	TMonom new_monom;
	EXPECT_EQ(new_monom.coeff_, 0);
	EXPECT_EQ(new_monom.degree_, -1);
}

TEST(TMonom, can_creat_normal_monom) {
	ASSERT_NO_THROW(TMonom new_monom(3, 111));
}

TEST(TMonom, check_correct_monom_data) {
	TMonom new_monom(3, 111);
	EXPECT_EQ(new_monom.coeff_, 3);
	EXPECT_EQ(new_monom.degree_, 111);
}

TEST(TMonom, cannot_create_wrong_monom) {
	ASSERT_ANY_THROW(TMonom new_monom(3, 1234));
}

TEST(TMonom, check_G_operation) {
	TMonom mon1(5, 122);
	TMonom mon2(5, 233);

	EXPECT_TRUE(mon2 > mon1);
}

TEST(TMonom, check_GE_operation) {
	TMonom mon1(5, 122);
	TMonom mon2(5, 233);

	EXPECT_TRUE(mon2 >= mon1);
}

TEST(TMonom, check_L_operation) {
	TMonom mon1(5, 122);
	TMonom mon2(5, 233);

	EXPECT_TRUE(mon1 < mon2);
}

TEST(TMonom, check_LE_operation) {
	TMonom mon1(5, 122);
	TMonom mon2(5, 233);

	EXPECT_TRUE(mon1 <= mon2);
}

TEST(TMonom, check_E_operation) {
	TMonom mon1(5, 122);
	TMonom mon2(5, 122);

	EXPECT_TRUE(mon1 == mon2);
}

TEST(TMonom, check_NE_operation) {
	TMonom mon1(5, 122);
	TMonom mon2(5, 21);

	EXPECT_TRUE(mon1 != mon2);
}

TEST(TMonom, can_assign_monom)
{
	TMonom mon1(5, 122);
	TMonom mon2;
	mon2 = mon1;
	EXPECT_EQ(5, mon2.coeff_);
	EXPECT_EQ(122, mon2.degree_);
}

TEST(TMonom, can_compare_monom_degrees_for_equal)
{
	TMonom mon1(5, 122);
	TMonom mon2(3, 122);
	EXPECT_TRUE(mon1 == mon2);
}

TEST(TMonom, can_compare_monom_degrees_for_not_equal)
{
	TMonom mon1(5, 122);
	TMonom mon2(3, 123);
	EXPECT_TRUE(mon1 != mon2);
}