#include<iostream>
//��git������ô�ð�������
using namespace std;
#include<ctime>
#include"speechManager.h"
int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;//�Ͼ�SpeechMenuһ���࣬�º�������˵�ȷ��һ������
	sm.show_Menu();
	int choice = 0;
	while (true) {
		sm.show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");//��������Ҫ����default
			break;
		}
	}
	system("pause");
	return 0;
}