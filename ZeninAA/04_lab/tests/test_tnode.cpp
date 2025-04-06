#include "list.h"
#include <gtest.h>

TEST(TNode, can_create_node) {
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>);
}

TEST(TNode, can_create_node_with_data) {
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(1));
}

TEST(TNode, check_is_data_correct) {
	TNode<int>* node = new TNode<int>(1);
	EXPECT_EQ(1, node->data);
}

TEST(TNode, node_work_correct) {
	TNode<int>* node = new TNode<int>(5);
	node->pNext = new TNode<int>(6);
	EXPECT_EQ(6, node->pNext->data);
}

TEST(TNode, copied_node_is_equal) {
	TNode<int>* tmp = new TNode<int>(5);
	TNode<int>* node = new TNode<int>(tmp->data, tmp->pNext);
	bool p1 = node->data == tmp->data;
	bool p2 = node->pNext == tmp->pNext;
	EXPECT_EQ(true, p1 == p2 == true);
}

TEST(TNode, copied_node_have_equal_data) {
	TNode<int>* tmp = new TNode<int>(1);
	TNode<int>* node = new TNode<int>(tmp->data);
	EXPECT_EQ(1, node->data);
}

TEST(TNode, next_node_has_correct_data) {
	TNode<int>* tmp = new TNode<int>(7);
	TNode<int>* node = new TNode<int>(3, tmp);
	EXPECT_EQ(7, node->pNext->data);
}

TEST(TNode, next_node_is_null) {
	TNode<int>* tmp = new TNode<int>(7);
	TNode<int>* node = new TNode<int>(3, tmp);
	EXPECT_EQ(nullptr, node->pNext->pNext);
}
TEST(TNode, can_set_data_to_node)
{
	TNode<int>* node = new TNode<int>();
	node->data = 10;
	EXPECT_EQ(10, node->data);
}

TEST(TNode, can_set_next_node)
{
	TNode<int>* node1 = new TNode<int>(1);
	TNode<int>* node2 = new TNode<int>(2);
	node1->pNext = node2;
	EXPECT_EQ(2, node1->pNext->data);
}

TEST(TNode, can_create_node_with_custom_data)
{
	TNode<string>* node = new TNode<string>("Hello");
	EXPECT_EQ("Hello", node->data);
}

TEST(TNode, can_create_node_with_null_next)
{
	TNode<double>* node = new TNode<double>(3.14);
	EXPECT_EQ(nullptr, node->pNext);
}

TEST(TNode, can_compare_nodes_data)
{
	TNode<char>* node1 = new TNode<char>('a');
	TNode<char>* node2 = new TNode<char>('a');
	EXPECT_EQ(node1->data, node2->data);
}

TEST(TNode, can_update_node_data)
{
	TNode<int>* node = new TNode<int>(5);
	node->data = 10;
	EXPECT_EQ(10, node->data);
}

TEST(TNode, can_update_next_node)
{
	TNode<int>* node1 = new TNode<int>(1);
	TNode<int>* node2 = new TNode<int>(2);
	node1->pNext = node2;

	TNode<int>* updatedNode = new TNode<int>(3);
	node1->pNext = updatedNode;

	EXPECT_EQ(3, node1->pNext->data);
}