#pragma once
#include "GameObject.h"


#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define PADDLE_KEYBOARD_SPEED 1.0f
#define PADDLE_MOUSE_SPEED 0.1f

class Paddle :public CGameObject {

public:
	Paddle(LPCWSTR texturePath) :CGameObject(texturePath) {};
	void Update(DWORD dt);
	void UpdateR(DWORD dt,int xs,int ys);
	void SetDxDy(int vx, int dy) { this->vx = vx; this->vy = vy; }

};
