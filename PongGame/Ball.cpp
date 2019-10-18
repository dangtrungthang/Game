#include "Ball.h"
void Ball::Update(DWORD dt) {
	//move the ball sprite
	x += vx;
	y += vy;

	//bounce the ball at screen edges

	if (y > GetSystemMetrics(SM_CYSCREEN) - height)
	{
		y -= height;
		vy *= -1;
	}
	else if (y < 0)
	{
		y += height;
		vy *= -1;
	}
	if (x > GetSystemMetrics(SM_CXSCREEN) - width) {
		x -= width;
		vx *= -1;
	}
	else if (x < 0) {
		x = 500; y = 500;
	}
	
	rect.left = x;
	rect.top = y;
	rect.right = 40;
	rect.bottom = 40;
	
}

