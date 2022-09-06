#include "Input.h"
#include "Transform.h"

namespace Input
{
	HWND hWnd_;
	LPDIRECTINPUT8   pDInput_ = nullptr;
	//キーボード
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];    //前フレームでの各キーの状態
	//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//デバイスオブジェクト
	DIMOUSESTATE mouseState_;				//マウスの状態
	DIMOUSESTATE prevMouseState_;			//前フレームのマウスの状態
	XMFLOAT3 mousePosition_;							//マウスカーソルの位置
	//コントローラー
	const int MAX_PAD_NUM = 4;    //4人までコントローラーが使える
	XINPUT_STATE controllerState_[MAX_PAD_NUM];
	XINPUT_STATE prevControllerState_[MAX_PAD_NUM];


	HRESULT Initialize(HWND hWnd)
	{
		//ウィンドウハンドル
		hWnd_ = hWnd;
		HRESULT hr;
		hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		if (FAILED(hr))
		{
			return hr;
			if (Input::IsKey(DIK_ESCAPE))
			{
				static int cnt = 0;
				cnt++;
				if (cnt >= 3)
				{
					PostQuitMessage(0);
				}
			}
		}
		hr = pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		if (FAILED(hr))
		{
			return hr;
			if (Input::IsKey(DIK_ESCAPE))
			{
				static int cnt = 0;
				cnt++;
				if (cnt >= 3)
				{
					PostQuitMessage(0);
				}
			}
		}
		//キーボード
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//マウス
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		//キーボード
		memcpy(prevKeyState, keyState, sizeof(keyState));
		pKeyDevice_->Acquire();
		pKeyDevice_->GetDeviceState(sizeof(keyState), &keyState);

		//マウス
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

		//コントローラー
		for (int i = 0; i < MAX_PAD_NUM; i++)
		{
			memcpy(&prevControllerState_[i], &controllerState_[i], sizeof(controllerState_[i]));
			XInputGetState(i, &controllerState_[i]);
		}

	}


	/////////キーボード情報//////////

	//キーが押されているか
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//押したか
	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode & 0x80]))
		{
			return true;
		}
		return false;
	}

	//離したか
	bool IsKeyUp(int keyCode)
	{
		//さっきは押してて、今は押してない
		if (prevKeyState[keyCode & 0x80] && !(IsKey(keyCode)))
		{
			return true;
		}
		return false;
	}

	/////マウス情報/////

//マウスのボタンが押されているか調べる
	bool IsMouseButton(int buttonCode)
	{
		//押してる
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//マウスのボタンを今押したか調べる（押しっぱなしは無効）
	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//マウスのボタンを今放したか調べる
	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//マウスカーソルの位置を取得
	XMFLOAT3 GetMousePosition()
	{
		return mousePosition_;
	}

	//マウスカーソルの位置をセット
	void SetMousePosition(int x, int y)
	{
		mousePosition_.x = x;
		mousePosition_.y = y;
	}


	//そのフレームでのマウスの移動量を取得
	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}


	///////////コントローラー情報///////////////

	//コントローラーのボタンが押されているか調べる
	bool IsPadButton(int buttonCode, int padID)
	{
		if (controllerState_[padID].Gamepad.wButtons & buttonCode)
		{
			return true; //押してる
		}
		return false; //押してない
	}

	//コントローラーのボタンを今押したか調べる（押しっぱなしは無効）
	bool IsPadButtonDown(int buttonCode, int padID)
	{
		//今は押してて、前回は押してない
		if (IsPadButton(buttonCode, padID) && !(prevControllerState_[padID].Gamepad.wButtons & buttonCode))
		{
			return true;
		}
		return false;
	}

	//コントローラーのボタンを今放したか調べる
	bool IsPadButtonUp(int buttonCode, int padID)
	{
		//今押してなくて、前回は押してる
		if (!IsPadButton(buttonCode, padID) && prevControllerState_[padID].Gamepad.wButtons & buttonCode)
		{
			return true;
		}
		return false;
	}


	float GetAnalogValue(int raw, int max, int deadZone)
	{
		float result = (float)raw;

		if (result > 0)
		{
			//デッドゾーン
			if (result < deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result - deadZone) / (max - deadZone);
			}
		}

		else
		{
			//デッドゾーン
			if (result > -deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result + deadZone) / (max - deadZone);
			}
		}

		return result;
	}


	//左スティックの傾きを取得
	XMFLOAT3 GetPadStickL(int padID)
	{
		float x = GetAnalogValue(controllerState_[padID].Gamepad.sThumbLX, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[padID].Gamepad.sThumbLY, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//右スティックの傾きを取得
	XMFLOAT3 GetPadStickR(int padID)
	{
		float x = GetAnalogValue(controllerState_[padID].Gamepad.sThumbRX, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[padID].Gamepad.sThumbRY, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//左トリガーの押し込み具合を取得
	float GetPadTrrigerL(int padID)
	{
		return GetAnalogValue(controllerState_[padID].Gamepad.bLeftTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//右トリガーの押し込み具合を取得
	float GetPadTrrigerR(int padID)
	{
		return GetAnalogValue(controllerState_[padID].Gamepad.bRightTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}


	void Release()
	{
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}
}