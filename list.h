#include<cstddef>
#include<iostream>

template <typename T>
struct node;

template <typename T>
class list;

template <typename T>
struct dblNode;

template <typename T>
class dblList;

template <typename T>
struct node
{
	T member;
	node<T>* ptrNext;
};

//Singly linked list template class
template <typename T>
class list
{
	private:
	node<T>* ptrHead;
	node<T>* ptrCurrent;
	node<T>* ptrTail;
	int* ptrNumCopies;
	int numel;
	
	public:
	list()
	{
		ptrHead = NULL;
		ptrCurrent = NULL;
		ptrTail = NULL;
		numel = 0;
		ptrNumCopies = new int;
		*ptrNumCopies = 1;
	}
	
	list(T a)
	{
		node<T>* ptrCurrentNode = new node<T>;
		ptrCurrentNode->member = a;
		ptrCurrentNode->ptrNext = NULL;
		ptrHead = ptrCurrentNode;
		ptrCurrent = ptrCurrentNode;
		ptrTail = ptrCurrentNode;
		numel = 1;
		ptrNumCopies = new int;
		*ptrNumCopies = 1;
	}
	
	list(const list &L)
	{
		ptrHead = L.ptrHead;
		ptrCurrent = L.ptrCurrent;
		ptrTail = L.ptrTail;
		numel = L.numel;
		ptrNumCopies = L.ptrNumCopies;
		*ptrNumCopies = *ptrNumCopies + 1;
	}
	
	void operator=(const list &L)
	{
		if(*ptrNumCopies == 1)
		{
			node<T>* ptrDelete = ptrHead;
			node<T>* ptrTemp;
			while(ptrDelete != NULL)
			{
				ptrTemp = ptrDelete;
				ptrDelete = ptrDelete->ptrNext;
				delete ptrTemp;
			}
		}
		else
			*ptrNumCopies = *ptrNumCopies - 1;
		ptrHead = L.ptrHead;
		numel = L.numel;
		ptrCurrent = L.ptrCurrent;
		ptrTail = L.ptrTail;
		ptrNumCopies = L.ptrNumCopies;
		*ptrNumCopies = *ptrNumCopies + 1;
	}
	
	~list()
	{
		if(*ptrNumCopies == 1)
		{
			node<T>* ptrDelete = ptrHead;
			node<T>* ptrTemp;
			while(ptrDelete != NULL)
			{
				ptrTemp = ptrDelete;
				ptrDelete = ptrDelete->ptrNext;
				delete ptrTemp;
			}
			delete ptrNumCopies;
		}
		else
			*ptrNumCopies = *ptrNumCopies - 1;
	}
	
	void PushBack(T a)
	{
		if(ptrHead == NULL)
		{
			node<T>* ptrCurrentNode = new node<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = NULL;
			ptrHead = ptrCurrentNode;
			ptrTail = ptrCurrentNode;
			ptrCurrent = ptrCurrentNode;
			numel++;
		}
		else
		{
			node<T>* ptrCurrentNode = new node<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = NULL;
			ptrTail->ptrNext = ptrCurrentNode;
			ptrTail = ptrCurrentNode;
			numel++;
		}
	}
	
	void PushFront(T a)
	{
		if(ptrHead == NULL)
		{
			node<T>* ptrCurrentNode = new node<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = NULL;
			ptrHead = ptrCurrentNode;
			ptrTail = ptrCurrentNode;
			ptrCurrent = ptrCurrentNode;
			numel++;
		}
		else
		{
			node<T>* ptrCurrentNode = new node<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = ptrHead;
			ptrHead = ptrCurrentNode;
			numel++;
		}
	}
	
	void Append(const list &L)
	{
		if(L.ptrHead != NULL)
		{
			node<T>* ptrTempL = L.ptrHead;
			if(ptrHead == NULL)
			{
				PushFront(ptrTempL->member);
				ptrTempL = ptrTempL->ptrNext;
			}
			node<T>* ptrTemp = ptrTail;
			while(ptrTempL != NULL)
			{
				node<T>* ptrCurrentNode = new node<T>;
				ptrTemp->ptrNext = ptrCurrentNode;
				ptrCurrentNode->member = ptrTempL->member;
				ptrTemp = ptrTemp->ptrNext;
				ptrTempL = ptrTempL->ptrNext;
				numel++;
			}
			ptrTail = ptrTemp;
			ptrTail->ptrNext = NULL;
		}
	}
	
