#pragma once
#include<Windows.h>
#include<string>
class Hub
{
	int scorePlayer1=0;
	int scorePlayer2 = 0;
	RECT boundBox = {GetSystemMetrics(SM_CXSCREEN)/2-200,100,GetSystemMetrics(SM_CXSCREEN) / 2+400,100+300};
public:
	void AddScorePlayer1() {
		this->scorePlayer1++;
	}
	void AddScorePlayer2() {
		this->scorePlayer2++;
	}
	void Update();
	void Render();
	Hub();
	~Hub();
};

