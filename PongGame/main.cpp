#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Ball.h"
#include "Paddle.h"
#include"Hub.h"
#include"define.h"
#include <cstdlib>

//#define SCREEN_WIDTH 400
//#define SCREEN_HEIGHT 600

#define MAX_FRAME_RATE 120
#define	BALL_SPEED 70.0f

CGame *game;
Ball* ball;
Paddle* paddleLeft;
Paddle* paddleRight;
Hub* hub;
//Score *point1;
//Score *point2;
int p1 = 0;
int p2 = 0;


class CSampleKeyHander :public KeyEventHandler {
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_ESCAPE:
		PostQuitMessage(0);
	case MOUSEEVENTF_XDOWN:
		PostQuitMessage(0);
	

	default:
		break;
	}
	
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	if (game->IsKeyDown(DIK_S))
		paddleLeft->SetState(MOVE_DOWN_KEYBOARD);
	else if (game->IsKeyDown(DIK_W))
		paddleLeft->SetState(MOVE_UP_KEYBOARD);
	else
	{
		paddleLeft->SetState(IDLE);	
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources. In this example, create a brick object and mario object
*/
void LoadResources()
{
	
	paddleLeft = new Paddle(TEXTURE_PATH);
	paddleLeft->SetPosition(100.0f, 350.0f);
	//paddleLeft->SetDxDy(1, 1);
	
	
	paddleRight = new Paddle(TEXTURE_PATH);
	D3DXIMAGE_INFO infoPaddleR = paddleRight->GetInfo();
	paddleRight->SetPosition(SCREEN_WIDTH- infoPaddleR.Width-100,SCREEN_HEIGHT/2 );


	ball = new Ball(TEXTURE_PATH_BALL);
	ball->SetPosition( SCREEN_WIDTH/2 , rand() % 350 +200);
	ball->SetVxVy(BALL_SPEED,-BALL_SPEED);
	
	hub = new Hub();
	//point1 = new Score(tex); // init default value
	/*point1->SetTexPath(tex);
	point1->SetPosition(10, 10);*/
}


/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/

void Update(DWORD dt)
{
	D3DXIMAGE_INFO ballInfo = ball->GetInfo();
	float normalx, normaly;
	float collisiontimeL, collisiontimeR;

	collisiontimeL = ball->SweptAABB(ball, paddleLeft, normalx, normaly);
	collisiontimeR = ball->SweptAABB(ball, paddleRight, normalx, normaly);
	
	/*if (paddleLeft->x < ball->x + ball->width &&
		paddleLeft->x + paddleLeft->width>ball->x &&
		paddleLeft->y<ball->y + ball->height &&
		paddleLeft->y + paddleLeft->height>ball->y) {
		ball->vx = -ball->vx;
	}
	if (paddleRight->x < ball->x + ball->width &&
		paddleRight->x + paddleRight->width>ball->x &&
		paddleRight->y<ball->y + ball->height &&
		paddleRight->y + paddleRight->height>ball->y) {
		ball->vx = -ball->vx;
	}
	if (ball->x < paddleLeft->x - 50.0f || ball->x > paddleRight->x+50.0f)
	{
		ball->SetPosition(SCREEN_WIDTH/2, rand() % 350 + 200);
		ball->SetVxVy((rand() % 4 ? 1 : -1), rand() % 4 ? 1 : -1);
	}
	if (ball->x < paddleLeft->x )
	{
		p2++;
		
		hub->AddScorePlayer2();
		ball->Reset();
		
	}
	else if (ball->x > paddleRight->x )
	{
		p1++;
		
		hub->AddScorePlayer1();
		ball->Reset();
		
	}*/
	
	paddleLeft->Update(dt);
	paddleRight->UpdateR(dt, game->Mouse_X(), game->Mouse_Y());
	
	ball->Update(dt);
	
	
	



	
	

	
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		
		paddleLeft->Render();
		paddleRight->Render();
		ball->Render();
		//point1->Render();
		hub->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	ShowCursor(FALSE);
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			NULL,
			//WS_OVERLAPPEDWINDOW, 
			 WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			0,
			0,
			SCREEN_WIDTH,
			SCREEN_HEIGHT, 
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
		game->InitKeyboard(keyHandler);
	
	LoadResources();
	Run();

	return 0;
}