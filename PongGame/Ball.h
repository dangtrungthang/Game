#pragma once
#include "GameObject.h"
#include"define.h"
#define BALL_SPEED 2.0f
class Ball :public CGameObject {
	
public:
	
	int dx, dy;
	RECT rect;
	Ball(LPCWSTR texturePath) :CGameObject(texturePath) {};
	void Reset() {
		this->x =SCREEN_HEIGHT/2;
		this->y = SCREEN_HEIGHT/2-10; // -10 offset
	}
	void Update(DWORD dt);
	void SetVxVy(int vx,int vy) { this->vx = vx; this->vy = vy; }
};
