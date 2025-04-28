#include <gtest.h>
#include "node.h"



TEST(TNode, can_create_node)
{
    ASSERT_NO_THROW(TNode<int> Node);
}

TEST(TNode, can_create_node_with_key)
{
    TNode<int> Node(7);
    EXPECT_EQ(Node.key, 7);
}

TEST(TNode, can_assign_nodes)
{
    TNode<int> Node(7);
    TNode<int> Node1(9);
    ASSERT_NO_THROW(Node = Node1);
}

TEST(TNode, assigned_nodes_have_same_keys)
{
    TNode<int> Node(7);
    TNode<int> Node1(9);
    Node1 = Node;
    EXPECT_EQ(Node.key, Node1.key);
}