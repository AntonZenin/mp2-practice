#pragma once
#include "node.h"
#include <iostream>
using namespace std;
template <typename TData>
class TList {
protected:
	TNode<TData>* pFirst;
	TNode<TData>* pLast;
	TNode<TData>* pCurr;
	TNode<TData>* pPrev;
	TNode<TData>* pStop;

public:
	TList();
	TList(const TList<TData>&);
	TList(TNode<TData>*); //////////
	virtual ~TList();
	TNode<TData>* Search(const TData&);
	virtual void InsertFirst(const TData&);
	virtual void InsertLast(const TData&);
	void InsertBefore(const TData&, const TData&);
	void InsertAfter(const TData&, const TData&);
	virtual void RemoveFirst();
	void Remove(const TData&);
	virtual void Clear();
	void Reset();
	void Next();
	TNode<TData>* GetCurr() const;
	virtual bool IsEnded() const;
	bool IsEmpty() const;
	bool IsFull() const;

	friend std::ostream& operator<<(std::ostream& out, const TList<TData>& list) {
		TNode<TData>* tmp = list.pFirst;
		int num = 1;
		while (tmp != nullptr) {
			out << num << " node " << tmp->data << std::endl;
			tmp = tmp->pNext;
			num++;
		}
		return out;
	}
};

template <typename TData>
TList<TData>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurr = nullptr;
	pPrev = nullptr;
	pStop = nullptr;
}

template <typename TData>
bool TList<TData>::IsEmpty() const {
	return pFirst == nullptr;
}

template <typename TData>
TList<TData>::TList(const TList& l) {
	if (l.IsEmpty())
	{
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pPrev = nullptr;
		pStop = nullptr;
		return;
	}

	pFirst = new TNode<TData>(l.pFirst->data);
	TNode<TData>* tmp = pFirst;
	TNode<TData>* ltmp = l.pFirst->pNext;
	while (ltmp != l.pStop)
	{
		tmp->pNext = new TNode<TData>(ltmp->data);
		tmp = tmp->pNext;
		ltmp = ltmp->pNext;
	}
	pLast = tmp;
	pCurr = pFirst;
	pPrev = nullptr;
	pStop = nullptr;
}

template <typename TData>
TList<TData>::TList(TNode<TData>* pNode) {
	pFirst = pNode;
	TNode<TData>* tmp = pNode;
	while (tmp->pNext != nullptr)
		tmp = tmp->pNext;
	pLast = tmp;
	pCurr = pFirst;
	pPrev = nullptr;
	pStop = nullptr;
}

template <typename TData>
void TList<TData>::Clear() {
	if (pFirst == nullptr)
		return;
	TNode<TData>* curr = pFirst;
	TNode<TData>* next = pFirst->pNext;
	while (next != pStop) {
		delete curr;
		curr = next;
		next = curr->pNext;
	}
	delete curr;
	pCurr = nullptr;
	pFirst = nullptr;
	pPrev = nullptr;
	pLast = nullptr;
}

template <typename TData>
TList<TData>::~TList() {
	Clear();
}

template <typename TData>
bool TList<TData>::IsFull() const {
	TNode<TData>* tmp = new TNode<TData>();
	if (tmp == nullptr)
		return true;
	delete tmp;
	return false;
}

template <typename TData>
bool TList<TData>::IsEnded()const {
	return pCurr == pStop;
}

template <typename TData>
TNode<TData>* TList<TData>::Search(const TData& data) {
	if (IsEmpty()) return nullptr;

	TNode<TData>* prev = nullptr;
	TNode<TData>* curr = pFirst;

	while (curr != pStop && curr->data != data) {
		prev = curr;
		curr = curr->pNext;
	}

	if (curr == pStop) return nullptr;
	pCurr = curr;
	pPrev = prev;
	return curr;
}

template <typename TData>
void TList<TData>::InsertFirst(const TData& data) {
	TNode<TData>* new_first = new TNode<TData>(data, pFirst);
	pFirst = new_first;
	if (pLast == nullptr) {
		pLast = pFirst;
	}
	pCurr = pFirst;
	pPrev = nullptr;
}

template <typename TData>
void TList<TData>::InsertLast(const TData& data) {
	if (IsEmpty()) {
		InsertFirst(data);
		return;
	}
	TNode<TData>* new_last = new TNode<TData>(data, pStop);
	pLast->pNext = new_last;
	pPrev = pLast;
	pLast = new_last;
	pCurr = new_last;
}

template <typename TData>
void TList<TData>::InsertBefore(const TData& who, const TData& where) {
	TNode<TData>* pWhere = Search(where);
	if (pWhere == nullptr) {
		throw exception("no elements");
	}

	if (pWhere == pFirst) {
		InsertFirst(who);
		return;
	}
	TNode<TData>* new_node = new TNode<TData>(who, pWhere);
	pPrev->pNext = new_node;
	pCurr = new_node;
}

template <typename TData>
void TList<TData>::InsertAfter(const TData& who, const TData& where) {
	TNode<TData>* pWhere = Search(where);
	if (pWhere == nullptr) {
		throw exception("no elements");
	}
	if (pWhere == pLast) {
		InsertLast(who);
		return;
	}
	TNode<TData>* new_node = new TNode<TData>(who, pWhere->pNext);
	pWhere->pNext = new_node;
	pCurr = new_node;
	pPrev = pWhere;
}

template <typename TData>
void TList<TData>::RemoveFirst() {
	TNode<TData>* first = pFirst;
	pFirst = pFirst->pNext;
	delete first;
}

template <typename TData>
void TList<TData>::Remove(const TData& where)
{
	TNode<TData>* pWhere = Search(where);
	if (pWhere == nullptr) {
		throw exception("no elements");
	}

	if (pWhere == pFirst && pWhere->pNext == pStop)
	{
		Clear();
		return;
	}
	if (pWhere == pFirst)
	{
		RemoveFirst();
		pCurr = pFirst;
		return;
	}
	if (pWhere == pLast)
	{
		pPrev->pNext = pStop;
		pLast = pPrev;
		pCurr = pStop;
		delete pWhere;
		return;
	}
	pPrev->pNext = pWhere->pNext;
	pCurr = pWhere->pNext;
	delete pWhere;

}

template <typename TData>
void TList<TData>::Reset() {
	pCurr = pFirst;
	pPrev = nullptr;
}

template <typename TData>
void TList<TData>::Next() {
	if (pCurr == pStop)
		throw exception("end of the list");
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}

template <typename TData>
TNode<TData>* TList<TData>::GetCurr() const {
	return pCurr;
}