	void DeleteFirst()
	{
		if(ptrHead != NULL)
		{
			if(ptrHead->ptrNext == NULL)
			{
				delete ptrHead;
				ptrHead = NULL;
				ptrCurrent = NULL;
				ptrTail = NULL;
				numel--;
			}
			else
			{
				node<T>* ptrTemp = ptrHead->ptrNext;
				if(ptrCurrent == ptrHead)
					ptrCurrent = ptrTemp;
				delete ptrHead;
				ptrHead = ptrTemp;
				numel--;
			}
		}
	}
	
	void DeleteLast()
	{
		if(ptrHead != NULL)
		{
			if(ptrHead->ptrNext == NULL)
			{
				delete ptrHead;
				ptrHead = NULL;
				ptrCurrent = NULL;
				ptrTail = NULL;
				numel--;
			}
			else
			{
				node<T>* ptrTemp = ptrHead;
				while(ptrTemp->ptrNext != ptrTail)
					ptrTemp = ptrTemp->ptrNext;
				ptrTemp->ptrNext = NULL;
				delete ptrTail;
				ptrTail = ptrTemp;
				numel--;
			}
		}
	}
	
	void Delete(int a)
	{
		if(a < 1 || a > numel)
			void();
		else if(ptrHead != NULL)
		{
			if(a == 1)
				DeleteFirst();
			else if(a == numel)
				DeleteLast();
			else
			{
				ptrCurrent = ptrHead;
				for(int i=2; i<a; i++)
					ptrCurrent = ptrCurrent->ptrNext;
				node<T>* ptrTemp = ptrCurrent->ptrNext->ptrNext;
				delete ptrCurrent->ptrNext;
				ptrCurrent->ptrNext = ptrTemp;
				numel--;
			}
		}
	}
	
	void Reverse()
	{
		if(ptrHead == NULL || ptrHead->ptrNext == NULL)
			void();
		else
		{
			list<T> reverseList;
			node<T>* ptrTemp = ptrHead;
			node<T>* ptrTempR;
			while(ptrTemp != NULL)
			{
				reverseList.PushFront(ptrTemp->member);
				ptrTemp = ptrTemp->ptrNext;
			}
			ptrTemp = ptrHead;
			ptrTempR = reverseList.ptrHead;
			while(ptrTemp != NULL)
			{
				ptrTemp->member = ptrTempR->member;
				ptrTemp = ptrTemp->ptrNext;
				ptrTempR = ptrTempR->ptrNext;
			}
		}
	}
	
	T GetFirst()
	{
		return ptrHead->member;
	}
	
	T GetLast()
	{
		return ptrTail->member;
	}
	
	T GetCurrent()
	{
		return ptrCurrent->member;
	}

	T GetNext()
	{
		if(ptrCurrent->ptrNext != NULL)
			return ptrCurrent->ptrNext->member;
		else
			return ptrTail->member;
	}
	
	T Get(int a)
	{
		if(a < 0 || a> numel)
			return T(NULL);	
		node<T>* ptrTemp = ptrHead;
		for(int i=1; i<a; i++)
			ptrTemp = ptrTemp->ptrNext;
		return ptrTemp->member;
	}
	
	bool EndofList()
	{
		if(ptrCurrent == NULL)
			return true;
		else
			return false;
	}
	
	dblList<T> MakeDouble()
	{
		dblList<T> doubleList;
		node<T>* ptrTemp = ptrHead;
		while(ptrTemp != NULL)
		{
			doubleList.PushBack(ptrTemp->member);
			ptrTemp = ptrTemp->ptrNext;
		}
		return doubleList;
	}

	void Reset()
	{
		ptrCurrent = ptrHead;
	}
	
	void StepForward()
	{
		ptrCurrent = ptrCurrent->ptrNext;
	}
	
	int Numel()
	{
		return numel;
	}
	
	void PrintList()
	{
		node<T>* temp = ptrHead;
		while(temp != NULL)
		{
			std::cout << temp->member << std::endl;
			temp = temp->ptrNext;
		}
	}
};

template <typename T>
struct dblNode
{
	T member;
	dblNode<T>* ptrNext;
	dblNode<T>* ptrLast;
};

//Doubly linked list template class
template <typename T>
class dblList
{
	private:
	dblNode<T>* ptrHead;
	dblNode<T>* ptrCurrent;
	dblNode<T>* ptrTail;
	int* ptrNumCopies;
	int numel;
	
	public:
	dblList()
	{
		ptrHead = NULL;
		ptrCurrent = NULL;
		ptrTail = NULL;
		numel = 0;
		ptrNumCopies = new int;
		*ptrNumCopies = 1;
	}
	
