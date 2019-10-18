#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

#define center_X GetSystemMetrics(SM_CXSCREEN)/2;
#define center_Y GetSystemMetrics(SM_CYSCREEN)/2;

#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)


CGameObject::CGameObject(LPCWSTR texturePath)
{
	x = y = 0;
	t = 0;

	D3DXIMAGE_INFO info;
	
	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	infoSquare = info;
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n",texturePath);
		return;
	}

	width = info.Width;
	height = info.Height;

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
}

float CGameObject::SweptAABB(CGameObject* b1, CGameObject* b2, float& normalx, float& normaly) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1->vx > 0.0f)
	{
		xInvEntry = b2->x - (b1->x + b1->width);
		xInvExit = (b2->x + b2->width) - b1->x;
	}
	else
	{
		xInvEntry = (b2->x + b2->width) - b1->x;
		xInvExit = b2->x - (b1->x + b1->width);
	}

	if (b1->vy > 0.0f)
	{
		yInvEntry = b2->y - (b1->y + b1->height);
		yInvExit = (b2->y + b2->height) - b1->y;
	}
	else
	{
		yInvEntry = (b2->y + b2->height) - b1->y;
		yInvExit = b2->y - (b1->y + b1->height);
	}
	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1->vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1->vx;
		xExit = xInvExit / b1->vx;
	}

	if (b1->vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1->vy;
		yExit = yInvExit / b1->vy;
	}
	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
				direction = NORMAL_DIRECTION::RIGHT;

			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
				direction = NORMAL_DIRECTION::LEFT;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
				direction = NORMAL_DIRECTION::TOP;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
				direction = NORMAL_DIRECTION::BOTTOM;
			}
		}
		OnCollision(direction);
		// return the time of collision
		return entryTime;
	}
}

void CGameObject::OnCollision(NORMAL_DIRECTION normalDirection) {
	switch (normalDirection)
	{
	case NORMAL_DIRECTION::LEFT:
		this->vx *= -1;
		break;
	case NORMAL_DIRECTION::RIGHT:
		this->vx *= -1;
		break;
	case NORMAL_DIRECTION::TOP:
		this->vy *= -1;
		break;
	case NORMAL_DIRECTION::BOTTOM:
		this->vy *= -1;
		break;
	default:
		break;
	}
}
void CGameObject::Update(DWORD dt)
{
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}


CGameObject::~CGameObject()
{
	if (texture != NULL) texture->Release();
}
//
//void Score::SetTexPath(LPCWSTR tex)
//{
//	//this->tex = tex;
//	switch (score)
//	{
//	case 0:
//		tex = ZERO;
//		break;
//	case 1:
//		tex = ONE;
//		CGameObject::CGameObject(ONE); // dumb code
//		break;
//	case 2:
//		tex = TWO;
//		break;
//	case 3:
//		tex = THREE;
//		break;
//	case 4:
//		tex = FOUR;
//		break;
//	case 5:
//		tex = FIVE;
//		break;
//	case 6:
//		tex = SIX;
//		break;
//	case 7:
//		tex = SEVEN;
//		break;
//	case 8:
//		tex = EIGHT;
//		break;
//	case 9:
//		tex = NINE;
//		break;
//	default:
//		break;
//	}
//}
//
