#include "list.h"
#include <gtest.h>

TEST(TList, can_create_new_list)
{
	ASSERT_NO_THROW(TList<int> new_list);
}

TEST(TList, list_is_empty_check)
{
	TList<int> list;
	ASSERT_TRUE(list.IsEmpty());
}

TEST(TList, check_non_empty)
{
	TList<int> list;
	list.InsertLast(2);
	EXPECT_EQ(false, list.IsEmpty());
}

TEST(TList, can_InsertLast_in_the_list)
{
	TList<int> list;
	ASSERT_NO_THROW(list.InsertLast(1));
}

TEST(TList, can_insert_element_in_not_empty_list)
{
	TList<int> list;
	list.InsertLast(1);
	ASSERT_NO_THROW(list.InsertLast(2));
}

TEST(TList, can_Remove_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	list.InsertLast(3);
	list.Remove(3);
	EXPECT_EQ(true, list.IsEnded());
}

TEST(TList, can_get_current_elemet)
{
	TList<int> list;
	list.InsertLast(1);
	EXPECT_EQ(1, list.GetCurr()->data);
}

TEST(TList, can_clear_list)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	list.Clear();
	EXPECT_EQ(true, list.IsEmpty());
}

TEST(TList, error_when_Remove_from_empty_list)
{
	TList<int> list;
	ASSERT_ANY_THROW(list.Remove(5));
}

TEST(TList, error_when_Remove_non_exist_elem)
{
	TList<int> list;
	list.InsertLast(4);
	ASSERT_ANY_THROW(list.Remove(5));
}

TEST(TList, can_InsertFirst_element)
{
	TList<int> list;
	list.InsertFirst(1);
	ASSERT_NO_THROW(list.InsertFirst(2));
}

TEST(TList, can_insert_after_element)
{
	TList<int> list;
	list.InsertFirst(1);
	list.InsertFirst(2);
	ASSERT_NO_THROW(list.InsertAfter(3, 2));
}

TEST(TList, next_element)
{
	TList<int> list;
	list.InsertFirst(1);
	list.InsertFirst(2);
	list.Next();
	EXPECT_EQ(1, list.GetCurr()->data);
}

TEST(TList, reset_test)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	list.Reset();
	EXPECT_EQ(1, list.GetCurr()->data);
}

TEST(TList, can_InsertBefore_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	ASSERT_NO_THROW(list.InsertBefore(3, 2));
}

TEST(TList, can_RemoveFirst_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	ASSERT_NO_THROW(list.RemoveFirst());
}

TEST(TList, can_RemoveLast_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	ASSERT_NO_THROW(list.Remove(2));
}

TEST(TList, can_Reset_to_First_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	list.Reset();
	EXPECT_EQ(1, list.GetCurr()->data);
}

TEST(TList, can_Search_for_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	EXPECT_NE(nullptr, list.Search(2));
}

TEST(TList, can_InsertBefore_first_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	ASSERT_NO_THROW(list.InsertBefore(3, 1));
}

TEST(TList, can_Insert_last_element)
{
	TList<int> list;
	list.InsertLast(1);
	list.InsertLast(2);
	ASSERT_NO_THROW(list.InsertAfter(3, 2));
}