	dblList(T a)
	{
		dblNode<T>* ptrCurrentNode = new dblNode<T>;
		ptrCurrentNode->member = a;
		ptrCurrentNode->ptrNext = NULL;
		ptrCurrentNode->ptrLast = NULL;
		ptrHead = ptrCurrentNode;
		ptrCurrent = ptrCurrentNode;
		ptrTail = ptrCurrentNode;
		numel = 1;
		ptrNumCopies = new int;
		*ptrNumCopies = 1;
	}
	
	dblList(const dblList &L)
	{
		ptrHead = L.ptrHead;
		ptrCurrent = L.ptrCurrent;
		ptrTail = L.ptrTail;
		numel = L.numel;
		ptrNumCopies = L.ptrNumCopies;
		*ptrNumCopies = *ptrNumCopies + 1;
	}
	
	void operator=(const dblList &L)
	{
		if(*ptrNumCopies == 1)
		{
			dblNode<T>* ptrDelete = ptrHead;
			dblNode<T>* ptrTemp;
			while(ptrDelete != NULL)
			{
				ptrTemp = ptrDelete;
				ptrDelete = ptrDelete->ptrNext;
				delete ptrTemp;
			}
		}
		else
			*ptrNumCopies = *ptrNumCopies - 1;
		ptrHead = L.ptrHead;
		numel = L.numel;
		ptrCurrent = L.ptrCurrent;
		ptrTail = L.ptrTail;
		ptrNumCopies = L.ptrNumCopies;
		*ptrNumCopies = *ptrNumCopies + 1;
	}
	
	~dblList()
	{
		if(*ptrNumCopies == 1)
		{
			dblNode<T>* ptrDelete = ptrHead;
			dblNode<T>* ptrTemp;
			while(ptrDelete != NULL)
			{
				ptrTemp = ptrDelete;
				ptrDelete = ptrDelete->ptrNext;
				delete ptrTemp;
			}
			delete ptrNumCopies;
		}
		else
			*ptrNumCopies = *ptrNumCopies - 1;
	}
	
	void PushBack(T a)
	{
		if(ptrHead == NULL)
		{
			dblNode<T>* ptrCurrentNode = new dblNode<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = NULL;
			ptrCurrentNode->ptrLast = NULL;
			ptrHead = ptrCurrentNode;
			ptrTail = ptrCurrentNode;
			ptrCurrent = ptrCurrentNode;
			numel++;
		}
		else
		{
			dblNode<T>* ptrCurrentNode = new dblNode<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = NULL;
			ptrCurrentNode->ptrLast = ptrTail;
			ptrTail->ptrNext = ptrCurrentNode;
			ptrTail = ptrCurrentNode;
			numel++;
		}
	}
	
	void PushFront(T a)
	{
		if(ptrHead == NULL)
		{
			dblNode<T>* ptrCurrentNode = new dblNode<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = NULL;
			ptrCurrentNode->ptrLast = NULL;
			ptrHead = ptrCurrentNode;
			ptrTail = ptrCurrentNode;
			ptrCurrent = ptrCurrentNode;
			numel++;
		}
		else
		{
			dblNode<T>* ptrCurrentNode = new dblNode<T>;
			ptrCurrentNode->member = a;
			ptrCurrentNode->ptrNext = ptrHead;
			ptrCurrentNode->ptrLast = NULL;
			ptrCurrentNode->ptrNext->ptrLast = ptrCurrentNode;
			ptrHead = ptrCurrentNode;
			numel++;
		}
	}
	
	void Append(const dblList &L)
	{
		if(L.ptrHead != NULL)
		{
			dblNode<T>* ptrTempL = L.ptrHead;
			if(ptrHead == NULL)
			{
				PushFront(ptrTempL->member);
				ptrTempL = ptrTempL->ptrNext;
			}
			dblNode<T>* ptrTemp = ptrTail;
			while(ptrTempL != NULL)
			{
				dblNode<T>* ptrCurrentNode = new dblNode<T>;
				ptrTemp->ptrNext = ptrCurrentNode;
				ptrCurrentNode->member = ptrTempL->member;
				ptrCurrentNode->ptrLast = ptrTemp;
				ptrTemp = ptrTemp->ptrNext;
				ptrTempL = ptrTempL->ptrNext;
				numel++;
			}
			ptrTail = ptrTemp;
			ptrTail->ptrNext = NULL;
		}
	}
	
