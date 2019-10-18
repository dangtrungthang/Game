#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "KeyEventHandler.h"
#include <string>
#include "GameObject.h"
using namespace std;

#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80) 
typedef KeyEventHandler* LPKEYEVENTHANDLER;

struct Box
{
	float x, y;
	float width, height;
	float vx, vy;

};
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 
	LPDIRECTINPUTDEVICE8 didvMouse; // The mouse device

	
	DIMOUSESTATE mouse_state;
	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	

	LPKEYEVENTHANDLER keyHandler;
	

	D3DXVECTOR3 camPos; //vị trí camera

	// font 
	ID3DXFont * font;

public:
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);
	void DrawUIText(std::string _string, RECT bound);
	int IsKeyDown(int KeyCode);
	int IsKeyPress(int KeyCode);
	int IsKeyReleased(int KeyCode);
	int Mouse_X() { return mouse_state.lX; }
	int Mouse_Y() { return mouse_state.lY;  }
	int Mouse_Button(int button){ return BUTTON_DOWN(mouse_state, button); }
	void ProcessKeyboard();
	
	



	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y);

	static CGame* GetInstance();

	~CGame();
};