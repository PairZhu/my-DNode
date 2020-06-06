#include<iostream>
#include"doubly_list.h"
using namespace std;
int main()
{
	doubly_list<int> a={2,1,3,1,2,4};//֧�����б��ʼ��
	a.push_back(1);//(2),1,3,1,2,4,1
	a.push_front(7);//7,(2),1,3,1,2,4,1
	a.insert(10,a.find(3));//7,(2),1,10,3,1,2,4,1
	//back��forward�ƶ��ڲ�ָ��ָ��Ľڵ㣬Ĭ�ϲ���Ϊ1
	a.erase(a.back().get());//(7),2,1,10,3,1,2,4,1  ->  (2),1,10,3,1,2,4,1
	a.forward(2).get_v() = 99;//2,1,(99),3,1,2,4,1
	while(auto q=a.find(1))//2,99,3,2,4
		a.erase(q);
	a.sort();//Ĭ�ϴ�С����ȫ������
	a.sort([](int &a, int &b) {return a > b; });//����ν�ʴ��桰<�����бȽ�,ʵ�ִӴ�С
	node<int>* temp = a.find(99);
	temp->v() = 101;//�ڶ����޸�ֵ�ķ���
	*temp = 102;//�������޸�ֵ�ķ���
	//����Ԫ�صķ�����locateʹ�ڲ�ָ��ָ���Ӧ�Ľڵ㣬get�����ڲ�ָ��ָ��Ľڵ�
	for (a.locate(a.begin()); a.get() != a.end(); a.forward())
		cout << a.get_v() << " ";
	cout << endl;
	doubly_list<string> b(string("hello"));//��������ʱ�����һ��ֵ���ڳ�ʼ����������������Ϊ0������
	//�����������������쳣����ֹ��������Ϊ0
	//b.pop_back();
	//b.pop_front();
	b.push_back("ab");
	b.push_back("abcdefg");
	b.push_back("c++����QAQ");
	b.push_front("e");
	b.pop_back();
	b.pop_front();
	b.sort([](string a, string b) {return a.length() > b.length(); }, b.begin(), b.forward(3).get());//��һ����Χ������
	doubly_list<string> c{ "Creeper?","Aw_man","So_we_back_in_the_mine" };
	b.connect(c);//��c���ӵ�b��ĩβ�����c�ᱻ���٣���ֹ��ʹ��c
	doubly_list<string> d{ "����","�Թ�","վ��" };
	b.connect(d, b.find("Creeper?"));//��d���ӵ�b�еڶ���������ָ��ĵ�λ�õ�ǰ�������d�ᱻ���٣���ֹ��ʹ��d
	//(ֻ����d��ĳ���ֵ�����Ҫ���ǵ����̫�࣬������д�ˡ�����)
	b.sort([](const string& a,const string& b) {return a.length() > b.length(); });
	for (b.locate(b.begin()); b.get() != b.end(); b.forward())
		cout << b.get_v() << " ";
	cout << endl;
	return 0;
}