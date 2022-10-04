#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[5];

    struct
    {
        int type;
        int height;
    } table_[15][15];

    int mode_;
    int select_;



public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};