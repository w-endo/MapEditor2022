#pragma once

#include <dInput.h>
#include "XInput.h"
#include <DirectXMath.h>
#include "Direct3D.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib,"Xinput.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
#define SAFE_DELETE(p) if(p != nullptr) {delete p; p =nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}

using namespace DirectX;
namespace Input
{
	HRESULT Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);//キーが押されているか調べる
	void Release();
	bool IsKeyDown(int keyCode);//キーを今押したか調べる（押しっぱなしは無効）
	bool IsKeyUp(int keyCode);//キーを今離したか調べる

	//マウス
	bool IsMouseButton(int buttonCode);//マウスのボタンが押されているか調べる //引数：buttonCode 調べたいボタンの番号
	bool IsMouseButtonDown(int buttonCode);//マウスのボタンを今押したか調べる（押しっぱなしは無効）
	bool IsMouseButtonUp(int buttonCode);	//マウスのボタンを今離したか調べる
	XMFLOAT3 GetMousePosition();//マウスカーソルの位置を取得
	XMFLOAT3 GetMouseMove();//そのフレームでのマウスの移動量を取得
	void SetMousePosition(int x, int y);

	//コントローラー
	bool IsPadButton(int buttonCode, int padID = 0);//コントローラーのボタンが押されているか調べる
	bool IsPadButtonDown(int buttonCode, int padID = 0);//コントローラーのボタンを今押したか調べる
	bool IsPadButtonUp(int buttonCode, int padID = 0);//コントローラーのボタンを今放したか調べる
	XMFLOAT3 GetPadStickL(int padID = 0);//左スティックの傾きを取得
	XMFLOAT3 GetPadStickR(int padID = 0);//右スティックの傾きを取得
	float	GetPadTrrigerL(int padID = 0);//左トリガーの押し込み具合を取得
	float	GetPadTrrigerR(int padID = 0);//右トリガーの押し込み具合を取得
};