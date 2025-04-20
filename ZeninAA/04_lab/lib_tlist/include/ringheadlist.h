#pragma once
#include "list.h"
#include <iostream>
using namespace std;

template <typename TData>
class headlist : public TList<TData> {
protected:
	TNode<TData>* pHead;
public:
	headlist();
	headlist(const headlist<TData>& list);
	~headlist();
	void RemoveFirst();
	void Clear();
	void InsertFirst(const TData& data);
	void InsertLast(const TData& data);
	bool IsEnded() const;
	const headlist<TData>& operator=(const headlist<TData>& l);

	friend std::ostream& operator<<(std::ostream& out, headlist<TData>& ringList) {
		TNode<TData>* tmp = ringList.pFirst;
		int num = 1;
		while (tmp != ringList.pHead) {
			out << num << " node " << tmp->data << std::endl;
			tmp = tmp->pNext;
			num++;
		}
		return out;
	}
};

template <typename TData>
headlist<TData>::headlist() : TList<TData>() {
	pHead = new TNode<TData>();
	pHead->pNext = pHead;
	pStop = pHead;
}

template <typename TData>
headlist<TData>::headlist(const headlist<TData>& list) : TList<TData>(list) {
	pHead = new TNode<TData>(list.pHead->data, pFirst);
	if (!list.IsEmpty())
		pLast->pNext = pHead;
	else
		pHead->pNext = pHead;
	pStop = pHead;
}

template <typename TData>
headlist<TData>::~headlist() {
	delete pHead;
	if (pLast != nullptr)
		pLast->pNext = nullptr;
	pStop = nullptr;
}

template <typename TData>
void headlist<TData>::InsertFirst(const TData& data) {
	TList<TData>::InsertFirst(data);
	pHead->pNext = pFirst;
	pStop = pHead;
	pLast->pNext = pHead;
}

template <typename TData>
void headlist<TData>::InsertLast(const TData& data) {
	if (IsEmpty()) {
		headlist<TData>::InsertFirst(data);
		return;
	}
	TList<TData>::InsertLast(data);
}

template <typename TData>
void headlist<TData>::RemoveFirst() {
	TNode<TData>* first = pFirst;
	pFirst = pFirst->pNext;
	pHead->pNext = pFirst;
	delete first;
}

template <typename TData>
void headlist<TData>::Clear()
{
	TList<TData>::Clear();
	pHead->pNext = pHead;
}

template <typename TData>
const headlist<TData>& headlist<TData>::operator=(const headlist<TData>& l) {
	if (this == &l) return (*this);

	if (l.IsEmpty())
	{
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pPrev = nullptr;
		pStop = nullptr;
		return *(this);
	}

	Clear();
	Copy(l); 

	return *(this);
}

template <typename TData>
bool headlist<TData>::IsEnded() const {
	if (IsEmpty())
		return true;
	return pCurr == pStop;
}