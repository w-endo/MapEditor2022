#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
}

//�X�V
void Controller::Update()
{
    //����]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //�E��]
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

    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //���݈ʒu���x�N�g���ɂ��Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�ړ��x�N�g��
    XMFLOAT3 front = { 0, 0, 0.1f };                //��������XMFLOAT3�\���̂�p�ӂ�
    XMFLOAT3 right = { 0.1f, 0, 0 };
    XMVECTOR vMoveFront = XMLoadFloat3(&front);               //������x�N�g���ɂ���
    XMVECTOR vMoveRight = XMLoadFloat3(&right);               //������x�N�g���ɂ���
    vMoveFront = XMVector3TransformCoord(vMoveFront, mRotateY);    //��Ԃ̌����ɍ��킹�ĉ�]
    vMoveRight = XMVector3TransformCoord(vMoveRight, mRotateY);    //��Ԃ̌����ɍ��킹�ĉ�]

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
    
    //�J����
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));        //�J�����̏œ_�̓v���C���[�̈ʒu
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}