#pragma once
#include<iostream>
using namespace std;
template <typename T> class node //�����ڵ������
{
	template<typename> friend class doubly_list;
private:
	T value=T();
	node<T>* next = nullptr;
	node<T>* last = nullptr;
	node(const T& _value) :value(_value) {};
	node() = default;
	void swap(node<T>& a); //ͨ������ָ���ָ����ʵ�ֽڵ�λ�õĽ�����aһ���ϸ���*this���棩
public:
	operator T&(){ return v(); }//����node<T>����Ĭ��ת��ΪT�����ã�ֵΪvalue
	node<T>& operator =(const T& _value) { value = _value; return *this; }//������Tֱ�Ӹ�node<T>����ֵ����ֵ��value
	//����node<T>��T������бȽ�
	bool operator ==(const T& _value) { return value == _value;}
	bool operator !=(const T& _value) { return value != _value; }
	bool operator >(const T& _value) { return value > _value; }
	bool operator <(const T& _value) { return value < _value; }
	bool operator >=(const T& _value) { return value >= _value; }
	bool operator <=(const T& _value) { return value <= _value; }
	//node<T>������бȽϵȼ��ڱȽ�value��ֵ
	bool operator ==(const node<T>& a) { return value == a._value; }
	bool operator !=(const node<T>& a) { return value != a._value; }
	bool operator >(const node<T>& a) { return value > a._value; }
	bool operator <(const node<T>& a) { return value < a._value; }
	bool operator >=(const node<T>& a) { return value >= a._value; }
	bool operator <=(const node<T>& a) { return value <= a._value; }
	//����value������
	T& v()
	{
		if (!(next))//�����һ��λ��Ϊ��ָ����˵����β��λ��
			throw out_of_range("��ֹ����β��λ��");
		return value;
	}
};
template<typename T>
void node<T>::swap(node<T>& a)
{
	if (next == &a)
	{
		if (last)//last�ǿգ���*this��ͷ�ڵ�
			last->next = &a;
		a.next->last = this;
		next = a.next;
		a.next = this;
		a.last = last;
		last = &a;
	}
	else
	{
		::swap(a.last, last);
		::swap(a.next, next);
		if(a.last)
			a.last->next = &a;
		a.next->last = &a;
		last->next = this;
		next->last = this;
	}
}
template <typename T> class doubly_list
{
private:
	node<T>* head;//���������ͷ��
	node<T>* end_node;//���������β��λ��
	node<T>* pointer;//������ڲ�ָ�룬ָ�������ڵĽڵ�
	size_t length;//��������Ľڵ���(β��ڵ㲻������)
public:
	doubly_list(const T& _value) :doubly_list({_value}) {}
	doubly_list(const initializer_list<T>);//�б��ʼ��
	~doubly_list();//�����������ڴ����������ʱ�黹����Ŀռ�
	node<T>* insert(const T&, node<T>* q);//����ָ�����ӵ�λ�õ�ָ��
	node<T>* insert(const T& _value) { return insert(_value, pointer); }//������pointerָ���λ��ǰ����ڵ�
	node<T>* erase(node<T>* q);//����q��λ�õ�ָ��,��ɾ����λ��������pointer�غ���pointer����һ��
	node<T>* erase() { return erase(pointer); }//ɾ������pointerָ���λ��
	node<T>* push_back(const T& _value) { return insert(_value, end_node); }
	node<T>* push_front(const T& _value) { return insert(_value, head); }
	node<T>* pop_back() { return erase(end_node->last); }
	node<T>* pop_front() { return erase(head); }
	node<T>* find (const T&) const;
	node<T>* begin() const { return head; }//��������ͷ�ڵ�
	node<T>* end() const { return end_node; }//��������β��ڵ�
	node<T>* get() const { return pointer; }//��ȡ����pointerָ���λ��
	T& get_v() const { return pointer->v(); }//��ȡ����pointerָ���λ�õ�ֵ������
	//������pointerָ��q��λ��
	doubly_list<T>& locate(node<T> * q) 
	{ 
		if (!q)
			throw out_of_range("ָ��Ϊ��");
		pointer = q;
		return *this;
	}
	//ʹ����pointerǰ��step����Ĭ�ϲ���Ϊ1������������pointer����Ľڵ�����ͣ����β��ڵ㴦
	doubly_list<T>& forward(size_t step = 1);
	//ͬ��ʹ����pointer����
	doubly_list<T>& back(size_t step = 1);
	//���ڲ����нڵ��С�������򣬻�Ӱ��pointer��λ��(poniter��ָ��ԭ�ڵ����ڵ�λ��)
	void sort() { sort([](const T& a, const T& b) {return a < b; }); }
	//��first��last�γɵ�����ҿ��������ڵĽڵ�����
	void sort(node<T>* first, node<T>* last) { sort([](const T& a, const T& b) {return a < b; }, first, last); }
	//����һ��ν�ʴ���С�ںŽ��бȽϵ�����
	template <typename U>
	void sort(U compare) { sort(compare, head, end_node); };
	//�ۺ���ǰ��������
	template <typename U> 
	void sort(U compare, node<T>* first, node<T>* last);
	//�������˫������������ӵ�*this��β���������˫�������ֹ�ٴ�ʹ��
	void connect(doubly_list<T>&);
	//�������˫������������ӵ��ڶ�������ָ���λ��֮ǰ�������˫�������ֹ�ٴ�ʹ��
	void connect(doubly_list<T>&,node<T>*);
	//��������Ľڵ���
	const size_t size()const { return length; }
};
template<typename T>
doubly_list<T>::~doubly_list()
{
	while (head != end_node)
	{
		head = head->next;
		delete head->last;
	}
	delete end_node;
}
template<typename T>
doubly_list<T>::doubly_list(const initializer_list<T> list)
{
	if (list.size() == 0)
		throw runtime_error("��ʼ���б��ֹΪ��");
	length = 1;
	head = new node<T>(*list.begin());
	pointer = head;
	end_node = new node<T>();
	head->next = end_node;
	end_node->last = head;
	for (auto i = list.begin() + 1; i != list.end(); ++i)
		push_back(*i);
}
template<typename T>
node<T>* doubly_list<T>::insert(const T& _value, node<T>* q)
{
	if (!q)
		throw out_of_range("ָ��Ϊ��");
	node<T>* p = new node<T>(_value);
	if (q == head)
		head = p;
	else
		q->last->next = p;
	p->last = q->last;
	p->next = q;
	q->last = p;
	++length;
	return p;
}
template<typename T>
node<T>* doubly_list<T>::erase(node<T>* q)
{
	if (!q)
		throw out_of_range("ָ��Ϊ��");
	if (q == end_node)
		throw out_of_range("��ֹ����β��λ��");
	if (q == pointer)
		pointer = q->next;
	if (q == head)
	{
		if(length==1)
			throw out_of_range("�����ֹΪ��");
		head = head->next;
		delete head->last;
		--length;
		return head;
	}
	q->last->next = q->next;
	q->next->last = q->last;
	node<T>* p = q->next;
	delete q;
	--length;
	return p;
}
template<typename T>
node<T>* doubly_list<T>::find(const T& target) const
{
	for (node<T>* p = head; p != end_node; p = p->next)
	{
		if (*p == target)
			return p;
	}
	return nullptr;
}
template<typename T>
doubly_list<T>& doubly_list<T>::forward(size_t step)
{
	for (; step ; --step)
	{
		if (pointer == end_node)
			break;
		pointer = pointer->next;
	}
	return *this;
}
template<typename T>
doubly_list<T>& doubly_list<T>::back(size_t step)
{
	for (; step; --step)
	{
		if (pointer == head)
			break;
		pointer = pointer->last;
	}
	return *this;
}
template<typename T> template<typename U>
void doubly_list<T>::sort( U compare , node<T>* first , node<T>* last)
{
	for (node<T>* p = first; p != last; p = p->next)
	{
		node<T>* min_pos = p;
		for (node<T>* q = p->next; q != last; q = q->next)
		{
			if (compare(*q, *min_pos))
				min_pos = q;
		}
		if (min_pos != p)
		{
			if (p == head)
				head = min_pos;
			p->swap(*min_pos);
			p = min_pos;
		}
	}
}
template<typename T>
void doubly_list<T>::connect(doubly_list<T>& a)
{
	end_node->last->next = a.head;
	a.head->last = end_node->last;
	delete end_node;
	end_node = a.end_node;
	length += a.length;
	a.head = new node<T>;
	a.end_node = a.head;
}
template<typename T>
void doubly_list<T>::connect(doubly_list<T>& a, node<T>* pos)
{
	pos->last->next = a.head;
	a.head->last = pos->last;
	pos->last = a.end_node->last;
	a.end_node->last->next = pos;
	a.head = a.end_node;
}