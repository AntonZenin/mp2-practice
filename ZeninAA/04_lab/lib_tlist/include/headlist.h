#pragma once
#include "list.h"

template <typename TData>
class HeadList : public TList<TData>
{
protected:
    TNode<TData>* pHead;

public:
    
    HeadList();
    HeadList(const HeadList<TData>& list);
    void push_front(TNode<TData>* newNode);
    void push_back(TNode<TData>* newNode);
    void push_before(TNode<TData>* newNode, TData target_key);
    void remove(TData target_key);
    const HeadList<TData>& operator=(const HeadList<TData>& list);
};



template <typename TData>
HeadList<TData>::HeadList() : TList<TData>()
{
    pHead = new TNode<TData>();
    pHead->pNext = this->pFirst;
}

template <typename TData>
HeadList<TData>::HeadList(const HeadList<TData>& list) : TList(list)
{
    pHead = new TNode<TData>();
    pHead->pNext = this->pFirst;
}

template <typename TData>
void HeadList<TData>::push_front(TNode<TData>* newNode)
{
    TList<TData>::push_front(newNode);
    pHead->pNext = this->pFirst;
}

template <typename TData>
void HeadList<TData>::push_back(TNode<TData>* newNode)
{
    TList<TData>::push_back(newNode);
    pHead->pNext = this->pFirst;
}

template <typename TData>
void HeadList<TData>::push_before(TNode<TData>* newNode, TData target_key)
{
    TList<TData>::push_before(newNode, target_key);
    pHead->pNext = this->pFirst;
}

template <typename TData>
void HeadList<TData>::remove(TData target_key)
{
    TList<TData>::remove(target_key);
    pHead->pNext = this->pFirst;
}

template <typename TData>
const HeadList<TData>& HeadList<TData>::operator=(const HeadList<TData>& list)
{
    TList<TData>::operator=(list);
    pHead->pNext = this->pFirst;
    return *this;
}