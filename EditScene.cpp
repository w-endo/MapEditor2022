#include "EditScene.h"
#include "Stage.h"
#include "Controller.h"

//�R���X�g���N�^
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene")
{
}

//������
void EditScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Controller>(this);
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