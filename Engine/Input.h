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
	bool IsKey(int keyCode);//�L�[��������Ă��邩���ׂ�
	void Release();
	bool IsKeyDown(int keyCode);//�L�[���������������ׂ�i�������ςȂ��͖����j
	bool IsKeyUp(int keyCode);//�L�[���������������ׂ�

	//�}�E�X
	bool IsMouseButton(int buttonCode);//�}�E�X�̃{�^����������Ă��邩���ׂ� //�����FbuttonCode ���ׂ����{�^���̔ԍ�
	bool IsMouseButtonDown(int buttonCode);//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsMouseButtonUp(int buttonCode);	//�}�E�X�̃{�^�����������������ׂ�
	XMFLOAT3 GetMousePosition();//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 GetMouseMove();//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	void SetMousePosition(int x, int y);

	//�R���g���[���[
	bool IsPadButton(int buttonCode, int padID = 0);//�R���g���[���[�̃{�^����������Ă��邩���ׂ�
	bool IsPadButtonDown(int buttonCode, int padID = 0);//�R���g���[���[�̃{�^�����������������ׂ�
	bool IsPadButtonUp(int buttonCode, int padID = 0);//�R���g���[���[�̃{�^�����������������ׂ�
	XMFLOAT3 GetPadStickL(int padID = 0);//���X�e�B�b�N�̌X�����擾
	XMFLOAT3 GetPadStickR(int padID = 0);//�E�X�e�B�b�N�̌X�����擾
	float	GetPadTrrigerL(int padID = 0);//���g���K�[�̉������݋���擾
	float	GetPadTrrigerR(int padID = 0);//�E�g���K�[�̉������݋���擾
};