#pragma once
using namespace std;
template <typename TData>
struct TNode {
    TData data;
    TNode* pNext;

    TNode() {
        this->data = TData();
        this->pNext = nullptr;
    }

    TNode(const TData& data, TNode* pNext = nullptr) {
        this->data = data;
        this->pNext = pNext;
    }
};