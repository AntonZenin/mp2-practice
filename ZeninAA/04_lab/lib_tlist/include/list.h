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
    virtual ~TList();   
    void copy(const TList<TData>& list);
    void clear();
    void reset();
    void next();
    void removeFirst();
    void removeLast();

    bool is_ended() const;
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
    
    copy(list);
    pStop = nullptr;
}

template <typename TData>
TList<TData>::~TList()
{
    
    clear();
    
}

template <typename TData>
void TList<TData>::copy(const TList<TData>& list)
{
    if (list.pFirst == nullptr)
    {
        pFirst = nullptr;
        return;
    }
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
bool TList<TData>::is_ended() const
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
        pLast->pNext = pStop;
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
    if (pFirst == nullptr)
    {
        push_front(newNode);
        return;
    }
    pLast->pNext = newNode;
    pLast = pLast->pNext;
    pLast->pNext = pStop;
}

template <typename TData>
void TList<TData>::push_after(TNode<TData>* newNode, TData target_key)
{
    this->search(target_key);
    if (pCurr == nullptr)
    {
        throw "DID NOT FIND KEY";
    }
    if (pCurr == pLast)
    {
        push_back(newNode);
        return;
    }
    newNode->pNext = pCurr->pNext;
    pCurr->pNext = newNode;
}

template <typename TData>
void TList<TData>::push_before(TNode<TData>* newNode, TData target_key)
{
    this->search(target_key);
    if (pCurr == nullptr)
    {
        throw "DID NOT FIND KEY!";
    }
    if (pCurr == pFirst)
    {
        push_front(newNode);
        return;
    }
    newNode->pNext = pCurr;
    pPrev->pNext = newNode;
}


template <typename TData>
void TList<TData>::removeFirst()
{
    pFirst = pFirst->pNext;
    delete pCurr;
    if (pFirst == pStop)
    {
        pFirst = pCurr = pPrev = pLast = nullptr;
    }
}


template <typename TData>
void TList<TData>::removeLast()
{
    pPrev->pNext = pStop;
    delete pLast;
    pLast = pPrev;
}


template <typename TData>
void TList<TData>::remove(TData target_key)
{
    search(target_key);
    if (pCurr == nullptr)
    {
        throw "DID NOT FIND KEY!";
    }
    if (pCurr == pFirst)
    {
        removeFirst();
        return;
    }
    if (pCurr == pLast)
    {
        removeLast();
        return;
    }
    pPrev->pNext = pCurr->pNext; 
    delete pCurr;
}
 
template <typename TData>
const TList<TData>& TList<TData>::operator=(const TList<TData>& list)
{
    
    if (this == &list)
    {
        return *this;
    }
    clear();
    copy(list);
    return *this;
}

template <typename TData>
bool TList<TData>::operator==(const TList<TData>& list) const
{
    TList<TData> myself(*this);
    TList<TData> listcopy(list);

    myself.reset();
    listcopy.reset();
    
    while (!listcopy.is_ended() && !myself.is_ended())
    {
        if ((myself.pCurr->key != listcopy.pCurr->key))
        {
            return false;
        }
        listcopy.next();
        myself.next();
    }
    return listcopy.is_ended() && myself.is_ended(); 
}

template <typename TData>
bool TList<TData>::operator!=(const TList<TData>& list) const
{
    return !(*this == list);
}
