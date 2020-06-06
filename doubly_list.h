#pragma once
#include<iostream>
using namespace std;
template <typename T> class node //单个节点的类型
{
	template<typename> friend class doubly_list;
private:
	T value=T();
	node<T>* next = nullptr;
	node<T>* last = nullptr;
	node(const T& _value) :value(_value) {};
	node() = default;
	void swap(node<T>& a); //通过交换指针的指向来实现节点位置的交换（a一定严格在*this后面）
public:
	operator T&(){ return v(); }//允许node<T>对象默认转换为T的引用，值为value
	node<T>& operator =(const T& _value) { value = _value; return *this; }//允许用T直接给node<T>对象赋值，赋值给value
	//允许node<T>和T对象进行比较
	bool operator ==(const T& _value) { return value == _value;}
	bool operator !=(const T& _value) { return value != _value; }
	bool operator >(const T& _value) { return value > _value; }
	bool operator <(const T& _value) { return value < _value; }
	bool operator >=(const T& _value) { return value >= _value; }
	bool operator <=(const T& _value) { return value <= _value; }
	//node<T>对象进行比较等价于比较value的值
	bool operator ==(const node<T>& a) { return value == a._value; }
	bool operator !=(const node<T>& a) { return value != a._value; }
	bool operator >(const node<T>& a) { return value > a._value; }
	bool operator <(const node<T>& a) { return value < a._value; }
	bool operator >=(const node<T>& a) { return value >= a._value; }
	bool operator <=(const node<T>& a) { return value <= a._value; }
	//返回value的引用
	T& v()
	{
		if (!(next))//如果下一个位置为空指针则说明是尾后位置
			throw out_of_range("禁止操作尾后位置");
		return value;
	}
};
template<typename T>
void node<T>::swap(node<T>& a)
{
	if (next == &a)
	{
		if (last)//last非空，即*this非头节点
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
	node<T>* head;//保存链表的头部
	node<T>* end_node;//保存链表的尾后位置
	node<T>* pointer;//链表的内部指针，指向链表内的节点
	size_t length;//保存链表的节点数(尾后节点不计在内)
public:
	doubly_list(const T& _value) :doubly_list({_value}) {}
	doubly_list(const initializer_list<T>);//列表初始化
	~doubly_list();//析构函数，在次类对象被销毁时归还申请的空间
	node<T>* insert(const T&, node<T>* q);//返回指向增加的位置的指针
	node<T>* insert(const T& _value) { return insert(_value, pointer); }//在内置pointer指向的位置前插入节点
	node<T>* erase(node<T>* q);//返回q后位置的指针,若删除的位置与内置pointer重合则pointer后移一步
	node<T>* erase() { return erase(pointer); }//删除内置pointer指向的位置
	node<T>* push_back(const T& _value) { return insert(_value, end_node); }
	node<T>* push_front(const T& _value) { return insert(_value, head); }
	node<T>* pop_back() { return erase(end_node->last); }
	node<T>* pop_front() { return erase(head); }
	node<T>* find (const T&) const;
	node<T>* begin() const { return head; }//返回链表头节点
	node<T>* end() const { return end_node; }//返回链表尾后节点
	node<T>* get() const { return pointer; }//获取内置pointer指向的位置
	T& get_v() const { return pointer->v(); }//获取内置pointer指向的位置的值的引用
	//将内置pointer指向q的位置
	doubly_list<T>& locate(node<T> * q) 
	{ 
		if (!q)
			throw out_of_range("指针为空");
		pointer = q;
		return *this;
	}
	//使内置pointer前进step步，默认步长为1，若步长超过pointer后面的节点数则停留在尾后节点处
	doubly_list<T>& forward(size_t step = 1);
	//同理，使内置pointer后退
	doubly_list<T>& back(size_t step = 1);
	//将内部所有节点从小到大排序，会影响pointer的位置(poniter仍指向原节点所在的位置)
	void sort() { sort([](const T& a, const T& b) {return a < b; }); }
	//将first和last形成的左闭右开的区间内的节点排序
	void sort(node<T>* first, node<T>* last) { sort([](const T& a, const T& b) {return a < b; }, first, last); }
	//接收一个谓词代替小于号进行比较的排序
	template <typename U>
	void sort(U compare) { sort(compare, head, end_node); };
	//综合了前两种排序
	template <typename U> 
	void sort(U compare, node<T>* first, node<T>* last);
	//将传入的双向链表对象连接到*this的尾部，传入的双向链表禁止再次使用
	void connect(doubly_list<T>&);
	//将传入的双向链表对象连接到第二个参数指向的位置之前，传入的双向链表禁止再次使用
	void connect(doubly_list<T>&,node<T>*);
	//返回链表的节点数
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
		throw runtime_error("初始化列表禁止为空");
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
		throw out_of_range("指针为空");
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
		throw out_of_range("指针为空");
	if (q == end_node)
		throw out_of_range("禁止操作尾后位置");
	if (q == pointer)
		pointer = q->next;
	if (q == head)
	{
		if(length==1)
			throw out_of_range("链表禁止为空");
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