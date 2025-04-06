#include "list.h"
#include "ringheadlist.h"
#include <gtest.h>

TEST(headlist, can_Reset_hr_list)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.Reset();
	EXPECT_EQ(1, hr_list.GetCurr()->data);
}

TEST(headlist, can_copy_hr_list)
{
	headlist<int> hr_list1;
	hr_list1.InsertLast(1);
	headlist<int> hr_list2(hr_list1);
	hr_list1.Reset();
	EXPECT_EQ(hr_list1.GetCurr()->data, hr_list2.GetCurr()->data);
}
TEST(headlist, can_assign_hr_list)
{
	headlist<int> hr_list1;
	hr_list1.InsertLast(1);
	hr_list1.InsertLast(2);
	headlist<int> hr_list2;
	hr_list2.InsertLast(3);
	hr_list2 = hr_list1;
	hr_list1.Reset();
	EXPECT_EQ(hr_list1.GetCurr()->data, hr_list2.GetCurr()->data);
}

TEST(headlist, can_insert_element) {
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	EXPECT_EQ(1, hr_list.GetCurr()->data);
}

TEST(headlist, can_get_Next_elemet)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}

TEST(headlist, check_hr_list_cannot_do_Next_method_at_Head)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.Next();
	ASSERT_ANY_THROW(hr_list.Next());
}

TEST(headlist, can_insert_element_at_beginning)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertFirst(2);
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}

TEST(headlist, can_insert_element_in_middle)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(3);
	hr_list.Reset();
	hr_list.InsertAfter(2, hr_list.GetCurr()->data);
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}

TEST(headlist, can_remove_first_element)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.Remove(1);
	hr_list.Reset();
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}

TEST(headlist, can_remove_last_element)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.Remove(2);
	hr_list.Reset();
	hr_list.Next();
	EXPECT_TRUE(hr_list.IsEnded());
}

TEST(headlist, can_clear_hr_list)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.InsertLast(3);
	hr_list.Clear();
	EXPECT_TRUE(hr_list.IsEmpty());
}

TEST(headlist, can_insert_element_before_current)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(3);
	hr_list.InsertBefore(2, hr_list.GetCurr()->data);
	hr_list.Reset();
	hr_list.Next();
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}

TEST(headlist, can_insert_element_after_current)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(3);
	hr_list.InsertAfter(2, hr_list.GetCurr()->data);
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}

TEST(headlist, can_check_if_hr_list_is_empty)
{
	headlist<int> hr_list;
	EXPECT_TRUE(hr_list.IsEmpty());
	hr_list.InsertLast(1);
	EXPECT_FALSE(hr_list.IsEmpty());
}

TEST(headlist, can_find_element_by_value)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.InsertLast(3);
	EXPECT_EQ(2, hr_list.Search(2)->data);
}

TEST(headlist, can_assign_empty_list)
{
	headlist<int> hr_list1;
	headlist<int> hr_list2;
	hr_list2 = hr_list1;
	EXPECT_TRUE(hr_list2.IsEmpty());
}

TEST(headlist, can_insert_element_in_empty_list)
{
	headlist<int> hr_list;
	hr_list.InsertFirst(1);
	EXPECT_EQ(1, hr_list.GetCurr()->data);
}

TEST(headlist, can_search_nonexistent_element)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.InsertLast(2);
	hr_list.InsertLast(3);
	EXPECT_EQ(nullptr, hr_list.Search(4));
}

TEST(headlist, can_correctly_copy_list)
{
	headlist<int> hr_list1;
	hr_list1.InsertLast(1);
	hr_list1.InsertLast(2);
	headlist<int> hr_list2(hr_list1);
	hr_list1.RemoveFirst();
	EXPECT_NE(hr_list1.GetCurr()->data, hr_list2.GetCurr()->data);
}

TEST(headlist, can_insert_after_end)
{
	headlist<int> hr_list;
	hr_list.InsertLast(1);
	hr_list.Next();
	hr_list.InsertLast(2);
	EXPECT_EQ(2, hr_list.GetCurr()->data);
}