	void DeleteFirst()
	{
		if(ptrHead != NULL)
		{
			if(ptrHead->ptrNext == NULL)
			{
				delete ptrHead;
				ptrHead = NULL;
				ptrCurrent = NULL;
				ptrTail = NULL;
				numel--;
			}
			else
			{
				dblNode<T>* ptrTemp = ptrHead->ptrNext;
				if(ptrCurrent == ptrHead)
					ptrCurrent = ptrTemp;
				delete ptrHead;
				ptrHead = ptrTemp;
				ptrHead->ptrLast = NULL;
				numel--;
			}
		}
	}
	
	void DeleteLast()
	{
		if(ptrHead != NULL)
		{
			if(ptrHead->ptrNext == NULL)
			{
				delete ptrHead;
				ptrHead = NULL;
				ptrCurrent = NULL;
				ptrTail = NULL;
				numel--;
			}
			else
			{
				dblNode<T>* ptrTemp = ptrHead;
				while(ptrTemp->ptrNext != ptrTail)
					ptrTemp = ptrTemp->ptrNext;
				ptrTemp->ptrNext = NULL;
				delete ptrTail;
				ptrTail = ptrTemp;
				numel--;
			}
		}
	}
	
	void DeleteCurrent()
	{
		if(ptrCurrent == ptrHead)
			DeleteFirst();
		else if(ptrCurrent == ptrTail)
			DeleteLast();
		else
		{
			ptrCurrent->ptrLast->ptrNext = ptrCurrent->ptrNext;
			ptrCurrent->ptrNext->ptrLast = ptrCurrent->ptrLast;
			dblNode<T>* ptrTemp = ptrCurrent->ptrNext;
			delete ptrCurrent;
			ptrCurrent = ptrTemp;
			numel--;
		}
	}
	
	void Delete(int a)
	{
		if(a < 1 || a > numel)
			void();
		else if(ptrHead != NULL)
		{
			if(a == 1)
				DeleteFirst();
			else if(a == numel)
				DeleteLast();
			else
			{
				ptrCurrent = ptrHead;
				for(int i=2; i<a; i++)
					ptrCurrent = ptrCurrent->ptrNext;
				dblNode<T>* ptrTemp = ptrCurrent->ptrNext->ptrNext;
				delete ptrCurrent->ptrNext;
				ptrCurrent->ptrNext = ptrTemp;
				ptrCurrent->ptrNext->ptrLast = ptrCurrent;
				numel--;
			}
		}
	}
	
	T GetFirst()
	{
		return ptrHead->member;
	}
	
	T GetLast()
	{
		return ptrTail->member;
	}
	
	T GetCurrent()
	{
		return ptrCurrent->member;
	}

	T GetNext()
	{
		if(ptrCurrent->ptrNext != NULL)
			return ptrCurrent->ptrNext->member;
		else
			return T(NULL);
	}
	
	T GetPrevious()
	{
		if(ptrCurrent == ptrHead)
			return T(NULL);
		else
			ptrCurrent->ptrLast->member;
	}
	
	T Get(int a)
	{
		if(a < 0 || a> numel)
			return T(NULL);	
		dblNode<T>* ptrTemp = ptrHead;
		for(int i=1; i<a; i++)
			ptrTemp = ptrTemp->ptrNext;
		return ptrTemp->member;
	}
	
	bool EndofList()
	{
		if(ptrCurrent == NULL)
			return true;
		else
			return false;
	}
	
	list<T> MakeSingle()
	{
		list<T> singleList;
		dblNode<T>* ptrTemp = ptrHead;
		while(ptrTemp != NULL)
		{
			singleList.PushBack(ptrTemp->member);
			ptrTemp = ptrTemp->ptrNext;
		}
		return singleList;
	}
	
	void Reset()
	{
		ptrCurrent = ptrHead;
	}
	
	void StepForward()
	{
		ptrCurrent = ptrCurrent->ptrNext;
	}
	
	void StepBack()
	{
		ptrCurrent = ptrCurrent->ptrLast;
	}
	
	void StepToLast()
	{
		ptrCurrent = ptrTail;
	}
	
	int Numel()
	{
		return numel;
	}

	void PrintList()
	{
		dblNode<T>* temp = ptrHead;
		while(temp != NULL)
		{
			std::cout << temp->member << std::endl;
			temp = temp->ptrNext;
		}
	}
	
	void PrintListBackwards()
	{
		dblNode<T>* temp = ptrTail;
		while(temp != NULL)
		{
			std::cout << temp->member << std::endl;
			temp = temp->ptrLast;
		}
	}
};