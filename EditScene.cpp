#include "EditScene.h"
#include "Stage.h"

//�R���X�g���N�^
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene")
{
}

//������
void EditScene::Initialize()
{
	Instantiate<Stage>(this);
}

//�X�V
void EditScene::Update()
{
}

//�`��
void EditScene::Draw()
{
}

//�J��
void EditScene::Release()
{
}