
#include <iostream>

using namespace std;



template <class T>                         // ����� ����
class Node
{
protected:
	T value;                              // �������� ����
	Node* next;                           // ����� ���������� ����
	Node* prev;                           // ����� ����������� ����
public:

	// ����������� ������������
	Node(T _value)
	{
		value = _value;
		next = 0;
		prev = 0;
	}
	//����������
	~Node()
	{
		next = 0;
		prev = 0;
	}


	T GetData()     { return value; }
	Node* GetNext() { return next; }
	Node* GetPrev() { return prev; }

	void SetValue(T _value) { value = _value; }
	void SetNext(Node* _next) { next = _next; }
	void SetPrev(Node* _prev) { prev = _prev; }

	//�������� ������
	ostream& operator<<(ostream& ostr, const Node<T1>& A)
	{
		ostr << A.value;
		return ostr;
	}
	//�������� �����
	istream& operator >> (istream& istr, Node<T1>& A)
	{
		istr >> A.value;
		return istr;
	}
	//������������� ����� ������
	template<class T1>
	friend class TList;
};

// ����� ���������
template<class T2>
class TListIterator
{
protected:

	TList<T2>&     link;
	TListNode<T2>* current;

public:

	// ����������� ������������
	TListIterator(TList<T2>& _list, Node<T2>* _c) : link(_list), current(_c) {}
	// ����������� �����������
	TListIterator(TListIterator<T2>& _v) : link(_v.link), current(_v.current) {}
	// ����������
	~TListIterator();

	CanGoFwd() { return (current->GetNext() != nullptr); }
	CanGoBck() { return (current->GetPrev() != nullptr); }

	// ����� ������������ ����� �� ������
	GoFwd()
	{
		if (!CanGoFwd())
			throw - 1;
		current = current->GetNext();
	}
	// ������������ ����� �� ������
	GoBck()
	{
		if (!CanGoBck())
			throw - 1;
		current = current->GetPrev();
	}

	// �������� ��������� ����������
	bool operator==(const TListIterator<T2>& _v){return (current == _v.current);}
	
	// ��������� ������������ 
	TListIterator<T2> operator=(const TListIterator<T2>& _v)
	{
		link = _v.link;
		current = _v.current;
	}

	// �����, ������������ �������� �������� �����
	T2 GetValue()
	{
			if (current == nullptr)
				throw - 1;
			return current->GetData();
	};
	
};

template <class T>
class TList
{
protected:
	//����� ������ ������
	Node<T>* root;
	// ����� ����� ������
	Node<T>* end;
	int count;
public:
	
	// ����������� �� ���������
	TList()
	{
		root = 0;
		end = 0;
		count = 0;
	}
	//����������� �����������
	TList(TList<T>& _v)
	{
		root = nullptr;
		count = _v.count;
		Node<T>* i = _v.root;
		Node<T>* j = this->root;
		Node<T>* p = 0;

		while (i != 0)
		{
			j = new Node<T>(*i);
			j->SetNext(0);
			if (p != 0)
			{
				p->SetNext(j);
				j->SetPrev(p);
			}

			p = j;

			if (root == nullptr)
				root = j;

			end = j;
			i = i->next;
		}
	}
	//����������
	~TList()
	{
		if (this->root != 0)
		{
			TListElem<T>* i = this->root;
			TListElem<T>* p = 0;

			while (i != 0)
			{
				p = i;
				i = i->GetNext();
				delete p;
			}

			this->root = 0;
			this->end = 0;
			count = 0;
		}
	}

	// �������� ��������� ���� �������
	TList<T>& operator =(TList<T>& _v);

	//�����, ������������ ������ ������
	Begin() { return TListIterator<T>(*this, root); }
	//�����, ������������ ����� ������
	End(){ return TListIterator<T>(*this, end); }
	//������� � ������ ������
	InsFirst(T d)
	{
		Node<T>* tmp = new Node<T>(d);
		tmp->SetNext(root);
		root = tmp;
		if (end == 0)
			end = tmp;
		count++;
	}
	//����� ������� � ����� ������
	InsLast(T d)
	{
		if (IsEmpty())
			InsFirst(d);
		else
		{
			Node<T>* tmp = new Node<T>(d);
			if (end != 0)
				end->SetNext(tmp);
			tmp->SetPrev(end);
			tmp->SetNext(0);
			end = tmp;
			count++;
		}
	}
	//����� ������� � ������������ ����� ������
	Ins(Node<T>* e, T d)
	{
		Node<T>* tmp = new Node<T>(d);
		tmp->SetNext(e->GetNext());
		tmp->SetPrev(e);
		e->GetNext()->SetPrev(tmp);
		e->SetNext(tmp);
		count++;
	}

	// �����, ������������ ������ ������� ������
	Node<T>* GetFirst()
	{
		if ((*this).IsEmpty())
			throw logic_error("empty_list");
		return root;
	}
	// �����, ������������ ��������� ������� ������
	Node<T>* GetLast()
	{
		if ((*this).IsEmpty())
			throw logic_error("empty_list");
		return end;
	}
	//
	IsEmpty(void) const { return count == 0; }
	// ����� �������� ������� �������� �� ������
	DelFirst()
	{
		if (root == 0) throw logic_error("invalid argument");
		Node<T>* i = root;
		root = root->GetNext();
		delete i;
		count--;
	}
	// ����� �������� ���������� �������� �� ������
	DelLast()
	{
		if ((*this).IsEmpty())
			throw logic_error("empty list");

		Node<T>* j = root;

		if (j->GetNext() != 0)
		{
			while (j->GetNext()->GetNext() != 0)
				j = j->GetNext();

			delete j->GetNext();
			j->SetNext(0);
			return;
		}

		delete j;
		root = 0;
	}
	// ������ �������� �������� �� ������������� ����� �� ������ 
	Del(Node<T>* e)
	{
		e->GetPrev()->SetNext(e->GetNext());
		e->GetNext()->SetPrev(e->GetPrev());
		count--;
		delete e;
	}
	//�������� ������ ������
	ostream& operator<< (ostream& ostr, const TList<T1>& A)
	{
		Node<T1>* i = A.root;

		while (i != 0)
		{
			ostr << *i << endl;
			i = i->GetNext();
		}
		return ostr;
	}
	//������� ����� ������
	istream& operator >> (istream& istr, TList<T1>& A) {
		int count;
		istr >> count;
		for (int i = 0; i < count; i++)
		{
			T1 d;
			istr >> d;
			A.InsLast(d);
		}
		return istr;
	}

	// ����� , ������������ ���-�� ���������
	int GetCount() { return count; }

	// �������� ������������ �������
	TList<T>& operator =(TList<T>& _v)
	{
		if (this == &_v)
			return *this;

		if (this->root != 0)
		{
			Node<T>* i = this->root;
			Node<T>* p = 0;

			while (i != 0)
			{
				p = i;
				i = i->GetNext();
				delete p;
			}

			this->root = 0;
			this->end = 0;
			count = 0;
		}

		root = nullptr;
		count = _v.count;

		Node<T>* i = _v.root;
		Node<T>* j = this->root;
		Node<T>* p = 0;

		while (i != 0)
		{
			j = new TListElem<T>(*i);
			j->SetNext(0);
			if (p != 0)
			{
				p->SetNext(j);
				j->SetPrev(p);
			}

			p = j;

			if (root == nullptr)
				root = j;

			end = j;

			i = i->next;
		}

	}
};



