#include"speechManager.h"
#include<algorithm>
#include<ctime>
#include<deque>
#include<numeric>
#include<fstream>
SpeechManager::SpeechManager() {
	this->initSpeech();//��ʼ������
	this->createSpeaker();//����ѡ��
	this->loadRecord();
}
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "************* ��ӭ�μ��ݽ����� ************" << endl;
	cout << "************* 1.��ʼ�ݽ����� *************" << endl;
	cout << "************* 2.�鿴�����¼ *************" << endl;
	cout << "************* 3.��ձ�����¼ *************" << endl;
	cout << "************* 0.�˳��������� *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//������ֹ��������
}
void SpeechManager::initSpeech() {
	this->v1.clear();//������֤Ϊ�գ���
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;//��ʼ����������
	this->m_Record.clear();//��ʼ����¼����
}
void SpeechManager::createSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++) {
		string name = "ѡ��";
		name += nameseed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_score[i] = 0;//����0ռλ
		}
		this->v1.push_back(i + 10001);//ѡ�ֱ��
		this->m_Speaker.insert(make_pair(i + 10001, sp));//�������ѡ�ַ���map��
	}
}
void SpeechManager::startSpeech() {
	speechDraw();
	speechContest();
	showScore();
	this->m_Index++;
	speechDraw();
	speechContest();
	showScore();
	saveRecord();//���ñ���
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw() {
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::speechContest() {
	cout << "------------- ��" << this->m_Index << "����ʽ������ʼ��------------- "<< endl;
	multimap<double, int, greater<int>> groupScore;//��ʱ����������key����value���
	int num = 0;
	vector<int>v_src;//��������Ա����
	if (this->m_Index == 1) {
		v_src = v1;
	}
	else {
		v_src = v2;
	}
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++) {
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600-1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->m_Speaker[*it].m_score[this->m_Index - 1] = avg;//cout << "��ţ� " << *it << " ѡ�֣� " << this->m_Speaker[*it].m_Name <<" ��ȡƽ����Ϊ�� " << avg << endl; //��ӡ����
		groupScore.insert(make_pair(avg, *it));//6��һ�飬��ʱ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it =
				groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second << " ������ " << this->m_Speaker[it->second].m_Name << " �ɼ��� " << this->m_Speaker[it->second].m_score[this->m_Index - 1] << endl;
			}
			int count = 0;
			//ȡǰ����
			for (multimap<double, int, greater<int>>::iterator it =
				groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					victory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------- ��" << this->m_Index << "�ֱ������ ------------- " <<
		endl;
	system("pause");
}
void SpeechManager::showScore() {
	cout << "---------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-----------" <<
		endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << m_Speaker[*it].m_Name << " �÷֣� " << m_Speaker[*it].m_score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++) {
		ofs << *it << ","
			<< m_Speaker[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ü�¼�ѱ���" << endl;
	this->fileIsEmpty = false;
}
void SpeechManager::loadRecord() {//û����TAT����������
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "���ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);//��0��ʼ����
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start); //�ҵ���,���зָ� ����1 ��ʼλ�ã�����2 ��ȡ����
				v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}