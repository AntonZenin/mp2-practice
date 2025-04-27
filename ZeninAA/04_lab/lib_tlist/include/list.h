#pragma once
#include "node.h"
#include <iostream>
using namespace std;

template <typename TData>
class TList
{
protected:
    TNode<TData>* pFirst;
    TNode<TData>* pCurr;
    TNode<TData>* pPrev;
    TNode<TData>* pLast;
    TNode<TData>* pStop;

public:
   
    TList();
    TList(const TList<TData>& list);
    ~TList();   
    void copy(const TList<TData>& list);
    void clear();
    void reset();
    void next();
    bool is_ended();
    TNode<TData>* getCurr() const;
    TNode<TData>* search(TData target_key);
    virtual void push_front(TNode<TData>* newNode);
    virtual void push_back(TNode<TData>* newNode);
    virtual void push_after(TNode<TData>* newNode, TData target_key);
    virtual void push_before(TNode<TData>* newNode, TData target_key);
    virtual void remove(TData target_key);
    const TList<TData>& operator=(const TList<TData>& list);
    bool operator==(const TList<TData>& list) const;
    bool operator!=(const TList<TData>& list) const;
};


template <typename TData>
TList<TData>::TList()
{
    pFirst = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
    pStop = nullptr;
    pLast = nullptr;
}

template <typename TData>
TList<TData>::TList(const TList<TData>& list)
{
    if (list.pFirst == nullptr)
    {
        pFirst = nullptr;
        return;
    }
    copy(list);
    pStop = nullptr;
}

template <typename TData>
TList<TData>::~TList()
{
    reset();
    if (pFirst == nullptr)
    {
        return;
    }
    clear();
    pFirst = nullptr;
}

template <typename TData>
void TList<TData>::copy(const TList<TData>& list)
{
    pFirst = new TNode<TData>(list.pFirst->key);
    TNode<TData>* curr_origin = list.pFirst->pNext;
    TNode<TData>* curr_copy = pFirst;
    while (curr_origin != list.pStop)
    {
        curr_copy->pNext = new TNode<TData>(curr_origin->key);
        curr_copy = curr_copy->pNext;
        curr_origin = curr_origin->pNext;
    }
    pLast = curr_copy;
}

template <typename TData>
void TList<TData>::clear()
{
    reset();
    while (!(is_ended()))
    {
        TNode<TData>* tmp = pCurr->pNext;
        delete pCurr;
        pCurr = tmp;
    }
}

template <typename TData>
void TList<TData>::reset()
{
    pCurr = pFirst;
    pPrev = nullptr;
}

template <typename TData>
void TList<TData>::next()
{
    pPrev = pCurr;
    pCurr = pCurr->pNext;
}

template <typename TData>
bool TList<TData>::is_ended()
{
    return pCurr == pStop;
}

template <typename TData>
TNode<TData>* TList<TData>::getCurr() const
{
    return pCurr;
}

template <typename TData>
TNode<TData>* TList<TData>::search(TData target_key)
{
    reset();
    if (pCurr == nullptr)
    {
        return nullptr;
    }
    while (!(is_ended()))
    {
        if (pCurr->key == target_key)
        {
            return pCurr;
        }
        next();
    }
    return nullptr;
}

template <typename TData>
void TList<TData>::push_front(TNode<TData>* newNode)
{
    if (pFirst == nullptr)
    {
        pFirst = newNode;
        pLast = pFirst;
        return;
    }
    newNode->pNext = pFirst;
    pFirst = newNode;
}

template <typename TData>
void TList<TData>::push_back(TNode<TData>* newNode)
{
    if (newNode == nullptr)
    {
        throw "EMPTY NODE";
    }
    reset();
    if (pCurr == nullptr)
    {
        push_front(newNode);
        return;
    }
    while (pCurr->pNext != pStop)
    {
        next();
    }
    pCurr->pNext = newNode;
    pLast = pCurr->pNext;
}

template <typename TData>
void TList<TData>::push_after(TNode<TData>* newNode, TData target_key)
{
    pCurr = this->search(target_key);
    if (pCurr == nullptr)
    {
        throw "DID NOT FIND KEY";
    }
    newNode->pNext = pCurr->pNext;
    pCurr->pNext = newNode;
}

template <typename TData>
void TList<TData>::push_before(TNode<TData>* newNode, TData target_key)
{
    reset();
    if (pCurr->key == target_key)
    {
        push_front(newNode);
        return;
    }
    pCurr = this->search(target_key);
    if (pCurr == nullptr)
    {
        throw "DID NOT FIND KEY!";
    }
    TNode<TData>* tmp = pCurr;
    pPrev->pNext = newNode;
    newNode->pNext = tmp;
}

template <typename TData>
void TList<TData>::remove(TData target_key)
{
    reset();
    if (search(target_key) == nullptr)
    {
        throw "DID NOT FIND KEY!";
    }
    if (pFirst->key == target_key)
    {
        pFirst = pCurr->pNext;
        return;
    }
    pCurr = this->search(target_key);
    if (pCurr == pLast)
    {
        pPrev->pNext = pCurr->pNext;
        pLast = pPrev;
        return;
    }
    pPrev->pNext = pCurr->pNext;
}

template <typename TData>
const TList<TData>& TList<TData>::operator=(const TList<TData>& list)
{
    TList<TData> listcopy(list);
    if (this == &list)
    {
        return *this;
    }
    if (listcopy.pFirst == nullptr)
    {
        pFirst = nullptr;
        pLast = nullptr;
        return *this;
    }
    if (pFirst != nullptr)
    {
        clear();
    }
    copy(listcopy);
    return *this;
}

template <typename TData>
bool TList<TData>::operator==(const TList<TData>& list) const
{
    TList<TData> myself(*this);
    TList<TData> listcopy(list);

    myself.reset();
    listcopy.reset();
    if (myself.pCurr == nullptr && listcopy.pCurr == nullptr)
    {
        return true;
    }
    while (!(listcopy.is_ended()) && !(myself.is_ended()))
    {
        if ((myself.pCurr->key != listcopy.pCurr->key))
        {
            return false;
        }
        listcopy.next();
        myself.next();
    }
    return true;
}

template <typename TData>
bool TList<TData>::operator!=(const TList<TData>& list) const
{
    return !(*this == list);
}
