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
    virtual ~HeadList(); 


    virtual void push_front(TNode<TData>* newNode);
    virtual void push_back(TNode<TData>* newNode);
    virtual void push_before(TNode<TData>* newNode, TData target_key);
    void remove(TData target_key);
    virtual const HeadList<TData>& operator=(const HeadList<TData>& list);
};



template <typename TData>
HeadList<TData>::HeadList() : TList<TData>()
{
    pHead = new TNode<TData>();
    this->pStop = pHead; 
    pHead->pNext = this->pFirst;
}

template <typename TData>
HeadList<TData>::HeadList(const HeadList<TData>& list) : TList(list)
{
    pHead = new TNode<TData>();
    this->pStop = pHead;
    pHead->pNext = this->pFirst;
}

template <typename TData>
HeadList<TData>::~HeadList()
{
    
    delete pHead;  
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
    
}

template <typename TData>
void HeadList<TData>::push_before(TNode<TData>* newNode, TData target_key)
{
    TList<TData>::push_before(newNode, target_key);
    if (this->pFirst == newNode)  
    {
        pHead->pNext = newNode;
    }
}

template <typename TData>
void HeadList<TData>::remove(TData target_key)
{
    TNode<TData>* toRemove = this->search(target_key);
    if (toRemove == nullptr)
    {
        throw "DID NOT FIND KEY!";
    }

    if (toRemove == this->pFirst)
    {
        this->pFirst = this->pFirst->pNext;
        pHead->pNext = this->pFirst;
        delete toRemove;
        if (this->pFirst == this->pStop)
        {
            this->pLast = nullptr;
        }
        return;
    }

    TList<TData>::remove(target_key);
}

template <typename TData>
const HeadList<TData>& HeadList<TData>::operator=(const HeadList<TData>& list)
{
    if (this == &list)
    {
        return *this;
    }

    TList<TData>::operator=(list);
    pHead->pNext = this->pFirst;
    return *this;
}