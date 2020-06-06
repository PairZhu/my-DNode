#include<iostream>
#include"doubly_list.h"
using namespace std;
int main()
{
	doubly_list<int> a={2,1,3,1,2,4};//支持用列表初始化
	a.push_back(1);//(2),1,3,1,2,4,1
	a.push_front(7);//7,(2),1,3,1,2,4,1
	a.insert(10,a.find(3));//7,(2),1,10,3,1,2,4,1
	//back和forward移动内部指针指向的节点，默认步长为1
	a.erase(a.back().get());//(7),2,1,10,3,1,2,4,1  ->  (2),1,10,3,1,2,4,1
	a.forward(2).get_v() = 99;//2,1,(99),3,1,2,4,1
	while(auto q=a.find(1))//2,99,3,2,4
		a.erase(q);
	a.sort();//默认从小到大，全部排序
	a.sort([](int &a, int &b) {return a > b; });//传入谓词代替“<”进行比较,实现从大到小
	node<int>* temp = a.find(99);
	temp->v() = 101;//第二种修改值的方法
	*temp = 102;//第三种修改值的方法
	//遍历元素的方法，locate使内部指针指向对应的节点，get返回内部指针指向的节点
	for (a.locate(a.begin()); a.get() != a.end(); a.forward())
		cout << a.get_v() << " ";
	cout << endl;
	doubly_list<string> b(string("hello"));//创建链表时必须给一个值用于初始化，不允许创建长度为0的链表
	//下面两个语句会引发异常：禁止令链表长度为0
	//b.pop_back();
	//b.pop_front();
	b.push_back("ab");
	b.push_back("abcdefg");
	b.push_back("c++好难QAQ");
	b.push_front("e");
	b.pop_back();
	b.pop_front();
	b.sort([](string a, string b) {return a.length() > b.length(); }, b.begin(), b.forward(3).get());//在一定范围内排序
	doubly_list<string> c{ "Creeper?","Aw_man","So_we_back_in_the_mine" };
	b.connect(c);//将c连接到b的末尾，随后c会被销毁，禁止再使用c
	doubly_list<string> d{ "啊♂","乖乖","站好" };
	b.connect(d, b.find("Creeper?"));//将d连接到b中第二个参数所指向的的位置的前方，随后d会被销毁，禁止再使用d
	//(只插入d的某部分的重载要考虑的情况太多，我懒得写了。。。)
	b.sort([](const string& a,const string& b) {return a.length() > b.length(); });
	for (b.locate(b.begin()); b.get() != b.end(); b.forward())
		cout << b.get_v() << " ";
	cout << endl;
	return 0;
}