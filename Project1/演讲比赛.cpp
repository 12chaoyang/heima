#include<iostream>
//死git到底怎么用啊！！！
using namespace std;
#include<ctime>
#include"speechManager.h"
int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;//毕竟SpeechMenu一个类，仿函数，因此得确定一变量名
	sm.show_Menu();
	int choice = 0;
	while (true) {
		sm.show_Menu();
		cout << "请输入您的选择" << endl;
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
			system("cls");//清屏，不要忘记default
			break;
		}
	}
	system("pause");
	return 0;
}