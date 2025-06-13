#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
using namespace std;
class SpeechManager {
public:
	SpeechManager();
	void show_Menu();
	void exitSystem();
	void initSpeech();//初始化函数
	void createSpeaker();//初始化创建12名选手
	void startSpeech();
	void speechDraw();
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	void showRecord();
	void clearRecord();
	bool fileIsEmpty;
	map<int, vector<string>>m_Record;
	~SpeechManager();
	vector<int>v1;
	vector<int>v2;
	vector<int>victory;
	map<int, Speaker>m_Speaker;
	int m_Index = 1;
};
