#include <gtest.h>
#include "tpolynom.h"

const string str = "x+y+z";

TEST(TPolynom, create_empty_polinom)
{
	ASSERT_NO_THROW(TPolynom p());
}

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p(str));
}

TEST(TPolynom, can_create_copied_polinom)
{
	TPolynom p1(str);
	ASSERT_NO_THROW(TPolynom p2(p1));
}

TEST(TPolynom, equality_operator_is_correct)
{
	TPolynom p1(str);
	TPolynom p2(str);

	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, copied_polinom_is_correct)
{
	TPolynom p1(str);
	TPolynom p2(p1);
	EXPECT_EQ(p1, p2);
}
