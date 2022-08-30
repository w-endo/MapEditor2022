#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
}

//更新
void Controller::Update()
{
    //左回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //右回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }


    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x -= 1.0f;
    }


    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x += 1.0f;
    }

    //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //現在位置をベクトルにしておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //移動ベクトル
    XMFLOAT3 front = { 0, 0, 0.1f };                //奥向きのXMFLOAT3構造体を用意し
    XMFLOAT3 right = { 0.1f, 0, 0 };
    XMVECTOR vMoveFront = XMLoadFloat3(&front);               //それをベクトルにする
    XMVECTOR vMoveRight = XMLoadFloat3(&right);               //それをベクトルにする
    vMoveFront = XMVector3TransformCoord(vMoveFront, mRotateY);    //戦車の向きに合わせて回転
    vMoveRight = XMVector3TransformCoord(vMoveRight, mRotateY);    //戦車の向きに合わせて回転

    if (Input::IsKey(DIK_W))
    {
        vPos += vMoveFront;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_S))
    {
        vPos -= vMoveFront;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_D))
    {
        vPos += vMoveRight;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_A))
    {
        vPos -= vMoveRight;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    
    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));        //カメラの焦点はプレイヤーの位置
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}