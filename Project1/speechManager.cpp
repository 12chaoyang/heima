#include"speechManager.h"
#include<algorithm>
#include<ctime>
#include<deque>
#include<numeric>
#include<fstream>
SpeechManager::SpeechManager() {
	this->initSpeech();//初始化属性
	this->createSpeaker();//创建选手
	this->loadRecord();
}
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "************* 欢迎参加演讲比赛 ************" << endl;
	cout << "************* 1.开始演讲比赛 *************" << endl;
	cout << "************* 2.查看往届记录 *************" << endl;
	cout << "************* 3.清空比赛记录 *************" << endl;
	cout << "************* 0.退出比赛程序 *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//用于终止程序运行
}
void SpeechManager::initSpeech() {
	this->v1.clear();//容器保证为空？？
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;//初始化比赛轮数
	this->m_Record.clear();//初始化记录容器
}
void SpeechManager::createSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++) {
		string name = "选手";
		name += nameseed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_score[i] = 0;//先以0占位
		}
		this->v1.push_back(i + 10001);//选手编号
		this->m_Speaker.insert(make_pair(i + 10001, sp));//将编号与选手放在map中
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
	saveRecord();//重置比赛
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw() {
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
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
	cout << "------------- 第" << this->m_Index << "轮正式比赛开始：------------- "<< endl;
	multimap<double, int, greater<int>> groupScore;//临时容器，保存key分数value编号
	int num = 0;
	vector<int>v_src;//比赛的人员容器
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
		this->m_Speaker[*it].m_score[this->m_Index - 1] = avg;//cout << "编号： " << *it << " 选手： " << this->m_Speaker[*it].m_Name <<" 获取平均分为： " << avg << endl; //打印分数
		groupScore.insert(make_pair(avg, *it));//6人一组，临时容器
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it =
				groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second << " 姓名： " << this->m_Speaker[it->second].m_Name << " 成绩： " << this->m_Speaker[it->second].m_score[this->m_Index - 1] << endl;
			}
			int count = 0;
			//取前三名
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
	cout << "------------- 第" << this->m_Index << "轮比赛完毕 ------------- " <<
		endl;
	system("pause");
}
void SpeechManager::showScore() {
	cout << "---------第" << this->m_Index << "轮晋级选手信息如下：-----------" <<
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
		cout << "选手编号：" << *it << " 姓名： " << m_Speaker[*it].m_Name << " 得分： " << m_Speaker[*it].m_score[this->m_Index - 1] << endl;
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
	cout << "该记录已保存" << endl;
	this->fileIsEmpty = false;
}
void SpeechManager::loadRecord() {//没读懂TAT？？？？？
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "该文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
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
			pos = data.find(",", start);//从0开始查找
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start); //找到了,进行分割 参数1 起始位置，参数2 截取长度
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
		cout << "文件不存在，或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}