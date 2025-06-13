#include<iostream>
#include<vector>
#include<ctime>
#include<map>
#include<ctime>
using namespace std;
#define CeHua 0
#define MeiShu 1
#define YanFa 2
class Person {
public:
	Person(string name, int salary) {
		this->m_name = name;
		this->m_salary = salary;
	}
	string m_name;
	int m_salary;
};
void createPerson(vector<Person>& v) {
	string nameseed = "ABCDENFGHIJ";
	for (int i = 0; i < 10; i++) {
		string name = "Ա��";
		name += nameseed[i];
		int salary = rand() % 10000 + 10000;
		Person p(name, salary);
		v.push_back(p);
	}
}
void setGroup(vector<Person>& v, multimap<int, Person>&m) {
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		int deptID = rand() % 3;
		m.insert(make_pair(deptID, *it));
	}
}
void show(multimap<int, Person>& m) {
	cout << "�߻����ţ� " << endl;
	//��posָ���һ����ַ��count���ظ���������ֱ�ӱȽ�pos1��pos2��pos����int����
	multimap<int, Person>::iterator pos = m.find(CeHua);
	int count = m.count(CeHua);
	int index = 0;
	for (; pos!=m.end() && index<count; pos++,index++) {
		cout << "������ " << pos->second.m_name << "���ʣ� " << pos->second.m_salary << endl;
	}
	cout << "�������ţ� " << endl;
	pos = m.find(MeiShu);
	count = m.count(MeiShu);
	index = 0;
	for (; pos != m.end() && index < count; pos++, index++) {
		cout << "������ " << pos->second.m_name << "���ʣ� " << pos->second.m_salary << endl;
	}
	cout << "�з����ţ� " << endl;
	pos = m.find(YanFa);
	count = m.count(YanFa);
	index = 0;
	for (; pos != m.end() && index < count; pos++,index++) {
		cout << "������ " << pos->second.m_name << "���ʣ� " << pos->second.m_salary << endl;
	}
}
int main() {
	srand((unsigned int) time(NULL));
	vector<Person>v;
	createPerson(v);
	multimap<int, Person>m;
	setGroup(v, m);
	show(m);
	return 0;
}