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

    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //���݈ʒu���x�N�g���ɂ��Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�ړ��x�N�g��
    XMFLOAT3 move = { 0, 0, 0.1f };                //��������XMFLOAT3�\���̂�p�ӂ�
    XMVECTOR vMove = XMLoadFloat3(&move);               //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotate);    //��Ԃ̌����ɍ��킹�ĉ�]


    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_S))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    
    //�J����
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotate);
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