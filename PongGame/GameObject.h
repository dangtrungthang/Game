#pragma once

#include <Windows.h>
#include <d3dx9.h>
#define MOVE_UP_KEYBOARD 10
#define MOVE_DOWN_KEYBOARD 20
#define MOVE_UP_MOUSE 15
#define MOVE_DOWN_MOUSE 30
#define IDLE 0

#define ZERO L"0.png"
#define ONE L"1.png"
#define TWO L"2.png"
#define THREE L"3.png"
#define FOUR L"4.png"
#define FIVE L"5.png"
#define SIX L"6.png"
#define SEVEN L"7.png"
#define EIGHT L"8.png"
#define NINE L"9.png"
enum class NORMAL_DIRECTION {
	LEFT = 0,
	RIGHT = 1,
	TOP=2,
	BOTTOM=3
};
class CGameObject
{
protected: 
	
	float t;

	
	int state;
	
	LPDIRECT3DTEXTURE9 texture;		
	D3DXIMAGE_INFO infoSquare;
public: 
	
	float x;
	float y;

	float width;
	float height;

	float vx;
	float vy;

	NORMAL_DIRECTION direction;



	RECT rect;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetState(int state) { this->state = state; }

	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	void OnCollision(NORMAL_DIRECTION);
	float SweptAABB(CGameObject* b1, CGameObject* b2, float& normalx, float& normaly);
	int GetState() { return this->state; }
	D3DXIMAGE_INFO GetInfo() { return this->infoSquare; }
	CGameObject(LPCWSTR texturePath);
	void LoadTex(LPCWSTR texturePath);
	void Update(DWORD dt);
	void Render();
	~CGameObject();
};

//class Score
//	:public CGameObject
//{
//	int score = 0;
//	LPCWSTR tex;
//public:
//	void SetScore(int a) { this->score = a; }
//	void SetTexPath(LPCWSTR tex);
//	
//	Score(LPCWSTR texturePath) :CGameObject(texturePath) {};
//};

