#pragma once
#include "headlist.h"

template <typename TData>
class RingHeadList : public HeadList<TData>
{
public:
    
    RingHeadList();
    RingHeadList(const RingHeadList<TData>& list);
    void push_front(TNode<TData>* newNode);
    void push_back(TNode<TData>* newNode);
    void push_after(TNode<TData>* newNode, TData target_key);
    void remove(TData target_key);

    
    const RingHeadList<TData>& operator=(const RingHeadList<TData>& list);
};


template <typename TData>
RingHeadList<TData>::RingHeadList() : HeadList<TData>()
{
    this->pLast = this->pHead;
    this->pHead->pNext = this->pLast;
    this->pStop = this->pHead;
}

template <typename TData>
RingHeadList<TData>::RingHeadList(const RingHeadList<TData>& list) : HeadList(list)
{
    if (list.pFirst == nullptr)
    {
        this->pFirst = nullptr;
        this->pLast = this->pHead;
        this->pHead->pNext = this->pLast;
        this->pStop = this->pHead;
        return;
    }
    this->pStop = this->pHead;
    this->pLast->pNext = this->pHead;
}

template <typename TData>
void RingHeadList<TData>::push_front(TNode<TData>* newNode)
{
    HeadList<TData>::push_front(newNode);
    this->pLast->pNext = this->pHead;
}

template <typename TData>
void RingHeadList<TData>::push_back(TNode<TData>* newNode)
{
    HeadList<TData>::push_back(newNode);
    this->pLast->pNext = this->pHead;
}

template <typename TData>
void RingHeadList<TData>::push_after(TNode<TData>* newNode, TData target_key)
{
    if (this->pLast->key == target_key)
    {
        this->push_back(newNode);
        return;
    }
    if (this->pHead->key == target_key)
    {
        this->push_front(newNode);
        return;
    }
    HeadList<TData>::push_after(newNode, target_key);
}

template <typename TData>
void RingHeadList<TData>::remove(TData target_key)
{
    if (this->pFirst->key == target_key && this->pFirst == this->pLast)
    {
        this->pLast = this->pHead;
        this->pLast->pNext = this->pHead;
        this->pFirst = nullptr;
        return;
    }
    HeadList<TData>::remove(target_key);
    this->pLast->pNext = this->pHead;
}

template <typename TData>
const RingHeadList<TData>& RingHeadList<TData>::operator=(const RingHeadList<TData>& list)
{
    if (list.pFirst == nullptr)
    {
        this->pFirst = nullptr;
        this->pLast = this->pHead;
        this->pHead->pNext = this->pLast;
        this->pStop = this->pHead;
        return *this;
    }

    HeadList<TData>::operator=(list);

    this->pStop = this->pHead;
    this->pLast->pNext = this->pHead;
    return *this;
}