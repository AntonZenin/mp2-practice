#pragma once
#include <iostream>
using namespace std;

template <typename TData>
struct TNode
{
    TData key;
    TNode* pNext;

    TNode()
    {
        key = TData();
        pNext = nullptr;
    }
    TNode(TData key)
    {
        this->key = key;
        pNext = nullptr;
    }

    friend ostream& operator << (ostream& os, const TNode<TData>& node)
    {
        os << node.key;
        return os;
    }
    const TNode<TData>& operator = (const TNode<TData>& node)
    {
        if (this == &node)
        {
            return *this;
        }
        key = node.key;
        pNext = node.pNext;
        return *this;
    }
};