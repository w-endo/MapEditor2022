#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <string>

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    ZeroMemory(table_, sizeof(table_));


}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    std::string fileName[] = {
        "BoxDefault.fbx" ,
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx" ,
        "BoxWater.fbx" };

    for (int i = 0; i < 5; i++)
    {
        std::string fn = "assets/" + fileName[i];
        hModel_[i] = Model::Load(fn);
        assert(hModel_[i] >= 0);
    }


    table_[3][4].type = 1;
    table_[13][8].type = 2;
    table_[5][0].type = 3;
    table_[7][7].type = 4;

    table_[7][7].height = 2;
    table_[1][1].height = 5;
}

//�X�V
void Stage::Update()
{
    //�r���[�|�[�g�s��
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;
    XMMATRIX vp = {
        w, 0, 0, 0,
        0,-h, 0, 0,
        0, 0, 1, 0,
        w, h, 0, 1
    };

    //�e�s��̋t�s��
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //XMMATRIX invPrj =
    //XMMATRIX invView =

    //�}�E�X�ʒu�i��O�j
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;

    //�}�E�X�ʒu�i���j
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //�@�@mousePosFront���x�N�g���ɕϊ�
    //�A�@�@��invVP�AinvPrj�AinvView��������

    //�B�@mousePosBack���x�N�g���ɕϊ�
    //�C�@�B��invVP�AinvPrj�AinvView��������

    //�D�@�A����C�Ɍ������ă��C�����i�Ƃ肠�������f���ԍ���hModel_[0]�j

    //�E�@���C������������u���[�N�|�C���g�Ŏ~�߂�

}

//�`��
void Stage::Draw()
{
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height+1; y++)
            {
                int type = table_[x][z].type;

                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[type], trans);
                Model::Draw(hModel_[type]);
            }
        }
    }
}

//�J��
void Stage::Release()
{
}