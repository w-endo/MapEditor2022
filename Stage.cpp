#include "Stage.h"
#include "Engine/Model.h"
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


    table_[3][4] = 1;
    table_[13][8] = 2;
    table_[5][0] = 3;
    table_[7][7] = 4;
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            int type = table_[x][z];

            Transform trans;
            trans.position_.x = x;
            trans.position_.z = z;
            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }
}

//�J��
void Stage::Release()
{
}